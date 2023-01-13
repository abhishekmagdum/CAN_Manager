#include <stdio.h>
#include <stdint.h>

uint32_t reverse_bytes(uint32_t bytes)
{
    uint32_t aux = 0;
    uint8_t byte;
    int i;

    for(i = 0; i < 32; i+=8)
    {                                   //0000ff
        byte = (bytes >> i) & 0xff;     //123456 
        aux |= byte << (32 - 8 - i);    
    }
    return aux;
}

int main()
{

    // 0b      1      1      0111       0      1

    unsigned int length = 8; //size of value

    unsigned char value = 0b11011101;
    unsigned int input = 0xAB01;
    printf("input: %u\n", value);
    unsigned int output = reverse_bytes(value);
    output = output >> (32 - sizeof(value)*8);
    printf("output: %u\n", output);



    return 0;
}