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

SeedAttribute& SeedAttribute::operator+=(const SeedAttribute &rhs)
{
    this->growthSegments += rhs.growthSegments;
    this->growthTurns    += rhs.growthTurns;
    this->maturedDuration += rhs.maturedDuration;
    this->decayTurns += rhs.decayTurns;
    this->maxExpressedTraits += rhs.maxExpressedTraits;
    this->decaySeed.chance += rhs.decaySeed.chance;
    this->maturedSeed.chance += rhs.maturedSeed.chance;
    return *this;
}

void SeedAttribute::setToMinMax()
{
    this->growthSegments = growthSegments < 1 ? 1 : this->growthSegments;
    this->growthTurns = growthTurns < 1 ? 1 : this->growthTurns;
    this->maturedDuration = maturedDuration < 1 ? 1 : this->maturedDuration;
    this->decayTurns = decayTurns < 1 ? 1 : this->decayTurns;
    this->maxExpressedTraits = maxExpressedTraits < 0 ? 0 : this->maxExpressedTraits;
    this->decaySeed.chance = decaySeed.chance < 0 ? 0 : (decaySeed.chance > 70 ? 70 : decaySeed.chance);
    this->maturedSeed.chance = maturedSeed.chance < 0 ? 0 : (maturedSeed.chance > 70 ? 70 : maturedSeed.chance);
}

SeedAttribute operator+(SeedAttribute lhs, const SeedAttribute &rhs)
{
    lhs+=rhs;
    return lhs;
}
