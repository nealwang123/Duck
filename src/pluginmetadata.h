#pragma once
#include <QObject>
#include <QVariant>
#include <QMap>
#include <QString>


/**
 * 插件通信消息封装体
 **/
struct PluginMetaData
{
    QString src;                //消息源插件
    QString dest;               //消息目标插件
    int type;                   //消息类型
    QMap<QString,QVariant> map; //消息映射（参数名称，参数类型）
    QObject *object = nullptr;  //消息源
};
Q_DECLARE_METATYPE(PluginMetaData);
