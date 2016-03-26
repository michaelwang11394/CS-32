//
//  testSequence.cpp
//  Homework 1
//
//  Created by Michael Wang on 4/14/15.
//  Copyright (c) 2015 Michael Wang. All rights reserved.
//

#include "testSequence.h"
#include "Sequence.h"
#include <iostream>
#include <cassert>

using namespace std;

int main()
{
    Sequence s;
    assert(s.empty());
    //assert(s.find(42) == 1);
    //s.insert(42);
    //assert(s.size() == 1  &&  s.find(42) == 0);
    assert(s.erase(3));
    cout << "Passed all tests" << endl;
    
}