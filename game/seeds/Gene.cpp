#include "Gene.h"

Gene::Gene(SeedAttribute attr, Probability p_ih_exp, Probability p_ih_unexp, Probability p_exp_exp, Probability p_exp_unexp , Mutation mutation)
{
    this->attributeContribution = attr;
    this->inheritanceProbability_expressed = p_ih_exp;
    this->inheritanceProbability_unexpressed = p_ih_unexp;
    this->expressedProbability_expressed = p_exp_exp;
    this->expressedProbability_unexpressed = p_exp_unexp;
    this->mutation = mutation;
}

Gene::~Gene()
{
}