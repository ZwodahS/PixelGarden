#include "Pixel.hpp"
#include "../SeedManager.hpp"
#include "../g_seeds.hpp"
#include "../Game.hpp"
#include "../consts.hpp"


Pixel::Pixel(Game* game,Garden* garden,SeedManager* seedM,int row ,int col)
{
    this->_game = game;
    this->_garden = garden;
    this->_seedM = seedM;
    this->_state = pixelstate::DEAD;
    this->_location = Grid(row,col);
    this->_accumulatedColor = PixelColor(0,0,0);
    this->_displayedColor = PixelColor(0,0,0);
    clearSeedState();
    clearGrowingState();
    clearMaturedState();
    _mainPixel = _game->_assets.pixel.pixelTexture.createSprite();
    _mainPixel.setPosition(
            displayconsts::PIXEL_SPACING + (col * (displayconsts::PIXEL_SIZE + displayconsts::PIXEL_SPACING)), 
            displayconsts::PIXEL_SPACING + (row * (displayconsts::PIXEL_SIZE + displayconsts::PIXEL_SPACING))
            );
}
Pixel::~Pixel()
{
    for(int i = 0 ; i < _parentsContributions.size() ; i++)
    {
        delete _parentsContributions[i];
    }
}

Seed* Pixel::getParentSeed()
{
    return _seed;
}
bool Pixel::plantSeed(Seed* seed)
{
    if(this->_state != pixelstate::DEAD)
    {
        return false;
    }
    _seed = seed;
    _maturedSeed = seed;
    this->_accumulatedColor = _seed->_color;
    this->_displayedColor = this->_accumulatedColor;
    this->_state = pixelstate::SEED;
    this->_plantState = plantstate::GROWING;
    this->_seedSprite = _game->_assets.pixel.seed.createSprite();
    this->_seedSprite.setPosition(
            8+displayconsts::PIXEL_SPACING + (_location.col * (displayconsts::PIXEL_SIZE + displayconsts::PIXEL_SPACING)), 
            8+displayconsts::PIXEL_SPACING + (_location.row * (displayconsts::PIXEL_SIZE + displayconsts::PIXEL_SPACING))
            );
    this->_seedSprite.setScale(0.5f,0.5f);
    this->_seedSprite.setColor(sf::Color(50,50,50));
    return true;
}

void Pixel::dies()
{
    clearSeedState();
    clearGrowingState();
    clearMaturedState();
    this->_state = pixelstate::DEAD;
}

void Pixel::clearSeedState()
{
    this->_seed = NULL;
    this->_leafPixels = std::vector<Pixel*>(0);
    this->_leafContributions = std::vector<ParentContribution*>(0);
    this->_plantState = plantstate::NA;
    this->_currentStateDuration = 0;
    this->_accumulatedColor = PixelColor(0,0,0);
    this->_displayedColor = PixelColor(0,0,0);
}

void Pixel::clearGrowingState()
{
    for(int i = 0 ; i < _parentsContributions.size(); i++)
    {
        delete _parentsContributions[i];
    }
    this->_parentsContributions = std::vector<ParentContribution*>(0);
}

void Pixel::clearMaturedState()
{
    this->_maturedSeed = NULL;
    this->seedBonus = 0;
    this->mutated = false;
}

void Pixel::updateOneTurn(std::vector<Seed*> &newSeeds)
{
    switch(_state)
    {
        case pixelstate::DEAD:
            updateDeadTurn(newSeeds);
            break;
        case pixelstate::SEED:
            updateSeedTurn(newSeeds);
            break;
        case pixelstate::GROWING:
            updateGrowingTurn(newSeeds);
            break;
        case pixelstate::MATURED_WAITING:
            updateMaturedWaitingTurn(newSeeds);
            break;
        case pixelstate::MATURED:
            updateMaturedTurn(newSeeds);
            break;
        case pixelstate::DECAYING:
            updateDecayingTurn(newSeeds);
            break;
        default:
            break;
    }
}

