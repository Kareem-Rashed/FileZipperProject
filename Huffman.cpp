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

        for(int i=0; i<enc.size()-1; i++)
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

void Huffman::Compress()
{
    buildHuffmanTree();  // Build the Huffman tree
    CreateEncodings(root, "");  // Create Huffman codes for each character

    // Open files for reading and writing
    ofstream outfile("Compressed.txt", ios::binary);
    ifstream infile(fileName);
    if (!infile.is_open()) {
        cerr << "Error: Unable to open corpus file '" << fileName << "'." << endl;
        return;
    }

    char ch;


    while (infile.get(ch))
    {
        if (ch >= 32 && ch <= 126)  // Only handle printable ASCII characters
        {
            vector<bool> encoding = Encodings[ch];

            for(int i=0; i<encoding.size(); i++)
            {
                if(encoding[i] == 1)
                {
                    outfile<<'1';
                }
                else
                {
                    outfile<<'0';
                }
            }
        }
    }

    infile.close();
    outfile.close();
}
void Huffman::Decompress()
{
    ofstream outfile;
    outfile.open("Decompressed.txt");
    ifstream infile;
    infile.open("Compressed.txt", ios::binary);

    if (!infile.is_open()) {
        cerr << "Error: Unable to open compressed file." << endl;
        return;
    }

    char ch;
    Node<char>* currentNode = root;

    while (infile.get(ch))
    {
        bool bit = (ch == '1');

        if (bit == 0) {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }

        if (currentNode->left == nullptr && currentNode->right == nullptr) {
            outfile.put(currentNode->data);
            currentNode = root;
        }
    }


    // Close the files
    infile.close();
    outfile.close();
}