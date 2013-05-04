#include "SeedManager.hpp"

SeedManager::SeedManager()
{
    _seeds = std::vector<Seed*>(0);
    _counts = std::vector<int>(0);
    initBaseSeeds();
}

SeedManager::~SeedManager()
{

}

void SeedManager::initBaseSeeds()
{
        
}
