#include "src/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon/set.ico"));
    MainWindow w;
    w.setWindowTitle("SetGame");
    w.init();
    w.show();
    return a.exec();
}
