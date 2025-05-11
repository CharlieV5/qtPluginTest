#include "myplugin.h"
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

MyPlugin::MyPlugin()
    : m_mainWindow(nullptr), m_pluginMenu(nullptr), m_pluginToolBar(nullptr), m_pluginWidget(nullptr), m_pluginAction(nullptr)
{
    qDebug() << "MyPlugin constructor";
}

MyPlugin::~MyPlugin()
{
    qDebug() << "MyPlugin destructor";
    // 注意：这里不需要手动删除 m_pluginMenu, m_pluginToolBar, m_pluginWidget 和 m_pluginAction
    // 因为它们被添加到主窗口的菜单栏、工具栏或 DockWidget 中，Qt 的父子对象机制会负责它们的销毁。
}

void MyPlugin::initialize(QMainWindow *mainWindow)
{
    m_mainWindow = mainWindow;
    qDebug() << "MyPlugin initialized with main window.";
}

QMenu *MyPlugin::getPluginMenu()
{
    if (!m_pluginMenu)
    {
        m_pluginMenu = new QMenu("&Plugin", m_mainWindow);                    // 以主窗口为父对象
        m_pluginAction = new QAction("&Trigger Plugin Action", m_pluginMenu); // 以菜单为父对象
        m_pluginMenu->addAction(m_pluginAction);

        // 连接信号到插件内部的槽
        connect(m_pluginAction, &QAction::triggered, this, &MyPlugin::onPluginActionTriggered);
    }
    return m_pluginMenu;
}

QToolBar *MyPlugin::getPluginToolBar()
{
    if (!m_pluginToolBar)
    {
        m_pluginToolBar = new QToolBar("Plugin Toolbar", m_mainWindow); // 以主窗口为父对象
        // 可以将同一个 Action 添加到工具栏
        if (m_pluginAction)
        {
            m_pluginToolBar->addAction(m_pluginAction);
        }
        else
        {
            // 或者创建一个新的 Action
            QAction *toolbarAction = new QAction("Toolbar Action", m_pluginToolBar);
            m_pluginToolBar->addAction(toolbarAction);
            connect(toolbarAction, &QAction::triggered, this, &MyPlugin::onPluginActionTriggered);
        }
    }
    return m_pluginToolBar;
}

QWidget *MyPlugin::getPluginWidget()
{
    if (!m_pluginWidget)
    {
        m_pluginWidget = new QWidget(m_mainWindow);       // 以主窗口为父对象
        m_pluginWidget->setWindowTitle("Plugin Content"); // 设置窗口标题，用于 DockWidget
        QVBoxLayout *layout = new QVBoxLayout(m_pluginWidget);
        QLabel *label = new QLabel("Content from Plugin", m_pluginWidget);
        QPushButton *button1 = new QPushButton("Click Me1", m_pluginWidget);
        QPushButton *button2 = new QPushButton("Click Me2", m_pluginWidget);

        layout->addWidget(label);
        layout->addWidget(button1);
        layout->addWidget(button2);       
        m_pluginWidget->setLayout(layout);

        connect(button1, &QPushButton::clicked, this, &MyPlugin::onPluginWidgetButtonClicked);
        connect(button2, &QPushButton::clicked, this, &MyPlugin::onPluginWidgetButtonClicked2);    
    }
    return m_pluginWidget;
}

void MyPlugin::onPluginActionTriggered()
{
    qDebug() << "Plugin action triggered!";
    QMessageBox::information(m_mainWindow, "Plugin Action", "Hello from the plugin menu/toolbar!");
}

void MyPlugin::onPluginWidgetButtonClicked()
{
    qDebug() << "Plugin widget button1 clicked!";
    QMessageBox::information(m_mainWindow, "Plugin Widget", "Button1 clicked inside plugin widget!");
}

void MyPlugin::onPluginWidgetButtonClicked2()
{
    qDebug() << "Plugin widget button2 clicked!";
    QMessageBox::information(m_mainWindow, "Plugin Widget", "Button2 clicked inside plugin widget!");
}
