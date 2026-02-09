//
// Created by Kok on 2/9/26.
//

#ifndef STM32WB55_HW_H
#define STM32WB55_HW_H

void HW_IPCC_Init(void);
void HW_IPCC_Enable(void);
void HW_IPCC_BLE_Init(void);

void HW_IPCC_BLE_SendCmd(void);
void HW_IPCC_BLE_RxEvtNot( void );

void HW_IPCC_BLE_SendAclData(void);
void HW_IPCC_BLE_AclDataAckNot( void );

void HW_IPCC_SYS_Init(void);
void HW_IPCC_SYS_SendCmd(void);
void HW_IPCC_SYS_CmdEvtNot( void );
void HW_IPCC_SYS_EvtNot( void );

void HW_IPCC_MM_SendFreeBuf(void (*cb)( void ));

void HW_IPCC_TRACES_Init(void);
void HW_IPCC_TRACES_EvtNot( void );

#endif //STM32WB55_HW_H