#include "card_button_mgr.h"

U16 CardButtonMgr::pick_one_card()
{
    U16 idx = 0U;
    do
    {
        idx = gen_idx();
    } while(true == card_map_[idx]);
    card_map_[idx] = true;
    return idx;
}

bool CardButtonMgr::check_ans(U16 idx_1, U16 idx_2, U16 idx_3)
{
    if (idx_1 >= CARD_NUM ||  idx_2 >= CARD_NUM || idx_3 >= CARD_NUM)
    {
        return false;
    }

    U16 shape_1 = idx_1 / T_SHAPE;
    U16 shape_2 = idx_2 / T_SHAPE;
    U16 shape_3 = idx_3 / T_SHAPE;

    U16 color_1 = (idx_1 % T_SHAPE) / T_COLOR;
    U16 color_2 = (idx_2 % T_SHAPE) / T_COLOR;
    U16 color_3 = (idx_3 % T_SHAPE) / T_COLOR;

    U16 filler_1 = (idx_1 % T_COLOR) / T_FILLER;
    U16 filler_2 = (idx_2 % T_COLOR) / T_FILLER;
    U16 filler_3 = (idx_3 % T_COLOR) / T_FILLER;

    U16 num_1 = idx_1 % 3;
    U16 num_2 = idx_2 % 3;
    U16 num_3 = idx_3 % 3;

    bool shape_ans = (shape_1 == shape_2 && shape_2 == shape_3) |
                     (shape_1 != shape_2 && shape_1 != shape_3 && shape_2 != shape_3);
    bool color_ans = (color_1 == color_2 && color_2 == color_3) |
                     (color_1 != color_2 && color_1 != color_3 && color_2 != color_3);
    bool filler_ans = (filler_1 == filler_2 && filler_2 == filler_3) |
                     (filler_1 != filler_2 && filler_1 != filler_3 && filler_2 != filler_3);
    bool num_ans = (num_1 == num_2 && num_2 == num_3) |
                     (num_1 != num_2 && num_1 != num_3 && num_2 != num_3);

    return shape_ans && color_ans && filler_ans && num_ans;
}
