#ifndef _GAME_GARDEN_PIXEL_H_
#define _GAME_GARDEN_PIXEL_H_
#include "ParentContribution.hpp"

#include "../PixelColor.hpp"
#include "../g_seeds.hpp"
#include "../../zf_common/Grid.hpp"
#include <SFML/Graphics.hpp>


#include <vector>
namespace pixelstate
{
    enum PixelState
    {
        DEAD, // DEAD PIXEL ? trololol..
        SEED, // a seed is planted in this pixel.
        GROWING, // a seed or multiple seeds are growing into this pixel.
        MATURED_WAITING, // waiting for parent to mature.
        MATURED, // this pixel is matured. Nothing grows here any more. 
        
        DECAYING, // this pixel is decaying.
    };
}

namespace plantstate
{
    enum PlantState
    {
        NA,
        GROWING,
        MATURED,
        DECAYING,
    };
}

class Game;
class Garden;
class SeedManager;
class Pixel
{
    public:
        Pixel(Game* game,Garden* garden,SeedManager* seedM,int row ,int col);
        ~Pixel();

        pixelstate::PixelState getState();

        void updateOneTurn(std::vector<Seed*> &newSeeds);
        void updateState(std::vector<Seed*> &newSeeds);
        
        
        // tell this pixel that you want to grow.
        // return NULL if this pixel cannot be grown into.
        ParentContribution* beginGrowth(Seed* seed);
        void contributeColor(PixelColor color);        

        bool plantSeed(Seed* seed);
        void dies(); // kill this pixel.
    
        void update(sf::Time &delta);
        void draw(sf::RenderWindow* window, sf::Time &delta);
        Pixel* findNextPixelToGrow();

        bool canPlant(Seed* seed);
        bool hasParentSeed(Seed* seed);
        Grid _location;
    protected:
        Game* _game;
        Garden* _garden;
        SeedManager* _seedM;
        pixelstate::PixelState _state;
        PixelColor _displayedColor;
        PixelColor _accumulatedColor; // this is the accumulated color, which is different from the actual color.
        int _currentStateDuration; // for counting how long the plant has been in it's current state.

    /// DRAW STUFFS ///
        sf::Sprite _mainPixel;


    ////// for state seed. //////
        Seed* _seed; // the seed that is planted here. only valid if state = SEED.    
        std::vector<Pixel*> _leafPixels; // the pixel that this seeds has grown into.
        std::vector<ParentContribution*> _leafContributions;
        plantstate::PlantState _plantState; 

    ////// growing state. ///////
        std::vector<ParentContribution*> _parentsContributions; // stores the parent's contribution.
    ////// matured state / decay state //////
        Seed* _maturedSeed; // for the storing the matured seed. This will be the same as the parent if there is no cross breeding.
            /* used when 2 of the same seed grows into the same spot or when another plant "boost" this pixel. 
             * This allow the player to increase the chance of seed. */
        int seedBonus; 
        bool mutated;
        void setPlantMatured();
        void changeState(pixelstate::PixelState state);
        
        void clearSeedState();
        void clearGrowingState();
        void clearMaturedState();
        
        Seed* crossBreed();

        void updateDeadTurn(std::vector<Seed*> &newSeeds);
        void updateSeedTurn(std::vector<Seed*> &newSeeds);
        void updateGrowingTurn(std::vector<Seed*> &newSeeds);
        void updateMaturedWaitingTurn(std::vector<Seed*> &newSeeds);
        void updateMaturedTurn(std::vector<Seed*> &newSeeds);
        void updateDecayingTurn(std::vector<Seed*> &newSeeds);

        void updateDeadState(std::vector<Seed*> &newSeeds);
        void updateSeedState(std::vector<Seed*> &newSeeds);
        void updateGrowingState(std::vector<Seed*> &newSeeds);
        void updateMaturedWaitingState(std::vector<Seed*> &newSeeds);
        void updateMaturedState(std::vector<Seed*> &newSeeds);
        void updateDecayingState(std::vector<Seed*> &newSeeds);

        int getSeedGrowthTurn();
        int getGrowthSegments();
        int getMaturedDuration();
        int getDecayDuration();
};
#endif
