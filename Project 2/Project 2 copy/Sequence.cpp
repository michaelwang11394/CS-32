//
//  Sequence.cpp
//  Project 2
//
//  Created by Michael Wang on 4/20/15.
//  Copyright (c) 2015 Michael Wang. All rights reserved.
//
#include "Sequence.h"
#include <iostream>
using namespace std;

Sequence::Sequence()
: m_size(0), head(nullptr), tail(nullptr) // initialize the sequence.
{}

Sequence::~Sequence()              //destructor
{
    Node* p;
    for (p = head; p != nullptr; ) //loop to make sure all nodes are covered
    {
        Node* n = p->next;         // address needs to be stored in new node so we're not lost on where to go next
        delete p;                  // node can now be safely deleted
        p = n;                     // the stored address from earlier will now be our new value p to be deleted
    }
}

Sequence::Sequence(const Sequence& other)       //copy constructor
{
    head = nullptr;                             //initialize the head
    tail = nullptr;                             //initialize the tail
    Node* p;
    for (p = other.tail; p != nullptr; p = p->previous)// we're going backwards in the copy to ensure proper seq
    {
        for (int i = 0; i < other.find(p->m_value); i++)//insert the other's m_value m_count times to this
            this->insert(p->m_value);
    }
    m_size = other.size();                               // copy size

}

Sequence& Sequence::operator=(const Sequence& rhs)// assignment operator
{
    if (this != &rhs)                           // make sure we don't copy oursevles
    {
        Node* p;
        for (p = head; p != nullptr;)           //delete all the nodes in the list
        {
            Node* n = p->next;
            delete p;
            p = n;
        }
        this->head = nullptr; // let head and tail equal to nullptr so that the list first become empty
        this->tail = nullptr;
        Node* q;
        for (q = rhs.tail; q != nullptr; q = q->previous) //travel the linked list of rhs backwards to make sure the order of node in this is not opposite
        {
            for (int i = 0; i < rhs.find (q->m_value); i++)//copy the find value over to this
                this->insert (q->m_value);
        }
        m_size = rhs.size();                              //copy size
        
    }
    return *this;                                         //self assignment return itself
}

bool Sequence::empty() const  // Return true if the set is empty. False if not empty
{
    // if the size is 0, return true.
    if (m_size== 0)
        return true;
    else
        return false;
}

int Sequence::size() const    // Return the number of items in the set.
{
    return m_size;
}

int Sequence::find(const ItemType& value)const
{
    int pos = -1;
    int cur = 0;
    
    for (Node* p = head; p != nullptr; p = p->next)//search the list
    {
        cout << p->m_value << endl;
        if (p->m_value == value)// find a node having value
        {
            pos = cur;
        }
        
        cur++;
        
    }
    return pos;
    //exit(1); // not find a node with value
}
bool Sequence::insert(int pos, const ItemType& value)
{
    return true;
}

bool Sequence::insert(const ItemType& value)
{
    if (head == nullptr)   //if the linked list is empty
    {
        addToFront(value); //add to the front
        tail = head;       //let tail and head point to the same item
        return true;
    }
    
   
    else                   //if the linked list is not empty
    {
        Node *p=head;
        while (p->next != nullptr)
            p=p->next;
        Node *q =new Node;
        q->m_value= *new ItemType;
        q->next=p->next;
        p->next=q;
        return true;
        
    }
    return false;
}

bool Sequence::erase(int pos)
// Remove the value from the set if present.  Return true if the
// value was removed; otherwise, leave the set unchanged and
// return false.
{
    Node *p = head->next;
    
    while (p != head)
    {
        pos= p->next;
        if (p->m_value == pos)
        {
            Node *d = p;
            p->next->previous = d->previous;
            p->previous->next = d->next;
            
            delete d;
            
            m_size--;
            return true;
        }
        else
        {
            p = p->next;
        }
    }
    
    //if it doesn't contain the value, return false
    return false;
}

int Sequence::remove(const ItemType &value)
{
    return true;
}

void Sequence::swap(Sequence& other)
{
    Sequence temp = other;
    other=*this;
    *this= temp;
}

void Sequence::addToFront(const ItemType& value)
{
    Node* p;
    p = new Node;         //create a new node
    p->m_value = value;   //store value into node
    p->m_count = 1;       //initialize the count of the item to 1
    p->next = head;       //let p->next points to where head used to point to such as nullptr and a node
    if (p->next!=nullptr) //check if the list is empty
        p->next->previous = p;
    p->previous = nullptr;//let p->previous be nullptr since the new node is the first one of the list
    head = p;             //let head points to the new node
    m_size++;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos < 0 || pos >= m_size)  // test whether i is inbound
        return 0;
    Node*p;
    int n = 0;
    for (p = head; p != nullptr; p = p->next, n++)
    {
        if (n == pos) //get (i+1)th node
            break;
    }
    p->m_value=value;
    return p->m_count;
}

bool Sequence::get(int pos, ItemType &value) const

{
    return true;
}
void Sequence:: interleave(const Sequence& ms1, const Sequence& ms2, Sequence& result)
{
    Sequence trans;
    trans = ms1; //let result equal to ms1
    ItemType temp;
    for (int i = 0; i < m_size; i++)
    {
        int n = ms2.get(i, temp); // get each item in each node of ms2
        for (int k = 0; k < n; k++)
            trans.insert(temp); // insert those items to result
    }
    result = trans;
}

int Sequence::subsequence(const Sequence &seq1, const Sequence &seq2)
{
    return true;
}

