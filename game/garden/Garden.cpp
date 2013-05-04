#include "Garden.hpp"
#include "Pixel.hpp"
#include "GardenEvent.hpp"
#include "GardenSelector.hpp"

#include "../consts.hpp"
#include "../Game.hpp"
Garden::Garden(Game* game)
{
    _pixels = std::vector<std::vector<Pixel*> >(gameconsts::MAX_GARDEN_ROW,std::vector<Pixel*>(gameconsts::MAX_GARDEN_COL));
    this->_game = game;
    for(int r = 0 ; r < _pixels.size () ; r++)
    {
        for(int c = 0 ; c < _pixels.size() ; c++)
        {
            _pixels[r][c] = new Pixel(game,this,r,c);
        }
    }
    selector = new GardenSelector(game,displayconsts::PIXEL_SIZE,displayconsts::PIXEL_SIZE,2,5);
}

Garden::~Garden()
{
    for(int r = 0 ; r < _pixels.size() ; r++)
    {
        for(int c = 0 ; c < _pixels[r].size() ; c++)
        {
            delete _pixels[r][c];
        }
    }
    delete selector;
}

bool Garden::inRange(int row, int col)
{
    if(row < 0 || row >= gameconsts::MAX_GARDEN_ROW || col < 0 || col >= gameconsts::MAX_GARDEN_COL)
    {
        return false;
    }
    return true;
}

Pixel* Garden::pixelAt(int row, int col)
{
    if(!inRange(row,col))
    {
        return NULL;
    }
    return _pixels[row][col];
}

std::vector<GardenEvent*> Garden::doOneTurn()
{
    std::vector<Seed*> newSeeds = std::vector<Seed*>(0);
    // iterate each pixel, and ask each pixel to grow.
    for(int r = 0 ; r < gameconsts::MAX_GARDEN_ROW ; r++)
    {
        for(int c = 0 ; c < gameconsts::MAX_GARDEN_COL ; c++)
        {
            _pixels[r][c]->updateOneTurn(newSeeds);
        }
    }
    for(int r = 0 ; r < gameconsts::MAX_GARDEN_ROW ; r++)
    {
        for(int c = 0 ; c < gameconsts::MAX_GARDEN_COL ; c++)
        {
            _pixels[r][c]->updateState(newSeeds);
        }
    }
    std::vector<GardenEvent*> events = std::vector<GardenEvent*>(0);
    return events;    
}


void Garden::update(sf::Time &delta)
{

}

void Garden::draw(sf::RenderWindow* window, sf::Time &delta,zf::Mouse* mouse)
{
    sf::Vector2i pixelPos = mouse->getPosition(*window);
    sf::Vector2f mousePos = window->mapPixelToCoords(pixelPos);
    Grid selectedGrid = Grid::toGrid(mousePos.x,mousePos.y,displayconsts::PIXEL_SIZE,displayconsts::PIXEL_SPACING);
    for(int r = 0 ; r < gameconsts::MAX_GARDEN_ROW ; r ++)
    {
        for(int c = 0 ; c < gameconsts::MAX_GARDEN_COL ; c++)
        {
            _pixels[r][c] -> draw(window,delta);
        }
    }
    if(inRange(selectedGrid.row,selectedGrid.col))
    {
        selector->draw(window,delta,selectedGrid.col*(displayconsts::PIXEL_SIZE+displayconsts::PIXEL_SPACING), selectedGrid.row*(displayconsts::PIXEL_SIZE+displayconsts::PIXEL_SPACING));
    }
}
