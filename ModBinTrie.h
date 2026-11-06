#ifndef MODBINTRIE_H
#define MODBINTRIE_H

#include <iostream>
#include <bit>
#include <cstdint>

class ModBinTrie
{
private:
    using value_type = unsigned long;
    using reference = value_type &;

    struct Node
    {
        uint8_t value;
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

    inline Node *MakeNode(value_type &&value)
    {
        Node *node = new Node();

        node->value = value;
        node->left = header;
        node->right = header;

        return node;
    }

    void MoveToNextNodeI(Node *&node, Node *&side_node, bool is_last)
    {
        if (is_last)
        {
            if (side_node == header)
            {
                side_node = MakeNode(0b100);
                node->value = node->value | side_node == node->left ? 0b10 : 0b1;
            }
            else
            {
                side_node->value = side_node->value | 0b100;
            }
        }
        else
        {
            if (side_node == header)
            {
                side_node = MakeNode(0b0);
                node->value = node->value | side_node == node->left ? 0b10 : 0b1;
            }
        }
        node = side_node;
    }

public:
    ModBinTrie() : header(MakeHeader()) {}

    void insert(value_type &&value)
    {
        Node *current_node = header;

        int length = std::bit_width(value);

        for (int i = 0; i < length; i++)
        {
            bool bit = (value >> i) & 1;
            if (bit)
            {
                MoveToNextNodeI(current_node, current_node->right, i == length - 1);
            }
            else
            {
                MoveToNextNodeI(current_node, current_node->left, i == length - 1);
            }
        }
    }

    bool contains(value_type &&value)
    {
        Node *current_node = header;

        int length = std::bit_width(value);

        for (int i = 0; i < length; i++)
        {
            bool bit = (value >> i) & 1;
            if (bit)
            {
                if (current_node->right == header)
                    return false;
                current_node = current_node->right;
            }
            else
            {
                if (current_node->left == header)
                    return false;
                current_node = current_node->left;
            }
        }
        if (current_node->value & 100)
            return true;
        else
            return false;
    }

private:
    friend void print_horizontal(const ModBinTrie &, std::ostream &);
    friend void print_horizontal_helper(typename ModBinTrie::Node *,
                                        typename ModBinTrie::Node *,
                                        std::ostream &, const std::string &, bool,
                                        bool);
};

#endif