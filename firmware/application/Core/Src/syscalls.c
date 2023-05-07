#include <stddef.h>

#include "main.h"
#include "stm32f4xx_hal.h"

void _exit(int status) {
  Error_Handler();
}

int _write(int fd, const char *data, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    ITM_SendChar(data[i]);
  }
  return size;
}

