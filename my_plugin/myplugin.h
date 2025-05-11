#ifndef MYPLUGIN_H
#define MYPLUGIN_H

#include <QObject>
#include <QMenu>
#include <QToolBar>
#include <QWidget>
#include <QAction>
#include <QLabel>

// 包含插件接口头文件
#include "../interfaces/myplugininterface.h"

// 插件类需要继承自 QObject 并实现插件接口
class MyPlugin : public QObject, public MyPluginInterface
{
    Q_OBJECT
    // 使用 Q_INTERFACES 宏声明实现的接口
    Q_INTERFACES(MyPluginInterface)

    // 使用 Q_PLUGIN_METADATA 宏提供插件元数据
    Q_PLUGIN_METADATA(IID "com.yourcompany.MyPluginInterface/1.0" FILE "myplugin.json") // IID 必须与接口中 Q_DECLARE_INTERFACE 的第二个参数一致

public:
    MyPlugin();
    ~MyPlugin() override; // 使用 override 关键字

    // 实现插件接口的方法
    void initialize(QMainWindow *mainWindow) override;
    QMenu *getPluginMenu() override;
    QToolBar *getPluginToolBar() override;
    QWidget *getPluginWidget() override;

private slots:
    void onPluginActionTriggered();
    void onPluginWidgetButtonClicked(); // 插件 Widget 中的按钮槽函数
    void onPluginWidgetButtonClicked2(); // 插件 Widget 中的按钮槽函数
private:
    QMainWindow *m_mainWindow; // 保存主窗口指针
    QMenu *m_pluginMenu;
    QToolBar *m_pluginToolBar;
    QWidget *m_pluginWidget;
    QAction *m_pluginAction;
};

#endif // MYPLUGIN_H
