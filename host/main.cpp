#include <QApplication>
#include "hostwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HostWindow mainWindow;
    mainWindow.show();

    return a.exec();
}
