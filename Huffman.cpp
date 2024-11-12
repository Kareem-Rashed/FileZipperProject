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


    for (auto& it : freqmap) {
        if (std::isprint(it.first)) {
            std::cout << "'" << it.first << "' : " << it.second << '\n';
        } else {
            std::cout << "Character: " << ch << " ASCII: " << static_cast<int>(it.first) << '\n'
                      << " : " << it.second << '\n';
        }
    }
    cout<<"total: "<<total<<endl;
}


