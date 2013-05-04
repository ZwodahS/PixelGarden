#ifndef _GAME_SEEDS_SEED_H_
#define _GAME_SEEDS_SEED_H_

#include "Gene.hpp"
#include "../PixelColor.hpp"
#include "SeedAttribute.hpp"
#include "GrowthSegment.hpp"
#include <vector>
class Seed
{
    public:
        Seed(int seedId,std::vector<Gene*> expressed, std::vector<Gene*> unexpressed,PixelColor color,SeedAttribute baseAttributes,std::vector<GrowthSegment> segments);
        ~Seed();
        
        int _id; // for seed id , best way to check 2 seed.

        std::vector<Gene*> _expressedGenes;
        std::vector<Gene*> _unexpressedGenes;
        std::vector<GrowthSegment> _segments;    
        PixelColor _color;
        SeedAttribute _baseAttributes; // base attributes 
        SeedAttribute _bonusAttributes; // bonus attributes from all the genes
        SeedAttribute _effectiveAttributes; // the effective attributes : base attributes + bonus attributes
};
#endif
