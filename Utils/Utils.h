#pragma once
#include <string>
#include <random>
#include "../Definitions.h"
template <typename Collection1, typename Collection2, typename Lambda>void zip(Collection1& t1, Collection2& t2, Lambda lambda){
    int smallerSize = t1.size() < t2.size()?t1.size():t2.size();
    for(int i = 0; i < smallerSize;i++){
        lambda(t1[i],t2[i]);
    }
}



class Utils {
public:

    static int genRand(int min, int max);
    static Vec<std::string> splitStr(std::string &s, char delim);

    template<typename T>static void deleteAtIndex(int i, Vec<T>& v){
        v.erase(v.begin() + i);
    }

    template<typename Collection,typename T>static bool vecContains(Collection& vec, T item){
        return std::find(vec.begin(), vec.end(), item) != vec.end();
    }
};


//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.



#define C_RESET   "\033[0m"
#define C_RED     "\033[31m"      /* Red */
#define C_MAGENTA "\033[35m"
#define C_YELLOW  "\033[33m"      /* Yellow */
#define C_BLUE    "\033[34m"

#define C_CYAN    "\033[36m"
#define C_WHITE   "\033[37m"      /* White */
#define C_BOLDGREEN   "\033[1m\033[32m"

/*
#define C_BLACK   "\033[30m"
#define C_GREEN   "\033[32m"

#define C_BOLDBLACK   "\033[1m\033[30m"
#define C_BOLDBLUE    "\033[1m\033[34m"
#define C_BOLDMAGENTA "\033[1m\033[35m"
#define C_BOLDCYAN    "\033[1m\033[36m"
#define C_BOLDWHITE   "\033[1m\033[37m"
*/

