#include "PGS.hpp"

#include <iostream>
#define GENECOUNT 58
#define BLOCKSIZE 15
PGS::PGS(Game* game,Seed* seed,sf::Vector2f drawOffset)
{
    this->_seed = seed;
    this->_game = game;
    //set up all the blocks
    _gblocks = std::vector<sf::Sprite>() ;
    for(int i = 0 ; i < GENECOUNT ; i++)
    {
        _gblocks.push_back(_game->_assets.pixel.pgs.dark.createSprite());
    }
    for(int i = 0 ; i < 17 ; i++)
    {
        _gblocks[i].setPosition(drawOffset + sf::Vector2f(BLOCKSIZE+(i*BLOCKSIZE),0));
    }
    for(int i = 17,x =0; i < 35 ; i++,x++)
    {
        _gblocks[i].setPosition(drawOffset + sf::Vector2f(x*BLOCKSIZE,4*BLOCKSIZE));
    }
    for(int i = 35,x=0 ; i < 52 ; i++,x++)
    {
        _gblocks[i].setPosition(drawOffset + sf::Vector2f(x*BLOCKSIZE,8*BLOCKSIZE));
    }
    _gblocks[52].setPosition(drawOffset + sf::Vector2f(17*BLOCKSIZE,1*BLOCKSIZE));
    _gblocks[53].setPosition(drawOffset + sf::Vector2f(17*BLOCKSIZE,2*BLOCKSIZE));
    _gblocks[54].setPosition(drawOffset + sf::Vector2f(17*BLOCKSIZE,3*BLOCKSIZE));
    _gblocks[55].setPosition(drawOffset + sf::Vector2f(0*BLOCKSIZE,5*BLOCKSIZE));
    _gblocks[56].setPosition(drawOffset + sf::Vector2f(0*BLOCKSIZE,6*BLOCKSIZE));
    _gblocks[57].setPosition(drawOffset + sf::Vector2f(0*BLOCKSIZE,7*BLOCKSIZE));
    // get all the expressed gene of the seed
    for(int i = 0 ; i < _seed->_unexpressedGenes.size() ; i++)
    {
        int id = _game->_pgsSequence[_seed->_unexpressedGenes[i]->id]; 
        sf::Sprite s = _game->_assets.pixel.pgs.gray.createSprite();
        _gblocks[id].setTextureRect(s.getTextureRect());
    }
    for(int i = 0 ; i < _seed->_expressedGenes.size() ; i++)
    {
        int id = _game->_pgsSequence[_seed->_expressedGenes[i]->id]; 
        sf::Sprite s = _game->_pgsColor[_game->_pgsSequence[id]]->createSprite();
        _gblocks[id].setTextureRect(s.getTextureRect());
    }
}

PGS::~PGS()
{

}

void PGS::draw(sf::RenderWindow* window, sf::Time delta)
{
    for(int i = 0; i < _gblocks.size() ; i++)
    {
        window->draw(_gblocks[i]);
    }
}
