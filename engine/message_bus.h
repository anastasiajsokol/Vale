/**
 *  For efficency 'message_bus' is a global variable, a better design would be to make in a singleton, however such a system would be less optimized
 * 
 *  ! use of dynamic array is rather terrible, switch out to static size with exit_error() on overflow when you know the size
**/

#ifndef VALE_MESSAGE_BUS
#define VALE_MESSAGE_BUS

#include "dynamic_array.h"

namespace vale {

enum sender_id{keyboard_msg = 0b10000000};

/**
 *  The mail type is passed along by the message bus
 *      origin: on character ID of origin of mail (TODO: add enums to abstract the meaning)
 *      message: this has 3 different possible states, and it is important that the reciever will know which one is in use
 *          code - some messages only need one character, in this case they will use code
 *          data - for slightly longer messages that need up to 3 bytes for whatever reason will use this list
 *          ref  - for more complicated messages that require a complex datastructure, use ref
**/
struct mail_t {
    char origin;

    union {
        char code;
        char data[3];
        void* ref;
    } message;
};

typedef void (*mail_handler_t)(const mail_t&);

/**
 *  every entity which wishes to respond to messages sent to the message bus must register a mailbox
 *      handler - a void function which takes a (const mail_t&)
 *      mask    - a char which can be used to mask senders (using sender_id enum, each bit in the mask is a different sender)
**/
struct mailbox_t {
    mail_handler_t handler;
    char mask;
};

class {
    private:
        memory::dynamic_array<mailbox_t> mailboxes;

    public:
        void enlist(const mailbox_t &mailbox){
            mailboxes.push(mailbox);
        }

        void send(const mail_t &mail){
            for(const mailbox_t &mailbox : mailboxes){
                if(mailbox.mask & mail.origin){
                    mailbox.handler(mail);
                }
            }
        }
} message_bus;

};

#endif