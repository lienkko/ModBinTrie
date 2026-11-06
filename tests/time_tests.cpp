#include <iostream>
#include <chrono>
#include <set>
#include <random>

#include "ModBinTrie.h"

static std::pair<long long, bool> testFunctContainsMBT(std::string fName,
                                                       unsigned long num,
                                                       ModBinTrie &mbt)
{
    std::chrono::high_resolution_clock::time_point t1 =
        std::chrono::high_resolution_clock::now();

    bool ans = mbt.contains(std::move(num));

    std::chrono::high_resolution_clock::time_point t2 =
        std::chrono::high_resolution_clock::now();
    return std::pair(std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count(), ans);
}

static std::pair<long long, bool> testFunctContainsSet(std::string fName,
                                                       unsigned long num,
                                                       std::set<unsigned long> &set)
{
    std::chrono::high_resolution_clock::time_point t1 =
        std::chrono::high_resolution_clock::now();

    bool ans = set.contains(std::move(num));

    std::chrono::high_resolution_clock::time_point t2 =
        std::chrono::high_resolution_clock::now();
    return std::pair(std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count(), ans);
}

static long long testFunctInsertMBT(std::string fName,
                                    unsigned long num,
                                    ModBinTrie &mbt)
{
    std::chrono::high_resolution_clock::time_point t1 =
        std::chrono::high_resolution_clock::now();

    mbt.insert(std::move(num));

    std::chrono::high_resolution_clock::time_point t2 =
        std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
}

static long long testFunctInsertSet(std::string fName,
                                    unsigned long num,
                                    std::set<unsigned long> &set)
{
    std::chrono::high_resolution_clock::time_point t1 =
        std::chrono::high_resolution_clock::now();

    set.insert(std::move(num));

    std::chrono::high_resolution_clock::time_point t2 =
        std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
}

int main(int argc, char **argv)
{
    std::random_device rd;
    std::mt19937_64 gen(rd());

    std::uniform_int_distribution<long long> dis(std::numeric_limits<long long>::min(), std::numeric_limits<long long>::max());

    ModBinTrie *bt = new ModBinTrie();
    std::set<unsigned long> *st = new std::set<unsigned long>();
    // print_horizontal(*bt);
    double avg1 = 0;
    double avg2 = 0;
    for (long i = 0; i < 10000000; i++)
    {
        long long r = dis(gen);

        // if (r > 0 && r < 100)
        //     std::cout << r << std::endl;
        auto res = testFunctInsertMBT("test", r, *bt);
        auto res2 = testFunctInsertSet("test", r, *st);

        avg1 = (avg1 + res) / 2;
        avg2 = (avg2 + res2) / 2;
    }

    std::cout << "InsertAvg1: " << avg1 << std::endl;
    std::cout << "InsertAvg2: " << avg2 << std::endl;

    for (long i = 0; i < 10000000; i++)
    {
        long long r = dis(gen);

        // if (r > 0 && r < 100)
        //     std::cout << r << std::endl;
        auto res = testFunctContainsMBT("Test", r, *bt);
        auto res2 = testFunctContainsSet("Test", r, *st);

        avg1 = (avg1 + res.first) / 2;
        avg2 = (avg2 + res2.first) / 2;
    }
    std::cout << "ContainsAvg1: " << avg1 << std::endl;
    std::cout << "ContainsAvg2: " << avg2 << std::endl;
}