#include "GeneManager.hpp"

GeneManager::GeneManager()
{
    _genes = std::vector<Gene*>(0);
}

GeneManager::~GeneManager()
{
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
    newGene(1  , 0  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 50 , 20 , 5  , 1  , 0  , 0  , 0  , 0  , 0  , 0);
    newGene(2  , 0  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 20 , 10 , 10 , 1  , 0  , 0  , 0  , 0  , 0  , 0);
    newGene(3  , 0  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 10 , 5  , 15 , 1  , 0  , 0  , 0  , 0  , 0  , 0);
    newGene(4  , 0  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 5  , 5  , 20 , 1  , 0  , 0  , 0  , 0  , 0  , 0);
    newGene(-1 , 0  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 50 , 20 , 5  , -1 , 0  , 0  , 0  , 0  , 0  , 0);
    newGene(-2 , 0  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 20 , 10 , 10 , -1 , 0  , 0  , 0  , 0  , 0  , 0);
    newGene(-3 , 0  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 10 , 5  , 15 , -1 , 0  , 0  , 0  , 0  , 0  , 0);
    newGene(-4 , 0  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 5  , 5  , 20 , -1 , 0  , 0  , 0  , 0  , 0  , 0);
    // growth turns 
    newGene(0  , 1  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 1  , 0  , 0  , 0  , 0  , 0);
    newGene(0  , 2  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 1  , 0  , 0  , 0  , 0  , 0);
    newGene(0  , 3  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 1  , 0  , 0  , 0  , 0  , 0);
    newGene(0  , 4  , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 1  , 0  , 0  , 0  , 0  , 0);
    newGene(0  , -1 , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , -1 , 0  , 0  , 0  , 0  , 0);
    newGene(0  , -2 , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 20 , 10 , 10 , 0  , -1 , 0  , 0  , 0  , 0  , 0);
    newGene(0  , -3 , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 10 , 5  , 15 , 0  , -1 , 0  , 0  , 0  , 0  , 0);
    newGene(0  , -4 , 0  , 0  , 0  , 0   , 0 , 100 , 20 , 5  , 5  , 20 , 0  , -1 , 0  , 0  , 0  , 0  , 0);
    // maturedDuration
    newGene(0  , 0  , 1  , 0  , 0  , 0   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 0  , 1  , 0  , 0  , 0  , 0);
    newGene(0  , 0  , 2  , 0  , 0  , 0   , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , 1  , 0  , 0  , 0  , 0);
    newGene(0  , 0  , 3  , 0  , 0  , 0   , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , 1  , 0  , 0  , 0  , 0);
    newGene(0  , 0  , 4  , 0  , 0  , 0   , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , 1  , 0  , 0  , 0  , 0);
    newGene(0  , 0  , -1 , 0  , 0  , 0   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 0  , -1 , 0  , 0  , 0  , 0);
    newGene(0  , 0  , -2 , 0  , 0  , 0   , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , -1 , 0  , 0  , 0  , 0);
    newGene(0  , 0  , -3 , 0  , 0  , 0   , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , -1 , 0  , 0  , 0  , 0);
    newGene(0  , 0  , -4 , 0  , 0  , 0   , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , -1 , 0  , 0  , 0  , 0);
    //decayTurns
    newGene(0  , 0  , 0  , 1  , 0  , 0   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 0  , 0  , 1  , 0  , 0  , 0);
    newGene(0  , 0  , 0  , 2  , 0  , 0   , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , 0  , 1  , 0  , 0  , 0);
    newGene(0  , 0  , 0  , 3  , 0  , 0   , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , 0  , 1  , 0  , 0  , 0);
    newGene(0  , 0  , 0  , 4  , 0  , 0   , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , 0  , 1  , 0  , 0  , 0);
    newGene(0  , 0  , 0  , -1 , 0  , 0   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 0  , 0  , -1 , 0  , 0  , 0);
    newGene(0  , 0  , 0  , -2 , 0  , 0   , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , 0  , -1 , 0  , 0  , 0);
    newGene(0  , 0  , 0  , -3 , 0  , 0   , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , 0  , -1 , 0  , 0  , 0);
    newGene(0  , 0  , 0  , -4 , 0  , 0   , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , 0  , -1 , 0  , 0  , 0);
    //maxExpressedTraits
    newGene(0  , 0  , 0  , 0  , 1  , 0   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 0  , 0  , 0  , 1  , 0  , 0);
    newGene(0  , 0  , 0  , 0  , 2  , 0   , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , 0  , 0  , 1  , 0  , 0);
    newGene(0  , 0  , 0  , 0  , 3  , 0   , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , 0  , 0  , 1  , 0  , 0);
    newGene(0  , 0  , 0  , 0  , 4  , 0   , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , 0  , 0  , 1  , 0  , 0);
    newGene(0  , 0  , 0  , 0  , -1 , 0   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 0  , 0  , 0  , -1 , 0  , 0);
    newGene(0  , 0  , 0  , 0  , -2 , 0   , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , 0  , 0  , -1 , 0  , 0);
    newGene(0  , 0  , 0  , 0  , -3 , 0   , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , 0  , 0  , -1 , 0  , 0);
    newGene(0  , 0  , 0  , 0  , -4 , 0   , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , 0  , 0  , -1 , 0  , 0);
    //chance to get seed when decaying
    newGene(0  , 0  , 0  , 0  , 0  , 5   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 0  , 0  , 0  , 0  , 5  , 0);
    newGene(0  , 0  , 0  , 0  , 0  , 10  , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , 0  , 0  , 0  , 5  , 0);
    newGene(0  , 0  , 0  , 0  , 0  , 15  , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , 0  , 0  , 0  , 5  , 0);
    newGene(0  , 0  , 0  , 0  , 0  , 20  , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , 0  , 0  , 0  , 5  , 0);
    newGene(0  , 0  , 0  , 0  , 0  , -5  , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 0  , 0  , 0  , 0  , -5 , 0);
    newGene(0  , 0  , 0  , 0  , 0  , -10 , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , 0  , 0  , 0  , -5 , 0);
    newGene(0  , 0  , 0  , 0  , 0  , -15 , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , 0  , 0  , 0  , -5 , 0);
    newGene(0  , 0  , 0  , 0  , 0  , -20 , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , 0  , 0  , 0  , -5 , 0);
    //chance to get seed when matured
    newGene(0  , 0  , 0  , 0  , 0  , 5   , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 0  , 0  , 0  , 0  , 0  , 5);
    newGene(0  , 0  , 0  , 0  , 0  , 10  , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , 0  , 0  , 0  , 0  , 5);
    newGene(0  , 0  , 0  , 0  , 0  , 15  , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , 0  , 0  , 0  , 0  , 5);
    newGene(0  , 0  , 0  , 0  , 0  , 20  , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , 0  , 0  , 0  , 0  , 5);
    newGene(0  , 0  , 0  , 0  , 0  , -5  , 0 , 100 , 20 , 50 , 20 , 5  , 0  , 0  , 0  , 0  , 0  , 0  , -5);
    newGene(0  , 0  , 0  , 0  , 0  , -10 , 0 , 100 , 20 , 20 , 10 , 10 , 0  , 0  , 0  , 0  , 0  , 0  , -5);
    newGene(0  , 0  , 0  , 0  , 0  , -15 , 0 , 100 , 20 , 10 , 5  , 15 , 0  , 0  , 0  , 0  , 0  , 0  , -5);
    newGene(0  , 0  , 0  , 0  , 0  , -20 , 0 , 100 , 20 , 5  , 5  , 20 , 0  , 0  , 0  , 0  , 0  , 0  , -5);
}
