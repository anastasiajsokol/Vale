/**
 *  For efficency 'work_queue' is a global variable, a better design would be to make in a singleton, however such a system would be less optimized
 * 
 *  Only tasks that take significant time to the point it is worth the additional overhead to fit them into a frame should be used
 * 
 *  ! dynamic allocation is iffy, switch to either overflow flushing or rejection (or both)
 * 
 *  * a minor performance and memory benifit can be gained by offsetting delay tasks by a few frames
**/

#ifndef VALE_WORK_QUEUE
#define VALE_WORK_QUEUE

#include "type.h"
#include "dynamic_queue.h"

namespace vale {

/**
 *  How the state object is used is entirely up to the task itself
 *      a one byte flag can be used for anything
 *      data can be used either as an interger, or a pointer to a more complicated data structure
 *          - if a more complicated structure is used, free any memory after the task is complete
 *          - note that the pointer method can be used to split a task into multiple sub-tasks
 *              - the datastructure ensures that tasks in the same queue will be called in the order you add them (FIFO)
 *                  - unless a delay is stated
**/
union task_state_t {
    char flag;

    union {
        int val;
        void* mem;
    } data;
};

typedef void (*task_handler_t)(task_state_t);

/**
 *  A task is simply a unit of work
 *      Ideally, task code should be as optimized as possible
**/
struct task_t {
    task_handler_t handler;
    task_state_t state;
};

class {
    private:
        struct delay_t {
            task_t task;
            clock_t time;
        };

        struct {
            memory::dynamic_queue<delay_t> queue{4};

            // if waiting() returns true, then it is ok to call pop()
            bool waiting(){
                return !queue.empty() && (queue[0].time < clock());
            }

            //! only call pop() if waiting() is true
            task_t pop(){
                return queue.pop().task;
            }

            void push(const delay_t &task){
                queue.push(task);
            }
        } delay_queue;
        
        memory::dynamic_queue<task_t> work_queue{8};
        memory::dynamic_queue<task_t> priority_queue{4};
    public:
        // update internal state, primarily delay queue
        void update(){
            while(delay_queue.waiting()){
                work_queue.push(delay_queue.pop());
            }
        }

        // check if any work is ready to be done
        // ! always check before calling dispatch()
        bool waiting(){
            return !(priority_queue.empty() && work_queue.empty());
        }

        // dispatch event
        // ! always check waiting() before calling dispatch()
        void dispatch(){
            if(!priority_queue.empty()){
                task_t val = priority_queue.pop();
                val.handler(val.state);
            } else if(!work_queue.empty()){ // technically, this doesn't have to be checked... but, ok
                task_t val = work_queue.pop();
                val.handler(val.state);
            }
        }

        void push(const task_t &task){
            work_queue.push(task);
        }

        void push_priority(const task_t &task){
            priority_queue.push(task);
        }

        void scedual(const task_t &task, clock_t time){
            delay_queue.push(delay_t{task, time});
        }

        void delay_ticks(const task_t &task, clock_t ticks){
            delay_queue.push(delay_t{task, clock() + ticks});
        }
        
        void delay_seconds(const task_t &task, clock_t seconds){
            delay_queue.push(delay_t{task, clock() + seconds * CLOCKS_PER_SEC});
        }
} work_queue;

};

#endif