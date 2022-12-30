#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define DLC 8U

//*RecieveMessageTable[i].pointerToUserVariable = CAN_MESSAGE>>(DLC*8 - RecieveMessageTable[i].offset - RecieveMessageTable[i].length) & 0xFFFFFFFFFFFFFFFF>>(64 - RecieveMessageTable[i].length);


#define CAN_BITS 64U
#define BIT_MASK(__length__) (UINT64_MAX >> (CAN_BITS - __length__))
#define GET_BITS(__data__, __offset__, __length__) ((__data__ >> (CAN_BITS - __length__ - __offset__)) & BIT_MASK(__length__))


// 0011`0110 & 0b00001111

// offset = 7, length = 4
// 0b 001100`11 00`110110 -> 00000000 1100`1100` >> DLC*8 - offset - length
// 0b 11111111 11111111 -> DLC*8 - length



// 0b

typedef enum MessageID {
    UNKNOWN_CAN_ID,
    AMK_SETPOINTS_CAN_ID = 0x240,
} MessageID;

typedef struct AMK_Setpoints_st{
    uint16_t torque_velocity;
    _Bool bEnable;
    int8_t motor_current;
}AMK_Setpoints_st;

// uint64_t test = 0b0100101001010010100101010110101010101010001101010111001011010110;

AMK_Setpoints_st AMK_Setpoints = {};

// typedef uint8_t decoder(rawData *uint8_t[8]);

uint8_t AMK_Setpoints_decoder(uint64_t rawData) {
    
    AMK_Setpoints.torque_velocity = GET_BITS(rawData, 48, 16);

    return 0;
}




int num1 = 0;
int num2 = 5;

int * num1Ptr = &num1;
int * num2Ptr = &num2;


int main()
{
    memcpy(num1Ptr, num2Ptr, sizeof(num1));
    printf("num1: %d, num2: %d \n", num1, num2);


    uint64_t test = 0b0100101001010010100101010110101010101010001101010111001011010110;
    
    printf("%lu \n", GET_BITS(test, 4, 11));

    //printf("Hello World \n");

    return 0;
}

