//
// Created by acmec on 4/23/2025.
//
#include <fstream>
#include <string>
#include <cstdint>
#include "DataReader.h"

using namespace std;
void data_reader(uint64_t frequency[256],string &text) {
    ifstream fin("Huffman.in");
    char c;
    while (fin.get(c)) {
        text+=c;
    }
    for (int i=0;i<text.length();i++) {
        if (isprint(text[i])) {
            frequency[(uint64_t)text[i]]++;
        }

    }
}