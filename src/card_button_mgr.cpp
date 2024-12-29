#include "card_button_mgr.h"

void CardButtonMgr::init_attributes()
{
    const int16_t T_FILLER = N_NUM;
    const int16_t T_COLOR = T_FILLER * N_FILLER;
    const int16_t T_SHAPE = T_COLOR * N_COLOR;
    for(U16 i_shape = 0; i_shape < N_SHAPE; ++i_shape)
    {
        for(U16 i_color = 0; i_color < N_COLOR; ++i_color)
        {
            for (U16 i_filler = 0; i_filler < N_FILLER; ++i_filler)
            {
                for(U16 i_num = 0; i_num < N_NUM; ++i_num)
                {
                    U16 idx = i_shape * T_SHAPE + i_color * T_COLOR + i_filler * T_FILLER + i_num;
                    U16 mask = 0U | (1 << (i_shape + O_SHAPE)) | (1 << (i_color + O_COLOR)) |
                               (1 << (i_filler + O_FILLER)) | (1 << i_num);
                    attributes_[idx] = mask;
                }
            }
        }
    }
}

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

    U16 attr_1 = attributes_[idx_1];
    U16 attr_2 = attributes_[idx_2];
    U16 attr_3 = attributes_[idx_3];

    U16 m_shape = ((1 << N_SHAPE) - 1) << O_SHAPE;
    U16 m_color = ((1 << N_COLOR) - 1) << O_COLOR;
    U16 m_filler = ((1 << N_FILLER) - 1) << O_FILLER;
    U16 m_num = (1 << N_NUM) - 1;

    U16 shape_1 = attr_1 & m_shape;
    U16 shape_2 = attr_2 & m_shape;
    U16 shape_3 = attr_3 & m_shape;

    U16 color_1 = attr_1 & m_color;
    U16 color_2 = attr_2 & m_color;
    U16 color_3 = attr_3 & m_color;

    U16 filler_1 = attr_1 & m_filler;
    U16 filler_2 = attr_2 & m_filler;
    U16 filler_3 = attr_3 & m_filler;

    U16 num_1 = attr_1 & m_num;
    U16 num_2 = attr_2 & m_num;
    U16 num_3 = attr_3 & m_num;

    bool shape_ans = (shape_1 == shape_2 && shape_2 == shape_3) ||
                     (m_shape == (shape_1 | shape_2 | shape_3));
    bool color_ans = (color_1 == color_2 && color_2 == color_3) ||
                     (m_color == (color_1 | color_2 | color_3));
    bool filler_ans = (filler_1 == filler_2 && filler_2 == filler_3) ||
                      (m_filler == (filler_1 | filler_2 | filler_3));
    bool num_ans = (num_1 == num_2 && num_2 == num_3) ||
                   (m_num == (num_1 | num_2 | num_3));

    card_map_[idx_1] = false;
    card_map_[idx_2] = false;
    card_map_[idx_3] = false;

    return shape_ans && color_ans && filler_ans && num_ans;
}
