#include "Probability.h"
#include <stdlib.h>

Probability::Probability()
{
    this->chance = 1;
    this->maxRoll = 5;
}

Probability::Probability(int chance)
{
    this->chance = chance;
    this->maxRoll = 100;
}

Probability::Probability(int chance,int max)
{
    this->chance = chance;
    this->maxRoll = max;
}

bool Probability::roll()
{
    return (rand() % maxRoll < chance);
}