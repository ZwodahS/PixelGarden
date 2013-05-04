#include "SeedManager.hpp"
#include "consts.hpp"
#include <iostream>
SeedManager::SeedManager(GeneManager* geneManager)
{
    _seeds = std::vector<Seed*>(0);
    _counts = std::vector<int>(0);
    _genesManager = geneManager;
    initBaseSeeds();
}

SeedManager::~SeedManager()
{

}

void SeedManager::initBaseSeeds()
{
    std::vector<Gene*> expressedGenes = _genesManager->getDefaultExpressedGenes();
    std::vector<Gene*> unexpressedGenes = _genesManager->getDefaultUnexpressedGenes();
    SeedAttribute seedAttr = SeedAttribute(2,3,3,3,3,20,20);
    // the left seed will be red.
    std::vector<GrowthSegment> segments;
    segments.push_back(GROW_SOURCE_WEST);
    segments.push_back(GROW_LAST_WEST);
    this->_seeds.push_back(new Seed(_seeds.size(),expressedGenes,unexpressedGenes,PixelColor(150,0,0),seedAttr,segments));
    this->_counts.push_back(gameconsts::STARTING_SEED);
    
    //the right seed will be blue
    segments.clear();
    segments.push_back(GROW_SOURCE_EAST);
    segments.push_back(GROW_LAST_EAST);
    this->_seeds.push_back(new Seed(_seeds.size(),expressedGenes,unexpressedGenes,PixelColor(0,0,150),seedAttr,segments));
    this->_counts.push_back(gameconsts::STARTING_SEED);
    
    // the top seed will be green
    segments.clear();
    segments.push_back(GROW_SOURCE_NORTH);
    segments.push_back(GROW_LAST_NORTH);
    this->_seeds.push_back(new Seed(_seeds.size(),expressedGenes,unexpressedGenes,PixelColor(0,150,0),seedAttr,segments));
    this->_counts.push_back(gameconsts::STARTING_SEED);

    // the top seed will be gray
    segments.clear();
    segments.push_back(GROW_SOURCE_SOUTH);
    segments.push_back(GROW_LAST_SOUTH);
    this->_seeds.push_back(new Seed(_seeds.size(),expressedGenes,unexpressedGenes,PixelColor(50,50,50),seedAttr,segments));
    this->_counts.push_back(gameconsts::STARTING_SEED);
}
