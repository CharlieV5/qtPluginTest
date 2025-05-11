#ifndef HOSTWINDOW_H
#define HOSTWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QToolBar>
#include <QDockWidget>

// 前向声明插件接口
class MyPluginInterface;

class HostWindow : public QMainWindow
{
    Q_OBJECT

public:
    HostWindow(QWidget *parent = nullptr);
    ~HostWindow();

private:
    void loadPlugins(); // 加载插件的方法

private:
    QMenu *fileMenu;
    QToolBar *mainToolBar;
};

#endif // HOSTWINDOW_H
