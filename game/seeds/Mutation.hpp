#ifndef _GAME_SEEDS_MUTATION_H_
#define _GAME_SEEDS_MUTATION_H_

#include "SeedAttribute.hpp"
#include "../../zf_common/Probability.hpp"

struct Mutation
{
    // the probability of mutation
    Probability probability;
    SeedAttribute attributeMutated; // the attribute(s) that is mutated.
    Mutation();
    Mutation(Probability probability, SeedAttribute attributeMutated);
    ~Mutation();
};
#endif
