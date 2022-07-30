#include "Utils.h"
#include "array"

#include <vector>
#include <sstream>


Vec<std::string> Utils::splitStr(std::string& s, char delim){
    std::stringstream test(s);
    std::string segment;
    Vec<std::string> seglist{};

    while(std::getline(test, segment, delim))
    {
        seglist.push_back(segment);
    }
    return seglist;
}

std::mt19937 generator (std::time(nullptr));

int Utils::genRand(int min, int max) {
    return (int)std::uniform_real_distribution<>(min, max)(generator);
}
