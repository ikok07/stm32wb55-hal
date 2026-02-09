//
// Created by Kok on 2/8/26.
//

#include "cpu2.h"

#include "clocks.h"
#include "shci_tl.h"

void SHCI_UserEvtRx(void *pData);

SHCI_CmdStatus_t CPU2_Start() {
    SHCI_CmdStatus_t status = SHCI_Success;

    if ((status = SHCI_C2_Reinit()) != SHCI_Success) return status;

    SHCI_C2_CONFIG_Cmd_Param_t CPU2_Config = {
        .PayloadCmdSize = SHCI_C2_CONFIG_PAYLOAD_CMD_SIZE,
        .Config1 = 0, // Store RF information in flash
        .EvtMask1 = SHCI_C2_CONFIG_EVTMASK1_BIT0_ERROR_NOTIF_ENABLE,
        .Spare1 = 0
    };
    if ((status = SHCI_C2_Config(&CPU2_Config)) != SHCI_Success) return status;

    return status;
}

void SHCI_UserEvtRx(void *pData) {

}