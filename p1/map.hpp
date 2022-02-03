//
//  map.hpp
//  p1
//
//  Created by zewei yu on 1/16/22.
//
//40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD
#ifndef map_hpp
#define map_hpp

#include <vector>
#include <iostream>
#include <stdio.h>
#include <deque>
using namespace std;
struct Spot{
    char terrian='.';
    char last=0;
};

struct Coordinate{
    uint32_t row;
    uint32_t col;
};

class Map{
private:
    vector<vector<Spot>> map;
    vector<Coordinate> ashores;
    deque<char> path;
    string order;
    uint32_t startCol;
    uint32_t startRow;
    uint32_t treasureCol;
    uint32_t treasureRow;
    uint32_t landNum=0;
    uint32_t waterNum=0;
    uint32_t mapLength;
    uint32_t pathLength;
    bool ifFound=false;

public:
    void createVector(uint32_t size);
    void readMap();
    void readList();
    void assignLast(const Coordinate& current,const Coordinate &around);
    void hunt(const string& capOption,const string& firOption);
    bool validSpot(const Coordinate& pair);
    bool validSpot2(const Coordinate& pair);
    bool getifFound();
    void setOrder(string& huntOrder);
    void getPath();
    void printVerbose();
    void printStats();
    void printMap();
    void printList();
    void printOutput();

    ~Map();
};




#endif /* map_hpp */
