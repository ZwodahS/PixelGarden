#include "SeedManager.hpp"
#include "f_debug.hpp"
#include "consts.hpp"
#include <iostream>
#include <algorithm>
#include <stdlib.h>
SeedManager::SeedManager(GeneManager* geneManager)
{
    _seeds = std::vector<Seed*>(0);
    _counts = std::vector<int>(0);
    _used = std::vector<int>(0);
    _genesManager = geneManager;
    initBaseSeeds();
}

SeedManager::~SeedManager()
{

}

std::vector<Seed*>::iterator SeedManager::getIterator()
{
    return _seeds.begin();
}

std::vector<Seed*>::iterator SeedManager::end()
{
    return _seeds.end();
}

void SeedManager::seedPlanted(Seed* seed)
{
    _counts[seed->_id]--;
    _used[seed->_id]++;
}

int SeedManager::getCount(Seed* seed)
{
    return _counts[seed->_id];
}

int SeedManager::getUsed(Seed* seed)
{
    return _used[seed->_id];
}

void SeedManager::initBaseSeeds()
{
    std::vector<Gene*> expressedGenes = _genesManager->getDefaultExpressedGenes();
    std::vector<Gene*> unexpressedGenes = _genesManager->getDefaultUnexpressedGenes();
    SeedAttribute seedAttr = SeedAttribute(2,3,3,3,3,20,20);
    // the left seed will be red.
    std::vector<GrowthSegment> segments;
    segments.push_back(GROW_SOURCE_WEST);
    segments.push_back(GROW_SOURCE_WEST);
    segments.push_back(GROW_SOURCE_WEST);
    this->_seeds.push_back(new Seed(_seeds.size(),expressedGenes,unexpressedGenes,PixelColor(200,0,0),seedAttr,segments));
    this->_counts.push_back(gameconsts::STARTING_SEED);
    this->_used.push_back(0);
    //the right seed will be blue
    segments.clear();
    segments.push_back(GROW_SOURCE_EAST);
    segments.push_back(GROW_SOURCE_EAST);
    segments.push_back(GROW_SOURCE_EAST);
    this->_seeds.push_back(new Seed(_seeds.size(),expressedGenes,unexpressedGenes,PixelColor(0,0,200),seedAttr,segments));
    this->_counts.push_back(gameconsts::STARTING_SEED);
    this->_used.push_back(0);
    // the top seed will be green
    segments.clear();
    segments.push_back(GROW_SOURCE_NORTH);
    segments.push_back(GROW_SOURCE_NORTH);
    segments.push_back(GROW_SOURCE_NORTH);
    this->_seeds.push_back(new Seed(_seeds.size(),expressedGenes,unexpressedGenes,PixelColor(0,200,0),seedAttr,segments));
    this->_counts.push_back(gameconsts::STARTING_SEED);
    this->_used.push_back(0);
    // the top seed will be gray
    segments.clear();
    segments.push_back(GROW_SOURCE_SOUTH);
    segments.push_back(GROW_SOURCE_SOUTH);
    segments.push_back(GROW_SOURCE_SOUTH);
    this->_seeds.push_back(new Seed(_seeds.size(),expressedGenes,unexpressedGenes,PixelColor(200,200,200),seedAttr,segments));
    this->_counts.push_back(gameconsts::STARTING_SEED);
    this->_used.push_back(0);
    // the left seed will be red.
    segments.clear();
    segments.push_back(GROW_LAST_WEST);
    segments.push_back(GROW_LAST_WEST);
    segments.push_back(GROW_LAST_WEST);
    this->_seeds.push_back(new Seed(_seeds.size(),expressedGenes,unexpressedGenes,PixelColor(200,200,0),seedAttr,segments));
    this->_counts.push_back(gameconsts::STARTING_SEED);
    this->_used.push_back(0);
    //the right seed will be blue
    segments.clear();
    segments.push_back(GROW_LAST_EAST);
    segments.push_back(GROW_LAST_EAST);
    segments.push_back(GROW_LAST_EAST);
    this->_seeds.push_back(new Seed(_seeds.size(),expressedGenes,unexpressedGenes,PixelColor(200,0,200),seedAttr,segments));
    this->_counts.push_back(gameconsts::STARTING_SEED);
    this->_used.push_back(0);
    // the top seed will be green
    segments.clear();
    segments.push_back(GROW_LAST_NORTH);
    segments.push_back(GROW_LAST_NORTH);
    segments.push_back(GROW_LAST_NORTH);
    this->_seeds.push_back(new Seed(_seeds.size(),expressedGenes,unexpressedGenes,PixelColor(0,200,200),seedAttr,segments));
    this->_counts.push_back(gameconsts::STARTING_SEED);
    this->_used.push_back(0);
    // the top seed will be gray
    segments.clear();
    segments.push_back(GROW_LAST_SOUTH);
    segments.push_back(GROW_LAST_SOUTH);
    segments.push_back(GROW_LAST_SOUTH);
    this->_seeds.push_back(new Seed(_seeds.size(),expressedGenes,unexpressedGenes,PixelColor(50,50,50),seedAttr,segments));
    this->_counts.push_back(gameconsts::STARTING_SEED);
    this->_used.push_back(0);
}

