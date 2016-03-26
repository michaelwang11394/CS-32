//
//  Arena.cpp
//  Project 3
//
//  Created by Michael Wang on 5/24/15.
//  Copyright (c) 2015 Michael Wang. All rights reserved.
//

#include "Arena.h"

//design for first lvl
Arena::Arena()
: m_player(NULL), m_rows(MAXROWS), m_cols(MAXCOLS), m_count(0),
endrow(0), endcol(0), m_level(0)
{
    m_rooms = SIZE+randInt(3);
    
    // Fill the grid with #'s
    for (int r = 0; r < rows(); r++)
        for (int c = 0; c < cols(); c++)
            grid[r][c] = '#';
    
    design();
    
    randomSpot(plrow, plcol);
}

Arena::Arena(int lvl, Player* prevPlayer)
: m_player(prevPlayer), m_rows(MAXROWS), m_cols(MAXCOLS), m_count(0),
endrow(0), endcol(0), m_level(lvl)
{
    //random # of rooms
    m_rooms = SIZE+lvl*(1+randInt(3));
    
    // Fill the grid with #'s
    for (int r = 0; r < rows(); r++)
        for (int c = 0; c < cols(); c++)
            grid[r][c] = '#';
    
    design();
    
    //if there isn't very many rooms, redesign
    while (m_count < m_rooms/2)
    {
        m_count = 0;
        for (int r = 0; r < rows(); r++)
            for (int c = 0; c < cols(); c++)
                grid[r][c] = '#';
        design();
    }
    
    //create a random spot for the initial
    randomSpot(plrow, plcol);
    display();
}

Arena::~Arena()
{
    delete m_player;
    for (int a = 0; a < m_items.size(); a++)
    {
        delete m_items[a];
    }
    for (int a = 0; a < m_monsters.size(); a++)
    {
        delete m_monsters[a];
    }
}

Actor* Levels::getMonster(int r, int c) const
{
    //serach through monster vector and return the monster
    for (int a = 0; a < m_monsters.size(); a++)
        if (r == m_monsters[a]->row() && c == m_monsters[a]->col())
            return m_monsters[a];
    return NULL;
}

bool Arena::rooms(int &row, int&col)
{
    //bool to check if rooms fit
    bool fit = true;
    
    //random spot
    int r = 3+randInt(MAXROWS-2);
    int c = 2+randInt(MAXCOLS-2);
    
    //random dimensions
    int height = 4+(randInt(3)*2); //even number from 4-10
    int width = 8+(randInt(4)*2); // 8-12
    
    row = r;
    col = c;
    
    //make sure it is only #'s and that the box is within the boundaries
    for (int a = (r-height/2)-1; a <= (r+height/2)+1; a++)
        for (int b = (c-width/2)-1; b <= (c+width/2)+1; b++)
            if (a > 0 && b > 0 && a < rows() && b < cols() && grid[a][b] != '#'
                || a < 0 || b < 0 || a > rows()-1 || b > cols()-1)
            {
                fit = false;
                break;
            }
    if (!fit)
        return false;
    else
        //if it fits, set all the box to blanks
        for (int a = (r-height/2); a <= (r+height/2); a++)
            for (int b = (c-width/2); b <= (c+width/2); b++)
                if (a < rows() && b < cols())
                {
                    grid[a][b] = ' ';
                }
    m_count++; // add to how many rooms total
    return true; // successfully added a room
}

