#ifndef _GAME_GAMEDATA_H_
#define _GAME_GAMEDATA_H_

#include "SeedManager.hpp"
#include "GeneManager.hpp"
#include "garden/Garden.hpp"

struct GameData
{
    SeedManager* seedManager;
    GeneManager* geneManager;
    Garden* garden;
    
    Seed* selectedSeed;
    GameData(SeedManager* sM, GeneManager* gM, Garden* garden)
    {
        this->seedManager = sM;
        this->geneManager = gM;
        this->garden = garden;
        this->selectedSeed = 0;
    }
    ~GameData()
    {
        if(seedManager != 0)
        {
            delete seedManager;
        }
        if(geneManager != 0)
        {
            delete geneManager;
        }
        if(garden != 0)
        {
            delete garden;
        }
    }

};
#endif
