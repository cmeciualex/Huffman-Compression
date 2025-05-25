#include "DataReader.h"
#include <fstream>
#include "Huffman.h"
#include "Node.h"
#include <string>
#include "Code.h"
#include <map>
#include <iostream>
#include <bitset>
#include <filesystem>
#include "PriorityQueue.h"
#include <cstdint>

using namespace std;

streamsize getFileSize(const string &filename) {
    ifstream file(filename, std::ios::binary | std::ios::ate);
    return file.tellg();
}

void dfsPostOrder(Node *root, Code &currentCode, map<uint8_t, Code> &huffman_table) {
    if (root == nullptr)
        return;

    if (root->left == nullptr && root->right == nullptr) {
        huffman_table[root->symbol] = currentCode;
        return;
    }
    if (root->right) {
        currentCode.push_bit(&currentCode, 1);
        dfsPostOrder(root->right, currentCode, huffman_table);
        currentCode.code_pop_bit(&currentCode);
    }
    if (root->left) {
        currentCode.push_bit(&currentCode, 0);
        dfsPostOrder(root->left, currentCode, huffman_table);
        currentCode.code_pop_bit(&currentCode);
    }
}

void dfsPostOrder2(Node *root, std::ostream &out) {
    char symbol, symbol2 = '$';

    if (root == nullptr)
        return;

    dfsPostOrder2(root->left, out);
    dfsPostOrder2(root->right, out);

    if (root->left == nullptr && root->right == nullptr) {
        symbol = root->symbol;
        out.write(&symbol, 1);
    } else {
        out.write(&symbol2, 1);
    }
}

void output(std::string text, std::map<uint8_t, Code> huffman_table, Node *root, std::ostream &out) {
    uint8_t mask = 0;
    int bitCount = 0;
    struct Header {
        uint32_t signature;
        uint16_t tree_size;
    };
    Header header;
    header.signature = MAGIC;
    header.tree_size = 3 * (uint16_t) huffman_table.size() - 1;
    char newline = '\n';

    out.write(reinterpret_cast<char *>(&header.signature), sizeof(header.signature));
    out.write(reinterpret_cast<char *>(&header.tree_size), sizeof(header.tree_size));
    dfsPostOrder2(root, out);
    out.write(&newline, 1);

    for (int i = 0; i < text.length(); i++) {
        uint8_t ch = static_cast<uint8_t>(text[i]);
        Code aux = huffman_table[ch];

        for (uint32_t i = 0; i < aux.codeSize(); ++i) {
            uint8_t bit;
            aux.code_get_bit(i, &bit);

            if (bit) {
                mask |= (1 << (7 - bitCount));
            }
            bitCount++;

            if (bitCount == 8) {
                char c = mask;
                out.write(&c, 1);
                mask = 0;
                bitCount = 0;
            }
        }
    }

    if (bitCount > 0 && bitCount != 8) {
        char c = mask;
        out.write(&c, 1);
    }
}

Node* buildPreorderTreeFromStack(PriorityQueue &st) {
    if (st.get_size() == 0) return nullptr;

    Node* node = st.top();
    st.pop();

    if (node->symbol == '$') {
        node->right = buildPreorderTreeFromStack(st);
        node->left = buildPreorderTreeFromStack(st);
    }

    return node;
}

void readFromBinaryFile(std::istream &in, std::ostream &out, PriorityQueue &st,
                        std::map<uint8_t, Code> &huffman_table_2, std::map<Code, uint8_t> &reversed_table) {
    uint32_t signature = 0;
    in.read(reinterpret_cast<char *>(&signature), sizeof(signature));
    if (signature != 0xDEADEAEF) {
        std::cerr << "Invalid signature!" << std::endl;
        return;
    }

    uint8_t size_bytes[2];
    in.read(reinterpret_cast<char *>(size_bytes), 2);

    uint8_t byte;
    while (in.read(reinterpret_cast<char *>(&byte), 1)) {
        if (byte == '\n') break;
        if (byte >= 32 && byte <= 126) {
            Node *node = new Node(static_cast<char>(byte), 0);
            st.push(node);
        }
    }

    Node *p = buildPreorderTreeFromStack(st);
    Code currentCode;
    dfsPostOrder(p, currentCode, huffman_table_2);

    for (const auto &el : huffman_table_2) {
        reversed_table.insert({el.second, el.first});
    }

    Code code;
    while (in.read(reinterpret_cast<char *>(&byte), 1)) {
        for (int i = 7; i >= 0; --i) {
            bool bit = (byte >> i) & 1;
            code.push_bit(&code, bit);
            auto it = reversed_table.find(code);
            if (it != reversed_table.end()) {
                out << it->second;
                code = Code();
            }
        }
    }
}

bool relation1(Node *a, Node *b) {
    return true;
}

int main() {
    std::ofstream fout("Huffman.bin", std::ios::binary);
    std::ofstream fout2("Huffman.out");
    std::ifstream fin("Huffman.bin", std::ios::binary);

    std::map<uint8_t, Code> huffman_table;
    std::map<uint8_t, Code> huffman_table_2;
    std::map<Code, uint8_t> reversed_table;
    PriorityQueue st(relation1);
    PriorityQueue st2(relation1);
    Code currentCode;
    std::string text;
    uint64_t histogram[256] = {0};

    data_reader(histogram, text);

    Node *root = Huffman::buildTree(histogram);

    dfsPostOrder(root, currentCode, huffman_table);
    output(text, huffman_table, root, fout);
    fout.close();

    readFromBinaryFile(fin, fout2, st, huffman_table_2, reversed_table);
    fin.close();
    fout2.close();

    std::cout << "Initial file : " << getFileSize("Huffman.in") << " bytes" << std::endl
              << "Compressed file : " << getFileSize("Huffman.bin") << " bytes" << std::endl;

    double saved = (1.0 - (double)getFileSize("Huffman.bin") / getFileSize("Huffman.in")) * 100;
    std::cout << "Reduced by " << saved << "% compared with initial size." << std::endl << std::endl;

    for (const auto &el : huffman_table) {
        std::cout << el.first << " " << el.second << std::endl;
    }

    return 0;
}
