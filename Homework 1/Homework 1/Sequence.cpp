//
//  Sequence.cpp
//  Homework 1
//
//  Created by Michael Wang on 4/13/15.
//  Copyright (c) 2015 Michael Wang. All rights reserved.
//

#include "Sequence.h"

Sequence::Sequence(int a)
:check(false)
{
    number=0;
    if(a<0)
        exit(1);
    else
    {
        items= new ItemType[a];
        
    }
}


Sequence::Sequence()   //creating an empty set.. also is default constructor
:check(false)
{
    number=0;
    max= DEFAULT_MAX_ITEMS;
    items = new ItemType[DEFAULT_MAX_ITEMS];
    
}

Sequence::Sequence(const Sequence& other) //copy constructor
:number(other.number), max(other.max)
{
   
    items = new ItemType [number + 1];
    
    for (int z = 0; z  < number; z++)
    {
        items[z] = other.items[z];
    }
}

bool Sequence:: empty() const
{
    if (number==0)
        return true;
    else
        return false;
}

int Sequence::size() const
{
    return number;
    
}
bool Sequence::insert(int pos, const ItemType& value)

{
if (pos >= 0 && pos < DEFAULT_MAX_ITEMS)
{
    items[pos] = value;
    pos++;
    return true;
}
    else
        return false;
    

}

bool Sequence::insert(const ItemType& value)

{
    if (!find(value) && number < DEFAULT_MAX_ITEMS)
    {
        items[number] = value;
        number++;
        return true;
    }
    else
    {

        return false;
    }
}

bool Sequence::erase(int pos)
{
// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed this item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
    if (0<=pos && pos < number)
    {
        for(int i =pos; i< number; i++)
            items[pos]= items[pos+1];
        number--;
        return true;
        
    }
        return false;
}
int Sequence::remove(const ItemType & value)
{
    for (int x = 0; x < number; x++)
    {
        if (items[x] == value)
        {
            for (int y = x; y < number; y++)
            {
                items[y] = items[y+1];
            }
            
            number--;
            
            return x;
        }
    }
    return false;
}



int Sequence::find(const ItemType & value) const
{
    for (int x = 0; x < number; x++)
    {
        if (items[x] == value)
        {
            return true;
        }
    }
    return false;
}

bool Sequence:: get(int pos, ItemType& value ) const
{
   
    if (pos >= 0 && pos < number)
    {
        value = items[pos];
        return true;
    }
    else {
        return false;
    }
}

bool Sequence::set(int pos, const ItemType& value)
{
// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
        if (pos >= 0 && pos < size())
        {
            items[pos] = value;

            return true;
        }
        else
            return false;
        
    
}

void Sequence::swap(Sequence &other)
{
   
    int tempsize = 0;
    ItemType temp[DEFAULT_MAX_ITEMS];
    
   
    tempsize = number;
    number = other.number;
    other.number = tempsize;
    
    
    for (int x = 0; x < DEFAULT_MAX_ITEMS; x++)
    {
        temp[x] = items[x];
        items[x] = other.items[x];
        other.items[x] = temp[x];
    }
}
//need to create a temp using the RHS, so we can later on utilize the above swap function
Sequence& Sequence::operator=(const Sequence& rhs)
{
    if (this != &rhs)
    {

        Sequence temp(rhs);
        swap(temp);
    }
    return *this;
}

Sequence::~Sequence()
{
    // delete the array after usage
    delete [] items;
}

