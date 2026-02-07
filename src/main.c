#include <stdint.h>
#include "stm32wbxx.h"
#include "stm32wbxx_hal.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
  if (HAL_Init() != HAL_OK) {
    while (1);
  }

  while (1);
}