void Levels::design()
{
    //making rooms
    //while it doesn't fail 1000 times, and there isn't m_rooms number of rooms
    int a = 0, newr = 0, newc = 0, prevr = 0, prevc = 0;
    bool check = false; // to check if there have been previous rooms
    while (a <= 1000 && m_count != m_rooms)
    {
        if (check)
        {
            prevr = newr;
            prevc = newc;
        }
        
        check = rooms(newr,newc);
        
        //adding corridors
        if (m_count > 1 && check)
        {
            //if prev was below of new
            if (prevr >= newr)
            {
                //if prev was to the right of new
                if (prevc > newc)
                {
                    //go up then left
                    for (int r = prevr; r >= newr; r--)
                        grid[r][prevc] = ' ';
                    for (int b = prevc; b > newc; b--)
                        grid[newr][b] = ' ';
                }
                //else if prev was to the left of new
                else
                {
                    //go up then right
                    for (int r = prevr; r >= newr; r--)
                        grid[r][prevc] = ' ';
                    for (int b = prevc; b < newc; b++)
                        grid[newr][b] = ' ';
                }
            }
            //if prev was above new
            else if (prevr < newr)
            {
                //if prev was to the right of new
                if (prevc > newc)
                {
                    //go left then down
                    for (int b = prevc; b >= newc; b--)
                        grid[prevr][b] = ' ';
                    for (int r = prevr; r < newr; r++)
                        grid[r][newc] = ' ';
                }
                //if prev was to the left of new
                else
                {
                    //go right then down
                    for (int b = prevc; b <= newc; b++)
                        grid[prevr][b] = ' ';
                    for (int r = prevr; r < newr; r++)
                        grid[r][newc] = ' ';
                }
            }
        }
        if (!check)
            a++;
    }
    
    //if there are enugh rooms
    if (m_count >= m_rooms/2)
    {
        //include 2-3 random items
        int startItems = 2+randInt(2);
        for (int a = 0; a < startItems; a++)
        {
            int q = 0, w = 0;
            randomSpot(q, w);
            addItem(q, w, randInt(7));
        }
        
        //add monsters
        //int m = 50 + randInt(5*(m_level+1));
        int m = 2 + randInt(5*(m_level+1));
        for (int a = 0; a < m; a++)
        {
            int mon = 0;
            switch (m_level) {
                case 2:
                    mon = 3;
                    break;
                case 3:
                    mon = 4;
                    break;
                default:
                    mon = 2;
                    break;
            }
            addMonster(randInt(mon));
        }
        
        //include the ending spot
        if (m_level != 4)
            //set a coordinate for end spot
            randomSpot(endrow, endcol);
        else
        {
            //if it's lvl 4, put the idol down
            int q = 0, w = 0;
            randomSpot(q, w);
            Items a(q, w);
            m_idol = a;
        }
    }
}

void Levels::display()
{
    // if it's not a # or a ) or a ?, put blanks there
    for (int o = 0; o < rows(); o++)
        for (int p = 0; p < cols(); p++)
            if (grid[o][p] != '#' && grid[o][p] != ')' && grid[o][p] != '?')
                grid[o][p] = ' ';
    
    //display the items
    for (int a = 0; a < m_items.size(); a++)
        grid[m_items[a]->rows()][m_items[a]->cols()] = m_items[a]->sym();
    
    //display exit or idol
    if (m_level != 4)
        grid[endrow][endcol] = '>';
    else
        grid[m_idol.rows()][m_idol.cols()] = '&';
    
    //display the monsters
    for (int a = 0; a < m_monsters.size(); a++)
        grid[m_monsters[a]->row()][m_monsters[a]->col()] = m_monsters[a]->sym();
    
    // Indicate player's position
    if (m_player != NULL)
    {
        char& gridChar = grid[m_player->row()][m_player->col()];
        if (grid[m_player->row()][m_player->col()] != '#')
            gridChar = m_player->sym();
    }
    
    //output the grid
    for (int o = 0; o < rows(); o++)
    {
        for (int p = 0; p < cols(); p++)
            cout << grid[o][p];
        cout << endl;
    }
    
    //output player status
    cout << "Dungeon Level: " << m_level << " Hit points: " <<
    m_player->hp() << " Armor: " << m_player->arm() << " Strength: " <<
    m_player->str() << " Dexterity: " << m_player->dex() << endl << endl;
}

void Levels::randomSpot(int &a, int &b)
{
    //look for a random open spot
    // or keep looking for one
    while (grid[a][b] != ' ')
    {
        a = 1+randInt(MAXROWS-2);
        b = 1+randInt(MAXCOLS-2);
    }
}

bool Levels::okayMove(int r, int c)
{
    //set the person
    grid[m_player->row()][m_player->col()] = '@';
    
    //check the monsters spots
    for (int a = 0; a < m_monsters.size(); a++)
        if (r == m_monsters[a]->row() &&
            c == m_monsters[a]->col())
            return false;
    
    //make sure the move doesn't hit a wall
    if(grid[r][c] != ' ' && grid[r][c] != ')' &&
       grid[r][c] != '?' && grid[r][c] != '&' &&
       grid[r][c] != '>')
        return false;
    
    return true;
}

bool Levels::checkWall(int r, int c)
{
    //if it's a wall, return true, false otherwise
    if (grid[r][c] == '#')
        return true;
    return false;
}

