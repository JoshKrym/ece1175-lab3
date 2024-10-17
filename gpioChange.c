#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <fcntl.h>

//each pin is 2 bits
void modifyValue(volatile long* gpio_map, int reg, int pin, long value){
    value = value << pin*2;
    gpio_map[reg]|=value;
}

int main(void){
    
    int memFile = open("/dev/mem", O_RDWR|O_SYNC);
    volatile long* gpio_map = (long*)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, memFile, 0x7e200000);
    //GPIO_PUP_PDN_CNTRL_REG2 is the register I want
    //offset of 0xec or 59
    //Resistor select for gpio42 is 21:20 on the bits or the 10th gpio pin in this register
    modifyValue(gpio_map, 59, 10, 10);
}
