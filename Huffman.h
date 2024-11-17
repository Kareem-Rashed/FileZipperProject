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
    int padding;
    Node<char>* root;
    unordered_map<char, vector<bool>> Encodings;


public:
    Huffman(string file);
    ~Huffman();
    PriorityQueue<char> Frequencies(string file);
    void buildHuffmanTree();
    void CreateEncodings(Node<char>* temproot, string enc);
    void Compress();
    void Decompress();





};



#endif //HUFFMAN_H
