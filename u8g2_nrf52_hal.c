//#include "sdk_config.h"

#include "u8g2_nrf52_hal.h"

static const unsigned int I2C_TIMEOUT_MS = 1000;

static u8g2_nrf52_hal_t u8g2_nrf52_hal;
static const nrf_drv_twi_t m_twi_master = NRF_DRV_TWI_INSTANCE(1);
static const nrf_drv_spi_t m_spi_master = NRF_DRV_SPI_INSTANCE(0);
 
//void spi_event_handler(nrf_drv_spi_evt_t const * p_event, void * p_context)
//{
//  switch(p_event->type){
//  case NRF_DRV_SPI_EVENT_DONE:
//    break;
//  default:
//    break;
//  }
//}

void u8g2_nrf52_hal_init(u8g2_nrf52_hal_t u8g2_nrf52_hal_param) {
    u8g2_nrf52_hal = u8g2_nrf52_hal_param;
}

void u8g2_hal_busy_wait()
{
  uint32_t bsy = 1;
  nrf_delay_ms(20);
  while(bsy != 0)
  {
    bsy = nrf_gpio_pin_read(u8g2_nrf52_hal.busy);
  }
}

void u8g2_nrf52_hard_reset()
{
  nrf_gpio_pin_clear(u8g2_nrf52_hal.reset);
  //u8g2_hal_busy_wait();
  nrf_gpio_pin_set(u8g2_nrf52_hal.reset);
  u8g2_hal_busy_wait();
}

