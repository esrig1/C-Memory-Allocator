#include "mem.h"              
#include <stdio.h>        
extern BLOCK_HEADER* first_header;

// return a pointer to the payload
// if a large enough free block isn't available, return NULL
void* Mem_Alloc(int size){


      if(size < 0) {
        return NULL;
      }
      
      int blockSize = size + 8;
      while(blockSize % 16 != 0){
          blockSize+=1;
      }
      
      BLOCK_HEADER* start = first_header;
      
      BLOCK_HEADER* nextHeader = NULL;
      int initialSize;
    // find a free block that's big enough
      
      while(start->size_alloc != 1) {
      if(start->size_alloc % 2 == 0 && start->size_alloc >= blockSize) {//if the block is free and is large enough
              initialSize = start->size_alloc;
             start->size_alloc = blockSize + 1;
             start->payload = size;
              if(initialSize > start->size_alloc && initialSize - start->size_alloc >= 16) {
                  nextHeader = (BLOCK_HEADER*)((unsigned long)start + (unsigned long)(start->size_alloc-1)); 
                  nextHeader->size_alloc = initialSize - blockSize;
                  nextHeader->payload = nextHeader->size_alloc - 8;
              }
              
              return (BLOCK_HEADER*)((unsigned long)start + (unsigned long)8);
          }
            
    
        start = (BLOCK_HEADER*)((unsigned long)start + (unsigned long)((int)(start->size_alloc/2)*2));   
        
        }
        
      
      
      
    // return NULL if we didn't find a block

    // allocate the block

    // split if necessary (if padding size is greater than or equal to 16 split the block)
  
    return NULL;
}


// return 0 on success
// return -1 if the input ptr was invalid
int Mem_Free(void *ptr){
    BLOCK_HEADER* previous = NULL;
    BLOCK_HEADER* start = first_header;
    BLOCK_HEADER* start2;
    BLOCK_HEADER* temp = (BLOCK_HEADER*)((unsigned long)ptr - (unsigned long)8);
    if((unsigned long) ptr % 8 != 0) {
        return -1;
    }
    if(temp->size_alloc % 2 == 0) {
        return -1;
    }
    if(ptr == NULL) {
        return -1;
    }
    
    int next;
    while(1) {
    start2 = (BLOCK_HEADER*)((unsigned long)start + (unsigned long)((int)(start->size_alloc/2)*2)); //next header
    if((BLOCK_HEADER*)((unsigned long)start + (unsigned long)8) == ptr) {
        
        if(start2->size_alloc == 1) {// case if the last block is being removed (not end of heap block)
            if(previous != NULL && previous->size_alloc % 2 == 0) {
            previous -> size_alloc += start->size_alloc;
            previous->payload = previous->size_alloc - 8;
            start = (BLOCK_HEADER*)((unsigned long)previous + (unsigned long)((int)(previous->size_alloc/2)*2));
            return 0;
        }
        }
        start->size_alloc -= 1;
        if(start2->size_alloc % 2 == 0) { //if next block is free
            start->size_alloc += start2->size_alloc;
            start->payload = start->size_alloc - 8;
            start2 = NULL;
            
        }
        if(previous != NULL && previous->size_alloc % 2 == 0) {
            previous -> size_alloc += start->size_alloc;
            previous->payload = previous->size_alloc - 8;
            start = (BLOCK_HEADER*)((unsigned long)previous + (unsigned long)((int)(previous->size_alloc/2)*2));
            return 0;
        }
        return 0;
      }
      previous = start;
        start = (BLOCK_HEADER*)((unsigned long)start + (unsigned long)((int)(start->size_alloc/2)*2));
        
        if(start->size_alloc == 1) {
            return -1;
        }
    }
    // traverse the list and check all pointers to find the correct block 
    // reach the end of the list without finding it return -1


    return -1;
}


