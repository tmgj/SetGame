#ifndef CHECKBUTTON_H
#define CHECKBUTTON_H

#include <QPushButton>

class CheckButton : public QPushButton
{
    Q_OBJECT
public:
    CheckButton(QWidget *parent = nullptr)
        : QPushButton(parent)
    {
        connect(this, &QPushButton::clicked, this, &CheckButton::on_click);
    }

signals:
    void send_sig();
public slots:
    void on_click();
};

#endif // CHECKBUTTON_H
