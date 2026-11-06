#include <iostream>
#include <chrono>
#include <set>
#include <random>

#include "ModBinTrie.h"

void print_horizontal_helper(typename ModBinTrie::Node *node,
                             typename ModBinTrie::Node *header,
                             std::ostream &os, const std::string &prefix,
                             bool is_left, bool is_last_child)
{
    if (node == header)
        return;

    os << prefix;

    // Рисуем ветвь
    if (is_last_child)
    {
        os << "|__ ";
    }
    else
    {
        os << "|-- ";
    }

    // Метка L/R
    os << (is_left ? "L: " : "R: ");

    // Значение и цвет
    os << ((node->value & 0b100) ? "[T]" : "[F]");
    os << "\n";

    // Новый префикс для детей
    std::string child_prefix = prefix;
    if (is_last_child)
    {
        child_prefix += "    ";
    }
    else
    {
        child_prefix += "|   ";
    }

    // Рекурсивно для детей
    if (node->right != header)
    {
        bool last = (node->left == header);
        print_horizontal_helper(node->right, header, os, child_prefix,
                                false, last);
    }
    if (node->left != header)
    {
        print_horizontal_helper(node->left, header, os, child_prefix,
                                true, true);
    }
}

void print_horizontal(const ModBinTrie &tree,
                      std::ostream &os = std::cout)
{
    if (tree.header->value == 0b0)
    {
        os << "(empty tree)\n";
        os << "===============================================\n\n";
        return;
    }

    os << "ROOT-- ";
    os << "\n";

    // Выводим детей корня
    if (tree.header->right != tree.header)
    {
        print_horizontal_helper(
            tree.header->right, tree.header, os, "", false,
            tree.header->left == tree.header // is_last_child
        );
    }
    if (tree.header->left != tree.header)
    {
        print_horizontal_helper(tree.header->left, tree.header, os,
                                "", true, true);
    }

    os << "===============================================\n\n";
}

int main(int argc, char **argv)
{
    ModBinTrie *bt = new ModBinTrie();
    std::set<unsigned long> *st = new std::set<unsigned long>();
    print_horizontal(*bt);
}