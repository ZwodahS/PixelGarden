#ifndef _GAME_SEEDMANAGER_H_
#define _GAME_SEEDMANAGER_H_

// Stores all the seeds available for this "savefile"
// It also stores how many seeds the player have.

#include "g_seeds.hpp"
#include <vector>
const int BASE_SEEDS = 4;
class SeedManager
{
    public:
        SeedManager();
        ~SeedManager();

        void initBaseSeeds();
    protected:
        std::vector<Seed*> _seeds;
        std::vector<int>   _counts;
};
#endif
