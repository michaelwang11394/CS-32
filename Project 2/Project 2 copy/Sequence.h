//
//  Sequence.h
//  Project 2
//
//  Created by Michael Wang on 4/20/15.
//  Copyright (c) 2015 Michael Wang. All rights reserved.
//

#ifndef __Project_2__Sequence__
#define __Project_2__Sequence__
#include <iostream>
#include <string>
#include <stdio.h>

typedef std::string ItemType;



class Sequence
{
public:
    Sequence();                                     //create an empty list
    ~Sequence();                                    //destructor for sequence
    Sequence(const Sequence &other);                //copy constructor for sequence
    Sequence &operator=(const Sequence &rhs);       //Assignment opperator for sequence
    
    
    bool empty() const;
    int size() const;
    bool insert(int pos, const ItemType& value);
    // Insert value into the sequence so that it becomes the item at
    // position pos.  The original item at position pos and those that
    // follow it end up at positions one higher than they were at before.
    // Return true if 0 <= pos <= size() and the value could be
    // inserted.  (It might not be, if the sequence has a fixed capacity,
    // e.g., because it's implemented using a fixed-size array.)  Otherwise,
    // leave the sequence unchanged and return false.  Notice that
    // if pos is equal to size(), the value is inserted at the end.
    bool insert(const ItemType& value);
    // Let p be the smallest integer such that value <= the item at
    // position p in the sequence; if no such item exists (i.e.,
    // value > all items in the sequence), let p be size().  Insert
    // value into the sequence so that it becomes the item at position
    // p.  The original item at position p and those that follow it end
    // up at positions one higher than before.  Return true if the value
    // was actually inserted.  Return false if the value was not inserted
    // (perhaps because the sequence has a fixed capacity and is full).
    bool erase(int pos);
    // If 0 <= pos < size(), remove the item at position pos from
    // the sequence (so that all items that followed this item end up at
    // positions one lower than they were at before), and return true.
    // Otherwise, leave the sequence unchanged and return false.
    int remove(const ItemType& value);
    // Erase all items from the sequence that == value.  Return the
    // number of items removed (which will be 0 if no item == value).
    bool get(int pos, ItemType& value) const;
    // If 0 <= pos < size(), copy into value the item at position pos
    // in the sequence and return true.  Otherwise, leave value unchanged
    // and return false.
    bool set(int pos, const ItemType& value);
    // If 0 <= pos < size(), replace the item at position pos in the
    // sequence with value and return true.  Otherwise, leave the sequence
    // unchanged and return false.

    int find(const ItemType& value) const;
    // Let p be the smallest integer such that value == the item at
    // position p in the sequence; if no such item exists, let p be -1.
    // Return p.
    void swap(Sequence& other);
    // Exchange the contents of this sequence with the other one.
    void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);
    int subsequence(const Sequence& seq1, const Sequence& seq2);
    
private:
    struct Node
    {
        ItemType m_value;
        int      m_count=0;
        Node* previous;
        Node* next;
    };
    int m_size;
    Node* head;
    Node* tail;
    
    void addToFront(const ItemType& value);// add a node to the front of a linked list
};
#endif /* defined(__Project_2__Sequence__) */
