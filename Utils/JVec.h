#pragma once
#include "array"
#include "sstream"
template<typename T>class JVec: public std::vector<T>{
public:
    JVec(){}

    



    T operator [](unsigned int i) const    {
        return this->at(i);
    }

    T& operator [](int i) {
        return this->at(i);
    }


    friend std::ostream & operator<<(std::ostream & cout, JVec const & v){
       std::stringstream sstream{};
        sstream << "JVec{";
        for(int i = 0;i < v.size();i++){
            sstream << v[i] << ", ";
        }
        std::string s = sstream.str();
        if(v.size() > 0){
            s.pop_back();
            s.pop_back();
        }
        s+="}";
        return cout << s;
    }
};