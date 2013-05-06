#ifndef _GAME_SEEDS_GROWTH_SEGMENT_H_
#define _GAME_SEEDS_GROWTH_SEGMENT_H_
#include <string>
enum GrowthSegment
{
    GROW_SOURCE_NORTH,
    GROW_SOURCE_SOUTH,
    GROW_SOURCE_EAST,
    GROW_SOURCE_WEST,
    GROW_LAST_NORTH,
    GROW_LAST_SOUTH,
    GROW_LAST_EAST,
    GROW_LAST_WEST,

};


std::string toString(GrowthSegment gs);

#endif
