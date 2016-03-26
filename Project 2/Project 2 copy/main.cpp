//
//  main.cpp
//  Project 2
//
//  Created by Michael Wang on 4/20/15.
//  Copyright (c) 2015 Michael Wang. All rights reserved.
//
#include "Sequence.h"
#include <string>
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
    Sequence mys;
    mys.insert("Hi");
    mys.insert("daf");
    int t = mys.find("Hi");
    cout<< t;
}

