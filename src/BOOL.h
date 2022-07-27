#pragma once
#include <string>
#include <iostream>

namespace heart{
    class BOOL{
        public:
        std::string name, val;
        BOOL(std::string& NAME,std::string& VALUE);
        ~BOOL(){
            name = "";
            val = "";
        }
        bool isUsing = false;
    }
}