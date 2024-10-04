// GPIO app
//
// Uses MMIO to control GPIO pins

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf.h"
#include "nrf_delay.h"

#include "microbit_v2.h"
#include "gpio.h"

int main(void) {
  printf("Board started!\n");

  // Turn on all LEDs on the back of the Microbit
  // Add code here

  // Control LED with raw MMIO
  // Microphone LED is P0.20 and active high
  // Add code here
  *(uint32_t*) 0x50000504 |= (1 << 20); // dir
  *(uint32_t*) 0x50000514 |= (1 << 20); // out

  gpio_print();

  uint8_t pinArray[10] = {21, 22, 15, 24, 19, 28, 11, 31, 37, 30};
  for(int i = 0; i < sizeof(pinArray); i++){
    gpio_config(pinArray[i], 1);
  }

  for(int i = 0; i < 5; i++){
    gpio_set(pinArray[i]);
  }

  for(int i = 5; i < 10; i++){
    gpio_clear(pinArray[i]);
  }

  // loop forever
  printf("Looping\n");
  while (1) {

    // Control LED with buttons
    // Button A is P0.14 and active low
    // Button B is P0.23 and active low
    // Add code here

    nrf_delay_ms(100);
  }
}

