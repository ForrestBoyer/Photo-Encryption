#include "FibLFSR.hpp"

int main(){
    FibLFSR flfsr("1011011000110110");
    //std::cout << flfsr << std::endl;
    
    for(int i = 0; i < 10; i++){
        int x = flfsr.step();
        std::cout << flfsr << " " << x << std::endl;
    }

    std::cout << std::endl << "GENERATE" << std::endl << std::endl;

    FibLFSR flfsr2("1011011000110110");

    for(int i = 0; i < 7; i++){
        int x = flfsr2.generate(5);
        std::cout << flfsr2 << " " << x << std::endl;
    }
}