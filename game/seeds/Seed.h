#ifndef _GAME_SEEDS_SEED_H_
#define _GAME_SEEDS_SEED_H_

#include "Gene.h"
#include "../PixelColor.h"
#include "SeedAttribute.h"
#include "GrowthSegment.h"
#include <vector>
class Seed
{
    public:
        Seed(int seedId,std::vector<Gene*> expressed, std::vector<Gene*> unexpressed,PixelColor color,SeedAttribute attributes,std::vector<GrowthSegment> segments);
        ~Seed();
        
        int _id; // for seed id , best way to check 2 seed.

        std::vector<Gene*> _expressedGenes;
        std::vector<Gene*> _unexpressedGenes;
        std::vector<GrowthSegment> _segments;    
        PixelColor _color;
        SeedAttribute _attributes;
};
#endif
