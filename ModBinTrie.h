#ifndef MODBINTRIE_H
#define MODBINTRIE_H

#include <iostream>
#include <bit>
#include <optional>

class ModBinTrie
{
private:
    using value_type = unsigned int;
    using reference = value_type &;

    struct Node
    {
        std::optional<uint8_t> value;
        Node *left;
        Node *right;
    };

    Node *header;

    inline Node *MakeHeader()
    {
        Node *hdr = new Node();
        hdr->left = hdr;
        hdr->right = hdr;
        return hdr;
    }

public:
    ModBinTrie() : header(MakeHeader()) {}
};

#endif