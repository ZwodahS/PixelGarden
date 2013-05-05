#ifndef _GAME_SEEDMANAGER_H_
#define _GAME_SEEDMANAGER_H_

// Stores all the seeds available for this "savefile"
// It also stores how many seeds the player have.

#include "g_seeds.hpp"
#include "GeneManager.hpp"
#include "garden/ParentContribution.hpp"
#include <vector>
const int BASE_SEEDS = 4;
class SeedManager
{
    public:
        SeedManager(GeneManager* gM);
        ~SeedManager();

        void initBaseSeeds();

        Seed* crossBreed(std::vector<ParentContribution> &contributions);


        std::vector<Seed*>::iterator getIterator();
        std::vector<Seed*>::iterator end();

        int getCount(Seed* seed);
    protected:
        std::vector<Seed*> _seeds;
        std::vector<int>   _counts;
        
        GeneManager* _genesManager;
};
#endif
