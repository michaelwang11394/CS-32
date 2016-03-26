

#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include "utilities.h"
#include "Levels.h"
#include "Objects.h"

class Levels;
class Objects;

class Actor
{
public:
    //Actor();
    Actor(Levels *ap, int r, int c, int hp, int str, int dex, int arm,
          Objects* equip, string name, char sym);
    virtual ~Actor() { delete m_equipped; }
    
    // Accessors
    int  row() const { return m_row; }
    int  col() const { return m_col; }
    int  hp() const { return m_hp; }
    int  arm() const { return m_arm + a_arm; }
    int  str() const { return m_str + a_str; }
    int  dex() const { return m_dex + a_dex + w_dex; }
    int  maxhp() const { return max_health; }
    int  dmg() const { return m_dmg + w_dmg; }
    string name() const { return m_name; }
    char sym() const { return m_sym; }
    bool is_dead() const { if (hp() <= 0) return true; return false; }
    bool is_sleep() const;
    Objects* getEquipped() const { return m_equipped; }
    Levels* level() const { return mLevels; }
    
    // Mutators
    void changeHp(int a) { m_hp += a; if (m_hp > max_health) m_hp = max_health; }
    void changeDeath(bool a) { m_dead = a; }
    void changeSleep(int a);
    void changeMaxSleep(int a) { m_maxSleep = a; }
    void changeMax(int a) { max_health += a; }
    void cheatMax(int a) { max_health = a; }
    void changeDex(int a) { a_dex += a; }
    void changeStr(int a) { a_str += a; }
    void changeArm(int a) { a_arm += a; }
    void change_spot(int r, int c) { m_row=r; m_col=c;}
    
    virtual void attack(int r, int c, string &act);
    virtual void drop(int r, int c) {}
    virtual char movementdirection(int r, int c) {return ' ';}
    virtual bool checkdistance() {return true;}
    
    bool checkPlayer(int r, int c) const;
    void set_equip(Objects* a);
    bool	move(char dir, string &str);
    void	stand();
    void	newSpot(Levels *ap, int r, int c);
    bool	checkEquipped();
    void	heal();
    int		rDiff();
    int		cDiff();
    
private:
    // able to pin point on the graph
    int		m_row;
    int		m_col;
    int		m_dmg, m_hp, m_arm, m_str, m_dex;
    
    //ways to add to scrolls and weapons
    int		a_arm, a_str, a_dex;
    int		w_dmg, w_dex;
    
    
    int		mSleep, m_maxSleep;
    int		max_health;
    string	m_name;
    char	m_sym;
    bool    m_dead;
    Levels* mLevels;
    Objects*   m_equipped;
};

class Player: public Actor
{
public:
    // Constructor
    Player(Levels *ap, int r, int c);
    virtual ~Player() {}
    
    int  Objects() const {return mObjects;}
    bool showInvent(char type, string& str);
    
    // Mutators
    void	more_objects() { mObjects++; } // add to Objects
    void	hold_objects(class Objects* a) {m_invent.push_back(a);} // add to vector
    void	cheat();
    void	scroll(class Objects* a);
    virtual void attack(int r, int c, string &act);
    
private:
    vector<class Objects*> m_invent;
    Actor*  m_monsters;
    int		mObjects; // number of Objects in inventory
};





//monsters
class Bogeyman: public Actor
{
public:
    Bogeyman();
    Bogeyman(Levels* ap, int r, int c);
    virtual void drop(int r, int c);
    virtual bool checkdistance();
    virtual char movementdirection(int r, int c);
    
    virtual ~Bogeyman();
private:
    
};

class Snakewomen: public Actor
{
public:
    Snakewomen();
    Snakewomen(Levels* ap, int r, int c);
    virtual void drop(int r, int c);
    virtual bool checkdistance();
    virtual char movementdirection(int r, int c);
    virtual ~Snakewomen();
private:
    
};

class Dragon: public Actor
{
public:
    Dragon();
    Dragon(Levels* ap, int r, int c);
    virtual void drop(int r, int c);
    virtual bool checkdistance();
    virtual char movementdirection(int r, int c);
    virtual ~Dragon();
private:
    
};

class Goblin: public Actor
{
public:
    Goblin();
    Goblin(Levels* ap, int r, int c);
    virtual void drop(int r, int c);
    virtual bool checkdistance();
    virtual char movementdirection(int r, int c);
    virtual ~Goblin();
private:
    
};

#endif //ACTOR_INCLUDED