#include <cassert>  // assert
#include <cstddef>  // size_t
#include <cstdint>  // uint64_t, uint32_t
#include <iostream>

// Expands the binary representation of input by a factor of scale.
// e.g., expand(0b1111ull, 3) == 0b001001001001

// 101 -->  0001 - 0 - 0001
uint64_t expand(uint64_t input, uint32_t scale) {

    uint64_t answer = 0;
    uint64_t next_available_position = 0;

    for (uint64_t i = 0; i < 64; ++i) { // iterate through each bit in the input

        auto is_ith_bit_set = (((uint64_t)1 << i) & input);
        answer = answer  | (is_ith_bit_set << next_available_position);
        next_available_position += is_ith_bit_set ? (scale - 1) : 1;

        /*

        Basic idea: we iterate through each bit in the input.
        If that bit is 1, then in our final answer, the position of the NEXT set bit will be the position of the first bit we checked, PLUS <scale> - 1 positions to the left.
        So if scale=3 and our input is 0011, then its like this:
        01001 -- >   0 - 001 - 0 - 001
            1. Is the 0'th bit set? 
                - If yes: Then the position of the 1st bit (if its also set) will be the position of bit 0 (i.e. 0) PLUS scale=3 - 1. 
                - If no, then the position of the 1st bit will be the position of bit 0 plus one.

        answer = 0
        next_available_position = 0        

        Here's the less efficient sudo code I initially came up with
        for (uint64_t i = 0; i < 64; ++i) {

            if (i'th bit is set) : 
                answer = answer | (1 << next_available_position)
                next_available_position += scale - 1
            else : {
                answer = answer | (0 << next_available_position)
                next_available_position += 1 // since we're not adding anymore 0's since bit i is not 1.
            }

            
        }
        
        */

    }
    return answer;  // replace this with your impl!
}

int main() {
    // test here... 

    std::cout << expand(3, 4) << "\n"; // should print 17
    return 0;
}
