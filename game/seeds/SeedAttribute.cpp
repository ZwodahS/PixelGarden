#include "SeedAttribute.hpp"
SeedAttribute::SeedAttribute(int growthSeg, int growthTurns, int maturedDuration, 
        int decayTurns,int maxExpressedTraits,int decaySeed,int maturedSeed)
{
    this->growthSegments = growthSeg;
    this->growthTurns = growthTurns;
    this->maturedDuration = maturedDuration;
    this->decayTurns = decayTurns;
    this->maxExpressedTraits = maxExpressedTraits;
    this->decaySeed = Probability(decaySeed,100);
    this->maturedSeed = Probability(maturedSeed,100);
}
SeedAttribute::SeedAttribute()
{
    growthSegments     = 0;
    growthTurns        = 0;
    maturedDuration   = 0;
    decayTurns         = 0;
    maxExpressedTraits = 0;
    decaySeed          = Probability(0,100);
    maturedSeed = Probability(0,100);
}

SeedAttribute::~SeedAttribute()
{

}
