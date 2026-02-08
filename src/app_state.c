//
// Created by Kok on 2/8/26.
//

#include "app_state.h"

BLE_InitTypeDef BLE_Config;

APP_State gAppState = {
    .pBLE_Config = &BLE_Config
};