#include "SoundLibrary.h"

APP_PWM_INSTANCE(PWM1, 1); // Create the instance "PWM1" using TIMER1.
static volatile bool ready_flag; // A flag indicating PWM status.

void pwm_ready_callback(uint32_t pwm_id) // PWM callback function
{
  ready_flag = true;
}

void buzzer_init_helper(uint32_t buzzPin)
{
  buzzerPin = buzzPin;
}

void toneByFreq(uint16_t freq, uint16_t dur)
{
  uint32_t period_us, err_code = NRF_SUCCESS;

  if(freq == 0)
    nrf_delay_ms(dur);
  else
  {
    period_us = 1000000/freq;

  app_pwm_config_t pwm1_cfg = APP_PWM_DEFAULT_CONFIG_1CH(period_us, buzzerPin);
    
  err_code = app_pwm_init(&PWM1, &pwm1_cfg, pwm_ready_callback);
  APP_ERROR_CHECK(err_code);
  app_pwm_enable(&PWM1);

  
    for (int i = 0; i < dur; i++) {
      app_pwm_channel_duty_set(&PWM1, 0, 50);
      nrf_delay_ms(1);
    }
  err_code = app_pwm_uninit(&PWM1);  
  APP_ERROR_CHECK(err_code);
  }  
}

void buzzer(uint16_t *sound)
{
  uint32_t err_code = NRF_SUCCESS;
  uint16_t freq = 0;
  uint16_t dur = 0;
  uint16_t toneNum = 0;

  nrf_gpio_pin_dir_set(buzzerPin, NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_clear(buzzerPin);

  while(sound[toneNum] != TONES_END)
  {
    freq = sound[toneNum++];
    dur = sound[toneNum++];
    toneByFreq(freq,dur);
  }

//  nrf_drv_gpiote_out_task_disable(buzzerPin);
  nrf_gpio_cfg_output(buzzerPin);
  nrf_gpio_pin_clear(buzzerPin);
}