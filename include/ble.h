//
// Created by Kok on 2/7/26.
//

#ifndef STM32WB55_BLE_H
#define STM32WB55_BLE_H

typedef enum {
    BLE_ERROR_OK,
    BLE_ERROR_CONFIG
} BLE_ErrorTypeDef;

BLE_ErrorTypeDef BLE_Config();

#endif //STM32WB55_BLE_H