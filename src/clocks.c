//
// Created by Kok on 2/8/26.
//

#include "clocks.h"

HAL_StatusTypeDef CLOCKS_Config() {

    HAL_StatusTypeDef status;

    RCC_OscInitTypeDef OSC_Config = {
        .OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_MSI | RCC_OSCILLATORTYPE_HSI48,
        .HSEState = RCC_HSE_ON,
        .LSEState = RCC_LSE_ON,
        .MSIState = RCC_MSI_ON,
        .MSIClockRange = RCC_MSIRANGE_6,
        .HSI48State = RCC_HSI48_OFF,
        .HSIState = RCC_HSI_OFF,
        .LSIState = RCC_LSI_OFF,
        .PLL = {.PLLState = RCC_PLL_OFF}
    };
    if ((status = HAL_RCC_OscConfig(&OSC_Config)) != HAL_OK) return status;

    RCC_ClkInitTypeDef CLK_Config = {
        .ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_HCLK2 | RCC_CLOCKTYPE_HCLK4 | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2,
        .SYSCLKSource = RCC_SYSCLKSOURCE_STATUS_HSE,
        .AHBCLKDivider = RCC_SYSCLK_DIV1,
        .AHBCLK2Divider = RCC_SYSCLK_DIV1,
        .AHBCLK4Divider = RCC_HCLK_DIV1,
        .APB1CLKDivider = RCC_HCLK_DIV1,
        .APB2CLKDivider = RCC_HCLK_DIV1
    };
    if ((status = HAL_RCC_ClockConfig(&CLK_Config, FLASH_LATENCY_1)) != HAL_OK) return status;

    // Enable HSE failure detection
    HAL_RCC_EnableCSS();
    __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_MSI);

    return HAL_OK;
}