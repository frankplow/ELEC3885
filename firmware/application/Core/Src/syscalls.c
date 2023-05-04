#include <stddef.h>

#include "main.h"
#include "stm32f4xx_hal.h"

void _exit(int status) {
  Error_Handler();
}



