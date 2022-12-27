//this is a github codespaces online test for the CAN message handler

#include <stdio.h>
#include <stdint.h>
#define MAX_RECEIVE_TABLE_SIZE (3u)

int vehicleSpeed = 0;
int motorTorque = 0;
int test = 0;

uint32_t reverseBits(uint32_t num)
{
    uint32_t NO_OF_BITS = sizeof(num) * 8;
    uint32_t reverse_num = 0;
    for (int i = 0; i < NO_OF_BITS; i++) {
        if ((num & (1 << i)))
            reverse_num |= 1 << ((NO_OF_BITS - 1) - i);
    }
    return reverse_num;
}

long long unsigned int CAN_MESSAGE = 0b01001011010100101010010110101101;  //101001011010
//long long unsigned int CAN_MESSAGE = 0xABCD;
int DLC = 4;

typedef struct {

    int ID;
    int * pointerToUserVariable;
    int offset;
    int length;

} sReceiveMessage;

sReceiveMessage RecieveMessageTable[MAX_RECEIVE_TABLE_SIZE] = {

    //ID        //poiterToUserVariable          //offset    //length
    {0x200,     &vehicleSpeed,                  16,         12},
    {0x240,     &motorTorque,                   13,         2},
    {0x250,     &test,                          1,          2}

};

//right now it checks value, will need to change it to update variables
void IncomingCANMessageHandler(int * ID){

    for(int i = 0; i < MAX_RECEIVE_TABLE_SIZE; i++){

        if (RecieveMessageTable[i].ID == *ID){
            //printf("%d \n", RecieveMessageTable[i].ID);

            if(RecieveMessageTable[i].length == 1){
                *RecieveMessageTable[i].pointerToUserVariable = CAN_MESSAGE>>(DLC*8 - RecieveMessageTable[i].offset - RecieveMessageTable[i].length) & 0xFFFFFFFFFFFFFFFF>>(64 - RecieveMessageTable[i].length);
            }
            
            if(RecieveMessageTable[i].length > 1){
                uint32_t temp = CAN_MESSAGE>>(DLC*8 - RecieveMessageTable[i].offset - RecieveMessageTable[i].length) & 0xFFFFFFFFFFFFFFFF>>(64 - RecieveMessageTable[i].length);
                temp = reverseBits(temp);
                *RecieveMessageTable[i].pointerToUserVariable = temp>>(32 - RecieveMessageTable[i].length);
            }
        }

    }

}

int main()
{

    int num = 0x250;
    IncomingCANMessageHandler(&num);
    
    //printf("%u \n", vehicleSpeed);

    printf("%u \n", test);

    return 0;
}