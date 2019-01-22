#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QEvent>
#include <MyButton.hpp>
#include <QTimer>
#include <MyButton.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QTimer *timer;
    MyButton *button;

    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_HPP
