#ifndef MYBUTTON_HPP
#define MYBUTTON_HPP
#include <QPushButton>
#include <QEvent>


class MyButton : public QPushButton
{
    Q_OBJECT

public:
    MyButton(QWidget *parent);
protected:
    virtual void enterEvent( QEvent* e );

public slots:
    void moveButton();
signals:
    void hovered();

private:
    QPushButton _button;
};

#endif // MYBUTTON_HPP
