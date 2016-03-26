//
//  Actor.cpp
//  Project 3
//
//  Created by Michael Wang on 5/24/15.
//  Copyright (c) 2015 Michael Wang. All rights reserved.
//

#include "Actor.h"
#include "utilities.h"
#include "Arena.h"
#include "Objects.h"

class Levels;
class Items;

class Actor
{
public:
    //Actor();
    Actor(Arena *ap, int r, int c, int hp, int str, int dex, int arm,
          Objects* equip, std::string name, char sym);
    
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
    std::string name() const { return m_name; }
    char sym() const { return m_sym; }
    bool isDead() const { if (hp() <= 0) return true; return false; }
    bool isSleep() const;
    Objects* getEquipped() const { return
        m_equipped; }
    Arena* level() const { return m_levels; }
    
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
    void changeSpot(int r, int c) { m_row=r; m_col=c;}
    
    virtual void attack(int r, int c, std::string &act);
    virtual void drop(int r, int c) {}
    virtual char moveDir(int r, int c) {return ' ';}
    virtual bool checkDistance() {return true;}
    
    bool checkPlayer(int r, int c) const;
    void setEquip(Items* a);
    bool	move(char dir, std::string &str);
    void	stand();
    void	newSpot(Levels *ap, int r, int c);
    bool	checkEquipped();
    void	heal();
    int		rDiff();
    int		cDiff();
    
private:
    int		m_row;
    int		m_col;
    int		m_dmg, m_hp, m_arm, m_str, m_dex;
    
    int		a_arm, a_str, a_dex; // additions from scrolls
    int		w_dmg, w_dex; //weapon dmg and dex
    
    int		m_sleep, m_maxSleep;
    int		max_health;
    std::string	m_name;
    char	m_sym;
    bool    m_dead;
    Levels* m_levels;
    Items*   m_equipped;
};

class Player: public Actor
{
public:
    // Constructor
    Player(Levels *ap, int r, int c);
    virtual ~Player() {}
    
    int  items() const {return m_items;}
    bool showInvent(chastd::string, std::string& str);
    
    // Mutators
    void
    moreItems() { m_items++; } // add to items
    void	holdItems(Items* a) {m_invent.push_back(a);} // add to vector
    void	cheat();
    void	useScroll(Items* a);
    virtual void attack(int r, int c, std::string &act);
    
private:
    std::vector<Items*> m_invent;
    Actor*  m_monsters;
    int		m_items; // number of items in inventory
};





//MONSTERSSSSSSSSS
class Bogeyman: public Actor
{
public:
    Bogeyman();
    Bogeyman(Levels* ap, int r, int c);
    virtual void drop(int r, int c);
    virtual bool checkDistance();
    virtual char moveDir(int r, int c);
    
    virtual ~Bogeyman();
private:
    
};

class Snakewomen: public Actor
{
public:
    Snakewomen();
    Snakewomen(Levels* ap, int r, int c);
    virtual void drop(int r, int c);
    virtual bool checkDistance();
    virtual char moveDir(int r, int c);
    virtual ~Snakewomen();
private:
    
};

class Dragon: public Actor
{
public:
    Dragon();
    Dragon(Levels* ap, int r, int c);
    virtual void drop(int r, int c);
    virtual bool checkDistance();
    virtual char moveDir(int r, int c);
    virtual ~Dragon();
private:
    
};

class Goblin: public Actor
{
public:
    Goblin();
    Goblin(Levels* ap, int r, int c);
    virtual void drop(int r, int c);
    virtual bool checkDistance();
    virtual char moveDir(int r, int c);
    virtual ~Goblin();
private:
    
};
