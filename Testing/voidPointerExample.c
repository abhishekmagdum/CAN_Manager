#include <stdio.h>
#include <stdint.h>

typedef enum dataTypes{
    UINT8,
    UINT16,
    UINT32,
    UINT64,
    BOOL,
} dataTypes;



void writeToUserVariable(){




    
}

int main()
{
    // printf("Hello World");

    uint8_t num = 5;
    //uint8_t * numPtr = &num;

    void * numPtr = &num;

    _Bool test = 0b1;

    printf("num is: %u \n", *(uint8_t *)numPtr);
    return 0;
}
