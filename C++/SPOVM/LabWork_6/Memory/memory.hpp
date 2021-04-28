//
//  memory.hpp
//  LabWork_6
//
//  Created by Belousov Ilya on 23.04.21.
//

#ifndef memory_hpp
#define memory_hpp

#include <iostream>
#include <sys/mman.h>
#include <stdio.h>
#include <cmath>

#define FREE_BLOCK_MEMORY 0
#define BUSY_BLOCK_MEMORY 1

#define MEMORY_ALLOCATE 1000 //(1024 * 1024 * 16)

#include <string>
#include <strings.h>

struct illoc_struct {
    struct illoc_struct *next;
    struct illoc_struct *previous;
    size_t size;
    unsigned char *value;
    int type;
};

namespace cMemory {
    // illoc
    static struct illoc_struct *illocStr;
    
    static unsigned char memoryRAM[MEMORY_ALLOCATE];
    
    void illoc_error(const char *msg, const int code) {
        std::cout << "Error msg: " << msg << std::endl;
        std::cout << "Code: " << code << std::endl;
        exit(code);
    }
    
    void illoc_initializer() {
        illocStr = (struct illoc_struct *) memoryRAM;
        illocStr->value = (unsigned char *) illocStr + sizeof(struct illoc_struct);
        illocStr->size = MEMORY_ALLOCATE - sizeof(struct illoc_struct);
        illocStr->next = nullptr;
        illocStr->previous = nullptr;
        illocStr->type = FREE_BLOCK_MEMORY;
    }
    
    struct illoc_struct* illoc_free_block_search(size_t size) {
        struct illoc_struct *current = illocStr;
        while (current != nullptr) {
            if (current->type == FREE_BLOCK_MEMORY && current->size >= size) {
                return current;
            }
            current = current->next;
        }
        if (current == nullptr) {
            illoc_error("Memory cannot be allocated there is no free structure of the specified size!", 4);
        }
        return current;
    }
    
    struct illoc_struct * illoc_initializer_next(size_t &size) {
        struct illoc_struct *current = nullptr, *newBlock = nullptr;
        current = illoc_free_block_search(size);
        current->size -= size;
        current->type = BUSY_BLOCK_MEMORY;
        
        newBlock = (struct illoc_struct *) (current->value + size);
        newBlock->value = (unsigned char *) newBlock + sizeof(struct illoc_struct);
        newBlock->size = current->size - sizeof(struct illoc_struct);
        newBlock->next = nullptr;
        newBlock->previous = current;
        newBlock->type = FREE_BLOCK_MEMORY;
        
        current->next = newBlock;
        current->size = size;
        return current;
    }
    
    void illoc_print_block() {
        struct illoc_struct *current = illocStr;
        std::cout << "\t ------RAM------" << std::endl;
        while (current != nullptr) {
            std::cout << "\nAddress of the current block: " << current;
            
            std::cout << "\nNext block address: " << (current->next == nullptr ? nullptr : current->next);
            
            std::cout << "\nPrevious block address: " << current->previous;
            std::cout << "\nBlock size (bytes): " << current->size;
            std::cout << "\nBlock type: " << (current->type == FREE_BLOCK_MEMORY ? "FREE" : "BUSY");
            
            if (current->type != FREE_BLOCK_MEMORY)
                std::cout << "\nBlock content: " << current->value;
            
            std::cout << "\n" << std::endl;
            current = current->next;
        }
    }
    
//    void illoc_size_adjustment(size_t &size) {
//        int x = 1;
//        if (size >= INT_MAX) illoc_error("Invalid buffer size!", 1);
//        while (true) {
//            if (pow(2, x) >= size) {
//                size = pow(2, x);
//                break;
//            }
//            x++;
//        }
//        return;
//    }
    
    void illoc_check_size(size_t &size) {
//        if (size >= INT_MAX) illoc_error("Invalid buffer size!", 1);
        if (size >= MEMORY_ALLOCATE - sizeof(struct illoc_struct)) {
            illoc_error("The specified memory exceeds the size of the buffer itself!", 4);
        }
    }
    
    void* illoc(size_t size) {
        struct illoc_struct *current = nullptr;
//        illoc_size_adjustment(size);
        illoc_check_size(size);
        if (illocStr == nullptr) {
            illoc_initializer();
        }
        current = illoc_initializer_next(size);
        return (void*) current->value;
    }
    
    // ifree
    template <typename type>
    struct illoc_struct* illoc_find_memory(type *addrFind) {
        struct illoc_struct *current = illocStr;
        while (current != NULL) {
            if (current->value == (unsigned char *) addrFind) {
                return current;
            }
            current = current->next;
        }
        return current;
    }
    
    void illoc_free_value_block(struct illoc_struct *current) {
        memset(current->value, '\0', current->size);
    }
    
    void illoc_free_block(struct illoc_struct *current) {
        illoc_free_value_block(current);
        current->type = FREE_BLOCK_MEMORY;
    }
    
    void illoc_delete_block(struct illoc_struct *current) {
        memset(current, '\0', current->size + sizeof(struct illoc_struct));
    }
    
    bool illoc_memory_empty() {
        struct illoc_struct *current = illocStr;
        while (current != nullptr) {
            if (current->type == BUSY_BLOCK_MEMORY) return false;
            current = current->next;
        }
        return true;
    }
    
