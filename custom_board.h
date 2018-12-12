/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
//#ifndef BOARD_CUSTOM
//#define BOARD_CUSTOM

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_gpio.h"

// LEDs definitions for PCA10056
//#define LEDS_NUMBER    4

//#define LED_1          (0)
//#define LED_2          (0)
//#define LED_3          (0)
//#define LED_4          (0)
//#define LED_START      LED_1
//#define LED_STOP       LED_4

//#define LEDS_ACTIVE_STATE 0

//#define LEDS_LIST { LED_1, LED_2, LED_3, LED_4 }

//#define LEDS_INV_MASK  LEDS_MASK

//#define BSP_LED_0      13
//#define BSP_LED_1      14
//#define BSP_LED_2      15
//#define BSP_LED_3      16

#define BUTTONS_NUMBER 6

//#define BUTTON_1             NRF_GPIO_PIN_MAP(0,7)//29)
//#define BUTTON_2             NRF_GPIO_PIN_MAP(1,13)
//#define BUTTON_3             NRF_GPIO_PIN_MAP(1,4)
//#define BUTTON_4             NRF_GPIO_PIN_MAP(1,6)
#define BUTTON_PULL          NRF_GPIO_PIN_PULLUP

#define BUTTONS_ACTIVE_STATE 0

//#define BUTTONS_LIST { BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4 }
//
//#define BSP_BUTTON_0         BUTTON_1
//#define BSP_BUTTON_1         BUTTON_2
//#define BSP_BUTTON_2         BUTTON_3
//#define BSP_BUTTON_3         BUTTON_4
//
//#define ARDUINO_SDA_PIN      NRF_GPIO_PIN_MAP(0,17)
//#define ARDUINO_SCL_PIN      NRF_GPIO_PIN_MAP(0,15)
//
//#define BUZZER_PIN           NRF_GPIO_PIN_MAP(1,2)
//
//#define INPUT_VOLTAGE_PIN    NRF_GPIO_PIN_MAP(0,12)
//
//#define BATTERY_VOLTAGE      NRF_GPIO_PIN_MAP(0,8)//4)

// SPI
#define SPI_SCL            NRF_GPIO_PIN_MAP(1,5)//0,3)
#define SPI_MOSI           NRF_GPIO_PIN_MAP(1,6)//0,4)
#define SPI_MISO           NRF_GPIO_PIN_MAP(1,3)

// TWI
#define TWI_SCL            NRF_GPIO_PIN_MAP(0,26)
#define TWI_SDA            NRF_GPIO_PIN_MAP(0,27)

// E-Paper display
#define EINK_CS            NRF_GPIO_PIN_MAP(1,12)//0,29)
#define EINK_BUSY          NRF_GPIO_PIN_MAP(0,3)//0,28)
#define EINK_RES           NRF_GPIO_PIN_MAP(1,15)//0,30)
#define EINK_DC            NRF_GPIO_PIN_MAP(1,14)//0,31)

// MPU-9250 (MEMS)
#define MPU_CS             NRF_GPIO_PIN_MAP(1,2)
#define MPU_INT            NRF_GPIO_PIN_MAP(1,0)

// APDS-9960 (Gesture)
#define AP_INT             NRF_GPIO_PIN_MAP(0,31)//1,14)

// MT25QL memory, QSPI
#define Q_CLK              NRF_GPIO_PIN_MAP(0,12)
#define Q_CS               NRF_GPIO_PIN_MAP(0,13)
#define Q_D0               NRF_GPIO_PIN_MAP(1,8)
#define Q_D1               NRF_GPIO_PIN_MAP(0,6)
#define Q_D2               NRF_GPIO_PIN_MAP(0,7)
#define Q_D3               NRF_GPIO_PIN_MAP(1,9)

// MCP73831T-ACI/OT (accumulator)
#define BATT_M             NRF_GPIO_PIN_MAP(0,5)

// TLV73333PDBVT (power source)
#define DC_ON              NRF_GPIO_PIN_MAP(0,16)

// Buttons
#define BUTTON_1           NRF_GPIO_PIN_MAP(0,20)
#define BUTTON_2           NRF_GPIO_PIN_MAP(1,10)
#define BUTTON_3           NRF_GPIO_PIN_MAP(0,15)
#define BUTTON_4           NRF_GPIO_PIN_MAP(0,28)//1,1)
#define BUTTON_MNU         NRF_GPIO_PIN_MAP(0,21)
#define BUTTON_RESET       NRF_GPIO_PIN_MAP(0,18)

#define BUTTONS_NUMBER 6
#define BUTTONS_LIST { BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4, BUTTON_MNU, BUTTON_RESET}


#define LED_PIN            NRF_GPIO_PIN_MAP(0,29)//1,12)

#define BUZZER_PIN           NRF_GPIO_PIN_MAP(0,23)

#define VIBRO_PIN          NRF_GPIO_PIN_MAP(0,24)






//#define RX_PIN_NUMBER  8
//#define TX_PIN_NUMBER  6
//#define CTS_PIN_NUMBER 7
//#define RTS_PIN_NUMBER 5
//#define HWFC           true

//#define BSP_QSPI_SCK_PIN   19
//#define BSP_QSPI_CSN_PIN   17
//#define BSP_QSPI_IO0_PIN   20
//#define BSP_QSPI_IO1_PIN   21
//#define BSP_QSPI_IO2_PIN   22
//#define BSP_QSPI_IO3_PIN   23

