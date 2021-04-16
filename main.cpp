#include "mainwindow.h"

#include <QApplication>
#include <wup/wup.hpp>

using namespace wup;

WUP_STATICS;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Params params(argc, argv);
    MainWindow w(params);
    w.show();
    return a.exec();
}
