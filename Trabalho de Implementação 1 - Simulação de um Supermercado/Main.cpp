// Copyright [2016] <Felipe Longarai Trisotto (15103032) e William Magagnin Kair (15200624)>

#include <iostream>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <stdlib.h>
#include <ctime>

#include "./Supermarket.hpp"

int main(int argc, const char * argv[]) {
    
    std::srand(std::time(NULL));
    
    structures::Supermarket* market = new structures::Supermarket();
    
    market->run();
    market->outputs();
   
    return 0;
}
