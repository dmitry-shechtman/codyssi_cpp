#pragma once

#include <vector>

#include "Rule.h"

typedef uint16_t Count;

class Solution {
    const uint16_t CountMask = 0x0007;
    const uint16_t SeenMask = 0x8000;

    static const int VectorCount = 7;
    static Point4 vectors[VectorCount];

    const std::vector<Rule>& rules;
    const Range4& range;
    const Range3 range3;
    const int length;
    const int lcm;
    Count* counts;

public:
    Solution(const std::vector<Rule>& rules, Range4 range):
        rules(rules),
        range(range),
        range3(range),
        length(range3.Length()),
        lcm(std::lcm(range3.Size())),
        counts(new Count[length * lcm]) {
    }

    ~Solution() {
        delete[] counts;
    }

    int Part1();
    int Part2();
    int Part3();
};
