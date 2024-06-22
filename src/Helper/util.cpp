#include <util.h>

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

namespace ts{
    vector<string> split(const string& src, char sep){
        vector<string> result;

        stringstream ss (src);
        string temp;

        while(getline(ss, temp, sep)){
            result.push_back(temp);
        }

        string& last = result.back();


        if (last.back() == '\0'){
            result.pop_back();
        }

        return result;
    }
}