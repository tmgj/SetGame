#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H

#include <QPushButton>
#include "define.h"

class CardButton : public QPushButton
{
    Q_OBJECT
public:
    CardButton(QWidget *parent = nullptr)
        : QPushButton(parent), id_(0U), image_idx_(0U)
    {
        connect(this, &QPushButton::clicked, this, &CardButton::on_click);
    }
    inline void set_id(U16 v) {id_ = v; }
    inline void set_image_idx(U16 v) { image_idx_ = v; }
    inline U16 get_image_idx() const { return image_idx_; }
    void set_back_image(U16 idx, U16 size);
signals:
    void send_id(U16 id);
public slots:
    void on_click();
private:
    U16 id_;
    U16 image_idx_;
};

#endif // CARD_BUTTON_H