uint8_t u8g2_nrf52_spi_byte_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    static uint8_t buffer[32];		/* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
    static uint8_t buf_idx;
    uint8_t *data;

    //u8g2_hal_busy_wait();

    switch(msg) {
        case U8X8_MSG_BYTE_SET_DC:
            if (u8g2_nrf52_hal.dc != U8G2_NRF52_HAL_UNDEFINED)
                if (arg_int) 
                    nrf_gpio_pin_set(u8g2_nrf52_hal.dc);
                else 
                    nrf_gpio_pin_clear(u8g2_nrf52_hal.dc);
        break;
        
        case U8X8_MSG_BYTE_INIT:
            if (u8g2_nrf52_hal.clk  == U8G2_NRF52_HAL_UNDEFINED ||
                u8g2_nrf52_hal.mosi == U8G2_NRF52_HAL_UNDEFINED ||
                u8g2_nrf52_hal.cs   == U8G2_NRF52_HAL_UNDEFINED)
                break;
            nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
            spi_config.ss_pin   = u8g2_nrf52_hal.cs;
            spi_config.mosi_pin = u8g2_nrf52_hal.mosi;
            spi_config.sck_pin  = u8g2_nrf52_hal.clk;
            APP_ERROR_CHECK(nrf_drv_spi_init(&m_spi_master, &spi_config, NULL, NULL));
        break;
        
        case U8X8_MSG_BYTE_SEND:
            buf_idx = 0;
            data = (uint8_t *)arg_ptr;      
            while( arg_int > 0 ) {
                buffer[buf_idx++] = *data;
                data++;
                arg_int--;
            }      
            APP_ERROR_CHECK(nrf_drv_spi_transfer(&m_spi_master, buffer, buf_idx, NULL, NULL));
//            if(buffer[0] == 0x12)
//              u8g2_hal_busy_wait();
        break;
    }
    return 0;
}

uint8_t u8g2_nrf52_i2c_byte_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    static uint8_t buffer[32];		/* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
    static uint8_t buf_idx;
    uint8_t *data;
    ret_code_t ret;
        
    switch(msg) {
        case U8X8_MSG_BYTE_SET_DC:
            if (u8g2_nrf52_hal.dc != U8G2_NRF52_HAL_UNDEFINED)
                if (arg_int) 
                    nrf_gpio_pin_set(u8g2_nrf52_hal.dc);
                else 
                    nrf_gpio_pin_clear(u8g2_nrf52_hal.dc);
        break;
        
        case U8X8_MSG_BYTE_INIT:
            if (u8g2_nrf52_hal.sda == U8G2_NRF52_HAL_UNDEFINED || u8g2_nrf52_hal.scl == U8G2_NRF52_HAL_UNDEFINED)
                break;

            nrf_drv_twi_config_t twi_config;
            twi_config.scl = u8g2_nrf52_hal.scl;
            twi_config.sda = u8g2_nrf52_hal.sda;
            twi_config.frequency = I2C_MASTER_FREQ_HZ;
            twi_config.interrupt_priority = TWI_DEFAULT_CONFIG_IRQ_PRIORITY;
            
            do {
                ret = nrf_drv_twi_init(&m_twi_master, &twi_config, NULL, NULL);
                if (NRF_SUCCESS != ret)
                    break;
                nrf_drv_twi_enable(&m_twi_master);
            } while (0);
            break;

        case U8X8_MSG_BYTE_START_TRANSFER:
            buf_idx = 0;
        break;
        
        case U8X8_MSG_BYTE_SEND:
            data = (uint8_t *)arg_ptr;      
            while( arg_int > 0 ) {
                buffer[buf_idx++] = *data;
                data++;
                arg_int--;
            }      
        break;

        case U8X8_MSG_BYTE_END_TRANSFER:
            ret = nrf_drv_twi_tx(&m_twi_master, u8x8_GetI2CAddress(u8x8), buffer, buf_idx, false);
        break;
    }
    return 0;
}

uint8_t u8g2_nrf52_gpio_and_delay_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    switch(msg) {
        case U8X8_MSG_GPIO_AND_DELAY_INIT:
            if (u8g2_nrf52_hal.dc != U8G2_NRF52_HAL_UNDEFINED)
                nrf_gpio_cfg_output(u8g2_nrf52_hal.dc);
                //nrf_gpio_cfg(u8g2_nrf52_hal.dc, NRF_GPIO_PIN_DIR_OUTPUT, NRF_GPIO_PIN_INPUT_DISCONNECT, NRF_GPIO_PIN_PULLDOWN, NRF_GPIO_PIN_S0S1, NRF_GPIO_PIN_NOSENSE);
            if (u8g2_nrf52_hal.reset != U8G2_NRF52_HAL_UNDEFINED)
                nrf_gpio_cfg_output(u8g2_nrf52_hal.reset);
                //nrf_gpio_cfg(u8g2_nrf52_hal.reset, NRF_GPIO_PIN_DIR_OUTPUT, NRF_GPIO_PIN_INPUT_DISCONNECT, NRF_GPIO_PIN_PULLDOWN, NRF_GPIO_PIN_S0S1, NRF_GPIO_PIN_NOSENSE);
            if (u8g2_nrf52_hal.cs != U8G2_NRF52_HAL_UNDEFINED)
                nrf_gpio_cfg_output(u8g2_nrf52_hal.cs);
                //nrf_gpio_cfg(u8g2_nrf52_hal.cs, NRF_GPIO_PIN_DIR_OUTPUT, NRF_GPIO_PIN_INPUT_DISCONNECT, NRF_GPIO_PIN_PULLDOWN, NRF_GPIO_PIN_S0S1, NRF_GPIO_PIN_NOSENSE);
        break;

        case U8X8_MSG_GPIO_RESET:
            if (u8g2_nrf52_hal.reset != U8G2_NRF52_HAL_UNDEFINED)
                if (arg_int) 
                    nrf_gpio_pin_set(u8g2_nrf52_hal.reset);
                else 
                    nrf_gpio_pin_clear(u8g2_nrf52_hal.reset);
        break;

        case U8X8_MSG_GPIO_CS:
            if (u8g2_nrf52_hal.cs != U8G2_NRF52_HAL_UNDEFINED)
                if (arg_int) 
                    nrf_gpio_pin_set(u8g2_nrf52_hal.cs);
                else 
                    nrf_gpio_pin_clear(u8g2_nrf52_hal.cs);
        break;

        case U8X8_MSG_GPIO_I2C_CLOCK:
            if (u8g2_nrf52_hal.scl != U8G2_NRF52_HAL_UNDEFINED)
                if (arg_int) 
                    nrf_gpio_pin_set(u8g2_nrf52_hal.scl);
                else 
                    nrf_gpio_pin_clear(u8g2_nrf52_hal.scl);
        break;

        case U8X8_MSG_GPIO_I2C_DATA:
            if (u8g2_nrf52_hal.sda != U8G2_NRF52_HAL_UNDEFINED)
                if (arg_int) 
                    nrf_gpio_pin_set(u8g2_nrf52_hal.sda);
                else 
                    nrf_gpio_pin_clear(u8g2_nrf52_hal.sda);
        break;

        case U8X8_MSG_DELAY_MILLI:
            nrf_delay_ms(arg_int);
        break;
    }
}