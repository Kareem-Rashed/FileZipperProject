//
// Created by Kareem Rashed on 12/11/2024.
//

#include "Huffman.h"

Huffman::Huffman(string file): fileName(file) {}

Huffman::~Huffman()
{

}

PriorityQueue<char> Huffman::Frequencies(string file)
{
    ifstream infile(file);
    if (!infile.is_open()) {
        cerr << "Error: Unable to open corpus file '" << file << "'." << endl;
    }

    unordered_map<char, int> freqmap;
int total = 0;
    char ch;
    while (infile.get(ch))
    {
        if (ch >= 32 && ch <= 126) // Printable ASCII range
        {
            if (freqmap.find(ch) == freqmap.end())
            {
                freqmap.insert(make_pair(ch, 1));
            }
            else
            {
                freqmap[ch]++;
            }
            total++;
        }
    }
    infile.close();

/*
    for (auto& it : freqmap) {
        if (std::isprint(it.first)) {
            std::cout << "'" << it.first << "' : " << it.second << '\n';
        } else {
            std::cout << "Character: " << ch << " ASCII: " << static_cast<int>(it.first) << '\n'
                      << " : " << it.second << '\n';
        }
    }
    cout<<"total: "<<total<<endl;
    */
    PriorityQueue<char> pq;

    for (auto& it : freqmap)
    {
        pq.insert(it.first, it.second);
    }
    return pq;
}

void Huffman::buildHuffmanTree()
{
    PriorityQueue<char> pq = Frequencies(fileName);

    while(pq.size>1)
    {
        Node<char> *FirstNode = pq.dequeue();
        Node<char> *SecondNode = pq.dequeue();


        Node<char> *ParentNode = new Node<char>( -999, FirstNode->priori + SecondNode->priori);
        ParentNode->right = SecondNode;
        ParentNode->left = FirstNode;
        pq.insert(ParentNode);
    }
    root = pq.dequeue();
}

void Huffman::CreateEncodings(Node<char>* temproot, string enc)
{
    if((temproot->left == nullptr)&&(temproot->right == nullptr))
    {
        vector<bool> newVector;

        for(int i=0; i<enc.size(); i++)
        {
            if(enc[i] == '1')
            {
                newVector.push_back(1);
            }
            else
            {
                newVector.push_back(0);
            }
        }
        Encodings.insert(make_pair(temproot->data, newVector));
        return;
    }
    else
    {
        CreateEncodings(temproot->left, enc + '0');
        CreateEncodings(temproot->right, enc + '1');

    }
}
void Huffman::Compress() {
    buildHuffmanTree();
    CreateEncodings(root, "");

    ifstream infile(fileName, ios::binary);
    ofstream outfile("Compressed.bin", ios::binary);

    if (!infile.is_open()) {
        cerr << "Error: Unable to open input file '" << fileName << "'." << endl;
        return;
    }

    unsigned char buffer = 0;
    int bitCount = 0;

    char ch;
    while (infile.get(ch)) {
        vector<bool> encoding = Encodings[ch];

        for (bool bit : encoding) {
            buffer = buffer * 2 + bit;
            bitCount++;

            if (bitCount == 8) {
                outfile.put(buffer);
                buffer = 0;
                bitCount = 0;
            }
        }
    }
//the rest
    if (bitCount > 0) {
        buffer = buffer << (8 - bitCount);
        outfile.put(buffer);
    }

    infile.close();
    outfile.close();
}
void Huffman::Decompress() {
    ifstream infile("Compressed.bin", ios::binary);
    ofstream outfile("Decompressed.txt");

    if (!infile.is_open()) {
        cerr << "Error: Unable to open compressed file." << endl;
        return;
    }

    char ch;
    unsigned char buffer;
    Node<char>* currentNode = root;

    while (infile.get(reinterpret_cast<char&>(buffer))) {
        for (int i = 7; i >= 0; i--) {

            bool bit = (buffer >> i) & 1;  //getting the ith bit
            if(bit)
            {
                currentNode = currentNode->right;
            }
            else
            {
                currentNode = currentNode->left;
            }
            if (!currentNode->left && !currentNode->right) {
                outfile.put(currentNode->data);
                currentNode = root;
            }
        }
    }

    infile.close();
    outfile.close();
}