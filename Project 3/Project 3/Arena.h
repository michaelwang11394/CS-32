//
//  Arena.h
//  Project 3
//
//  Created by Michael Wang on 5/24/15.
//  Copyright (c) 2015 Michael Wang. All rights reserved.
//

#ifndef __Project_3__Arena__
#define __Project_3__Arena__

#include <stdio.h>
#include "utilities.h"
#include <vector>
#include "Actor.h"
#include "Objects.h"

class Player;
class Items;
class Actor;

class Arena
{
public:
    // Constructor/destructor
    Arena();
    Arena(int lvl, Player* prevPlayer);
    ~Arena();
    
    // Accessors
    int     rows() const { return m_rows; }
    int     cols() const { return m_cols; }
    int     plrows() const { return plrow; }
    int     plcols() const { return plcol; }
    Player* player() const { return m_player; }
    Actor*	getMonster(int r, int c) const;
    char	nextSpot(int r, int c) const { return grid[r][c]; }
    void    display();
    
    // Mutators
    bool   addPlayer();
    bool    rooms(int &row, int &col);
    void    design();
    void    randomSpot(int &a, int &b);
    bool     okayMove(int r, int c);
    bool	checkWall(int r, int c);
    bool     nextLvl();
    bool     pickUp(std::string& str);
    bool	addItem(int r, int c, int a);
    bool	addMonster(int a);
    bool	checkDeadMonsters();
    bool	checkItems(int r, int c);
    bool	moveMonsters(std::string &str);
    
private:
    int     m_rows, m_cols;
    int		m_rooms, m_count; //room counter
    int     m_level;
    int		plrow, plcol; // coordinates of player
    int		endrow, endcol; // coordinates of the ending
    
    Items m_idol;
    std::vector<Items*> m_items; // items on map
    std::vector<Actor*> m_monsters;
    
    Player*       m_player;
    int			numOfItems;
    char		grid[MAXROWS][MAXCOLS];
};


//class Arena
//{
//public:
//    Arena();
//   
//private:
//    const int MAXROW = 18;
//    const int MAXCOL = 70;
//    
//    
//};





#endif /* defined(__Project_3__Arena__) */



