#include <fstream>
#include <sstream>

#include "Solution.h"

bool Parse(std::ifstream& file, std::vector<Rule>& rules) {
    std::string line;
    Rule rule;
    while (std::getline(file, line)) {
        std::istringstream istream(line);
        istream >> rule;
        rules.push_back(rule);
    }
    return true;
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: solve <file> [width[,height[,[depth[,anakata]]]]" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Cannot open " << argv[1] << std::endl;
        return 2;
    }

    std::vector<Rule> rules;
    if (!Parse(file, rules)) {
        std::cerr << "Error reading " << argv[1] << std::endl;
        return 3;
    }

    Point4 min(0, 0, 0, -1), size(10, 15, 60, 3);
    if (argc > 2) {
        std::istringstream istream(argv[2]);
        istream >> size;
    }
    Range4 range = Range4::FromMinAndSize(min, size);

    Solution solution(rules, range);
    int part1 = solution.Part1();
    int part2 = solution.Part2();
    int part3 = solution.Part3();

    std::cout << part1 << std::endl;
    std::cout << part2 << std::endl;
    std::cout << part3 << std::endl;

    return 0;
}
