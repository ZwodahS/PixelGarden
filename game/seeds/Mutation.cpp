#include "Mutation.hpp"
Mutation::Mutation()
{
}    
Mutation::Mutation(Probability probability, SeedAttribute attributeMutated)
{
    this->probability = probability;
    this->attributeMutated = attributeMutated;
}
Mutation::~Mutation()
{
}
