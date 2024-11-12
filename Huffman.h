//
// Created by Kareem Rashed on 12/11/2024.
//

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <queue>
#include <sstream>
#include "PriorityQueue.h"
using namespace std;

class Huffman {
private:
    string fileName;
    struct TreeNode
    {
        char data;
        TreeNode *left;
        TreeNode *right;
    };


public:
    Huffman(string file);
    PriorityQueue<char> Frequencies(string file);
    ~Huffman();





};



#endif //HUFFMAN_H
