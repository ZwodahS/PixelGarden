#ifndef _GAME_SEEDS_SEEDATTRIBUTE_H_
#define _GAME_SEEDS_SEEDATTRIBUTE_H_

#include "../../zf_common/Probability.hpp"
struct SeedAttribute
{
    int growthSegments;
    int growthTurns; // turns it takes to grow.
    int maturedDuration; // turns it stay matured.
    int decayTurns; // turns it takes to decay.
    int maxExpressedTraits;
    Probability decaySeed; // chance a decay pixel drop a seed. ( the number represents the chance in a 1000 )
    Probability maturedSeed; // chance a mature pixel drop a seed during matured stage..
    SeedAttribute();
    SeedAttribute(int growthSeg, int growthTurns, int maturedDuration, int decayTurns,int maxExpressedTraits,int decaySeed,int maturedSeed);
    ~SeedAttribute();
};


#endif
