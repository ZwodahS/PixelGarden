#include "Seed.hpp"

Seed::Seed(int seedId,std::vector<Gene*> expressed, std::vector<Gene*> unexpressed, PixelColor color, SeedAttribute baseAttributes, std::vector<GrowthSegment> segments)
{
    this->_id = seedId;
    this->_color = color;
    this->_baseAttributes = baseAttributes;
    _expressedGenes = std::vector<Gene*>(0);
    for(std::vector<Gene*>::iterator it = expressed.begin() ; it != expressed.end() ; it++)
    {
        _expressedGenes.push_back(*it);
        _bonusAttributes+=(*it)->attributeContribution;
    }
    _effectiveAttributes = _baseAttributes + _bonusAttributes;
    _effectiveAttributes.setToMinMax();
        
    _unexpressedGenes = std::vector<Gene*>(0);
    for(std::vector<Gene*>::iterator it = unexpressed.begin() ; it != unexpressed.end() ; it++)
    {
        _unexpressedGenes.push_back(*it);
    }
    _segments = std::vector<GrowthSegment>(0);
    for(std::vector<GrowthSegment>::iterator it = segments.begin() ; it != segments.end() ; it++)
    {
        _segments.push_back(*it);
    }
}

Seed::Seed(int seedId,std::vector<Gene*> expressed, std::vector<Gene*> unexpressed, PixelColor color, SeedAttribute baseAttributes)
{
    this->_id = seedId;
    this->_color = color;
    this->_baseAttributes = baseAttributes;
    _expressedGenes = std::vector<Gene*>(0);
    for(std::vector<Gene*>::iterator it = expressed.begin() ; it != expressed.end() ; it++)
    {
        _expressedGenes.push_back(*it);
        _bonusAttributes+=(*it)->attributeContribution;
    }
    _effectiveAttributes = _baseAttributes + _bonusAttributes;
    _effectiveAttributes.setToMinMax();
        
    _unexpressedGenes = std::vector<Gene*>(0);
    for(std::vector<Gene*>::iterator it = unexpressed.begin() ; it != unexpressed.end() ; it++)
    {
        _unexpressedGenes.push_back(*it);
    }
    _segments = std::vector<GrowthSegment>(0);
}

Seed::~Seed()
{
}

void Seed::setSegments(std::vector<GrowthSegment> segments)
{
    for(std::vector<GrowthSegment>::iterator it = segments.begin() ; it != segments.end() ; it++)
    {
        _segments.push_back(*it);
    }
}
