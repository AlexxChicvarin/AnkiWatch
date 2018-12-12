#ifndef U8G2_NRF52_HAL_H_
#define U8G2_NRF52_HAL_H_
#include "u8g2.h"

#include "nrf_drv_twi.h"
#include "nrf_drv_spi.h"
#include "nrf_delay.h"
#include "nrf_drv_gpiote.h"

#define U8G2_NRF52_HAL_UNDEFINED (-1)

#define I2C_MASTER_NUM I2C_NUM_1    //  I2C port number for master dev
#define I2C_MASTER_TX_BUF_DISABLE 0 //  I2C master do not need buffer
#define I2C_MASTER_RX_BUF_DISABLE 0 //  I2C master do not need buffer
#define I2C_MASTER_FREQ_HZ 50000    //  I2C master clock frequency
#define ACK_CHECK_EN 0x1            //  I2C master will check ack from slave
#define ACK_CHECK_DIS 0x0           //  I2C master will not check ack from slave

typedef struct {
  uint32_t clk;
  uint32_t mosi;
  uint32_t sda; // data for I2C
  uint32_t scl; // clock for I2C
  uint32_t cs;
  uint32_t reset;
  uint32_t dc;
  uint32_t busy;
} u8g2_nrf52_hal_t;

#define U8G2_NRF52_HAL_DEFAULT \
  { U8G2_NRF52_HAL_UNDEFINED, U8G2_NRF52_HAL_UNDEFINED, U8G2_NRF52_HAL_UNDEFINED, U8G2_NRF52_HAL_UNDEFINED, U8G2_NRF52_HAL_UNDEFINED, U8G2_NRF52_HAL_UNDEFINED, U8G2_NRF52_HAL_UNDEFINED }

void u8g2_nrf52_hal_init(u8g2_nrf52_hal_t u8g2_nrf52_hal_param);
void u8g2_nrf52_hard_reset();
void u8g2_hal_busy_wait();
uint8_t u8g2_nrf52_spi_byte_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8g2_nrf52_i2c_byte_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8g2_nrf52_gpio_and_delay_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);


#endif // U8G2_NRF52_HAL_H_