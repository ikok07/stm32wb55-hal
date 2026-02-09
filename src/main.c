#include <stdint.h>

#include "clocks.h"
#include "shci.h"
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

    if (CLOCKS_Config() != HAL_OK) {
        while (1);
    }

    // Start CPU2


    while (1);
}

/**
 * @brief Restart device if HSE failed
 */
void HAL_RCC_CSSCallback() {
    HAL_NVIC_SystemReset();
}