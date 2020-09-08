# -------------------------------------------------
# Duck 基于Qt的插件式开发框架，他是一个简易的插件框架，所有业务由插件处理，与主框架无关，也可以把他称为程序的集合。
# 感谢 gitee开源作者小而强大，本工程在作者基础之上丰富完善；并添加详细注释方便分析学习；
# 修改1：为了方便工程管理，在原来基础上添加子工程管理形式；
# -------------------------------------------------
TEMPLATE = subdirs

CONFIG += ordered
#有些编译器或者Qt版本不支持下面这行,需要注释掉
PRECOMPILED_HEADER = head.h
#CONFIG      += warn_off
#HEADERS     += head.h

SUBDIRS += \
     $$PWD/plugin/plugin.pro \
     $$PWD/src/Duck.pro

