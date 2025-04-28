#pragma once

#include <fstream>
#include <sstream>

#include "tree.h"

typedef tree<int, std::string> Tree;
typedef Tree::node Node;

class Solution {
    std::pair<int, std::string> pair1, pair2;
    Tree tree;
    int height;

public:
    bool Parse(std::ifstream& file) {
        int curr;
        std::pair<int, std::string> pair;
        for (height = 0; ReadPair(file, pair); height = std::max(height, curr)) {
            if (!(curr = tree.insert(pair))) {
                return false;
            }
        }
        return ReadPair(file, pair1) && ReadPair(file, pair2);
    }

    int Part1() const {
        int* sums = new int[height]{};
        int result = height * GetMaxSum(tree.root, sums, 0);
        delete[] sums;
        return result;
    }

    std::string Part2() const {
        std::string result;
        for (const Node *curr = tree.root; curr != nullptr; curr = curr->next(500000)) {
            if (!result.empty()) {
                result += '-';
            }
            result += curr->value.second;
        }
        return result;
    }

    std::string Part3() const {
        for (const Node *curr = tree.root, *next1, *next2; curr != nullptr; curr = next1) {
            if ((next1 = curr->next(pair1.first)) == nullptr) {
                return curr->value.second;
            }
            if ((next2 = curr->next(pair2.first)) == nullptr) {
                return curr->value.second;
            }
            if (next1 != next2) {
                return curr->value.second;
            }
        }
        return 0;
    }

private:
    bool ReadPair(std::ifstream& file, std::pair<int, std::string>& pair) const {
        std::string line;
        if (!std::getline(file, line) || line.empty()) {
            return false;
        }
        std::istringstream istream(line);
        std::string s;
        istream >> pair.second >> s >> pair.first;
        return true;
    }

    int GetMaxSum(const Node* curr, int* sums, int depth) const {
        return curr != nullptr
            ? std::max(sums[depth] += curr->value.first, std::max(
                GetMaxSum(curr->left, sums, depth + 1),
                GetMaxSum(curr->right, sums, depth + 1)))
            : 0;
    }
};