/*
// serialization APPLICATION board - temp. setup for running serialized MEMU tests
#define SER_APP_RX_PIN              NRF_GPIO_PIN_MAP(1,13)    // UART RX pin number.
#define SER_APP_TX_PIN              NRF_GPIO_PIN_MAP(1,14)    // UART TX pin number.
#define SER_APP_CTS_PIN             NRF_GPIO_PIN_MAP(0,2)     // UART Clear To Send pin number.
#define SER_APP_RTS_PIN             NRF_GPIO_PIN_MAP(1,15)    // UART Request To Send pin number.

#define SER_APP_SPIM0_SCK_PIN       NRF_GPIO_PIN_MAP(0,27)     // SPI clock GPIO pin number.
#define SER_APP_SPIM0_MOSI_PIN      NRF_GPIO_PIN_MAP(0,2)      // SPI Master Out Slave In GPIO pin number
#define SER_APP_SPIM0_MISO_PIN      NRF_GPIO_PIN_MAP(0,26)     // SPI Master In Slave Out GPIO pin number
#define SER_APP_SPIM0_SS_PIN        NRF_GPIO_PIN_MAP(1,13)     // SPI Slave Select GPIO pin number
#define SER_APP_SPIM0_RDY_PIN       NRF_GPIO_PIN_MAP(1,15)     // SPI READY GPIO pin number
#define SER_APP_SPIM0_REQ_PIN       NRF_GPIO_PIN_MAP(1,14)     // SPI REQUEST GPIO pin number

// serialization CONNECTIVITY board
#define SER_CON_RX_PIN              NRF_GPIO_PIN_MAP(1,14)    // UART RX pin number.
#define SER_CON_TX_PIN              NRF_GPIO_PIN_MAP(1,13)    // UART TX pin number.
#define SER_CON_CTS_PIN             NRF_GPIO_PIN_MAP(1,15)    // UART Clear To Send pin number. Not used if HWFC is set to false.
#define SER_CON_RTS_PIN             NRF_GPIO_PIN_MAP(0,2)     // UART Request To Send pin number. Not used if HWFC is set to false.


#define SER_CON_SPIS_SCK_PIN        NRF_GPIO_PIN_MAP(0,27)    // SPI SCK signal.
#define SER_CON_SPIS_MOSI_PIN       NRF_GPIO_PIN_MAP(0,2)     // SPI MOSI signal.
#define SER_CON_SPIS_MISO_PIN       NRF_GPIO_PIN_MAP(0,26)    // SPI MISO signal.
#define SER_CON_SPIS_CSN_PIN        NRF_GPIO_PIN_MAP(1,13)    // SPI CSN signal.
#define SER_CON_SPIS_RDY_PIN        NRF_GPIO_PIN_MAP(1,15)    // SPI READY GPIO pin number.
#define SER_CON_SPIS_REQ_PIN        NRF_GPIO_PIN_MAP(1,14)    // SPI REQUEST GPIO pin number.

#define SER_CONN_CHIP_RESET_PIN     NRF_GPIO_PIN_MAP(1,1)    // Pin used to reset connectivity chip

// Arduino board mappings
#define ARDUINO_SCL_PIN             27    // SCL signal pin
#define ARDUINO_SDA_PIN             26    // SDA signal pin
#define ARDUINO_AREF_PIN            2     // Aref pin

#define ARDUINO_13_PIN              NRF_GPIO_PIN_MAP(1, 15)  // Digital pin 13
#define ARDUINO_12_PIN              NRF_GPIO_PIN_MAP(1, 14)  // Digital pin 12
#define ARDUINO_11_PIN              NRF_GPIO_PIN_MAP(1, 13)  // Digital pin 11
#define ARDUINO_10_PIN              NRF_GPIO_PIN_MAP(1, 12)  // Digital pin 10
#define ARDUINO_9_PIN               NRF_GPIO_PIN_MAP(1, 11)  // Digital pin 9
#define ARDUINO_8_PIN               NRF_GPIO_PIN_MAP(1, 10)  // Digital pin 8

#define ARDUINO_7_PIN               NRF_GPIO_PIN_MAP(1, 8) // Digital pin 7
#define ARDUINO_6_PIN               NRF_GPIO_PIN_MAP(1, 7) // Digital pin 6
#define ARDUINO_5_PIN               NRF_GPIO_PIN_MAP(1, 6) // Digital pin 5
#define ARDUINO_4_PIN               NRF_GPIO_PIN_MAP(1, 5) // Digital pin 4
#define ARDUINO_3_PIN               NRF_GPIO_PIN_MAP(1, 4) // Digital pin 3
#define ARDUINO_2_PIN               NRF_GPIO_PIN_MAP(1, 3) // Digital pin 2
#define ARDUINO_1_PIN               NRF_GPIO_PIN_MAP(1, 2) // Digital pin 1
#define ARDUINO_0_PIN               NRF_GPIO_PIN_MAP(1, 1) // Digital pin 0

#define ARDUINO_A0_PIN              3     // Analog channel 0
#define ARDUINO_A1_PIN              4     // Analog channel 1
#define ARDUINO_A2_PIN              28    // Analog channel 2
#define ARDUINO_A3_PIN              29    // Analog channel 3
#define ARDUINO_A4_PIN              30    // Analog channel 4
#define ARDUINO_A5_PIN              31    // Analog channel 5          */


#ifdef __cplusplus
}
#endif

//#endif // BOARD_CUSTOM
