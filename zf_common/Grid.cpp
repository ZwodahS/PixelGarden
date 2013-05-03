#include "Grid.h"

Grid::Grid()
{
    this->row = 0;
    this->col = 0;
}

Grid::Grid(int row, int col)
{
    this->row = row;
    this->col = col;
}

Grid::~Grid()
{
}

bool operator==(const Grid &lhs, const Grid &rhs)
{
    if(lhs.row == rhs.row && lhs.col == rhs.col)
    {
        return true;
    }    
    return false;
}

bool operator!=(const Grid &lhs, const Grid &rhs)
{
    return !(operator==(lhs,rhs));
}