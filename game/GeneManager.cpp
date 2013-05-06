#include "GeneManager.hpp"

#include <iostream>
GeneManager::GeneManager()
{
    _genes = std::vector<Gene*>(0);
}

GeneManager::~GeneManager()
{
}

Gene* GeneManager::getGene(int geneId)
{
    if(geneId >= 0 && geneId < _genes.size())
    {
        return _genes[geneId];
    }
    return 0;
}

int GeneManager::getTotalGenes()
{
    return _genes.size();
}

std::vector<Gene*> GeneManager::getDefaultExpressedGenes()
{
    std::vector<Gene*> genes;
    genes.push_back(_genes[0]);  // growth segment +1
    genes.push_back(_genes[12]); // growth turn -1
    genes.push_back(_genes[20]); // matured duration -1
    genes.push_back(_genes[28]); // decay turn -1
    genes.push_back(_genes[48]); // seed chance -20% (decay)
    genes.push_back(_genes[49]); // seed chance -20% (matured)
    return genes;
}

std::vector<Gene*> GeneManager::getDefaultUnexpressedGenes()
{
    std::vector<Gene*> genes;
    for(int i = 0 ; i < _genes.size () ; i++)
    {
        if(i != 0 && i != 12 && i != 20 && i != 28 && i != 40 && i != 41)
        {
            genes.push_back(_genes[i]);
        }
    }
    return genes;
}

void GeneManager::newGene(int growthSeg,int growthTurns,int maturedDuration,int decayTurns,int maxExpressedTraits, int decaySeed,int maturedSeed,
        int prob_in_exp, int prob_in_unexp, int prob_exp_exp, int prob_exp_unexp,
        int prob_mutation, int m_growthSeg,int m_growthTurns, int m_maturedDuration, int m_decayTurns,
        int m_maxExpressedTraits, int m_decaySeed, int m_maturedSeed)
{
    _genes.push_back(new Gene(
                _genes.size(),
                SeedAttribute(growthSeg,growthTurns,maturedDuration,decayTurns,maxExpressedTraits,decaySeed,maturedSeed), // Attribute contribution
                Probability(prob_in_exp), // Prob inherited if expressed
                Probability(prob_in_unexp),  // Prob inherited if unexpressed
                Probability(prob_exp_exp),  // Prob expressed if expressed
                Probability(prob_exp_unexp),  // Prob expressed if unexpressed
                Mutation(Probability(prob_mutation),SeedAttribute(m_growthSeg,m_growthTurns,m_maturedDuration,m_decayTurns,m_maxExpressedTraits,m_decaySeed,m_maturedSeed)) // Mutation possibility
                ));
}



