/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __RTE_DEVICE_H
#define __RTE_DEVICE_H

/*Driver name mapping.*/
#define RTE_SPI1        1
#define RTE_SPI1_DMA_EN 1
#define RTE_SPI2        0
#define RTE_SPI2_DMA_EN 0
#define RTE_SPI3        0
#define RTE_SPI3_DMA_EN 0
#define RTE_SPI4        0
#define RTE_SPI4_DMA_EN 0
#define RTE_SPI5        0
#define RTE_SPI5_DMA_EN 0
#define RTE_SPI6        0
#define RTE_SPI6_DMA_EN 0

/* SPI configuration. */
#define RTE_SPI1_PCS_TO_SCK_DELAY       1000
#define RTE_SPI1_SCK_TO_PSC_DELAY       1000
#define RTE_SPI1_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI1_MASTER_PCS_PIN_SEL     (kLPSPI_MasterPcs0)
#define RTE_SPI1_SLAVE_PCS_PIN_SEL      (kLPSPI_SlavePcs0)
#define RTE_SPI1_DMA_TX_CH              0
#define RTE_SPI1_DMA_TX_PERI_SEL        (uint8_t) kDmaRequestMuxLPSPI1Tx
#if __CORTEX_M == 7
#define RTE_SPI1_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_SPI1_DMA_TX_DMA_BASE    DMA0
#else
#define RTE_SPI1_DMA_TX_DMAMUX_BASE DMAMUX1
#define RTE_SPI1_DMA_TX_DMA_BASE    DMA1
#endif
#define RTE_SPI1_DMA_RX_CH       1
#define RTE_SPI1_DMA_RX_PERI_SEL (uint8_t) kDmaRequestMuxLPSPI1Rx
#if __CORTEX_M == 7
#define RTE_SPI1_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_SPI1_DMA_RX_DMA_BASE    DMA0
#else
#define RTE_SPI1_DMA_RX_DMAMUX_BASE DMAMUX1
#define RTE_SPI1_DMA_RX_DMA_BASE    DMA1
#endif

#define RTE_SPI2_PCS_TO_SCK_DELAY       1000
#define RTE_SPI2_SCK_TO_PSC_DELAY       1000
#define RTE_SPI2_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI2_MASTER_PCS_PIN_SEL     (kLPSPI_MasterPcs0)
#define RTE_SPI2_SLAVE_PCS_PIN_SEL      (kLPSPI_SlavePcs0)
#define RTE_SPI2_DMA_TX_CH              2
#define RTE_SPI2_DMA_TX_PERI_SEL        (uint8_t) kDmaRequestMuxLPSPI2Tx
#if __CORTEX_M == 7
#define RTE_SPI2_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_SPI2_DMA_TX_DMA_BASE    DMA0
#else
#define RTE_SPI2_DMA_TX_DMAMUX_BASE DMAMUX1
#define RTE_SPI2_DMA_TX_DMA_BASE    DMA1
#endif
#define RTE_SPI2_DMA_RX_CH       3
#define RTE_SPI2_DMA_RX_PERI_SEL (uint8_t) kDmaRequestMuxLPSPI2Tx
#if __CORTEX_M == 7
#define RTE_SPI2_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_SPI2_DMA_RX_DMA_BASE    DMA0
#else
#define RTE_SPI2_DMA_RX_DMAMUX_BASE DMAMUX1
#define RTE_SPI2_DMA_RX_DMA_BASE    DMA1
#endif

#define RTE_SPI3_PCS_TO_SCK_DELAY       1000
#define RTE_SPI3_SCK_TO_PSC_DELAY       1000
#define RTE_SPI3_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI3_MASTER_PCS_PIN_SEL     (kLPSPI_MasterPcs0)
#define RTE_SPI3_SLAVE_PCS_PIN_SEL      (kLPSPI_SlavePcs0)
#define RTE_SPI3_DMA_TX_CH              4
#define RTE_SPI3_DMA_TX_PERI_SEL        (uint8_t) kDmaRequestMuxLPSPI3Tx
#if __CORTEX_M == 7
#define RTE_SPI3_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_SPI3_DMA_TX_DMA_BASE    DMA0
#else
#define RTE_SPI3_DMA_TX_DMAMUX_BASE DMAMUX1
#define RTE_SPI3_DMA_TX_DMA_BASE    DMA1
#endif
#define RTE_SPI3_DMA_RX_CH       5
#define RTE_SPI3_DMA_RX_PERI_SEL (uint8_t) kDmaRequestMuxLPSPI3Rx
#if __CORTEX_M == 7
#define RTE_SPI3_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_SPI3_DMA_RX_DMA_BASE    DMA0
#else
#define RTE_SPI3_DMA_RX_DMAMUX_BASE DMAMUX1
#define RTE_SPI3_DMA_RX_DMA_BASE    DMA1
#endif

