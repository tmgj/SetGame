#include "mainwindow.h"
#include "src/ui_mainwindow.h"
#include "card_button_mgr.h"
#include <string.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    this->setFixedSize(get_width(), get_height());

    memset(bt_map_, 0, sizeof(bt_map_));
    U16 idx = 0;
    CardButtonMgr &mgr = CardButtonMgr::get_instance();

    for(U16 r = 0; r < ROW_CARD_NUM; ++r)
    {
        for (U16 c = 0; c < COL_CARD_NUM; ++c)
        {
            CardButton &card_bt = card_arr_[idx];
            connect(&card_bt, SIGNAL(send_id(U16)), this, SLOT(select_card(U16)));
            card_bt.set_id(idx);
            card_bt.setParent(this);
            card_bt.resize(BT_SIZE, BT_SIZE);
            card_bt.move(MERGIN_LEN + c * (BT_SIZE + GAP_LEN),
                         MERGIN_LEN + r * (BT_SIZE + GAP_LEN));
            U16 image_idx = mgr.pick_one_card();
            card_bt.set_back_image(image_idx, BT_SIZE);
            ++idx;
        }
    }

    connect(&check_bt_, SIGNAL(send_sig()), this, SLOT(do_check()));
    check_bt_.setParent(this);
    check_bt_.resize(CHECK_BT_WIDTH, CHECK_BT_HEIGHT);
    check_bt_.move((get_width() - CHECK_BT_WIDTH) / 2,
                   get_height() - BOTTOM_HEIGHT + UP_GAP_LEN);
    check_bt_.setEnabled(false);
    check_bt_.setText("Check");

    QLabel *text_lb = new QLabel(this);
    text_lb->resize(LB_WIDTH, LB_HEIGHT);
    text_lb->move(MERGIN_LEN+30, get_height() - BOTTOM_HEIGHT + UP_GAP_LEN);
    text_lb->setText("Latest Result: ");

    ans_lb_.setParent(this);
    ans_lb_.resize(LB_WIDTH, LB_HEIGHT);
    ans_lb_.move(MERGIN_LEN + 110, get_height() - BOTTOM_HEIGHT + UP_GAP_LEN);
}

void MainWindow::select_card(U16 bt_id)
{
    if (bt_id >= CARD_NUM)
    {
        return;
    }
    CardButton &bt = card_arr_[bt_id];
    if (bt_map_[bt_id])
    {
        if (select_num_ > 0)
        {
            bt_map_[bt_id] = false;
            --select_num_;
            bt.setStyleSheet("border: 0px");
        }
    }
    else
    {
        if (select_num_ >= 0 && select_num_ < 3)
        {
            bt_map_[bt_id] = true;
            ++select_num_;
            bt.setStyleSheet("border: 3px solid rgba(0, 0, 255, 128)");
        }
    }
    if (3 == select_num_)
    {
        check_bt_.setEnabled(true);
    }
    else
    {
        check_bt_.setEnabled(false);
    }
}

void MainWindow::do_check()
{
    if (3 != select_num_)
    {
        return;
    }

    U16 select_cards_[3];
    U16 idx = 0;
    for(U16 i = 0; i < CARD_NUM; ++i)
    {
        if (bt_map_[i])
        {
            select_cards_[idx++] = i;
            if (3 == idx)
            {
                break;
            }
        }
    }
    if (3 != idx)
    {
        return;
    }

    U16 idx_1 = card_arr_[select_cards_[0]].get_image_idx();
    U16 idx_2 = card_arr_[select_cards_[1]].get_image_idx();
    U16 idx_3 = card_arr_[select_cards_[2]].get_image_idx();

    bool ans = CardButtonMgr::get_instance().check_ans(idx_1, idx_2, idx_3);
    if (ans)
    {
        ans_lb_.setText("Succ!");
        ans_lb_.setStyleSheet("color: green;");
        CardButtonMgr &mgr = CardButtonMgr::get_instance();
        for(U16 i = 0; i < 3; ++i)
        {
            CardButton &bt = card_arr_[select_cards_[i]];
            bt_map_[select_cards_[i]] = false;
            bt.set_back_image(mgr.pick_one_card(), BT_SIZE);
            bt.setStyleSheet("border: 0px");
        }
        select_num_ = 0;
    }
    else
    {
        ans_lb_.setText("Fail!");
        ans_lb_.setStyleSheet("color: red;");
    }
}
