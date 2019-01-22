#include "MyButton.hpp"

MyButton::MyButton(QWidget *parent)
{
    setMouseTracking(true);
    setParent(parent);
}

void MyButton::enterEvent(QEvent *e)
{
    QWidget::enterEvent(e);
    emit hovered();
}

void MyButton::moveButton()
{
    srand(time(NULL));
    int y = rand() % 500 + 1;
    int x = rand() % 500 + 1;

    this->move(x, y);
}
