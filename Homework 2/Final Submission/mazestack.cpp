//
//  main.cpp
//  Homework 2
//
//  Created by Michael Wang on 4/26/15.
//  Copyright (c) 2015 Michael Wang. All rights reserved.
//

#include <iostream>
#include <stack>

using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

stack <Coord> coordStack; // make a stack of coordinates
coordStack.push(Coord (sr,sc)); //push the starting cord onto the stack
maze[sr][sc] = 'X'; //label starting cord as X to show it's correct path
while (!coordStack.empty())
{
    int c_r = coordStack.top().r();
    int c_c = coordStack.top().c();
    coordStack.pop();               //pop off the coordinate
    if (c_r == er && c_c == ec)     //check whether the current point is ending or not
        return true;
    
    if (maze[c_r-1] [c_c] == '.')   //check whether the point in the north is the path
    {
        coordStack.push(Coord(c_r-1, c_c));
        maze[c_r-1][c_c] = 'X';
    }
    
    if (maze[c_r][c_c+1] == '.')    // check whether the point in the east is in the path
    {
        coordStack.push(Coord(c_r, c_c+1));
        maze[c_r][c_c+1] = 'X';
    }
    
    if (maze[c_r+1][c_c] == '.')    // check whether the point in the south is in the path
    {
        coordStack.push(Coord(c_r+1, c_c));
        maze[c_r+1][c_c] = 'X';
    }
    
    if (maze[c_r][c_c+1] == '.')
    {
        coordStack.push(Coord(c_r, c_c+1));
        maze [c_r][c_c+1] = 'X';
    }
    
}
    
    return false;
    
}

int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X'},
        { 'X','.','.','.','.','.','.','.','.','X'},
        { 'X','X','.','X','.','X','X','X','X','X'},
        { 'X','.','.','X','.','X','.','.','.','X'},
        { 'X','.','.','X','.','.','.','X','.','X'},
        { 'X','X','X','X','.','X','X','X','.','X'},
        { 'X','.','X','.','.','.','.','X','X','X'},
        { 'X','.','.','X','X','.','X','X','.','X'},
        { 'X','.','.','.','X','.','.','.','.','X'},
        { 'X','X','X','X','X','X','X','X','X','X'}
    };
    
    if (pathExists(maze, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
