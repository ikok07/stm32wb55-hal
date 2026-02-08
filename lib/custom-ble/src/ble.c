//
// Created by Kok on 2/7/26.
//

#include "stm32wbxx.h"
#include "../include/ble.h"

#include "ble_gap_aci.h"
#include "ble_gatt_aci.h"
#include "ble_hal_aci.h"

BLE_ErrorTypeDef BLE_Init(BLE_InitTypeDef *Cfg) {

    if (aci_hal_set_tx_power_level(DISABLE, Cfg->TxPowerLevel) != BLE_STATUS_SUCCESS) return BLE_ERROR_CONF_TX_PWR;

    if (aci_gatt_init() != BLE_STATUS_SUCCESS) return BLE_ERROR_CONF_GATT;

    if (
    aci_gap_init(
        Cfg->GapInit.Role,
        Cfg->GapInit.PrivacyEnabled,
        Cfg->GapInit.NameLen,
        &Cfg->GapInit.ServiceHandle,
        &Cfg->GapInit.NameHandle,
        &Cfg->GapInit.AppearanceHandle
    ) != BLE_STATUS_SUCCESS
    ) {
        return BLE_ERROR_CONF_GAP;
    }

    if (
        aci_gap_set_io_capability(
            Cfg->IoCapability
        ) != BLE_STATUS_SUCCESS
    ) {
        return BLE_ERROR_CONF_GAP_CAPABILITY;
    };

    if (
        aci_gap_set_authentication_requirement(
            Cfg->GapInit.Privacy.Bonding,
            Cfg->GapInit.Privacy.MitmProtection,
            Cfg->GapInit.Privacy.SecureConnection,
            Cfg->GapInit.Privacy.KeyPressNotifSup,
            Cfg->GapInit.Privacy.MinEncKeySize,
            Cfg->GapInit.Privacy.MaxEncKeySize,
            Cfg->GapInit.Privacy.UseFixedPin,
            Cfg->GapInit.Privacy.FixedPin,
            Cfg->GapInit.Privacy.AddrType
        ) != BLE_STATUS_SUCCESS
    ) {
        return BLE_ERROR_CONF_GAP_AUTH;
    }

    for (int i = 0; i < Cfg->GattInit.ServicesLen; i++) {
        if (
            aci_gatt_add_service(
                Cfg->GattInit.Services[i].UUIDType,
                &Cfg->GattInit.Services[i].ServiceUUID,
                Cfg->GattInit.Services[i].ServiceType,
                Cfg->GattInit.Services[i].MaxAttributeRecords,
                &Cfg->GattInit.Services[i].ServiceHandle
            ) != BLE_STATUS_SUCCESS
        ) {
            return BLE_ERROR_CONF_GATT_SERVICE;
        };

        for (int j = 0; j < Cfg->GattInit.Services[i].CharsLen; j++) {
            if (
                aci_gatt_add_char(
                    Cfg->GattInit.Services[i].ServiceHandle,
                    Cfg->GattInit.Services[i].Chars[j].UUIDType,
                    &Cfg->GattInit.Services[i].Chars[j].CharUUID,
                    Cfg->GattInit.Services[i].Chars[j].ValueLen,
                    Cfg->GattInit.Services[i].Chars[j].Properties,
                    Cfg->GattInit.Services[i].Chars[j].Permissions,
                    Cfg->GattInit.Services[i].Chars[j].EvtMask,
                    Cfg->GattInit.Services[i].Chars[j].EncKeySize,
                    Cfg->GattInit.Services[i].Chars[j].CharIsVariable,
                    &Cfg->GattInit.Services[i].Chars[j].CharHandle
                ) != BLE_STATUS_SUCCESS
            ) {
                    return BLE_ERROR_CONF_GATT_CHAR;
            }

            for (int k = 0; k < Cfg->GattInit.Services[i].Chars[j].DescriptorsLen; k++) {
                if (
                    aci_gatt_add_char_desc(
                        Cfg->GattInit.Services[i].ServiceHandle,
                        Cfg->GattInit.Services[i].Chars[j].CharHandle,
                        Cfg->GattInit.Services[i].Chars[j].Descriptors[k].UUIDType,
                        &Cfg->GattInit.Services[i].Chars[j].Descriptors[k].DescUUID,
                        Cfg->GattInit.Services[i].Chars[j].Descriptors[k].MaxLen,
                        Cfg->GattInit.Services[i].Chars[j].Descriptors[k].Len,
                        &Cfg->GattInit.Services[i].Chars[j].Descriptors[k].Value,
                        Cfg->GattInit.Services[i].Chars[j].Descriptors[k].SecurityPerm,
                        Cfg->GattInit.Services[i].Chars[j].Descriptors[k].AccessPerm,
                        Cfg->GattInit.Services[i].Chars[j].Descriptors[k].EvtMask,
                        Cfg->GattInit.Services[i].Chars[j].Descriptors[k].EncKeySize,
                        Cfg->GattInit.Services[i].Chars[j].Descriptors[k].DescIsVariable,
                        &Cfg->GattInit.Services[i].Chars[j].Descriptors[k].CharDescHandle
                    ) != BLE_STATUS_SUCCESS
                ) {
                    return BLE_ERROR_CONF_GATT_CHAR_DESC;
                }
            }
        }
    }

    return BLE_ERROR_OK;
}
