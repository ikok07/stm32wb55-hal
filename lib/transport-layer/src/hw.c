//
// Created by Kok on 2/9/26.
//

#include "hw.h"
#include "stm32wbxx_hal.h"
#include "stm32wbxx_ll_ipcc.h"
#include "utilities_conf.h"
#include "mbox_def.h"

#define HW_IPCC_TX_PENDING( channel ) ( !(LL_C1_IPCC_IsActiveFlag_CHx( IPCC, channel )) ) &&  (((~(IPCC->C1MR)) & (channel << 16U)))
#define HW_IPCC_RX_PENDING( channel )  (LL_C2_IPCC_IsActiveFlag_CHx( IPCC, channel )) && (((~(IPCC->C1MR)) & (channel << 0U)))

/* ------ Event Handlers ------ */
static void HW_IPCC_BLE_EvtHandler( void );
static void HW_IPCC_BLE_AclDataEvtHandler( void );
static void HW_IPCC_MM_FreeBufHandler( void );
static void HW_IPCC_SYS_CmdEvtHandler( void );
static void HW_IPCC_SYS_EvtHandler( void );
static void HW_IPCC_TRACES_EvtHandler( void );

/* ------ Callbacks ------ */
__weak void HW_IPCC_BLE_AclDataAckNot( void ){};
__weak void HW_IPCC_BLE_RxEvtNot( void ){};

__weak void HW_IPCC_SYS_CmdEvtNot( void ){};
__weak void HW_IPCC_SYS_EvtNot( void ){};

__weak void HW_IPCC_TRACES_EvtNot( void ){};

static void (*FreeBufCb)( void );

void HW_IPCC_Init(void) {
    LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_IPCC);
    LL_C1_IPCC_EnableIT_RXO( IPCC );
    LL_C1_IPCC_EnableIT_TXF( IPCC );

    HAL_NVIC_EnableIRQ(IPCC_C1_RX_IRQn);
    HAL_NVIC_EnableIRQ(IPCC_C1_TX_IRQn);
}

void HW_IPCC_Enable(void) {
    // Enable IPCC clock access
    LL_C2_AHB3_GRP1_EnableClock(LL_C2_AHB3_GRP1_PERIPH_IPCC);

    // Enable EXTI events
    LL_EXTI_EnableRisingTrig_32_63(LL_EXTI_LINE_41);
    LL_C2_EXTI_EnableEvent_32_63(LL_EXTI_LINE_41);

    // Send event to wake up CPU2
    __SEV();
    __WFE();

    // Enable CPU2
    LL_PWR_EnableBootC2();
}

void HW_IPCC_BLE_Init() {
    UTILS_ENTER_CRITICAL_SECTION();
    LL_C1_IPCC_EnableReceiveChannel(IPCC, HW_IPCC_BLE_EVENT_CHANNEL);
    UTILS_EXIT_CRITICAL_SECTION();
}

void HW_IPCC_BLE_SendCmd() {
    LL_C1_IPCC_SetFlag_CHx(IPCC, HW_IPCC_BLE_CMD_CHANNEL);
}

void HW_IPCC_BLE_SendAclData() {
    LL_C1_IPCC_SetFlag_CHx( IPCC, HW_IPCC_HCI_ACL_DATA_CHANNEL );
    UTILS_ENTER_CRITICAL_SECTION();
    LL_C1_IPCC_EnableTransmitChannel( IPCC, HW_IPCC_HCI_ACL_DATA_CHANNEL );
    UTILS_EXIT_CRITICAL_SECTION();
}

void HW_IPCC_BLE_AclDataEvtHandler() {
    UTILS_ENTER_CRITICAL_SECTION();
    LL_C1_IPCC_DisableTransmitChannel( IPCC, HW_IPCC_HCI_ACL_DATA_CHANNEL );
    UTILS_EXIT_CRITICAL_SECTION();

    HW_IPCC_BLE_AclDataAckNot();
}

void HW_IPCC_SYS_Init() {
    UTILS_ENTER_CRITICAL_SECTION();
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_SYSTEM_EVENT_CHANNEL );
    UTILS_EXIT_CRITICAL_SECTION();
}

