//
// Created by Kok on 2/8/26.
//

#ifndef STM32WB55_APP_STATE_H
#define STM32WB55_APP_STATE_H

#include "../lib/custom-ble/include/ble.h"

typedef struct {
    BLE_InitTypeDef *pBLE_Config;
} APP_State;

extern APP_State gAppState;

#endif //STM32WB55_APP_STATE_H