#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QGridLayout>
#include <QMouseEvent>
#include <QEvent>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    button = new MyButton(this);

    button->setText("Catch me!");
    button->setFixedSize(100, 50);

    connect(button, &MyButton::hovered, button, &MyButton::moveButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}
