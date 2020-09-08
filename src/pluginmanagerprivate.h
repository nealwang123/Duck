#ifndef PLUGINMANAGERPRIVATE_H
#define PLUGINMANAGERPRIVATE_H

#include <QVariant>
#include <QPluginLoader>
#include <QString>
#include <QDebug>
#include "plugininterface.h"
class PluginManagerPrivate
{
public:
    //插件依赖检测
    bool check(const QString &filepath);
    QHash<QString, QVariant> m_names; //插件路径--插件名称
    QHash<QString, QVariant> m_versions; //插件路径--插件版本
    QHash<QString, QVariantList>m_dependencies; //插件路径--插件额外依赖的其他插件
    QHash<QString, QPluginLoader *>m_loaders; //插件路径--QPluginLoader实例
    QHash<QString,PluginInterface *>m_interfaces;
};
#endif // PLUGINMANAGERPRIVATE_H
