#pragma once
#include "array"
#include "Utils/JVec.h"
#include "vector"
#define Expect_NotNull(val)if(val==nullptr)throw std::runtime_error(std::string(#val) + " is null")
template<typename T, unsigned int N>using Array = std::array<T,N>;
template<typename T>using Vec = JVec<T>;