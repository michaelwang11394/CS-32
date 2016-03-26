#undef _GLIBCXX_DEBUG
#undef _GLIBCXX_DEBUG_PEDANTIC
#undef _GLIBCXX_FULLY_DYNAMIC_STRING
#define _GLIBCXX_FULLY_DYNAMIC_STRING 1

#ifndef Levels_INCLUDED
#define Levels_INCLUDED

#include "utilities.h"
#include <vector>
#include "Actor.h"
#include "Levels.h"

class Player;
class Objects;
class Actor;

class Levels
{
public:
    // Constructor/destructor
    Levels();
    Levels(int lvl, Player* prevPlayer);
    ~Levels();
    
    // Accessors
    int     rows() const { return m_rows; }
    int     cols() const { return m_cols; }
    int     plrows() const { return plrow; }
    int     plcols() const { return plcol; }
    Player* player() const { return m_player; }
    Actor*	get_monster(int r, int c) const;
    char	next_spot(int r, int c) const { return grid[r][c]; }
    void    display();
    
    // Mutators
    bool   add_player();
    bool    rooms(int &row, int &col);
    void    design();
    void    random_spot(int &a, int &b);
    bool     okay_move(int r, int c);
    bool	check_wall(int r, int c);
    bool     next_level();
    bool     pick_up(string& str);
    bool	add_item(int r, int c, int a);
    bool	add_monster(int a);
    bool	check_dead_monsters();
    bool	check_object(int r, int c);
    bool	move_monsters(string &str);
    
private:
    int     m_rows, m_cols;
    int		m_rooms, m_count; //room counter
    int     mLevels;
    int		plrow, plcol; // coordinates of player
    int		endrow, endcol; // coordinates of the ending
    
    Objects* idol;
    vector<Objects*> mObjects; // Objects on map
    vector<Actor*> m_monsters;
    
    Player*       m_player;
    int			numOfObjects;
    char		grid[MAXROWS][MAXCOLS];
};

#endif //Levels_INCLUDED