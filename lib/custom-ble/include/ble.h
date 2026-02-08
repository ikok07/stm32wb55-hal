//
// Created by Kok on 2/7/26.
//

#ifndef STM32WB55_BLE_H
#define STM32WB55_BLE_H

#include <stdint.h>

#include "ble_types.h"

typedef enum {
    BLE_ERROR_OK,
    BLE_ERROR_CONF_TX_PWR,
    BLE_ERROR_CONF_GAP,
    BLE_ERROR_CONF_GAP_CAPABILITY,
    BLE_ERROR_CONF_GAP_AUTH,
    BLE_ERROR_CONF_GATT,
    BLE_ERROR_CONF_GATT_SERVICE,
    BLE_ERROR_CONF_GATT_CHAR,
    BLE_ERROR_CONF_GATT_CHAR_DESC,
} BLE_ErrorTypeDef;

typedef struct {
    uint8_t Bonding;                // NO_BONDING, BONDING
    uint8_t MitmProtection;         // MITM_PROTECTION_NOT_REQUIRED, MITM_PROTECTION_REQUIRED_AS_MANDATORY, MITM_PROTECTION_REQUIRED_AS_OPTIONAL
    uint8_t SecureConnection;       // SC_PAIRING_UNSUPPORTED, SC_PAIRING_OPTIONAL, SC_PAIRING_ONLY
    uint8_t KeyPressNotifSup;       // KEYPRESS_NOT_SUPPORTED, KEYPRESS_SUPPORTED
    uint8_t MinEncKeySize;
    uint8_t MaxEncKeySize;
    uint8_t UseFixedPin;            // USE_FIXED_PIN_FOR_PAIRING_ALLOWED, USE_FIXED_PIN_FOR_PAIRING_FORBIDDEN
    uint32_t FixedPin;              // 0 - 999999
    uint8_t AddrType;               // GAP_PUBLIC_ADDR, GAP_STATIC_RANDOM_ADDR
} BLE_GapPrivacyConfigTypeDef;

typedef struct {
    uint8_t Role;                   // GAP_PERIPHERAL_ROLE, GAP_BROADCASTER_ROLE, GAP_CENTRAL_ROLE, GAP_OBSERVER_ROLE
    uint8_t PrivacyEnabled;         // PRIVACY_DISABLED, PRIVACY_ENABLED
    uint8_t NameLen;
    uint16_t ServiceHandle;
    uint16_t NameHandle;
    uint16_t AppearanceHandle;
    BLE_GapPrivacyConfigTypeDef Privacy;
} BLE_GapInitTypeDef;

typedef struct {
    uint8_t UUIDType;               // UUID_TYPE_16, UUID_TYPE_128
    const Char_Desc_Uuid_t DescUUID;
    uint8_t MaxLen;
    uint8_t Len;
    uint8_t Value;
    uint8_t SecurityPerm;           // ATTR_PERMISSION_NONE, ATTR_PERMISSION_AUTHEN_READ, ATTR_PERMISSION_AUTHOR_READ, ATTR_PERMISSION_ENCRY_READ, ATTR_PERMISSION_AUTHEN_WRITE, ATTR_PERMISSION_AUTHOR_WRITE, ATTR_PERMISSION_ENCRY_WRITE, ATTR_PERMISSION_SC_READ, ATTR_PERMISSION_SC_WRITE
    uint8_t AccessPerm;             // ATTR_NO_ACCESS, ATTR_ACCESS_READ_ONLY, ATTR_ACCESS_WRITE_REQ_ONLY, ATTR_ACCESS_READ_WRITE, ATTR_ACCESS_WRITE_WITHOUT_RESPONSE, ATTR_ACCESS_SIGNED_WRITE_ALLOWED
    uint8_t EvtMask;                // GATT_DONT_NOTIFY_EVENTS, GATT_NOTIFY_ATTRIBUTE_WRITE, GATT_NOTIFY_WRITE_REQ_AND_WAIT_FOR_APPL_RESP, GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP, GATT_NOTIFY_NOTIFICATION_COMPLETION
    uint8_t EncKeySize;             // 0x07 - 0x10
    uint8_t DescIsVariable;         // CHAR_VALUE_LEN_CONSTANT, CHAR_VALUE_LEN_VARIABLE
    uint16_t CharDescHandle;
} BLE_GattCharDescTypeDef;

typedef struct {
    uint8_t UUIDType;               // UUID_TYPE_16, UUID_TYPE_128
    const Char_UUID_t CharUUID;
    uint16_t ValueLen;
    uint8_t Properties;             // CHAR_PROP_NONE, CHAR_PROP_BROADCAST, CHAR_PROP_READ, CHAR_PROP_WRITE_WITHOUT_RESP, CHAR_PROP_WRITE, CHAR_PROP_NOTIFY, CHAR_PROP_INDICATE, CHAR_PROP_SIGNED_WRITE, CHAR_PROP_EXT
    uint8_t Permissions;            // ATTR_PERMISSION_NONE, ATTR_PERMISSION_AUTHEN_READ, ATTR_PERMISSION_AUTHOR_READ, ATTR_PERMISSION_ENCRY_READ, ATTR_PERMISSION_AUTHEN_WRITE, ATTR_PERMISSION_AUTHOR_WRITE, ATTR_PERMISSION_ENCRY_WRITE, ATTR_PERMISSION_SC_READ, ATTR_PERMISSION_SC_WRITE
    uint8_t EvtMask;                // GATT_DONT_NOTIFY_EVENTS, GATT_NOTIFY_ATTRIBUTE_WRITE, GATT_NOTIFY_WRITE_REQ_AND_WAIT_FOR_APPL_RESP, GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP, GATT_NOTIFY_NOTIFICATION_COMPLETION
    uint8_t EncKeySize;             // 0x07 - 0x10
    uint8_t CharIsVariable;         // CHAR_VALUE_LEN_CONSTANT, CHAR_VALUE_LEN_VARIABLE
    BLE_GattCharDescTypeDef *Descriptors;
    uint8_t DescriptorsLen;
    uint16_t CharHandle;
} BLE_GattCharTypeDef;

typedef struct {
    uint8_t UUIDType;               // UUID_TYPE_16, UUID_TYPE_128
    const Service_UUID_t ServiceUUID;
    uint8_t ServiceType;            // PRIMARY_SERVICE, SECONDARY_SERVICE
    uint8_t MaxAttributeRecords;
    uint16_t ServiceHandle;
    BLE_GattCharTypeDef *Chars;
    uint8_t CharsLen;
} BLE_GattServiceTypeDef;

typedef struct {
    BLE_GattServiceTypeDef *Services;
    uint8_t ServicesLen;
} BLE_GattInitTypeDef;

typedef struct {
    uint8_t TxPowerLevel;           // From 0x00 to 0x23
    uint8_t IoCapability;           // IO_CAP_DISPLAY_ONLY, IO_CAP_DISPLAY_YES_NO, IO_CAP_KEYBOARD_ONLY, IO_CAP_NO_INPUT_NO_OUTPUT, IO_CAP_KEYBOARD_DISPLAY
    BLE_GapInitTypeDef GapInit;
    BLE_GattInitTypeDef GattInit;
} BLE_InitTypeDef;

BLE_ErrorTypeDef BLE_Init(BLE_InitTypeDef *Cfg);

#endif //STM32WB55_BLE_H