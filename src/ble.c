//
// Created by Kok on 2/7/26.
//

#include "stm32wbxx.h"
#include "ble.h"

#include "ble_gap_aci.h"
#include "ble_gatt_aci.h"
#include "ble_hal_aci.h"

BLE_ErrorTypeDef BLE_Config() {
    // TODO: Driver to be properly implemented...

    uint16_t hservice, hname, happearance;
    if (aci_hal_set_tx_power_level(DISABLE, 0) != BLE_STATUS_SUCCESS) return BLE_ERROR_CONFIG;
    if (aci_gatt_init() != BLE_STATUS_SUCCESS) return BLE_ERROR_CONFIG;
    if (
    aci_gap_init(GAP_PERIPHERAL_ROLE,
        0,
        5,
        &hservice,
        &hname,
        &happearance
    ) != BLE_STATUS_SUCCESS
    ) {
        return BLE_ERROR_CONFIG;
    }
    if (aci_gap_set_io_capability(IO_CAP_NO_INPUT_NO_OUTPUT) != BLE_STATUS_SUCCESS) return BLE_ERROR_CONFIG;

    return BLE_ERROR_OK;
}
