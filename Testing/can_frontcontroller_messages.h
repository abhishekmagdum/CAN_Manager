/*********************************************************
*                       INCLUDES
*********************************************************/

#include <stdio.h>
#include <stdint.h>
#include <string.h>

/*********************************************************
*                 TESTING GLOBAL VARIABLES
*********************************************************/

uint8_t RxData[8] = {
    0b10010100, 
    0b10010100, 
    0b10010100, 
    0b10010100, 
    0b10010100, 
    0b10010100, 
    0b10010100, 
    0b10010100
};

/*********************************************************
*                        ENUMS
*********************************************************/

typedef enum MessageID {
    UNKNOWN_CAN_ID = 0,
    AMK_SETPOINTS_CAN_ID = 0x240,
} MessageID_et;

// This status code will eventually be in a can.h file
typedef enum CAN_Ret {
    CAN_UNKNOWN_STATUS = 0,
    CAN_OK,
    CAN_ERROR,
}CAN_Ret_et;

//This contains endian type of incoming message
typedef enum Endianness {
    UNKNOWN_ENDIANNESS = 0,
    BIG_ENDIAN,
    LITTLE_ENDIAN,
} Endianness_et;

/*********************************************************
*                     MESSAGE STRUCTS
*********************************************************/

typedef struct AMK_Setpoints{
    uint16_t AMK_TargetVelocity;
    _Bool bEnable;
}AMK_Setpoints_st;

/*********************************************************
*                  MESSAGE WRAPPER STRUCT
*********************************************************/

typedef CAN_Ret_et BinaryUnmarshaller(uint8_t[8]);

typedef struct Message{
    MessageID_et ID;
    BinaryUnmarshaller* Unmarshal;
} Message_st;

/*********************************************************
*                       MESSAGE MACROS
*********************************************************/

#define AMK_SETPOINTS_ENDIANNESS (LITTLE_ENDIAN)

/*********************************************************
*                       SIGNAL MACROS
*********************************************************/

// AMK_Setpoints: AMK_TempMotor
#define AMK_SETPOINTS_AMK_TARGETVELOCITY_START   (24U)
#define AMK_SETPOINTS_AMK_TARGETVELOCITY_LENGTH  (16U)
#define AMK_SETPOINTS_AMK_TARGETVELOCITY_FACTOR  (0.125)
#define AMK_SETPOINTS_AMK_TARGETVELOCITY_OFFSET  (0U)

/*********************************************************
*                 GLOBAL STRUCT INSTANCES
*********************************************************/

AMK_Setpoints_st AMK_Setpoints = {};