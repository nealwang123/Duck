#include <QDir>
#include <QDebug>
#include <QPluginLoader>
#include "pluginmanager.h"
PluginManager::PluginManager(QObject *parent):
    QObject(parent)
{
    d=new PluginManagerPrivate;
}
PluginManager::~PluginManager()
{
    //delete m_instance;
    //m_instance=NULL;
}



QDir PluginManager::getPluginPath()
{
    QDir path =  QDir::currentPath();
    path.cd("plugins");
    qDebug()<<"path:"<<path;
    return path;
}
void PluginManager::loadAllPlugins()
{
    QDir path=getPluginPath();//进入插件目录
    foreach (QString pluginName, path.entryList(QDir::Files /*| QDir::NoDotAndDotDot*/))
    {
        // 扫描所有插件，录入元数据信息
        scan(path.absoluteFilePath(pluginName),pluginName);
//        qDebug()<<"pluginName:"<<pluginName;
    }

    foreach (QString pluginName, path.entryList(QDir::Files /*| QDir::NoDotAndDotDot*/))
    {
        // 加载插件
        loadPlugin(path.absoluteFilePath(pluginName),pluginName);
    }
}
void PluginManager::scan(const QString &path,const QString &name)
{
    /**
     *  判断是否是库，排除pdb等垃圾文件
     * Windows：.dll、.DLL
     * Unix/Linux：.so
     **/

    if (!QLibrary::isLibrary(path))
        return;
    //qDebug()<<"path"<<path;
    // 获取元数据（名称、版本、依赖）
    QPluginLoader *loader = new QPluginLoader(path);
    QJsonObject json = loader->metaData().value("MetaData").toObject();

    d->m_names.insert(path, json.value("name").toVariant());
    d->m_versions.insert(path, json.value("version").toVariant());
    d->m_dependencies.insert(path, json.value("dependencies").toArray().toVariantList());
    qDebug()<<""<<json.value("name")<<json.value("version")<<json.value("dependencies");
    delete loader;
    loader = Q_NULLPTR;
}
void PluginManager::loadPlugin(const QString &path,const QString &name)
{
    // 判断是否是库
    if (!QLibrary::isLibrary(path))
        return;

    // 检测插件依赖(递归调用)
    if (!d->check(path))
        return;

    // 加载插件
    QPluginLoader *loader = new QPluginLoader(path);
    if (loader->load())
    {
        qDebug()<<"loader->load()";
        // 如果继承自 Plugin，则认为是自己的插件（防止外部插件注入）。
        PluginInterface *plugin = qobject_cast<PluginInterface *>(loader->instance());
        if (plugin)
        {
            QStringList arr=name.split(".");
            QString libName=arr.at(0);
            d->m_loaders.insert(libName, loader);
            d->m_interfaces.insert(libName, plugin);
        }
        else
        {
            delete loader;
            loader = Q_NULLPTR;
        }
    }

}
void PluginManager::unloadAllPlugins()
{
    for(QString filepath:d->m_loaders.keys())
    {
        unloadPlugin(filepath);
    }
}
void PluginManager::unloadPlugin(const QString &filepath)
{
    QPluginLoader *loader=d->m_loaders.value(filepath);
    if(loader->unload())
    {
        d->m_loaders.remove(filepath);
        delete loader;
        loader=nullptr;
    }
}
QList<QPluginLoader *> PluginManager::allPlugins()
{
    return d->m_loaders.values();
}

QList<PluginInterface *> PluginManager::allDuck_Interfaces()
{
    return d->m_interfaces.values();
}
QPluginLoader* PluginManager::getPlugin(const QString &name)
{
    if(d->m_loaders.contains(name))
    {
        QPluginLoader *loader = (QPluginLoader *)(d->m_loaders.value(name));
        return  loader;
    }
    else
    {
        return nullptr;
    }
}


void PluginManager::initSignalAndSlot()
{
    auto plugins=allPlugins();
    foreach (auto loader, plugins)
    {
        // 每个插件发送消息到manager，然后由manager 根据 dest 字段转发
        //connect(loader->instance(),SIGNAL(sendMsg2Manager(PluginMetaData)),this,SLOT(recvMsgfromPlugin(PluginMetaData)));
    }
}
void PluginManager::recvMsgfromPlugin(PluginMetaData metadata)
{
    auto loader=getPlugin(metadata.dest);

    if(loader)
    {
        auto interface=qobject_cast<PluginInterface *>(loader->instance());
        if(interface)
        {
            //interface->recMsgfromManager(metadata);
        }
    }
}
