//
// Created by Kok on 2/8/26.
//

#ifndef STM32WB55_SERVICE_AUTOMATION_H
#define STM32WB55_SERVICE_AUTOMATION_H

#include "../../lib/custom-ble/include/ble.h"

#define BT_ENC_KEY_SIZE                             0x10

#define BT_AUTOMATION_SERVICE_UUID                  0x1815          // Automation I/O Service UUID
#define BT_DIGITAL_OUTPUT_CHAR_UUID                 0x2A57          // Digital Output Characteristic UUID

#define BT_DIGITAL_OUTPUT_DGS_CNT_DESC_UUID         0x2909          // Number of Digitals Descriptor UUID
#define BT_DIGITAL_OUTPUT_DGS_CNT                   1               // Number of digitals

BLE_GattCharDescTypeDef BT_AutomationDOCharDescriptors[1] = {
    {
        .UUIDType = UUID_TYPE_16,
        .DescUUID = {.Char_UUID_16 = BT_DIGITAL_OUTPUT_DGS_CNT_DESC_UUID},
        .Len = 1,
        .MaxLen = 1,
        .Value = BT_DIGITAL_OUTPUT_DGS_CNT,
        .AccessPerm = ATTR_ACCESS_READ_ONLY,
        .SecurityPerm = ATTR_PERMISSION_AUTHEN_READ,
        .DescIsVariable = CHAR_VALUE_LEN_CONSTANT,
        .EvtMask = GATT_DONT_NOTIFY_EVENTS,
        .EncKeySize = BT_ENC_KEY_SIZE,
        .CharDescHandle = 0
    }
};

BLE_GattCharTypeDef BT_AutomationChars[1] = {
    {
        .UUIDType = UUID_TYPE_16,
        .CharUUID = {.Char_UUID_16 = BT_DIGITAL_OUTPUT_CHAR_UUID},
        .ValueLen = 1,
        .EncKeySize = BT_ENC_KEY_SIZE,
        .CharIsVariable = CHAR_VALUE_LEN_CONSTANT,
        .Permissions = ATTR_PERMISSION_AUTHEN_READ | ATTR_PERMISSION_AUTHEN_WRITE,
        .EvtMask = GATT_NOTIFY_ATTRIBUTE_WRITE,
        .Properties = CHAR_PROP_READ | CHAR_PROP_WRITE | CHAR_PROP_NOTIFY,
        .Descriptors = BT_AutomationDOCharDescriptors,
        .DescriptorsLen = sizeof(BT_AutomationDOCharDescriptors) / sizeof(BT_AutomationDOCharDescriptors[0]),
        .CharHandle = 0
    }
};

BLE_GattServiceTypeDef BT_AutomationService = {
    .UUIDType = UUID_TYPE_16,
    .ServiceUUID = {.Service_UUID_16 = BT_AUTOMATION_SERVICE_UUID},
    .ServiceType = PRIMARY_SERVICE,
    .MaxAttributeRecords = 8,
    .Chars = BT_AutomationChars,
    .CharsLen = sizeof(BT_AutomationChars) / sizeof(BT_AutomationChars[0]),
    .ServiceHandle = 0
};

#endif //STM32WB55_SERVICE_AUTOMATION_H