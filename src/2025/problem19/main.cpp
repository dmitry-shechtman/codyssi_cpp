#include <iostream>

#include "Solution.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: solve <input>" << std::endl;
        return 1;
    }
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Cannot open " << argv[1] << std::endl;
        return 2;
    }
    Solution solution;
    if (!solution.Parse(file)) {
        std::cerr << "Error reading " << argv[1] << std::endl;
        return 3;
    }
    std::cout << solution.Part1() << std::endl;
    std::cout << solution.Part2() << std::endl;
    std::cout << solution.Part3() << std::endl;
    return 0;
}