    void illoc_free_and_union() {
        struct illoc_struct *current = illocStr;
        while (current->next != nullptr) {
            if (current->type == FREE_BLOCK_MEMORY && current->next->type == FREE_BLOCK_MEMORY) {
                current->size = current->size + current->next->size + sizeof(struct illoc_struct);
                if (current->next->next != nullptr) {
                    current->next = current->next->next;
                    current->next->previous = current;
                } else {
                    current->next = nullptr;
                }
                illoc_free_value_block(current);
            }
            else {
                current = current->next;
            }
        }
    }
    
    
    template <typename type>
    void ifree(type *addr) {
        if (addr != nullptr) {
            struct illoc_struct *current = illoc_find_memory(addr);
            if (current != nullptr) {
                illoc_free_block(current);
            }
            
            illoc_free_and_union();
        }
        return;
    }

    struct illoc_struct* rilloc_less(struct illoc_struct *current ,size_t &size) {
        struct illoc_struct *shiftFree = nullptr, *shiftBusy = nullptr, *newBlock = nullptr;
        if (current->next->type == FREE_BLOCK_MEMORY) {
            shiftFree = (struct illoc_struct *) (current->value + size);
            
            memset(current->value + size - 1, '\0', size);
            memmove(shiftFree, current->next, sizeof(struct illoc_struct));
            
            shiftFree->value = (unsigned char *) shiftFree + sizeof(struct illoc_struct);
            shiftFree->size += (current->size - size);
            
            if (shiftFree->next != nullptr) {
                shiftFree->next->previous = shiftFree;
            }
            
            current->next = shiftFree;
            current->size = size;
            
            illoc_free_value_block(shiftFree);
            return current;
        } else if (current->previous != NULL) {
            if (current->previous->type == FREE_BLOCK_MEMORY) {
                shiftBusy = (struct illoc_struct *) (current->previous->value + (current->previous->size + (current->size - size)));
                
                memmove(shiftBusy, current, sizeof(struct illoc_struct) + size - 1);
                
                shiftBusy->value = (unsigned char *) shiftBusy + sizeof(struct illoc_struct);
                shiftBusy->previous->size += shiftBusy->size - size;
                shiftBusy->size = size;
                shiftBusy->next->previous = shiftBusy;
                shiftBusy->previous->next = shiftBusy;
                
                illoc_free_value_block(shiftBusy->previous);
                return shiftBusy;
            }
        }
        newBlock = illoc_free_block_search(size);
        if (newBlock == nullptr) {
            illoc_error("No allocate memory!", 4);
        }
        
        illoc_initializer_next(size);
        
        newBlock->type = BUSY_BLOCK_MEMORY;
        
        memmove(newBlock->value, current->value, current->size);
        
        newBlock->size = size;
        
        illoc_free_block(current);
        return newBlock;
    }
    
    struct illoc_struct* rilloc_more(struct illoc_struct *current , size_t &size) {
        struct illoc_struct *shiftFree = nullptr, *newBlock = nullptr;
        size -= current->size;
        if (current->next != nullptr) {
            if (current->next->type == FREE_BLOCK_MEMORY && current->next->size > size) {
                shiftFree = (struct illoc_struct *) (current->value + size);
                
                memmove(shiftFree, current->next, sizeof(struct illoc_struct));
                memset(current->next, '\0', size);
                
                shiftFree->value = (unsigned char *) shiftFree + sizeof(struct illoc_struct);
                shiftFree->size -= size;
                
                if (shiftFree->next != nullptr) {
                    shiftFree->next->previous = shiftFree;
                }
                current->next = shiftFree;
                current->size = size + current->size;
                
                return current;
            } else if (current->next->type == FREE_BLOCK_MEMORY && current->next->size + sizeof(struct illoc_struct) == size) {
                shiftFree = current->next;
                current->next = shiftFree->next;
                shiftFree->next->previous = current;
                current->size += size;
                
                illoc_delete_block(shiftFree);
                
                return current;
            }
        }
        if (current->previous != nullptr) {
            if (current->previous->type == FREE_BLOCK_MEMORY && current->previous->size > size) {
                current->previous->size -= size;
                
                shiftFree = (struct illoc_struct *) (current->previous->value + current->previous->size);
                
                memmove(shiftFree, current, sizeof(struct illoc_struct) + current->size);
                shiftFree->value = (unsigned char *) shiftFree + sizeof(struct illoc_struct);
                memset((shiftFree->value + shiftFree->size), '\0', size);
                
                shiftFree->size += size;
                shiftFree->next->previous = shiftFree;
                shiftFree->previous->next = shiftFree;
                
                return shiftFree;
            } else if (current->previous->type == FREE_BLOCK_MEMORY && current->previous->size + sizeof(struct illoc_struct) == size) {
                shiftFree = current->previous;
                
                if (shiftFree->previous == nullptr) current->previous = nullptr;
                
                memmove(shiftFree, current, sizeof(struct illoc_struct) + current->size);
                shiftFree->value = (unsigned char *) shiftFree + sizeof(struct illoc_struct);
//                size_t a = (size + shiftFree->size) + sizeof(struct illoc_struct) - 1;
                memset((shiftFree->value + shiftFree->size), '\0', size);
                
                shiftFree->next->previous = shiftFree;
                shiftFree->size += size;
                return shiftFree;
            }
        }
        
        newBlock = illoc_free_block_search(size);
        if (newBlock == nullptr) {
            illoc_error("No allocate memory!", 4);
        }
        
        size += current->size;
        
        illoc_initializer_next(size);
        
        newBlock->type = BUSY_BLOCK_MEMORY;
        
        memmove(newBlock->value, current->value, current->size);
        
        illoc_free_block(current);
        return newBlock;
    }
    
    template <typename type>
    void* rilloc(type *addr ,size_t size) {
        struct illoc_struct *current = illoc_find_memory(addr);
//        illoc_size_adjustment(size);
        illoc_free_and_union();
        if (current->size > size) {
            current = rilloc_less(current, size);
        } else if (current->size < size) {
            current = rilloc_more(current, size);
        }
        return (void*) current->value;
    }
}

#endif /* memory_hpp */

