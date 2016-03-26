#undef _GLIBCXX_DEBUG
#undef _GLIBCXX_DEBUG_PEDANTIC
#undef _GLIBCXX_FULLY_DYNAMIC_STRING
#define _GLIBCXX_FULLY_DYNAMIC_STRING 1

#include "Levels.h"

#define SIZE 5

//here is the design for the first level
Levels::Levels()
: m_player(NULL), m_rows(MAXROWS), m_cols(MAXCOLS), m_count(0),
endrow(0), endcol(0), mLevels(0)
{
    m_rooms = SIZE+randInt(3);
    
    // Fill the grid with #'s
    for (int r = 0; r < rows(); r++)
        for (int c = 0; c < cols(); c++)
            grid[r][c] = '#';
    
    design();
    
    random_spot(plrow, plcol);
}

Levels::Levels(int lvl, Player* prevPlayer)
: m_player(prevPlayer), m_rows(MAXROWS), m_cols(MAXCOLS), m_count(0),
endrow(0), endcol(0), mLevels(lvl)
{
    //make random rooms
    m_rooms = SIZE+lvl*(1+randInt(3));
    
    // Fill the grid with #'s
    for (int r = 0; r < rows(); r++)
        for (int c = 0; c < cols(); c++)
            grid[r][c] = '#';
    
    design();
    
    //we have to maintain a certain amonut of rooms for the integrity of the game
    while (m_count < m_rooms/2)
    {
        m_count = 0;
        for (int r = 0; r < rows(); r++)
            for (int c = 0; c < cols(); c++)
                grid[r][c] = '#';
        design();
    }
    
    //intitial starting point
    random_spot(plrow, plcol);
    display();
}

Levels::~Levels()
{
    delete m_player;
    for (int a = 0; a < mObjects.size(); a++)
    {
        delete mObjects[a];
    }
    for (int a = 0; a < m_monsters.size(); a++)
    {
        delete m_monsters[a];
    }
}

Actor* Levels::get_monster(int r, int c) const
{
    //returning monsters
    for (int a = 0; a < m_monsters.size(); a++)
        if (r == m_monsters[a]->row() && c == m_monsters[a]->col())
            return m_monsters[a];
    return NULL;
}

bool Levels::rooms(int &row, int&col)
{
    //make sure the dimensions of room stay true
    bool fit = true;
    
    //create a random spot in the room
    int r = 3+randInt(MAXROWS-2);
    int c = 2+randInt(MAXCOLS-2);
    
    //random dimensions
    int height = 4+(randInt(3)*2); //even number from 4-10
    int width = 8+(randInt(4)*2); // 8-12
    
    row = r;
    col = c;
    
    //box needs to be within a certain boundry
    for (int a = (r-height/2)-1; a <= (r+height/2)+1; a++)
        for (int b = (c-width/2)-1; b <= (c+width/2)+1; b++)
            if ((a > 0 && b > 0 && a < rows() && b < cols() && grid[a][b] != '#')
                || a < 0 || b < 0 || a > rows()-1 || b > cols()-1)
            {
                fit = false;
                break;
            }
    if (!fit)
        return false;
    else
        //change # to blanks if the fit
        for (int a = (r-height/2); a <= (r+height/2); a++)
            for (int b = (c-width/2); b <= (c+width/2); b++)
                if (a < rows() && b < cols())
                {
                    grid[a][b] = ' ';
                }
    m_count++;
    return true; // successfully added a room
}

