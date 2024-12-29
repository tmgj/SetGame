#include "card_button.h"

void CardButton::set_back_image(U16 idx, U16 size)
{
    image_idx_ = idx;
    QString image = QString(":/cards/%1.PNG").arg(idx);
    QPixmap pixmap(image);
    setIcon(QIcon(pixmap));
    setIconSize(QSize(size - 6, size - 6));
}

void CardButton::on_click()
{
    emit send_id(id_);
}
