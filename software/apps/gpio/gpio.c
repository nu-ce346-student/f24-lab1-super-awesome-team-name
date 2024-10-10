#include "gpio.h"

#include <stdio.h>

typedef struct{
  // Step 3:
  // Add register definitions here
  uint32_t _unused_B[(0x504 - 0x0)/4];
  uint32_t OUT;
  uint32_t OUTSET;
  uint32_t OUTCLR;
  uint32_t IN;
  uint32_t DIR;
  uint32_t DIRSET;
  uint32_t DIRCLR;
  uint32_t LATCH;
  uint32_t DETECTMODE;
  uint32_t _unused_A[(0x700 - 0x524)/4 - 1];
  uint32_t PIN_CNF[32];
} gpio_reg_t;

volatile gpio_reg_t* GPIO_REG_P0 = (gpio_reg_t*) (0x50000000);
volatile gpio_reg_t* GPIO_REG_P1 = (gpio_reg_t*) (0x50000300);

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
//  dir - gpio direction (INPUT, OUTPUT)
void gpio_config(uint8_t gpio_num, gpio_direction_t dir) {
  // Implement me
  // This function should configure the pin as an input/output
  // Hint: Use proper PIN_CNF instead of DIR

  if(gpio_num < 32)
  {
    GPIO_REG_P0->PIN_CNF[gpio_num] |= (dir << 0) | (dir << 1); // is this okay? disconnect input buffer when output?
  } else
    GPIO_REG_P1->PIN_CNF[gpio_num-32] |= (dir << 0) | (dir << 1);

}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_set(uint8_t gpio_num) {
  // Implement me
  // This function should make the pin high
  // It can assume that the pin has already been configured

  if(gpio_num < 32)
  {
    GPIO_REG_P0->OUTSET |= (1 << gpio_num);
  } else
    GPIO_REG_P1->OUTSET |= (1 << (gpio_num - 32));
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_clear(uint8_t gpio_num) {
  // Implement me
  // This function should make the pin low
  // It can assume that the pin has already been configured
  if(gpio_num < 32)
  {
    GPIO_REG_P0->OUT |= (0 << gpio_num);
  } else
    GPIO_REG_P1->OUT |= (0 << (gpio_num - 32));
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
// Output:
//  bool - pin state (true == high)
bool gpio_read(uint8_t gpio_num) {
  // Implement me
  // This function should read the value from the pin
  // It can assume that the pin has already been configured

  if(gpio_num < 32)
  {
    return GPIO_REG_P0->IN & (1 << gpio_num);
  } else
    return GPIO_REG_P1->IN & (1 << gpio_num);

  return true; // shouldn't ever reach here
}

// prints out some information about the GPIO driver. Can be called from main()
void gpio_print(void) {
  // Use this function for debugging purposes
  // For example, you could print out struct field addresses
  // You don't otherwise have to write anything here
  printf("Port 0: OUT = %p, DIR = %p, PIN_CNF = %p \n", &(GPIO_REG_P0->OUT), &(GPIO_REG_P0->DIR), &(GPIO_REG_P0->PIN_CNF[0]));

  printf("OUT = %p, DIR = %p, PIN_CNF = %p \n", &(GPIO_REG_P1->OUT), &(GPIO_REG_P1->DIR), &(GPIO_REG_P1->PIN_CNF[0]));
}