void Pixel::updateDeadTurn(std::vector<Seed*> &newSeeds)
{
    // if I want to add buffs to certain pixel , this is where I can put it.
}

void Pixel::updateSeedTurn(std::vector<Seed*> &newSeeds)
{
    if(_plantState == plantstate::GROWING)
    {
        // if the size is 0 or if the last pixel is done,
        // check if we need to 
        if(_leafContributions.size() == 0 || _leafContributions[_leafContributions.size()-1]->seedDone)
        {
            // find a new spot to grow into.
            // if can't find, then this plant is matured.
            Pixel* target =  findNextPixelToGrow();
            if(target == 0)
            {
                setPlantMatured();
            }
            else
            {
                ParentContribution* pg = target->beginGrowth(_seed);
                if(pg == 0)
                {
                    setPlantMatured();
                }
                else
                {
                    _leafPixels.push_back(target);
                    _leafContributions.push_back(pg);
                }
            }
        }

        if(_plantState != plantstate::MATURED) // make sure some leaf is found.
        {
            _leafContributions[_leafContributions.size() - 1]->contributionValue++;
            if(_leafContributions[_leafContributions.size() -1]->contributionValue >= getSeedGrowthTurn())
            {
                _leafContributions[_leafContributions.size() -1]->seedDone = true;
            }
            _leafPixels[_leafPixels.size() -1]->contributeColor(PixelColor((_seed->_color)/getSeedGrowthTurn()));

            // growing state will change to matured when all plants is done.
            if(_leafContributions.back()->seedDone)
            {
                // if seed is done for this pixel, then check if the total growth segment is reached.
                if(_leafPixels.size() >= getGrowthSegments())
                {
                    setPlantMatured();
                }
            }
        }
    }
    else if(_plantState == plantstate::MATURED)
    {
        _currentStateDuration++;
    }
    else if(_plantState == plantstate::DECAYING)
    {
        _currentStateDuration++;
    }
}

int Pixel::getSeedGrowthTurn()
{
    return _seed == 0 ? 0 : _seed->_effectiveAttributes.growthTurns;
}

void Pixel::updateGrowingTurn(std::vector<Seed*> &newSeeds)
{
    // do nothing, just let parent pixel do the job.
}

void Pixel::updateMaturedWaitingTurn(std::vector<Seed*> &newSeeds)
{
    // do nothing, just wait for parent.
}

void Pixel::updateMaturedTurn(std::vector<Seed*> &newSeeds)
{
    _currentStateDuration++;
}

void Pixel::updateDecayingTurn(std::vector<Seed*> &newSeeds)
{
    _currentStateDuration++;
}

void Pixel::updateState(std::vector<Seed*> &newSeeds)
{
    switch(_state)
    {
        case pixelstate::DEAD:
            updateDeadState(newSeeds);
            break;
        case pixelstate::SEED:
            updateSeedState(newSeeds);
            break;
        case pixelstate::GROWING:
            updateGrowingState(newSeeds);
            break;
        case pixelstate::MATURED_WAITING:
            updateMaturedWaitingState(newSeeds);
            break;
        case pixelstate::MATURED:
            updateMaturedState(newSeeds);
            break;
        case pixelstate::DECAYING:
            updateDecayingState(newSeeds);
            break;
        default:
            break;
    }
}

void Pixel::updateDeadState(std::vector<Seed*> &newSeeds)
{
    // if I want to add buffs to certain pixel , this is where I can put it.
}

void Pixel::updateSeedState(std::vector<Seed*> &newSeeds)
{
    if(_plantState == plantstate::GROWING)
    {
        // nothing to do here. Just let the do one turn handles the state change.
        // this is because any state change here has to be done in the turn before the leaf pixel get notify. 
        // If not, some pixel may get it later than others.
    }    
    else if(_plantState == plantstate::MATURED)
    {
        if(_currentStateDuration >= getMaturedDuration())
        {
            _plantState = plantstate::DECAYING;
            _currentStateDuration = 0 ;
        }
    }
    else if(_plantState == plantstate::DECAYING)
    {
        if(_currentStateDuration >= getDecayDuration())
        {
            dies();
        }
    }
}