#define RTE_SPI4_PCS_TO_SCK_DELAY       1000
#define RTE_SPI4_SCK_TO_PSC_DELAY       1000
#define RTE_SPI4_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI4_MASTER_PCS_PIN_SEL     (kLPSPI_MasterPcs0)
#define RTE_SPI4_SLAVE_PCS_PIN_SEL      (kLPSPI_SlavePcs0)
#define RTE_SPI4_DMA_TX_CH              6
#define RTE_SPI4_DMA_TX_PERI_SEL        (uint8_t) kDmaRequestMuxLPSPI4Tx
#if __CORTEX_M == 7
#define RTE_SPI4_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_SPI4_DMA_TX_DMA_BASE    DMA0
#else
#define RTE_SPI4_DMA_TX_DMAMUX_BASE DMAMUX1
#define RTE_SPI4_DMA_TX_DMA_BASE    DMA1
#endif
#define RTE_SPI4_DMA_RX_CH       7
#define RTE_SPI4_DMA_RX_PERI_SEL (uint8_t) kDmaRequestMuxLPSPI4Rx
#if __CORTEX_M == 7
#define RTE_SPI4_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_SPI4_DMA_RX_DMA_BASE    DMA0
#else
#define RTE_SPI4_DMA_RX_DMAMUX_BASE DMAMUX1
#define RTE_SPI4_DMA_RX_DMA_BASE    DMA1
#endif

#define RTE_SPI5_PCS_TO_SCK_DELAY       1000
#define RTE_SPI5_SCK_TO_PSC_DELAY       1000
#define RTE_SPI5_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI5_MASTER_PCS_PIN_SEL     (kLPSPI_MasterPcs0)
#define RTE_SPI5_SLAVE_PCS_PIN_SEL      (kLPSPI_SlavePcs0)
#define RTE_SPI5_DMA_TX_CH              8
#define RTE_SPI5_DMA_TX_PERI_SEL        (uint8_t) kDmaRequestMuxLPSPI5Tx
#if __CORTEX_M == 7
#define RTE_SPI5_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_SPI5_DMA_TX_DMA_BASE    DMA0
#else
#define RTE_SPI5_DMA_TX_DMAMUX_BASE DMAMUX1
#define RTE_SPI5_DMA_TX_DMA_BASE    DMA1
#endif
#define RTE_SPI5_DMA_RX_CH       9
#define RTE_SPI5_DMA_RX_PERI_SEL (uint8_t) kDmaRequestMuxLPSPI5Rx
#if __CORTEX_M == 7
#define RTE_SPI5_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_SPI5_DMA_RX_DMA_BASE    DMA0
#else
#define RTE_SPI5_DMA_RX_DMAMUX_BASE DMAMUX1
#define RTE_SPI5_DMA_RX_DMA_BASE    DMA1
#endif

#define RTE_SPI6_PCS_TO_SCK_DELAY       1000
#define RTE_SPI6_SCK_TO_PSC_DELAY       1000
#define RTE_SPI6_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI6_MASTER_PCS_PIN_SEL     (kLPSPI_MasterPcs0)
#define RTE_SPI6_SLAVE_PCS_PIN_SEL      (kLPSPI_SlavePcs0)
#define RTE_SPI6_DMA_TX_CH              10
#define RTE_SPI6_DMA_TX_PERI_SEL        (uint8_t) kDmaRequestMuxLPSPI6Tx
#if __CORTEX_M == 7
#define RTE_SPI6_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_SPI6_DMA_TX_DMA_BASE    DMA0
#else
#define RTE_SPI6_DMA_TX_DMAMUX_BASE DMAMUX1
#define RTE_SPI6_DMA_TX_DMA_BASE    DMA1
#endif
#define RTE_SPI6_DMA_RX_CH       11
#define RTE_SPI6_DMA_RX_PERI_SEL (uint8_t) kDmaRequestMuxLPSPI6Rx
#if __CORTEX_M == 7
#define RTE_SPI6_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_SPI6_DMA_RX_DMA_BASE    DMA0
#else
#define RTE_SPI6_DMA_RX_DMAMUX_BASE DMAMUX1
#define RTE_SPI6_DMA_RX_DMA_BASE    DMA1
#endif

#endif /* __RTE_DEVICE_H */
