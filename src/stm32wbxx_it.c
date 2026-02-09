//
// Created by Kok on 2/8/26.
//

#include "stm32wbxx_hal_ipcc.h"
#include "stm32wbxx_hal_rcc.h"

void NMI_Handler() {
    HAL_RCC_NMI_IRQHandler();
}
