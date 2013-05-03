#ifndef _GAME_GARDEN_PARENTCONTRIBUTION_H_
#define _GAME_GARDEN_PARENTCONTRIBUTION_H_
class Seed;
struct ParentContribution
{
    Seed* parent;
    int contributionValue;
    bool seedDone; //if the seed has finish growth.
    bool parentDone; // if the parent has finish growth.

    ParentContribution();
    ParentContribution(Seed* seed);
    ~ParentContribution();
};
#endif
