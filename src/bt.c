//
// Created by Kok on 2/8/26.
//

#include "bt.h"
#include "bt_service_automation.h"

#include "app_state.h"

void BT_Init() {
    BLE_GattServiceTypeDef BLE_Services[1] = {
        BT_AutomationService
    };

    *gAppState.pBLE_Config = (BLE_InitTypeDef) {
        .TxPowerLevel = 0x10,
        .IoCapability = IO_CAP_DISPLAY_ONLY,
        .GapInit = (BLE_GapInitTypeDef) {
            .NameLen = 10,
            .PrivacyEnabled = PRIVACY_DISABLED,
            .Role = GAP_PERIPHERAL_ROLE,
            .Privacy = (BLE_GapPrivacyConfigTypeDef) {
                .Bonding = BONDING,
                .AddrType = GAP_PUBLIC_ADDR,
                .SecureConnection = SC_PAIRING_ONLY,
                .MitmProtection = MITM_PROTECTION_REQUIRED_AS_MANDATORY,
                .KeyPressNotifSup = KEYPRESS_NOT_SUPPORTED,
                .MinEncKeySize = 0x07,
                .MaxEncKeySize = 0x10,
                .UseFixedPin = USE_FIXED_PIN_FOR_PAIRING_ALLOWED,
                .FixedPin = 123456
            }
        },
        .GattInit = (BLE_GattInitTypeDef) {
            .Services = BLE_Services,
            .ServicesLen = sizeof(BLE_Services) / sizeof(BLE_Services[0])
        }
    };
}
