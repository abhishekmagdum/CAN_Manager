#include "can_frontcontroller_messages.h"

/*********************************************************
*                       MACROS
*********************************************************/

#define CAN_BITS (64U)
#define BIT_MASK(__length__) (UINT64_MAX >> (CAN_BITS - __length__))
#define GET_BITS(__data__, __start__, __length__) ((__data__ >> (CAN_BITS - __length__ - __start__)) & BIT_MASK(__length__))

/*********************************************************
*                    HELPER FUNCTIONS
*********************************************************/

//function from stackoverflow (works)
uint32_t reverseBits(uint32_t num)
{
    uint32_t NO_OF_BITS = sizeof(num) * 8;
    uint32_t reverse_num = 0;
    for (uint8_t i = 0; i < NO_OF_BITS; i++) {
        if ((num & (1 << i)))
            reverse_num |= 1 << ((NO_OF_BITS - 1) - i);
    }
    return reverse_num;
}



// Before:  AB CD EF 12 34 56 78 90
// After:   90 78 56 34 12 EF CD AB

static uint64_t getDataLittleEndian(uint8_t RawData[8]) {
    uint64_t ret;

    for (uint8_t i = 0; i<8; i++) {
        ret += RawData[i];
        ret <<= 8;
    }

    return ret;
}

static uint64_t getDataBigEndian(uint8_t RawData[8]) {
    uint64_t ret;

    for (uint8_t i = 7; i>=0; i--) {
        ret += RawData[i];
        ret <<= 8;
    }

    return ret;
}

CAN_Ret_et getDataFromByteArray(uint8_t dataArr[8], uint64_t* dataOutput, Endianness_et* Endianness) {
    switch (*Endianness)
    {
    case LITTLE_ENDIAN:
        *(dataOutput) = getDataLittleEndian(dataArr);
        break;
    case BIG_ENDIAN:
        *(dataOutput) = getDataBigEndian(dataArr);
        break;
    default:
        return CAN_ERROR;
        break;
    }

    return CAN_OK;
 }

/*********************************************************
*                    CAN FUNCTIONS
*********************************************************/

CAN_Ret_et UnmarshalAMKSetpoints(uint8_t RawData[8], Endianness_et * Endianness) {
    uint64_t data;
    AMK_Setpoints_st temp;
    
    CAN_Ret_et ret = getDataFromByteArray(RawData, &data, Endianness);
    if (ret != CAN_OK) return ret;

    //  Read raw bits
    temp.AMK_TargetVelocity = GET_BITS(data, AMK_SETPOINTS_AMK_TARGETVELOCITY_START, AMK_SETPOINTS_AMK_TARGETVELOCITY_LENGTH);

    //  Apply linear conversion
    temp.AMK_TargetVelocity = (temp.AMK_TargetVelocity * AMK_SETPOINTS_AMK_TARGETVELOCITY_FACTOR) + AMK_SETPOINTS_AMK_TARGETVELOCITY_OFFSET;

    //  Writing to global struct instance
    AMK_Setpoints = temp;
    
    return CAN_OK;
}


/*********************************************************
*                    MAIN FUNCTION
*********************************************************/
int main()
{

    printf("Hello World \n");

    return 0;
}
