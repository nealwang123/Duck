#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pluginmanager.h"
#include "plugininterface.h"
#include <QMessageBox>
#include <QMdiSubWindow>
#include <QDockWidget>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    iniForm();
    loadPlugin();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniForm()
{
    setMinimumSize(QSize(1024,768));
    QObject::connect(ui->mainToolBar, SIGNAL(actionTriggered(QAction*)), SLOT(actionTriggeredSlots(QAction* )));
}

void MainWindow::loadPlugin()
{
    PluginManager::getInstance()->loadAllPlugins();
    PluginManager::getInstance()->initSignalAndSlot();
    QList<PluginInterface*> m_interfaces=PluginManager::getInstance()->allDuck_Interfaces();
    int nCount=m_interfaces.count();
    qDebug()<<"nCount===="<<nCount;
    for(int i=0;i<nCount;i++)
    {
        PluginInterface *plugin=m_interfaces.at(i);
        QWidget *widget1=plugin->widget();
        widget1->setWindowTitle(plugin->name());
        _MapWidget[plugin->name()]=widget1;
        _MapDockWidgetArea[plugin->name()] = plugin->duck_DockWidgetArea();

        if(plugin->duck_Widget() == DUCK_WIDGETTYPE::MDIAREA )
        {
            ui->mainToolBar->addAction(QIcon(plugin->iconPath()),plugin->name());
            ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        }
        if(plugin->duck_Widget() == DUCK_WIDGETTYPE::DOCKWIDGET)//停靠窗口
        {
            QDockWidget* dockWidget=Duck_Widget(widget1);
            addDockWidget(plugin->duck_DockWidgetArea(),dockWidget);
            ui->menuView->addAction(dockWidget->toggleViewAction());
        }

//        QWidget *widget2=plugin->widget();
//        widget2->setWindowTitle("控制器1");
//        _MapWidget["控制器1"]=widget2;
//        _MapDockWidgetArea["控制器1"] = plugin->duck_DockWidgetArea();
//        if(plugin->duck_Widget() == DUCK_WIDGETTYPE::MDIAREA )
//        {
//            ui->mainToolBar->addAction(QIcon(plugin->iconPath()),"控制器1");
//            ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

//        }
//        else if(plugin->duck_Widget() == DUCK_WIDGETTYPE::DOCKWIDGET)
//        {
//            QDockWidget* dockWidget=Duck_Widget(widget1);
//            addDockWidget(plugin->duck_DockWidgetArea(),dockWidget);
//            ui->menuView->addAction(dockWidget->toggleViewAction());
//        }

    }

     ui->mainToolBar->toolButtonStyleChanged(Qt::ToolButtonTextOnly);

}

void MainWindow::loadPluginWidget()
{
    PluginManager::getInstance()->loadAllPlugins();
    PluginManager::getInstance()->initSignalAndSlot();
    QList<PluginInterface*> m_interfaces=PluginManager::getInstance()->allDuck_Interfaces();
    int nCount=m_interfaces.count();
    for(int i=0;i<nCount;i++)
    {
        PluginInterface *plugin=m_interfaces.at(i);
        QWidget *widget1=plugin->widget();
        widget1->setWindowTitle(plugin->name());
        _MapWidget[plugin->name()]=widget1;
        _MapDockWidgetArea[plugin->name()] = plugin->duck_DockWidgetArea();
    }

}

QDockWidget *MainWindow::Duck_Widget(QWidget *widget)
{
    QDockWidget *dock = new QDockWidget(widget->windowTitle());
    dock->setFeatures(QDockWidget::DockWidgetMovable);
    dock->setAllowedAreas(Qt::AllDockWidgetAreas);
    dock->setWidget(widget);
    return dock;
}

void MainWindow::actionTriggeredSlots(QAction *action)
{
    if(ui->mdiArea->subWindowList().count() != 0){
        for(int i =0 ; i < ui->mdiArea->subWindowList().count(); i++){
            if(ui->mdiArea->subWindowList().at(i)->windowTitle() == action->text()){
                return;
            }
        }
    }
    ui->mdiArea->addSubWindow(_MapWidget[action->text()],Qt::SubWindow);
    _MapWidget[action->text()]->setWindowIcon(action->icon());
    _MapWidget[action->text()]->setWindowTitle(action->text());
    _MapWidget[action->text()]->show();

    loadPluginWidget();
}
