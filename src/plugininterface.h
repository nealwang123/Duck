/*
C++ 没有类似 Java 或者 C# 的专门的 interface，
因此，我们使用的是 class 来模拟接口。这样做的要求是，接口应当有一个 virtual 的析构函数，
以便实现了接口的子类在析构的时候能够自动调用父类的析构函数，从而避免内存泄露。
第二，接口中所有的函数都应当是纯虚函数，也就是 virtual 的并且要有 = 0。这是 C++ 的要求，与 Qt 无关。
最后，注意，文件末尾处有一个Q_DECLARE_INTERFACE宏，用于告诉 Qt 的元数据系统 metadata system，这是一个接口。
这个宏有两个参数:
参数一:是接口类的名字，这里就是 PluginInterFace
参数二:是接口的标识符，是一个唯一的字符串，为保证唯一性，通常采取域名倒写的形式，最后用 / 分隔开版本号
（关于域名倒写，可以参考 Java package 的命名规范，简而言之，就是把你的域名倒过来书写）。
这样，我们就完成了接口的编写。

我们的接口很简单，出去虚析构函数，只有一个函数是子类必须实现的：QString name() const。顾名思义，也就是返回这个插件的名字。
当然，在真正使用的系统中，这个接口可能相当复杂，并且像 name 或者 version 这种属性，一般不大会放在代码中，而是在配置文件中（特别是版本号这种经常会修改的常量）。
现在，你可以编译一下这个工程。显然，你不会得到任何有意义的东西———仅仅是能够测试你的配置是否正确，代码是否能通过编译。
编译之后，如果使用了影子构建，你应该在于 Duck 文件夹平级处得到一个 build 文件夹，里面就是我们编译出的 Duck.exe （Windows）。
*/
#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#define BrushInterface_iid "org.XEQD.PlugAndPaint.BrushInterface"

#include <QObject>
#include <QString>
#include <QToolButton>
#include "pluginmetadata.h"
enum DUCK_WIDGETTYPE{
    MDIAREA,
    DOCKWIDGET
};


class PluginInterface
{

public:
    virtual ~PluginInterface() {}
    virtual QString name() const=0;
    virtual QString iconPath() const=0;
    virtual QWidget *widget() const=0;//QWidget *parent
    virtual DUCK_WIDGETTYPE duck_Widget() const=0;
    virtual Qt::DockWidgetArea duck_DockWidgetArea() const=0;

//    virtual void recMsgfromManager(PluginMetaData) = 0;
//    virtual void sendMsg2Manager(PluginMetaData)   = 0;
};

    QT_BEGIN_NAMESPACE
        Q_DECLARE_INTERFACE(PluginInterface, BrushInterface_iid)
    QT_END_NAMESPACE

#endif
