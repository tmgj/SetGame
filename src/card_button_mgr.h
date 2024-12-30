#ifndef CARD_BUTTON_MGR_H
#define CARD_BUTTON_MGR_H

#include <string.h>
#include <random>
#include "define.h"

class CardButtonMgr
{
public:
    static CardButtonMgr &get_instance()
    {
        static CardButtonMgr mgr;
        return mgr;
    }
    CardButtonMgr(const CardButtonMgr &) = delete;
    CardButtonMgr(CardButtonMgr &&) = delete;
    CardButtonMgr &operator= (const CardButtonMgr &) = delete;
    CardButtonMgr &operator= (CardButtonMgr &&) = delete;
    U16 pick_one_card();
    bool check_ans(U16 idx_1, U16 idx_2, U16 idx_3);
private:
    CardButtonMgr()
        : gen_(rd_())
    {
        memset(card_map_, 0, sizeof(card_map_));
    }
    inline U16 gen_idx() { return dist_(gen_); }
private:
    static const U16 SELECT_LIMIT = 3U;
    static const U16 N_SHAPE = 3U;
    static const U16 N_COLOR = 3U;
    static const U16 N_FILLER = 3U;
    static const U16 N_NUM = 3U;
    static const U16 CARD_NUM = N_SHAPE * N_COLOR * N_FILLER * N_NUM;
    const int16_t O_FILLER = N_NUM;
    const int16_t O_COLOR = O_FILLER + N_FILLER;
    const int16_t O_SHAPE = O_COLOR + N_COLOR;
    const int16_t T_FILLER = N_NUM;
    const int16_t T_COLOR = T_FILLER * N_FILLER;
    const int16_t T_SHAPE = T_COLOR * N_COLOR;
    static_assert(N_SHAPE + N_COLOR + N_FILLER + N_NUM <= 16U, "attributes too much!");
    static_assert(CARD_NUM <= ((1 << 16) - 1), "cards too much");
private:
    std::random_device rd_;
    std::mt19937 gen_;
    std::uniform_int_distribution<U16> dist_ {0, CARD_NUM - 1};
    bool card_map_[CARD_NUM];
};

#endif // CARD_BUTTON_MGR_H