void Pixel::updateGrowingState(std::vector<Seed*> &newSeeds)
{
    bool matured = true;
    bool hasDifferent = false;
    Seed* seed = _parentsContributions.size() > 0 ? _parentsContributions[0]->parent : 0;
    // checks. if not matured then do nothing else.
    for(int i = 0 ; i < _parentsContributions.size() ; i++)
    {
        // if there is a parent still contributing to the pixel then do nothing.
        if(!(_parentsContributions[i]->seedDone))
        {
            matured = false;
            break;
        }
        if(!hasDifferent && seed->_id != _parentsContributions[i]->parent->_id)
        {
            hasDifferent = true;
        }
    }
    if(matured)
    {
        // + check if all the seeds are the same type.
        //     + if all the seeds are the same type, 
        //           + the final seed will be the same as the seed.
        //           + the seed chance will be boosted.
        //     + if there are different kind of seeds
        //           + calculate a cross breed.
        if(hasDifferent)
        {
            _maturedSeed = crossBreed();
            seedBonus += gameconsts::BREED_SEED_BONUS;
        }
        else
        {
            _maturedSeed = seed; 
            seedBonus += _parentsContributions.size() * gameconsts::SAME_SEED_BONUS;
        }
        changeState(pixelstate::MATURED_WAITING);
        // do an update to matured waiting state as well, since the last pixel might turn out one turn later than this.
        updateMaturedWaitingState(newSeeds);
    }
}

void Pixel::updateMaturedWaitingState(std::vector<Seed*> &newSeeds)
{
    bool allParentMatured = true;
    // do a check if all parents are matured.
    for(int i = 0 ; i < _parentsContributions.size(); i++)
    {
        // if there is a parent that is not matured.
        if(!(_parentsContributions[i]->parentDone))
        {
            allParentMatured = false;
            break;
        }
    }
    if(allParentMatured)
    {
        changeState(pixelstate::MATURED);
    }
}

void Pixel::updateMaturedState(std::vector<Seed*> &newSeeds)
{
    if(_currentStateDuration >= getMaturedDuration())
    {
        changeState(pixelstate::DECAYING);
    }
}

void Pixel::updateDecayingState(std::vector<Seed*> &newSeeds)
{
    if(_currentStateDuration >= getDecayDuration())
    {
        dies();
    }
}

Seed* Pixel::crossBreed()
{
    Seed* seed = _seedM->crossBreed(_parentsContributions);
    return seed;
}


int Pixel::getGrowthSegments()
{
    return _seed == 0 ? 0 : _seed->_effectiveAttributes.growthSegments;
}

int Pixel::getMaturedDuration()
{
    return _maturedSeed == 0 ? 0 : _maturedSeed->_effectiveAttributes.maturedDuration;
}

int Pixel::getDecayDuration()
{
    return _maturedSeed == 0 ? 0 : _maturedSeed->_effectiveAttributes.decayTurns;
}

void Pixel::changeState(pixelstate::PixelState state)
{
    _state = state;
    _currentStateDuration = 0;
}

void Pixel::setPlantMatured()
{
    this->_plantState = plantstate::MATURED;
    this->_currentStateDuration = 0;
    for(int i = 0 ; i < _leafContributions.size() ; i++)
    {
        _leafContributions[i]->parentDone = true;
    }
}

ParentContribution* Pixel::beginGrowth(Seed* seed)
{
    if(_state != pixelstate::DEAD && _state != pixelstate::GROWING)
    {
        return 0;
    }
    ParentContribution* pc = new ParentContribution(seed);
    _parentsContributions.push_back(pc);
    _state = pixelstate::GROWING;
    return pc;
}

void Pixel::contributeColor(PixelColor color)
{
    this->_accumulatedColor += color;
    this->_displayedColor = _accumulatedColor;
    this->_displayedColor.normalizeTo(displayconsts::NORMALIZED_TARGET_VALUE);
}

void Pixel::update(sf::Time &delta)
{

}

