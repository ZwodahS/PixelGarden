#ifndef _GAME_CONSTS_H_
#define _GAME_CONSTS_H_

namespace gameconsts
{
    const int MAX_GARDEN_ROW = 19;
    const int MAX_GARDEN_COL = 19;
    const int SAME_SEED_BONUS = 5;
    const int BREED_SEED_BONUS = 10;
}

namespace displayconsts
{
    const int NORMALIZED_TARGET_VALUE = 200;

    const int PIXEL_SIZE = 32;
    const int PIXEL_SPACING = 1;

    const int GARDEN_WIDTH = (PIXEL_SIZE + PIXEL_SPACING) * gameconsts::MAX_GARDEN_COL + PIXEL_SPACING;
    const int GARDEN_HEIGHT = (PIXEL_SIZE + PIXEL_SPACING) * gameconsts::MAX_GARDEN_ROW + PIXEL_SPACING;

    const int GARDEN_DISPLAY_WIDTH = GARDEN_WIDTH;
    const int GARDEN_DISPLAY_HEIGHT = GARDEN_HEIGHT;

}
#endif
