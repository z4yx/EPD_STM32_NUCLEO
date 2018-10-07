#include "stm32l0xx_hal.h"
extern UART_HandleTypeDef huart2;

/* Retargeting functions for gcc-arm-embedded */

int _write (int fd, char *ptr, int len)
{
  /* Write "len" of char from "ptr" to file id "fd"
   * Return number of char written.
   * Need implementing with UART here. */
  int i;
  for (i = 0; i < len; ++i)
  {
    _ttywrch(ptr[i]);
  }
  return len;
}

int _read (int fd, char *ptr, int len)
{
  /* Read "len" of char to "ptr" from file id "fd"
   * Return number of char read.
   * Need implementing with UART here. */
  return len;
}

void _ttywrch(int ch) {
  /* Write one char "ch" to the default console
   * Need implementing with UART here. */
  HAL_UART_Transmit(&huart2, &ch, 1, 1000);
}