void HW_IPCC_SYS_SendCmd() {
    LL_C1_IPCC_SetFlag_CHx( IPCC, HW_IPCC_SYSTEM_CMD_RSP_CHANNEL );
    UTILS_ENTER_CRITICAL_SECTION();
    LL_C1_IPCC_EnableTransmitChannel( IPCC, HW_IPCC_SYSTEM_CMD_RSP_CHANNEL );
    UTILS_EXIT_CRITICAL_SECTION();
}

void HW_IPCC_SYS_CmdEvtHandler()
{
    UTILS_ENTER_CRITICAL_SECTION();
    LL_C1_IPCC_DisableTransmitChannel( IPCC, HW_IPCC_SYSTEM_CMD_RSP_CHANNEL );
    UTILS_EXIT_CRITICAL_SECTION();

    HW_IPCC_SYS_CmdEvtNot();
}

static void HW_IPCC_SYS_EvtHandler( void )
{
    HW_IPCC_SYS_EvtNot();
    LL_C1_IPCC_ClearFlag_CHx( IPCC, HW_IPCC_SYSTEM_EVENT_CHANNEL );
}

void HW_IPCC_BLE_EvtHandler() {
    HW_IPCC_BLE_RxEvtNot();
    LL_C1_IPCC_ClearFlag_CHx( IPCC, HW_IPCC_BLE_EVENT_CHANNEL );
}

void HW_IPCC_MM_SendFreeBuf(void (*cb)( void )) {
    if (LL_C1_IPCC_IsActiveFlag_CHx(IPCC, HW_IPCC_MM_RELEASE_BUFFER_CHANNEL)) {
        FreeBufCb = cb;
        UTILS_ENTER_CRITICAL_SECTION();
        LL_C1_IPCC_EnableTransmitChannel( IPCC, HW_IPCC_MM_RELEASE_BUFFER_CHANNEL );
        UTILS_EXIT_CRITICAL_SECTION();
    } else {
        cb();
        LL_C1_IPCC_SetFlag_CHx( IPCC, HW_IPCC_MM_RELEASE_BUFFER_CHANNEL );
    }
}

void HW_IPCC_MM_FreeBufHandler() {
    UTILS_ENTER_CRITICAL_SECTION();
    LL_C1_IPCC_DisableTransmitChannel( IPCC, HW_IPCC_MM_RELEASE_BUFFER_CHANNEL );
    UTILS_EXIT_CRITICAL_SECTION();

    FreeBufCb();

    LL_C1_IPCC_SetFlag_CHx( IPCC, HW_IPCC_MM_RELEASE_BUFFER_CHANNEL );
}

void HW_IPCC_TRACES_Init() {
    UTILS_ENTER_CRITICAL_SECTION();
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_TRACES_CHANNEL );
    UTILS_EXIT_CRITICAL_SECTION();
}

static void HW_IPCC_TRACES_EvtHandler( void )
{
    HW_IPCC_TRACES_EvtNot();
    LL_C1_IPCC_ClearFlag_CHx( IPCC, HW_IPCC_TRACES_CHANNEL );
}

void HW_IPCC_Rx_Handler() {
    if (HW_IPCC_RX_PENDING(HW_IPCC_SYSTEM_EVENT_CHANNEL)) {
        HW_IPCC_SYS_EvtHandler();
    } else if (HW_IPCC_RX_PENDING( HW_IPCC_BLE_EVENT_CHANNEL )) {
        HW_IPCC_BLE_EvtHandler();
    } else if (HW_IPCC_RX_PENDING( HW_IPCC_TRACES_CHANNEL )) {
        HW_IPCC_TRACES_EvtHandler();
    }
}

void HW_IPCC_Tx_Handler() {
    if (HW_IPCC_TX_PENDING( HW_IPCC_SYSTEM_CMD_RSP_CHANNEL )) {
        HW_IPCC_SYS_CmdEvtHandler();
    } else if (HW_IPCC_TX_PENDING( HW_IPCC_MM_RELEASE_BUFFER_CHANNEL )) {
        HW_IPCC_MM_FreeBufHandler();
    } else if (HW_IPCC_TX_PENDING( HW_IPCC_HCI_ACL_DATA_CHANNEL )) {
        HW_IPCC_BLE_AclDataEvtHandler();
    }
}