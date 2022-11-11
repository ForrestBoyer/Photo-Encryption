#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <math.h>
#include <algorithm>
using namespace std;

class FibLFSR {

public:

friend std::ostream& operator<<(std::ostream&, const FibLFSR& lfsr);

// Constructor to create LFSR with the given initial seed
FibLFSR(std::string seed){
    for(auto i = seed.begin(); i != seed.end(); i++){
        bits.push_back(*i - 48);
    }
    bits.pop_back();
}

// Simulate one step and return the new bit as 0 or 1
int step(){
    int newBit = (((bits[0] ^ bits[2]) ^ bits[3] ) ^ bits[5]);
    auto i = bits.begin();
    auto j = bits.begin();
    j++;
    for(; j != bits.end() + 1; i++, j++){
        *i = *j;
    }
    *(bits.end()) = newBit;
    return newBit;
}



// Simulate k steps and return a k-bit integer
int generate(int k){
    vector<int> ret;
    int total = 0;

    for(int i = 0; i < k; i++){
        ret.push_back(step());
    }

    reverse(ret.begin(), ret.end());

    for(int i = 0; i < int(ret.size()); i++){
        total += ret[i] * pow(2, i);
    }
    return total;
}


private:
// Any fields that you need
    vector<int> bits = {};
};

std::ostream& operator<<(std::ostream& out, const FibLFSR& lfsr){
    for(auto i = lfsr.bits.begin(); i != lfsr.bits.end() + 1; i++)
        out << *i; 
    return out;
}