void GeneManager::initBasicRules()
{
    //                                                        <MUT>                               
    // growth seg
    newGene(1  , 0  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 50 , 20 , 5  , 1  , 0  , 0  , 0  , 0  , 0  , 0); //0
    newGene(2  , 0  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 20 , 10 , 10 , 1  , 0  , 0  , 0  , 0  , 0  , 0);
    newGene(3  , 0  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 10 , 5  , 15 , 1  , 0  , 0  , 0  , 0  , 0  , 0);
    newGene(4  , 0  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 5  , 5  , 20 , 1  , 0  , 0  , 0  , 0  , 0  , 0);
    newGene(-1 , 0  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 50 , 20 , 5  , -1 , 0  , 0  , 0  , 0  , 0  , 0);
    newGene(-2 , 0  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 20 , 10 , 10 , -1 , 0  , 0  , 0  , 0  , 0  , 0);
    newGene(-3 , 0  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 10 , 5  , 15 , -1 , 0  , 0  , 0  , 0  , 0  , 0);
    newGene(-4 , 0  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 5  , 5  , 20 , -1 , 0  , 0  , 0  , 0  , 0  , 0); //7
    // growth turns 
    newGene(0  , 1  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 1  , 0  , 0  , 0  , 0  , 0); //8
    newGene(0  , 2  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 1  , 0  , 0  , 0  , 0  , 0);
    newGene(0  , 3  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 1  , 0  , 0  , 0  , 0  , 0);
    newGene(0  , 4  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 1  , 0  , 0  , 0  , 0  , 0);
    newGene(0  , -1 , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , -1 , 0  , 0  , 0  , 0  , 0);
    newGene(0  , -2 , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 20 , 10 , 10 , 0  , -1 , 0  , 0  , 0  , 0  , 0);
    newGene(0  , -3 , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 10 , 5  , 15 , 0  , -1 , 0  , 0  , 0  , 0  , 0);
    newGene(0  , -4 , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 5  , 5  , 20 , 0  , -1 , 0  , 0  , 0  , 0  , 0); //15
    // maturedDuration
    newGene(0  , 0  , 1  , 0  , 0  , 0   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 0  , 1  , 0  , 0  , 0  , 0); //16
    newGene(0  , 0  , 2  , 0  , 0  , 0   , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , 1  , 0  , 0  , 0  , 0);
    newGene(0  , 0  , 3  , 0  , 0  , 0   , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , 1  , 0  , 0  , 0  , 0);
    newGene(0  , 0  , 4  , 0  , 0  , 0   , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , 1  , 0  , 0  , 0  , 0);
    newGene(0  , 0  , -1 , 0  , 0  , 0   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 0  , -1 , 0  , 0  , 0  , 0);
    newGene(0  , 0  , -2 , 0  , 0  , 0   , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , -1 , 0  , 0  , 0  , 0);
    newGene(0  , 0  , -3 , 0  , 0  , 0   , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , -1 , 0  , 0  , 0  , 0);
    newGene(0  , 0  , -4 , 0  , 0  , 0   , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , -1 , 0  , 0  , 0  , 0); //23
    //decayTurns
    newGene(0  , 0  , 0  , 1  , 0  , 0   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 0  , 0  , 1  , 0  , 0  , 0); //24
    newGene(0  , 0  , 0  , 2  , 0  , 0   , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , 0  , 1  , 0  , 0  , 0);
    newGene(0  , 0  , 0  , 3  , 0  , 0   , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , 0  , 1  , 0  , 0  , 0);
    newGene(0  , 0  , 0  , 4  , 0  , 0   , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , 0  , 1  , 0  , 0  , 0);
    newGene(0  , 0  , 0  , -1 , 0  , 0   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 0  , 0  , -1 , 0  , 0  , 0);
    newGene(0  , 0  , 0  , -2 , 0  , 0   , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , 0  , -1 , 0  , 0  , 0);
    newGene(0  , 0  , 0  , -3 , 0  , 0   , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , 0  , -1 , 0  , 0  , 0);
    newGene(0  , 0  , 0  , -4 , 0  , 0   , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , 0  , -1 , 0  , 0  , 0); //31
    //chance to get seed when decaying
    newGene(0  , 0  , 0  , 0  , 0  , 5   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 0  , 0  , 0  , 0  , 5  , 0); //32
    newGene(0  , 0  , 0  , 0  , 0  , 10  , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , 0  , 0  , 0  , 5  , 0);
    newGene(0  , 0  , 0  , 0  , 0  , 15  , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , 0  , 0  , 0  , 5  , 0);
    newGene(0  , 0  , 0  , 0  , 0  , 20  , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , 0  , 0  , 0  , 5  , 0);
    newGene(0  , 0  , 0  , 0  , 0  , -5  , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 0  , 0  , 0  , 0  , -5 , 0);
    newGene(0  , 0  , 0  , 0  , 0  , -10 , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , 0  , 0  , 0  , -5 , 0);
    newGene(0  , 0  , 0  , 0  , 0  , -15 , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , 0  , 0  , 0  , -5 , 0);
    newGene(0  , 0  , 0  , 0  , 0  , -20 , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , 0  , 0  , 0  , -5 , 0); //39
    //chance to get seed when matured
    newGene(0  , 0  , 0  , 0  , 0  , 0 , 5   , 100 , 20 , 50 , 20 , 5  , 0  , 0  , 0  , 0  , 0  , 0  , 5); //40
    newGene(0  , 0  , 0  , 0  , 0  , 0 , 10  , 100 , 20 , 20 , 10 , 10 , 0  , 0  , 0  , 0  , 0  , 0  , 5);
    newGene(0  , 0  , 0  , 0  , 0  , 0 , 15  , 100 , 20 , 10 , 5  , 15 , 0  , 0  , 0  , 0  , 0  , 0  , 5);
    newGene(0  , 0  , 0  , 0  , 0  , 0 , 20  , 100 , 20 , 5  , 5  , 20 , 0  , 0  , 0  , 0  , 0  , 0  , 5);
    newGene(0  , 0  , 0  , 0  , 0  , 0 , -5  , 100 , 20 , 50 , 20 , 5  , 0  , 0  , 0  , 0  , 0  , 0  , -5);
    newGene(0  , 0  , 0  , 0  , 0  , 0 , -10 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , 0  , 0  , 0  , 0  , -5);
    newGene(0  , 0  , 0  , 0  , 0  , 0 , -15 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , 0  , 0  , 0  , 0  , -5);
    newGene(0  , 0  , 0  , 0  , 0  , 0 , -20 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , 0  , 0  , 0  , 0  , -5); //47

    //special seed denying gene for stem seed.
    //48
    newGene(0 , 0 , 0 , 0 , 0 , -20 , 0   , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0); // seed chance when decay - 20% 
    //49
    newGene(0 , 0 , 0 , 0 , 0 , 0   , -20 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0); // seed chance when matured - 20%

    // only provide mutation benefits
    //maxExpressedTraits - Does not add benefits , but provide mutation benefits
    newGene(0  , 0  , 0  , 0  , 0 , 0   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 0  , 0  , 0  , 1  , 0  , 0); //50
    newGene(0  , 0  , 0  , 0  , 0 , 0   , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , 0  , 0  , 1  , 0  , 0);
    newGene(0  , 0  , 0  , 0  , 0 , 0   , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , 0  , 0  , 1  , 0  , 0);
    newGene(0  , 0  , 0  , 0  , 0 , 0   , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , 0  , 0  , 1  , 0  , 0);
    newGene(0  , 0  , 0  , 0  , 0 , 0   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 0  , 0  , 0  , -1 , 0  , 0);
    newGene(0  , 0  , 0  , 0  , 0 , 0   , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , 0  , 0  , -1 , 0  , 0);
    newGene(0  , 0  , 0  , 0  , 0 , 0   , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , 0  , 0  , -1 , 0  , 0);
    newGene(0  , 0  , 0  , 0  , 0 , 0   , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , 0  , 0  , -1 , 0  , 0); //57
}
