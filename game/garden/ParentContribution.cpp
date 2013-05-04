#include "ParentContribution.hpp"
ParentContribution::ParentContribution(Seed* seed)
{
    this->parent = seed;
    this->contributionValue = 0;
    this->seedDone = false;
    this->parentDone = false;

}
ParentContribution::ParentContribution()
{
    this->parent = 0;
    this->contributionValue = 0;
    this->seedDone = false;
    this->parentDone = false;
}

ParentContribution::~ParentContribution()
{
}
