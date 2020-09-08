#------------------------------------------------- 
# 
# Project created by NewProject 
# 
#------------------------------------------------- 


QT       += widgets 

TEMPLATE = lib
CONFIG += plugin                // 声明为plugin，带static表面为静态，否则为动态。
MOC_DIR     = temp/moc
RCC_DIR     = temp/rcc
UI_DIR      = temp/ui
OBJECTS_DIR = temp/obj
DESTDIR     = $$PWD/../../bin/plugins

#手动指定文件名称,debug版本自动在后面加上字母d
#CONFIG(debug, debug|release) {
#TARGET = helloworldPlugind
#}
#CONFIG(release, debug|release) {
TARGET = helloworldPlugin
#}

DEFINES += HELLOWORLD_LIBRARY 

SOURCES += helloworld.cpp\
    helloworldwidget.cpp


HEADERS += helloworld.h\
    helloworld_global.h \
    helloworldwidget.h

FORMS += \
    helloworldwidget.ui

OTHER_FILES += helloworld.json
