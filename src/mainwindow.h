#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "card_button.h"
#include "check_button.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init();

public:
    constexpr uint16_t get_width() const
    {
        return 2 * MERGIN_LEN + (COL_CARD_NUM - 1) * GAP_LEN + COL_CARD_NUM * BT_SIZE;
    }
    constexpr uint16_t get_height() const
    {
        return MERGIN_LEN + (ROW_CARD_NUM - 1) * GAP_LEN + ROW_CARD_NUM * BT_SIZE + BOTTOM_HEIGHT;
    }

private slots:
    void select_card(U16 bt_id);
    void do_check();

private:
    Ui::MainWindow *ui;
private:
    const static uint16_t BT_SIZE = 150U;
    const static uint16_t MERGIN_LEN = 15U;
    const static uint16_t GAP_LEN = 10U;
    const static uint16_t BOTTOM_HEIGHT = 100U;
    const static uint16_t ROW_CARD_NUM = 4U;
    const static uint16_t COL_CARD_NUM = 5U;
    const static uint16_t CARD_NUM = ROW_CARD_NUM * COL_CARD_NUM;
    const static U16 CHECK_BT_WIDTH = 80U;
    const static U16 CHECK_BT_HEIGHT = 30U;
    const static U16 LB_WIDTH = 80U;
    const static U16 LB_HEIGHT = 30U;
    const static U16 UP_GAP_LEN = 30U;

private:
    CardButton card_arr_[CARD_NUM];
    CheckButton check_bt_;
    QLabel ans_lb_;
    bool bt_map_[CARD_NUM];
    U16 select_num_ = 0U;
};

#endif // MAINWINDOW_H
