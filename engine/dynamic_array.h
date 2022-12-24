/**
 *  Relatively simple way to manage variable length array memory
 *  ! use sparingly, as dynamic memory allocation is expensive, and limited space is available on the calculator
 *  ! if you choose to start with a capacity of zero, the structure will fail silently, no checking is done for performance
 *  ! overall the use of dynamic memory is strongly discouraged by the developers of the library (and uses several kbs of space)
 * 
 *  TODO: write mini 'allocation' program which grows in small chunks (avoid malloc)
**/

#ifndef VALE_DYNAMIC_ARRAY
#define VALE_DYNAMIC_ARRAY

#include "type.h"
#include "error.h"

namespace memory {

template <typename T>
class dynamic_array {
    private:
        T *memory;
        uint capacity;
        uint length;

    public:
        dynamic_array(const uint capacity = 1) : capacity(capacity), length(0) {
            memory = (T*)malloc(capacity * sizeof(T));
            if(!memory){ error::exit_error("dynamic_array <malloc failed>", 0xAA, error::panic); }
        }

        ~dynamic_array(){
            free(memory);
        }

        void push(const T data){
            if(length == capacity){
                capacity *= 2;
                T* new_memory = (T*)malloc(capacity * sizeof(T));
                if(!new_memory){ error::exit_error("dynamic_array <malloc failed>", 0xBB, error::saveable); }
                for(uint i = 0; i < length; ++i){
                    new_memory[i] = memory[i];
                }
                free(memory);
                memory = new_memory;
            }
            memory[length++] = data;
        }

        uint size(){
            return length;
        }

        T& operator [](const uint idx){
            return memory[idx];
        }

        T* begin(){
            return memory;
        }

        T* end(){
            return memory + length;
        }
};

};

#endif