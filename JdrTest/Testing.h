#pragma once
#include <utility>

#include "map"
#include "utility"
#include "string"
typedef std::optional<std::string> TestResult;
typedef std::function<TestResult()> Func;

class Test{
private:
    std::map<std::string,Func> tests{};
public:
    Test();
    void runTests();
    void addTest(const std::string& name,Func f);
};



