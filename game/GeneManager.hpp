#ifndef _GAME_GENEMANAGER_H_
#define _GAME_GENEMANAGER_H_

#include "g_seeds.hpp"
#include "../zf_common/Probability.hpp"
#include <vector>

class GeneManager
{
    public:
        GeneManager();
        ~GeneManager();
        void initBasicRules();
    protected:
        std::vector<Gene*> _genes;
        // put it in a easy to add format.
        void newGene(int growthSeg,int growthTurns,int maturedDuration,int decayTurns,int maxExpressedTraits, int decaySeed,int maturedSeed,
                int prob_in_exp, int prob_in_unexp, int prob_exp_exp, int prob_exp_unexp,
                int prob_mutation, int m_growthSeg,int m_growthTurns, int m_maturedDuration, int m_decayTurns,
                int m_maxExpressedTraits, int m_decaySeed, int m_maturedSeed);

};


#endif
