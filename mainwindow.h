#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <wup/wup.hpp>

using namespace wup;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Params &params, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
