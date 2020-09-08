#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H
//#include "plugin_global.h"
#include <QObject>
#include <QMap>
#include<QDir>
#include <QJsonArray>
#include <QDebug>
#include "plugininterface.h"
#include "pluginmanagerprivate.h"

class  PluginManager : public QObject
{
    Q_OBJECT
private:
    PluginManager(QObject *parent = 0);
public:
    ~PluginManager();
    static PluginManager *getInstance()
    {
        static PluginManager *m_instance;
        if(m_instance==NULL)
            m_instance=new PluginManager();
        return m_instance;
    }

    QDir getPluginPath();// 获取插件目录
    void loadAllPlugins();//加载所有插件
    void scan(const QString &filepath,const QString &name=""); //扫描JSON文件中的插件元数据
    void loadPlugin(const QString &filepath,const QString &name=""); //加载其中某个插件
    void unloadAllPlugins();//卸载所有插件
    void unloadPlugin(const QString &filepath);//卸载某个插件
    QList<QPluginLoader *> allPlugins();//获取所有插件
    QList<PluginInterface *> allDuck_Interfaces();
    QPluginLoader* getPlugin(const QString &name);//获取某个插件

    void initSignalAndSlot();//初始化和插件通信的信号槽
public slots:
    //接受来自各插件的消息
    void recvMsgfromPlugin(PluginMetaData);
private:
    PluginManagerPrivate *d;

signals:


};

#endif // PLUGINMANAGER_H
