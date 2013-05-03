#ifndef _ZF_FRAMEWORK_GRID_H_
#define _ZF_FRAMEWORK_GRID_H_
struct Grid
{
    int row;
    int col;
    Grid();
    Grid(int row, int col);
    ~Grid();

};

bool operator==(const Grid &lhs, const Grid &rhs);
bool operator!=(const Grid &lhs, const Grid &rhs);


#endif