void Levels::design()
{
    //make rooms
    
    int a = 0, newr = 0, newc = 0, prevr = 0, prevc = 0;
    //see if there were room made before
    bool check = false;
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
            //new corridor
            if (prevr >= newr)
            {
                //right of the corridor
                if (prevc > newc)
                {
                    //left etc
                    for (int r = prevr; r >= newr; r--)
                        grid[r][prevc] = ' ';
                    for (int b = prevc; b > newc; b--)
                        grid[newr][b] = ' ';
                }
                //left
                else
                {
                    //right
                    for (int r = prevr; r >= newr; r--)
                        grid[r][prevc] = ' ';
                    for (int b = prevc; b < newc; b++)
                        grid[newr][b] = ' ';
                }
            }
            //above new
            else if (prevr < newr)
            {
                //right of new
                if (prevc > newc)
                {
                    //left and down
                    for (int b = prevc; b >= newc; b--)
                        grid[prevr][b] = ' ';
                    for (int r = prevr; r < newr; r++)
                        grid[r][newc] = ' ';
                }
                //previous left of new
                else
                {
                    //right down
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
    
    
    if (m_count >= m_rooms/2)
    {
        //placement of random objects
        int startObjects = 2+randInt(2);
        for (int a = 0; a < startObjects; a++)
        {
            int q = 0, w = 0;
            random_spot(q, w);
            add_item(q, w, randInt(7));
        }
        
        //add monsters
    
        int m = 2 + randInt(5*(mLevels+1));
        for (int a = 0; a < m; a++)
        {
            int mon = 0;
            switch (mLevels) {
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
            add_monster(randInt(mon));
        }
        
    
        if (mLevels != 4)
            //set a coordinate for end spot
            random_spot(endrow, endcol);
        else
        {
          
            int q = 0, w = 0;
            random_spot(q, w);
            Objects a(q, w);
            idol = &a;
        }
    }
}

void Levels::display()
{
    // blanks
    for (int o = 0; o < rows(); o++)
        for (int p = 0; p < cols(); p++)
            if (grid[o][p] != '#' && grid[o][p] != ')' && grid[o][p] != '?')
                grid[o][p] = ' ';
    
    //objects
    for (int a = 0; a < mObjects.size(); a++)
        grid[mObjects[a]->rows()][mObjects[a]->cols()] = mObjects[a]->sym();
    
    //exit/idol
    if (mLevels != 4)
        grid[endrow][endcol] = '>';
    else
        grid[idol->rows()][idol->cols()] = '&';
    
    //monsters
    for (int a = 0; a < m_monsters.size(); a++)
        grid[m_monsters[a]->row()][m_monsters[a]->col()] = m_monsters[a]->sym();
    
    // players position
    if (m_player != NULL)
    {
        char& gridChar = grid[m_player->row()][m_player->col()];
        if (grid[m_player->row()][m_player->col()] != '#')
            gridChar = m_player->sym();
    }
    
    //printing out the grid
    for (int o = 0; o < rows(); o++)
    {
        for (int p = 0; p < cols(); p++)
            cout << grid[o][p];
        cout << endl;
    }
    
    //overall messages
    cout << "Dungeon Level: " << mLevels << " Hit points: " <<
    m_player->hp() << " Armor: " << m_player->arm() << " Strength: " <<
    m_player->str() << " Dexterity: " << m_player->dex() << endl << endl;
}

void Levels::random_spot(int &a, int &b)
{
   
    while (grid[a][b] != ' ')
    {
        a = 1+randInt(MAXROWS-2);
        b = 1+randInt(MAXCOLS-2);
    }
}

bool Levels::okay_move(int r, int c)
{
    //person
    grid[m_player->row()][m_player->col()] = '@';
    
    //monster
    for (int a = 0; a < m_monsters.size(); a++)
        if (r == m_monsters[a]->row() &&
            c == m_monsters[a]->col())
            return false;
    
    if(grid[r][c] != ' ' && grid[r][c] != ')' &&
       grid[r][c] != '?' && grid[r][c] != '&' &&
       grid[r][c] != '>')
        return false;
    
    return true;
}

bool Levels::check_wall(int r, int c)
{
    
    if (grid[r][c] == '#')
        return true;
    return false;
}

bool Levels::next_level()
{
    //if it's a '>', delete the monsters and Objects
    if (m_player->row() == endrow && m_player->col() == endcol)
    {
        for (int a = 0; a < mObjects.size(); a++)
            delete mObjects[a];
        for (int a = 0; a < m_monsters.size(); a++)
            delete m_monsters[a];
        return true;
    }
    return false;
}

bool Levels::pick_up(string &str)
{
    //winning yayyyy
    if (m_player->row() == idol->rows() && m_player->col() == idol->cols())
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
 
    
    if (mObjects.size() <= MAXObjects)
    {
        for (int a = 0; a < mObjects.size(); a++)
        {
            //matching person with object
            if (mObjects[a]->rows() == m_player->row()
                && mObjects[a]->cols() == m_player->col())
            {
                //output
                str = "You picked up " + mObjects[a]->name();
                
                
                m_player->hold_objects(mObjects[a]);
                mObjects[a] = mObjects[mObjects.size()-1];
                mObjects.pop_back();
            }
        }
        return true;
    }
    return false;
}
//playyaa
bool Levels::add_player()
{
    
    if (m_player != NULL)
    {
        m_player->newSpot(this, plrow, plcol);
        return false;
    }
    m_player = new Player(this, plrow, plcol);
    return true;
}

//levelll
bool Levels::add_item(int r, int c, int a)
{

    switch (a) {
        case 0:
            mObjects.push_back(new Mace(r,c));
            break;
        case 1:
            mObjects.push_back(new ShortSword(r,c));
            break;
        case 2:
            mObjects.push_back(new LongSword(r,c));
            break;
        case 3:
            mObjects.push_back(new Armor(r,c)); // armor scroll
            break;
        case 4:
            mObjects.push_back(new Str(r,c)); // str scroll 
            break;
        case 5:
            mObjects.push_back(new Health(r,c)); // health scroll
            break;
        case 6:
            mObjects.push_back(new Dex(r,c)); // dex scroll
            break;
        case 7:
            mObjects.push_back(new Tele(r,c)); // teleport scroll
            break;
        case 8:
            mObjects.push_back(new Fangs(r,c)); // fangs
            break;
        case 9:
            mObjects.push_back(new Axe(r,c)); // fangs
            break;
            
        default:
            break;
    }
    return true;
}

bool Levels::add_monster(int a)
{
    //randomize a location and push them onto the map
    int q = 0, w = 0;
    random_spot(q, w);
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

bool Levels::check_dead_monsters()
{
    for (vector<Actor*>::iterator p = m_monsters.begin(); p != m_monsters.end(); p++)
    {
        Actor* ptr = *p;
        if (ptr->is_dead())
        {
            //erase monster
            ptr->drop(ptr->row(), ptr->col());
            p = m_monsters.erase(p);
            return true;
        }
    }
    return false;
}

bool Levels::check_object(int r, int c)
{
    //
    for (int a = 0; a < mObjects.size(); a++)
    {
        if (mObjects[a]->rows() == r
            && mObjects[a]->cols() == c)
        {
            //return false if there's an item
            return false;
        }
    }
    // return true if there is no item
    return true;
}

bool Levels::move_monsters(string &str)
{

    bool hit[m_monsters.size()];
    
    for (int a = 0; a < m_monsters.size(); a++)
    {
        //reduce counter if necessary
        if (!m_monsters[a]->is_sleep())
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