#ifndef MYPLUGININTERFACE_H
#define MYPLUGININTERFACE_H

#include <QtPlugin> // 包含 Qt 插件相关的头文件
#include <QMenu>
#include <QToolBar>
#include <QWidget>
#include <QMainWindow> // 需要主窗口类型以便插件操作

// 定义一个纯虚类作为插件接口
class MyPluginInterface
{
public:
    virtual ~MyPluginInterface() {}

    // 插件启动时调用，传递主窗口指针
    virtual void initialize(QMainWindow *mainWindow) = 0;

    // 获取插件要添加的菜单 (可以返回 nullptr 如果不需要)
    virtual QMenu *getPluginMenu() = 0;

    // 获取插件要添加的工具栏 (可以返回 nullptr 如果不需要)
    virtual QToolBar *getPluginToolBar() = 0;

    // 获取插件要添加的窗口/Widget (例如 QDockWidget 的内容)
    // 返回的 QWidget 将被主程序添加到 QDockWidget 中
    virtual QWidget *getPluginWidget() = 0;

    // 可以在这里添加其他插件需要提供的功能接口
};

// 使用 Q_DECLARE_INTERFACE 宏声明接口，供 Qt 插件系统识别
Q_DECLARE_INTERFACE(MyPluginInterface, "com.yourcompany.MyPluginInterface/1.0") // 第二个参数是接口的唯一标识符和版本

#endif // MYPLUGININTERFACE_H
