#include "PGS.hpp"

#include <iostream>
#define GENECOUNT 58
#define BLOCKSIZE 15
PGS::PGS(Game* game,Seed* seed,sf::Vector2f drawOffset)
{
    this->_seed = seed;
    this->_game = game;
    
    //set up all the blocks
    gblocks = std::vector<sf::RectangleShape>() ;
    for(int i = 0 ; i < GENECOUNT ; i++)
    {
        gblocks.push_back(sf::RectangleShape(sf::Vector2f(BLOCKSIZE,BLOCKSIZE)));
        gblocks[i].setFillColor(sf::Color(0,0,0,255));
        gblocks[i].setOutlineThickness(1);
        gblocks[i].setOutlineColor(sf::Color(255,255,255,255));
    }
    for(int i = 0 ; i < 17 ; i++)
    {
        gblocks[i].setPosition(drawOffset + sf::Vector2f(BLOCKSIZE+(i*BLOCKSIZE),0));
    }
    for(int i = 17,x =0; i < 35 ; i++,x++)
    {
        gblocks[i].setPosition(drawOffset + sf::Vector2f(x*BLOCKSIZE,4*BLOCKSIZE));
    }
    for(int i = 35,x=0 ; i < 52 ; i++,x++)
    {
        gblocks[i].setPosition(drawOffset + sf::Vector2f(x*BLOCKSIZE,8*BLOCKSIZE));
    }
    gblocks[52].setPosition(drawOffset + sf::Vector2f(17*BLOCKSIZE,1*BLOCKSIZE));
    gblocks[53].setPosition(drawOffset + sf::Vector2f(17*BLOCKSIZE,2*BLOCKSIZE));
    gblocks[54].setPosition(drawOffset + sf::Vector2f(17*BLOCKSIZE,3*BLOCKSIZE));
    gblocks[55].setPosition(drawOffset + sf::Vector2f(0*BLOCKSIZE,5*BLOCKSIZE));
    gblocks[56].setPosition(drawOffset + sf::Vector2f(0*BLOCKSIZE,6*BLOCKSIZE));
    gblocks[57].setPosition(drawOffset + sf::Vector2f(0*BLOCKSIZE,7*BLOCKSIZE));
    // get all the expressed gene of the seed
    for(int i = 0 ; i < _seed->_unexpressedGenes.size() ; i++)
    {
        int id = _game->_pgsSequence[_seed->_unexpressedGenes[i]->id]; 
        gblocks[id].setFillColor(id%2 ==0 ? sf::Color(80,80,80,255) : sf::Color(40,40,40,255));
    }
    for(int i = 0 ; i < _seed->_expressedGenes.size() ; i++)
    {
        int id = _game->_pgsSequence[_seed->_expressedGenes[i]->id]; 
        sf::Color color = _game->_pgsColor[id];
        gblocks[id].setFillColor(sf::Color(color.r,color.g,color.b,255));
    }
    std::cout << _seed->_unexpressedGenes.size() << std::endl;
    std::cout << _seed->_expressedGenes.size() << std::endl;
}

PGS::~PGS()
{

}

void PGS::draw(sf::RenderWindow* window, sf::Time delta)
{
    for(int i = 0; i < gblocks.size() ; i++)
    {
        window->draw(gblocks[i]);
    }
}