void Pixel::draw(sf::RenderWindow* window, sf::Time &delta)
{
    if(_state == pixelstate::DEAD)
    {
        _mainPixel.setColor(sf::Color(20,20,20,255));
    }
    else
    {
        if(_state == pixelstate::SEED && _plantState == plantstate::DECAYING)
        {
            _seedSprite.setColor(sf::Color(50,50,50,100));
            _mainPixel.setColor(sf::Color(_displayedColor.r,_displayedColor.g,_displayedColor.b,100));
        }
        else if(_state == pixelstate::DECAYING)
        {
            _mainPixel.setColor(sf::Color(_displayedColor.r,_displayedColor.g,_displayedColor.b,100));
        }
        else
        {
            _mainPixel.setColor(sf::Color(_displayedColor.r,_displayedColor.g,_displayedColor.b,255));
        }
    }
    window->draw(_mainPixel);
    if(_state == pixelstate::SEED)
    {
        window->draw(_seedSprite);
    }
}

bool Pixel::canPlant(Seed* seed)
{
    if(_state == pixelstate::DEAD || _state == pixelstate::GROWING)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

bool Pixel::hasParentSeed(Seed* seed)
{
    if(this->_state == pixelstate::SEED && _seed == seed)
    {
        return true;
    }
    for(int i = 0 ; i < _parentsContributions.size() ; i++)
    {
        if(_parentsContributions[i]->parent == seed) // memory address test ? should/must be the same.
        {
            return true;
        }
    }
    return false;
}

Pixel* Pixel::findNextPixelToGrow()
{
    if(_seed == 0)
    {
        return 0;
    }
    if(_seed->_segments.size() <= _leafPixels.size())
    {
        return 0;
    }
    GrowthSegment gs = _seed->_segments[_leafPixels.size()];
    Grid next;
    Grid direction;
    switch(gs)
    {
        case GROW_SOURCE_NORTH:
            direction = Grid(-1,0);
            next = _location + direction;
            break;
        case GROW_SOURCE_SOUTH:
            direction = Grid(1,0);
            next = _location + direction;
            break;
        case GROW_SOURCE_EAST:
            direction = Grid(0,1);
            next = _location + direction;
            break;
        case GROW_SOURCE_WEST:
            direction = Grid(0,-1);
            next = _location + direction;
            break;
        case GROW_LAST_NORTH:
            direction = Grid(-1,0);
            next = (_leafPixels.size() == 0 ? _location : _leafPixels.back()->_location) + direction;
            break;
        case GROW_LAST_SOUTH:
            direction = Grid(1,0);
            next = (_leafPixels.size() == 0 ? _location : _leafPixels.back()->_location) + direction;
            break;
        case GROW_LAST_EAST:
            direction = Grid(0,1);
            next = (_leafPixels.size() == 0 ? _location : _leafPixels.back()->_location) + direction;
            break;
        case GROW_LAST_WEST:
            direction = Grid(0,-1);
            next = (_leafPixels.size() == 0 ? _location : _leafPixels.back()->_location) + direction;
            break;
    }
    Pixel* targetPixel = 0;
    Pixel* temp = 0;
    while(targetPixel == 0)
    {
        temp = _garden->pixelAt(next.row, next.col); 
        if(temp == 0)
        {
            break; // the north is out of range.
        }
        if(temp->canPlant(_seed)) // if cannot plant , means that the pixel has matured.
        {
            targetPixel = temp;
            break;
        }
        else if(isPartOfUs(temp)) // if next pixel is matured, check if it is our own. if it is , search above it
        {
            next += direction;
        }
        else // next pixel is a matured pixel but is not our own. then we can't grow any more.
        {
            break;
        }
    }
    return targetPixel;
}

bool Pixel::isPartOfUs(Pixel* pixel)
{
    if(pixel == this)
    {
        return true;
    }
    for(int i = 0 ; i < _leafPixels.size() ; i++)
    {
        if(pixel == _leafPixels[i])
        {
            return true;
        }
    }
    return false;
}
