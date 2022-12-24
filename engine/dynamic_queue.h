/**
 *  Manager for a circular buffer queue
 *  ! use sparingly, as dynamic memory allocation is expensive, and limited space is available on the calculator
 *  ! if you choose to start with a capacity of zero, the structure will fail silently, no checking is done for performance
 *  ! overall the use of dynamic memory is strongly discouraged by the developers of the library (and uses several kbs of space)
 * 
 *  TODO: perhaps impliment iterator
 *  TODO: write mini 'allocation' program which grows in small chunks (avoid malloc)
**/

#ifndef VALE_DYNAMIC_QUEUE
#define VALE_DYNAMIC_QUEUE

#include "type.h"
#include "error.h"

namespace memory {

template <typename T>
class dynamic_queue {
    private:
        T *memory;

        uint capacity;

        uint next;
        uint last;

        bool full;

    public:
        dynamic_queue(const uint capacity = 1) : capacity(capacity), next(0), last(0), full(false) {
            memory = (T*)malloc(capacity * sizeof(T));
            if(!memory){ error::exit_error("dynamic_queue <malloc failed>", 0xAA, error::panic); }
        }

        ~dynamic_queue(){
            free(memory);
        }

        T& operator [](const uint i){
            return memory[(next + i) % capacity];
        }

        void push(const T data){
            if(full){
                uint new_capacity = 2 * capacity;
                T *new_memory = (T*)malloc(new_capacity * sizeof(T));
                if(!memory){ error::exit_error("dynamic_queue <malloc failed>", 0xBB, error::saveable); }
                for(uint i = 0; i < capacity; ++i){
                    new_memory[i] = (*this)[i];
                }
                next = 0;
                last = capacity;
                capacity = new_capacity;
                free(memory);
                memory = new_memory;
                full = false;
            }

            memory[last] = data;
            last = (last + 1) % capacity;
            full = (next == last);
        }

        T pop(){
            if(!full && next == last){
                error::exit_error("dynamic_queue<empty>.pop()", 0xCC, error::saveable);
            }
            full = false;
            T value = memory[next];
            next = (next + 1) % capacity;
            return value;
        }

        uint size(){
            return last * ((last > next) ? 1 : capacity) - next;
        }

        bool empty(){
            return !full && (next == last);
        }
};

};

#endif