bool Levels::nextLvl()
{
    //if it's a '>', delete the monsters and items
    if (m_player->row() == endrow && m_player->col() == endcol)
    {
        for (int a = 0; a < m_items.size(); a++)
            delete m_items[a];
        for (int a = 0; a < m_monsters.size(); a++)
            delete m_monsters[a];
        return true;
    }
    return false;
}

bool Levels::pickUp(string &str)
{
    //if you pick up the idol, end game
    if (m_player->row() == m_idol.rows() && m_player->col() == m_idol.cols())
    {
        cout << "You pick up the golden idol" << endl;
        cout << "Congratulations, you won!" << endl;
        cout << "Press q to exit game." << endl;
        char a;
        
        while (a != 'q') {
            a = getCharacter();
            if (a == 'q')
                exit(1);
        }
        return true;
    }
    //if you don't have max items, pick it up
    
    if (m_items.size() <= MAXITEMS)
    {
        for (int a = 0; a < m_items.size(); a++)
        {
            //if your coordinates match with the item's
            if (m_items[a]->rows() == m_player->row()
                && m_items[a]->cols() == m_player->col())
            {
                //output
                str = "You picked up " + m_items[a]->name();
                
                //add to the items and pop from items on map
                m_player->holdItems(m_items[a]);
                m_items[a] = m_items[m_items.size()-1];
                m_items.pop_back();
            }
        }
        return true;
    }
    return false;
}

bool Levels::addPlayer()
{
    //if there's no player, move
    if (m_player != NULL)
    {
        m_player->newSpot(this, plrow, plcol);
        return false;
    }
    m_player = new Player(this, plrow, plcol);
    return true;
}

bool Levels::addItem(int r, int c, int a)
{
    //push items onto the map
    switch (a) {
        case 0:
            m_items.push_back(new Mace(r,c));
            break;
        case 1:
            m_items.push_back(new ShortSword(r,c));
            break;
        case 2:
            m_items.push_back(new LongSword(r,c));
            break;
        case 3:
            m_items.push_back(new Armor(r,c)); // armor scroll
            break;
        case 4:
            m_items.push_back(new Str(r,c)); // str scroll 
            break;
        case 5:
            m_items.push_back(new Health(r,c)); // health scroll
            break;
        case 6:
            m_items.push_back(new Dex(r,c)); // dex scroll
            break;
        case 7:
            m_items.push_back(new Tele(r,c)); // teleport scroll
            break;
        case 8:
            m_items.push_back(new Fangs(r,c)); // fangs
            break;
        case 9:
            m_items.push_back(new Axe(r,c)); // fangs
            break;
            
        default:
            break;
    }
    return true;
}

bool Levels::addMonster(int a)
{
    //randomize a location and push them onto the map
    int q = 0, w = 0;
    randomSpot(q, w);
    switch (a) {
        case 0:
            m_monsters.push_back(new Snakewomen(this, q,w)); // snakewomen
            break;
        case 1:
            m_monsters.push_back(new Goblin(this, q,w)); // goblin
            break;
        case 2:
            m_monsters.push_back(new Bogeyman(this, q,w)); // bogeyman
            break;
        case 3:
            m_monsters.push_back(new Dragon(this, q,w)); // dragon
            break;
        default:
            break;
    }
    return true;
}

bool Levels::checkDeadMonsters()
{
    for (vector<Actor*>::iterator p = m_monsters.begin(); p != m_monsters.end(); p++)
    {
        Actor* ptr = *p;
        if (ptr->isDead())
        {
            //erase the monster if he's dead
            ptr->drop(ptr->row(), ptr->col());
            p = m_monsters.erase(p);
            return true;
        }
    }
    return false;
}

bool Levels::checkItems(int r, int c)
{
    //check to make sure there's no items already there
    for (int a = 0; a < m_items.size(); a++)
    {
        if (m_items[a]->rows() == r
            && m_items[a]->cols() == c)
        {
            //return false if there's an item
            return false;
        }
    }
    // return true if there is no item
    return true;
}

bool Levels::moveMonsters(string &str)
{
    //bool to see if we need to output a message
    bool hit[m_monsters.size()];
    
    for (int a = 0; a < m_monsters.size(); a++)
    {
        //if he's not sleeping, move, otherwise, reduce counter
        if (!m_monsters[a]->isSleep())
            hit[a] = m_monsters[a]->move('p', str);
        m_monsters[a]->changeSleep(-1);
    }
    for (int a = 0; a < m_monsters.size(); a++)
    {
        //if there's at least 1 monster that attacked, output
        if (hit[a] == true)
            return true;
    } 
    return false;
}