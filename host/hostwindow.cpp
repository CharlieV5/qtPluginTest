#include "hostwindow.h"
#include <QLabel>
#include <QDir>
#include <QPluginLoader>
#include <QCoreApplication>
#include <QDebug>
#include <QMenuBar>

// 包含插件接口头文件
#include "../interfaces/myplugininterface.h"

HostWindow::HostWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Qt Plugin Host Application");
    setGeometry(100, 100, 800, 600);

    // 创建菜单栏和工具栏 (如果 QMainWindow 没有默认的)
    // QMainWindow 通常自带菜单栏和工具栏区域，但手动创建并获取指针更灵活
    QMenuBar *menuBar = this->menuBar();
    if (!menuBar)
    {
        menuBar = new QMenuBar(this);
        setMenuBar(menuBar);
    }
    fileMenu = menuBar->addMenu("&File");

    QToolBar *toolBar = addToolBar("Main Toolbar");
    mainToolBar = toolBar; // 保存指针

    // 添加一个中心控件
    QLabel *centralLabel = new QLabel("Qt Plugin Host Window", this);
    centralLabel->setAlignment(Qt::AlignCenter);
    setCentralWidget(centralLabel);

    // 加载插件
    loadPlugins();
}

HostWindow::~HostWindow()
{
}

void HostWindow::loadPlugins()
{
    // 假设插件放在可执行文件同级的 "plugins" 目录下
    QDir pluginsDir(QCoreApplication::applicationDirPath() + "/plugins");
    qDebug() << "Loading plugins from:" << pluginsDir.absolutePath();

    // 遍历目录下的所有文件
    QStringList nameFilters;
    // 根据平台设置共享库文件过滤器
#if defined(Q_OS_WIN)
    nameFilters << "*.dll";
#elif defined(Q_OS_LINUX)
    nameFilters << "*.so";
#elif defined(Q_OS_MAC)
    nameFilters << "*.dylib";
#endif

    QFileInfoList pluginFiles = pluginsDir.entryInfoList(nameFilters, QDir::Files | QDir::NoDotAndDotDot);

    for (const QFileInfo &fileInfo : pluginFiles)
    {
        QPluginLoader pluginLoader(fileInfo.absoluteFilePath());
        qDebug() << "Attempting to load:" << fileInfo.fileName();

        QObject *plugin = pluginLoader.instance();

        if (plugin)
        {
            // 尝试将加载的 QObject 转换为我们的插件接口
            MyPluginInterface *pluginInterface = qobject_cast<MyPluginInterface *>(plugin);
            if (pluginInterface)
            {
                qDebug() << "Loaded plugin:" << fileInfo.fileName();

                // 初始化插件，传递主窗口指针
                pluginInterface->initialize(this);

                // 获取并添加插件的菜单
                QMenu *pluginMenu = pluginInterface->getPluginMenu();
                if (pluginMenu)
                {
                    // 将插件菜单添加到主窗口的菜单栏
                    menuBar()->addMenu(pluginMenu);
                    qDebug() << "Added plugin menu.";
                }

                // 获取并添加插件的工具栏
                QToolBar *pluginToolBar = pluginInterface->getPluginToolBar();
                if (pluginToolBar)
                {
                    // 将插件工具栏添加到主窗口
                    addToolBar(pluginToolBar);
                    qDebug() << "Added plugin toolbar.";
                }

                // 获取并添加插件的 Widget 到 DockWidget
                QWidget *pluginWidget = pluginInterface->getPluginWidget();
                if (pluginWidget)
                {
                    QDockWidget *dockWidget = new QDockWidget(pluginWidget->windowTitle().isEmpty() ? "Plugin Dock" : pluginWidget->windowTitle(), this);
                    dockWidget->setWidget(pluginWidget);
                    addDockWidget(Qt::RightDockWidgetArea, dockWidget); // 添加到右侧停靠区域
                    qDebug() << "Added plugin dock widget.";
                }
            }
            else
            {
                qWarning() << "Could not cast plugin to MyPluginInterface:" << fileInfo.fileName();
                // 如果无法转换为接口，可能不是我们期望的插件，或者接口定义不匹配
                // 卸载插件
                pluginLoader.unload();
            }
        }
        else
        {
            qWarning() << "Failed to load plugin:" << fileInfo.fileName() << "Error:" << pluginLoader.errorString();
        }
    }
}