Seed* SeedManager::crossBreed(std::vector<ParentContribution*> &contributions)
{
    std::vector<std::pair<Gene*,bool> > inheritedGenes = std::vector<std::pair<Gene*,bool> >(0);
    
    std::vector<Seed*> baseSeedsChoice = std::vector<Seed*>(0);
    std::vector<GrowthSegment> growthSegmentChoices = std::vector<GrowthSegment>(0);
    std::vector<std::vector<GrowthSegment> > growthParts = std::vector<std::vector<GrowthSegment> >(0);
    PixelColor newColor = PixelColor(0,0,0);
    for(int i = 0 ; i < contributions.size() ; i++)
    {
        for(int c = 0 ; c < contributions[i]->contributionValue ; c++)
        {
            baseSeedsChoice.push_back(contributions[i]->parent);
            newColor += contributions[i]->parent->_color;
            for(int r = 0 ; r < contributions[i]->parent->_segments.size(); r++)
            {
                growthSegmentChoices.push_back(contributions[i]->parent->_segments[r]);
                if(growthParts.size() <= r)
                {
                    growthParts.push_back(std::vector<GrowthSegment>(0));
                }
                growthParts[r].push_back(contributions[i]->parent->_segments[r]);
            }
        }
    }
    newColor.normalizeTo(displayconsts::NORMALIZED_TARGET_VALUE);
    // choose base attribute.
    SeedAttribute baseAttribute = baseSeedsChoice[rand() % baseSeedsChoice.size()]->_baseAttributes;
    
    std::vector<bool> geneInherited = std::vector<bool>(_genesManager->getTotalGenes());
    for(int i = 0 ; i < contributions.size() ; i++)
    {
        Seed* parent = contributions[i]->parent;
        std::vector<Gene*> genes = parent->_expressedGenes;
        for(int c = 0 ; c < genes.size() ; c++)
        {
            // for every gene that is expressed, check if it is inherited.
            if(genes[c]->inheritanceProbability_expressed.roll() && !geneInherited[genes[c]->id])
            {
                //if inherited, add it to the list
                inheritedGenes.push_back(std::pair<Gene*,bool>(genes[c],true));
                geneInherited[genes[c]->id] = true;
            }
        }
        genes = parent->_unexpressedGenes;
        for(int c = 0 ; c < genes.size() ; c++)
        {
            // for every gene that is unexpressed, check if it is inherited.
            if(genes[c]->inheritanceProbability_unexpressed.roll() && !geneInherited[genes[c]->id])
            {
                //if inherited, add it to the list
                inheritedGenes.push_back(std::pair<Gene*,bool>(genes[c],false));
                geneInherited[genes[c]->id] = true;
            }
        }
    }
    SeedAttribute mutation;
    for(int i = 0 ; i < inheritedGenes.size(); i++)
    {
        if(inheritedGenes[i].second) // if the gene is expressed, then there is mutation possibility
        {
            if(inheritedGenes[i].first->mutation.probability.roll())
            {
                mutation += inheritedGenes[i].first->mutation.attributeMutated;
            }
        }
    }
    // mutate the base seed attribute.
    baseAttribute += mutation;
    baseAttribute.setToMinMax();
    // genes inherited set. find which gene to expressed
    std::random_shuffle(inheritedGenes.begin(), inheritedGenes.end());
    std::vector<Gene*> expressedGenes = std::vector<Gene*>(0);
    std::vector<Gene*> unexpressedGenes = std::vector<Gene*>(0);
    for(int i = 0 ; i < inheritedGenes.size (); i++)
    {
        if(expressedGenes.size() >= baseAttribute.maxExpressedTraits)
        {
            unexpressedGenes.push_back(inheritedGenes[i].first);
            continue;
        }
        if(inheritedGenes[i].second) // if expressed
        {
            if(inheritedGenes[i].first->expressedProbability_expressed.roll())
            {
                expressedGenes.push_back(inheritedGenes[i].first);
            }
            else
            {
                unexpressedGenes.push_back(inheritedGenes[i].first);
            }
        }
        else // if unexpressed
        {
            if(inheritedGenes[i].first->expressedProbability_unexpressed.roll())
            {
                expressedGenes.push_back(inheritedGenes[i].first);
            }
            else 
            {
                unexpressedGenes.push_back(inheritedGenes[i].first);
            }
        }
    }
    std::vector<GrowthSegment> segments;

    Seed* newSeed = new Seed(_seeds.size(), expressedGenes, unexpressedGenes,newColor,baseAttribute);
    int growthSegs = newSeed->_effectiveAttributes.growthSegments;
    for(int i = 0 ; i < growthSegs ; i++)
    {
        if(growthParts.size() > i)
        {
            segments.push_back(growthParts[i][rand() % growthParts[i].size()]);
        }
        else
        {
            segments.push_back(growthSegmentChoices[rand() % growthSegmentChoices.size()]);
        }
    }
    newSeed->setSegments(segments);
    _seeds.push_back(newSeed);
    _counts.push_back(0);
    _used.push_back(0);
    return newSeed;
}

Seed* SeedManager::getSeedById(int id)
{
    if(_seeds.size() > id)
    {
        return _seeds[id];
    }
    return 0;
}
