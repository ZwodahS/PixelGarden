#ifndef _GAME_SEEDS_GENE_H_
#define _GAME_SEEDS_GENE_H_

#include "SeedAttribute.h"
#include "Mutation.h"

#include "../../zf_common/Probability.h"
struct Gene
{
    SeedAttribute attributeContribution;
    
    Probability inheritanceProbability_expressed; // the chance of this being inherited if this is expressed in parent.
    Probability inheritanceProbability_unexpressed; // the chance of this gene being inherited if this is not expressed in parent.
    Probability expressedProbability_expressed; // the chance of this gene being expressed, if inherited.
    Probability expressedProbability_unexpressed; // the chance of this gene being expressed, if inherited.

    Mutation mutation;
    Gene(SeedAttribute attributes, Probability prob_inherit_expressed, 
            Probability prob_inherit_unexp, Probability prob_exp_exp, Probability prob_exp_unexp, Mutation mutation);
    ~Gene();
};
#endif