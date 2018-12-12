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
#include "app_button.h"
#include "app_error.h"
#include "app_timer.h"
#include "custom_board.h"
//#include "boards.h"
#include "compiler_abstraction.h"
#include "nordic_common.h"
#include "nrf_calendar.h"
//#include "nrf_delay.h"
#include "nrf_drv_clock.h"
//#include "nrf_drv_gpiote.h"
#include "nrf_drv_saadc.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "nrf_pwr_mgmt.h"
#include "nrf_soc.h"
#include "string.h"

//#include "binary.h"
//#include "ssd1306.h"
#include "u8g2.h"
#include "u8g2_nrf52_hal.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

// TODO: change names. STimer -> Anki иаиравиакпрепапркупкецин5епмк4уеку
#include "AnkiUsedFonts.h"
#include "STimerImages.h"
//#include "STimerRevision.h"
//#include "STimerLanguage.h"
//#include "STimerInterface.h"
//#include "STimerScreens.h"
#include "SoundLibrary.h"

u8g2_t u8g2;
u8g2_nrf52_hal_t u8g2_nrf52_hal = U8G2_NRF52_HAL_DEFAULT;

//===== TIME SECTION START ========
//volatile struct tm *currentTime;
//static char curTime[8];
//static char curDay[3];
//static char curMonth[4];
//static char curYear[5];
//int new_dt_hour, new_dt_min, new_dt_ampm, new_dt_day, new_dt_month, new_dt_year;
//===== TIME SECTION END ==========
//
//===== BATTERY SECTION START =====
//volatile int battery_level = 0;
//
//#define ADC_REF_VOLTAGE_IN_MILLIVOLTS 600 //!< Reference voltage (in milli volts) used by ADC while doing conversion.
//#define ADC_RES_10BIT 1024                //!< Maximum digital value for 10-bit ADC conversion.
//#define ADC_PRE_SCALING_COMPENSATION 5    //!< The ADC is configured to use VDD with 1/3 prescaling as input. And hence the result of conversion is to be multiplied by 3 to get the actual value of the battery voltage.
//#define ADC_RESULT_IN_MILLI_VOLTS(ADC_VALUE) \
//  ((((ADC_VALUE)*ADC_REF_VOLTAGE_IN_MILLIVOLTS) / ADC_RES_10BIT) * ADC_PRE_SCALING_COMPENSATION)
//
//static nrf_saadc_value_t adc_buf;          //!< Buffer used for storing ADC value.
//static uint16_t m_batt_lvl_in_milli_volts; //!< Current battery level.
//
//static uint8_t saadc_init_flag = 0;
//static bool app_btn_init_flag = false;
//===== BATTERY SECTION END =======


//===== POMODORO SECTION START =====
//#define POMODORO_TIME_MAX 25 //in minutes
//uint16_t pomodoroTime = POMODORO_TIME_MAX*60;
//uint8_t pomodoroShownTime = POMODORO_TIME_MAX;
//bool pomodoroInPause;
//
//pomodoro functions prototypes
//void pomodoroPrepareAndStart();
//void pomodoroPauseResume();
//void pomodoroStop();
//void pomodoroFinish();
//===== POMODORO SECTION END =======

//===== BUTTONS SECTION START =====
#define BUTTON_DEBOUNCE_DELAY 10

#define NUM_OF_BUTTONS 4

#define BTN_ID_MENU BUTTON_1
#define BTN_ID_CHOOSE BUTTON_2
#define BTN_ID_UP BUTTON_3
#define BTN_ID_DOWN BUTTON_4

static void button_handler(uint8_t button_no, uint8_t button_action);

static app_button_cfg_t p_button[] = {
    {BTN_ID_MENU, APP_BUTTON_ACTIVE_LOW, NRF_GPIO_PIN_PULLUP, button_handler},
    {BTN_ID_CHOOSE, APP_BUTTON_ACTIVE_LOW, NRF_GPIO_PIN_PULLUP, button_handler},
    {BTN_ID_UP, APP_BUTTON_ACTIVE_LOW, NRF_GPIO_PIN_PULLUP, button_handler},
    {BTN_ID_DOWN, APP_BUTTON_ACTIVE_LOW, NRF_GPIO_PIN_PULLUP, button_handler},
};
//===== BUTTONS SECTION END ========

//===== APP TIMERS SECTION START ======
//#define TIME_BEFORE_SLEEP APP_TIMER_TICKS(10000)
//#define LONGPUSH_TIME APP_TIMER_TICKS(1000)
//bool longpush = false;
//
//APP_TIMER_DEF(sleep_timer_id);
//APP_TIMER_DEF(pomodoro_timer_id);
//APP_TIMER_DEF(longpush_detected_timer_id);
//APP_TIMER_DEF(main_app_timer_id);
//===== APP TIMERS SECTION END ========


//#define DELAY_MS 1000             /**< Timer Delay in milli-seconds. */
//#define SSD1306_CONFIG_SCL_PIN 15 //ARDUINO_SCL_PIN//SCL_PIN_NUMBER
//#define SSD1306_CONFIG_SDA_PIN 17 //ARDUINO_SDA_PIN//SDA_PIN_NUMBER

//===== STATE MACHINE SECTION START ======
//void stimer_states();
//
//#define STIMER_INITIAL_STATE     0
//#define STIMER_MAIN_SCREEN       1
//#define STIMER_SLP               2
//#define STIMER_TIMER_RESET       6
//#define STIMER_TIMER_MOTIVATION  7
//#define STIMER_MENU             11
//#define STIMER_SET_MENU         20
//#define STIMER_SET_TIME         21
//#define STIMER_SET_DATE         22
//#define STIMER_LAST_UPD         23
//#define STIMER_LANG_MENU        24
//#define STIMER_LANG_SELECT      25
//#define STIMER_RESET            26
//#define STIMER_BRIGHT           27
//
//#define STIMER_POMODORO_CONFIRM_START     51
//#define STIMER_POMODORO_MAIN_SCREEN       52
//#define STIMER_POMODORO_CONFIRM_BACK      521
//#define STIMER_SLP_POMODORO               522
//#define STIMER_POMODORO_FINISH            53
//#define STIMER_SLP_POMODORO_FIN           531
//
//#define STIMER_TIMERS_LIST                   3    //screen with timers list
//#define STIMER_TIMERS_TIMER_MENU             30   //menu for selected timer
//#define STIMER_TIMERS_TIMER_CONFIRM_ACTIVATE 31   //confirm activation
//#define STIMER_TIMERS_SET_TIMER_NAME         32   //set name for timer
//#define STIMER_TIMERS_SET_TIMER_MOTIVATION   33	  //menu to add / view / delete motivation
//#define STIMER_TIMERS_TIMER_MOTIVATION_ADD   331  //screen where add motivation
//#define STIMER_TIMERS_TIMER_MOTIVATION_LIST  332  //VIEW/DELETE pressed, show mot. list
//#define STIMER_TIMERS_TIMER_MOTIVATION_VIEW  3321 //view selected motivation
//#define STIMER_TIMERS_TIMER_MOTIVATION_CONFIRM_DELETE 3322
//#define STIMER_TIMERS_TIMER_CONFIRM_DELETE   34   //confirm delete timer
//
//static uint16_t STimer_State = STIMER_INITIAL_STATE;
////===== STATE MACHINE SECTION END =========
//
//#define SET_DATE_INIT  0
//#define SET_DATE_HOUR  1
//#define SET_DATE_MIN   2
//#define SET_DATE_AMPM  3
//#define SET_DATE_DAY   4
//#define SET_DATE_MONTH 5
//#define SET_DATE_YEAR  6
//int set_date_time_state = SET_DATE_INIT;
//
//#define BRIGHTNESS_LEVEL_COUNT 7
//int brightnessLevel = 6;
//int oldBrightnessLevel = 6;
//
//
//static void time_change_event_handler()
//{
//  timerBaseAddMinuteToActiveTimers();
//}

//static void saadc_event_handler(nrf_drv_saadc_evt_t const *p_evt) {
//  if (p_evt->type == NRF_DRV_SAADC_EVT_DONE) {
//    nrf_saadc_value_t adc_result;
//
//    adc_result = p_evt->data.done.p_buffer[0];
//
//    m_batt_lvl_in_milli_volts = ADC_RESULT_IN_MILLI_VOLTS(adc_result);
//  }
//}
//
//uint8_t battery_lvl(uint16_t m_batt_lvl) {
//  if (m_batt_lvl >= 2300) //max
//    m_batt_lvl = 2299;
//  if (m_batt_lvl <= 1500) //min
//    m_batt_lvl = 1500;
//
//  return (uint8_t)((m_batt_lvl - 1500) / 133); // (max-min)/6
//}
//
//void battery_voltage_init(void) {
//
//  ret_code_t err_code = nrf_drv_saadc_init(NULL, saadc_event_handler);
//
//  APP_ERROR_CHECK(err_code);
//
//  nrf_saadc_channel_config_t config = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN2);
//  err_code = nrf_drv_saadc_channel_init(0, &config);
//  APP_ERROR_CHECK(err_code);
//
//  err_code = nrf_drv_saadc_buffer_convert(&adc_buf, 1);
//  APP_ERROR_CHECK(err_code);
//
//  err_code = nrf_drv_saadc_sample();
//  APP_ERROR_CHECK(err_code);
//
//  saadc_init_flag = 1;
//}
//
//void battery_voltage_uninit(void) {
//  nrf_drv_saadc_uninit();
//  NVIC_ClearPendingIRQ(SAADC_IRQn);
//  saadc_init_flag = 0;
//}
//
//void battery_voltage_get(uint16_t *p_vbatt) {
//  if (saadc_init_flag != 1)
//    battery_voltage_init();
//  VERIFY_PARAM_NOT_NULL_VOID(p_vbatt);
//
//  *p_vbatt = m_batt_lvl_in_milli_volts;
//  if (!nrf_drv_saadc_is_busy()) {
//    ret_code_t err_code = nrf_drv_saadc_buffer_convert(&adc_buf, 1);
//    APP_ERROR_CHECK(err_code);
//
//    err_code = nrf_drv_saadc_sample();
//    APP_ERROR_CHECK(err_code);
//  }
//  battery_voltage_uninit();
//}
//
//uint16_t battery_voltage;

//void enableButtons(bool state)
//{
//  uint32_t err_code = NRF_SUCCESS;
//  if(state)
//   {
//     err_code = app_button_init(p_button, sizeof(p_button) / sizeof(p_button[0]), BUTTON_DEBOUNCE_DELAY);
//     APP_ERROR_CHECK(err_code);
//     err_code = app_button_enable();
//     APP_ERROR_CHECK(err_code);
//   }
//   else
////     app_button_disable();
//   app_btn_init_flag = state;
//}
//
//void application_init() {
//
//  battery_voltage_init();
////  ssd1306_enable(SSD1306_CONFIG_SCL_PIN, SSD1306_CONFIG_SDA_PIN);
//}

//void preparing_to_sleep() {
//  uint32_t err_code;
//
//  app_button_disable();
//
//  app_btn_init_flag = 0;
//
//  nrf_gpio_cfg_sense_input(BTN_ID_UP, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
//
//  ssd1306_disable(SSD1306_CONFIG_SCL_PIN, SSD1306_CONFIG_SDA_PIN);
//}

//void preparing_to_wakeup() {
//  uint32_t err_code;
//
//  battery_voltage_init();
//
//  err_code = app_button_enable();
//  APP_ERROR_CHECK(err_code);
//
//  ssd1306_enable(SSD1306_CONFIG_SCL_PIN, SSD1306_CONFIG_SDA_PIN);
//}


//void calendar_updated() {
//    currentTime = nrf_cal_get_time();
//}

//void cal_update_date_time() {
//  strftime(curTime, 8, "%I:%M%p", nrf_cal_get_time());
//  strftime(curDay, 3, "%d", nrf_cal_get_time());
//  strftime(curMonth, 4, "%b", nrf_cal_get_time());
//  strftime(curYear, 5, "%Y", nrf_cal_get_time());
//}

//void pomodoroPrepareAndStart() {
//  //clear all variables & set pomodoro time
//  pomodoroTime = POMODORO_TIME_MAX*60;
//  pomodoroShownTime = POMODORO_TIME_MAX;
//  pomodoroInPause = false;
//  //animation
//  scrPomodoroAnimation();
//  //start pomodoro timer
//  uint32_t err_code = app_timer_start(pomodoro_timer_id,APP_TIMER_TICKS(1000),NULL);
//  APP_ERROR_CHECK(err_code);
//}

//static void pomodoro_event_handler() {
//  uint32_t err_code;
//
//  if(!pomodoroInPause)
//  {
//    pomodoroTime--;
//    if((pomodoroTime % 60) == 0)
//      pomodoroShownTime--;
//  }
//
//  if(pomodoroTime == 0)
//    pomodoroFinish();
//}

//void pomodoroPauseResume()
//{
//  pomodoroInPause = !pomodoroInPause;
//}

//void pomodoroStop()
//{
//  pomodoroInPause = false;
//  uint32_t err_code = app_timer_stop(pomodoro_timer_id);
//  APP_ERROR_CHECK(err_code);
//}

//void pomodoroFinish()
//{
//  if(STimer_State == STIMER_SLP_POMODORO)
//    {
//      preparing_to_wakeup();
//    }
//    STimer_State = STIMER_POMODORO_FINISH;
//    stimer_states();
//    pomodoroStop();
//    buzzer(BUZZER_PIN, soundPomodoro);
//}

//void set_date_time_up() {
//  switch (set_date_time_state) {
//  case SET_DATE_HOUR:
//    if (new_dt_hour == 11)
//      new_dt_hour = 0;
//    else
//      new_dt_hour++;
//    break;
//  case SET_DATE_MIN:
//    if (new_dt_min == 59)
//      new_dt_min = 0;
//    else
//      new_dt_min++;
//    break;
//  case SET_DATE_AMPM:
//    if (new_dt_ampm == 0)
//      new_dt_ampm = 1;
//    else
//      new_dt_ampm = 0;
//    break;
//  case SET_DATE_DAY:
//    if (new_dt_day == 31)
//      new_dt_day = 1;
//    else
//      new_dt_day++;
//    break;
//  case SET_DATE_MONTH:
//    if (new_dt_month == 11)
//      new_dt_month = 0;
//    else
//      new_dt_month++;
//    break;
//  case SET_DATE_YEAR:
//    new_dt_year++;
//    break;
//  case SET_DATE_INIT:
//  default:
//    break;
//  }
//}
//
//void set_date_time_down() {
//  switch (set_date_time_state) {
//  case SET_DATE_HOUR:
//    if (new_dt_hour == 0)
//      new_dt_hour = 11;
//    else
//      new_dt_hour--;
//    break;
//  case SET_DATE_MIN:
//    if (new_dt_min == 0)
//      new_dt_min = 59;
//    else
//      new_dt_min--;
//    break;
//  case SET_DATE_AMPM:
//    if (new_dt_ampm == 0)
//      new_dt_ampm = 1;
//    else
//      new_dt_ampm = 0;
//    break;
//  case SET_DATE_DAY:
//    if (new_dt_day == 0)
//      new_dt_day = 31;
//    else
//      new_dt_day--;
//    break;
//  case SET_DATE_MONTH:
//    if (new_dt_month == 0)
//      new_dt_month = 11;
//    else
//      new_dt_month--;
//    break;
//  case SET_DATE_YEAR:
//    new_dt_year--;
//    break;
//  case SET_DATE_INIT:
//  default:
//    break;
//  }
//}
//
//void set_date_time_choose() {
//  time_t currentOldTime, currentNewTime;
//  switch (set_date_time_state) {
//  case SET_DATE_INIT:
//    // save current time to new time
//    new_dt_hour = nrf_cal_get_time()->tm_hour;
//    if (new_dt_hour > 12) {
//      new_dt_hour -= 12;
//      new_dt_ampm = 1;
//    } else
//      new_dt_ampm = 0;
//    new_dt_min = nrf_cal_get_time()->tm_min;
//    new_dt_day = nrf_cal_get_time()->tm_mday;
//    new_dt_month = nrf_cal_get_time()->tm_mon;
//    new_dt_year = nrf_cal_get_time()->tm_year + 1900;
//    set_date_time_state++;
//    break;
//  case SET_DATE_HOUR:
//  case SET_DATE_MIN:
//  case SET_DATE_AMPM:
//  case SET_DATE_DAY:
//  case SET_DATE_MONTH:
//    set_date_time_state++;
//    break;
//  case SET_DATE_YEAR:
//    nrf_cal_set_time(new_dt_year, new_dt_month, new_dt_day, new_dt_hour + 12 * new_dt_ampm, new_dt_min, 0);
//    set_date_time_state = SET_DATE_INIT;
//    STimer_State = STIMER_SET_MENU;
//    calendar_updated();
//    break;
//  default:
//    break;
//  }
//}
//
//
//static void button_longpush_event_handler(void *p_context) {
//  UNUSED_PARAMETER(p_context);
//   longpush = true;
//}

//void powerOff()
//{
//  ssd1306_clear_display();
//  ssd1306_display();
//  //nrf_gpio_pin_clear(INPUT_VOLTAGE_PIN);
//  NRF_POWER->SYSTEMOFF = 1;
//}

//void stimer_states() {
//  calendar_updated();
//  battery_voltage_get(&battery_voltage);
//  battery_level = battery_lvl(battery_voltage);
//  cal_update_date_time();
//  switch (STimer_State) {
//  case STIMER_INITIAL_STATE:
//    startScreen(curTime, curDay, curMonth, curYear);
//    break;
//
//  case STIMER_MAIN_SCREEN:
//    timerScreen(currentShownTimer,timerBaseGetActiveTimersCount());
//    break;
//
//  case STIMER_POMODORO_CONFIRM_START:
//    scrPomodoroConfirmStart();
//    break;
//
//  case STIMER_POMODORO_MAIN_SCREEN:
//    scrPomodoroMain(true);
//    break;
//
//  case STIMER_POMODORO_CONFIRM_BACK:
//    scrPomodoroMain(false);
//    break;
//
//  case STIMER_POMODORO_FINISH:
//    scrPomodoroFinish();
//    break;
//
//  case STIMER_SLP:
//  case STIMER_SLP_POMODORO:
//  case STIMER_SLP_POMODORO_FIN:
//    ssd1306_clear_display();
//    ssd1306_display();
//    break;
//
//  case STIMER_TIMER_RESET:
//    timerResetScreen();
//    break;
//
//  case STIMER_TIMER_MOTIVATION://view selected motivation
//    timerMotivationScreen(false, menuSelectedItemNum, false);
//    break;
//
//  case STIMER_MENU:
//    menuScreen(menuSelectedItemNum, currentMenuItemsCount);
//    break;
//
//  case STIMER_TIMERS_LIST:
//    menuTimersListScreen(menuSelectedItemNum, currentMenuItemsCount);
//    break;
//
//  case STIMER_TIMERS_TIMER_MENU:
//    menuTimerMenuScreen(selectedTimer, menuSelectedItemNum, currentMenuItemsCount);
//    break;
//
//  case STIMER_TIMERS_TIMER_CONFIRM_ACTIVATE:
//    menuTimerActivateScreen(selectedTimer);
//    break;
//
//  case STIMER_TIMERS_SET_TIMER_NAME:
//    if(selectedLetter == -2)
//    {
//      newTimerName[newTimerNameLenght] = '\0';
//      selectedLetter = 0;
//    }
//    switch(currLang_id) {
//      case 0:
//        newTimerName[newTimerNameLenght-1] = letters_eng[selectedLetter][0];
//        break;
//      case 1:
//        newTimerName[newTimerNameLenght-1] = letters_esp[selectedLetter][0];
//        break;
//      case 2:
//        newTimerName[newTimerNameLenght-1] = letters_fra[selectedLetter][0];
//        break;
//      default:
//        newTimerName[newTimerNameLenght-1] = letters_eng[selectedLetter][0];
//        break;      
//    }
//    menuAddNewTimerScreen(selectedLetter, newTimerNameLenght, selectedTimer);
//    break;
//
//  case STIMER_TIMERS_SET_TIMER_MOTIVATION:
//    menuMotivMenuScreen(selectedTimer, menuSelectedItemNum, currentMenuItemsCount);
//    break;
//
//  case STIMER_TIMERS_TIMER_MOTIVATION_ADD:
//    if(selectedLetter == -2)
//    {
//      newMotivation[newMotivationLength] = '\0';
//      selectedLetter = 0;
//    }
//    switch(currLang_id) {
//      case 0:
//        newMotivation[newMotivationLength-1] = letters_eng[selectedLetter][0];
//        break;
//      case 1:
//        newMotivation[newMotivationLength-1] = letters_esp[selectedLetter][0];
//        break;
//      case 2:
//        newMotivation[newMotivationLength-1] = letters_fra[selectedLetter][0];
//        break;
//      default:
//        newMotivation[newMotivationLength-1] = letters_eng[selectedLetter][0];
//        break;      
//    }
//    menuAddNewMotivationScreen(selectedLetter, newMotivationLength, selectedTimer);
//    break;
//
//  case STIMER_TIMERS_TIMER_MOTIVATION_LIST:
//    menuMotivationsListScreen(menuSelectedItemNum, currentMenuItemsCount);
//    break;
//
//  case STIMER_TIMERS_TIMER_MOTIVATION_VIEW:
//    timerMotivationScreen(true, menuSelectedItemNum, false);
//    break;
//
//  case STIMER_TIMERS_TIMER_MOTIVATION_CONFIRM_DELETE:
//    timerMotivationScreen(true, menuSelectedItemNum, true);
//    break;
//
//  case STIMER_TIMERS_TIMER_CONFIRM_DELETE:
//    menuDeleteTimerScreen(selectedTimer);
//    break;
//
//  case STIMER_SET_MENU:
//    menuSettingsScreen(menuSelectedItemNum, currentMenuItemsCount);
//    break;
//
//  case STIMER_SET_TIME:
//    switch (set_date_time_state) {
//    case SET_DATE_HOUR:
//    case SET_DATE_MIN:
//    case SET_DATE_AMPM:
//      menuSettingsTimeScreen(set_date_time_state, new_dt_hour, new_dt_min, new_dt_ampm);
//      break;
//    case SET_DATE_DAY:
//    case SET_DATE_MONTH:
//    case SET_DATE_YEAR:
//      menuSettingsDateScreen(set_date_time_state, new_dt_day, new_dt_month, new_dt_year);
//    case SET_DATE_INIT:
//    default:
//      break;
//    }
//    break;
//
//  case STIMER_LAST_UPD:
//    menuSettingsLastUpdScreen();
//    break;
//
//  case STIMER_LANG_MENU:
//    menuSettingsLanguage(menuSelectedItemNum, currentMenuItemsCount);
//    break;
//
//  case STIMER_LANG_SELECT:
//    menuSettingsLanguageSelect(menuSelectedItemNum);
//    break;
//
//  case STIMER_RESET:
//    menuSettingsReset();
//    break;
//
//  case STIMER_BRIGHT:
//    menuSettingsBrightness(brightnessLevel);
//    break;
//
//  default:
//    break;
//  }
//  uint32_t err_code;
//
//  if(STimer_State != STIMER_TIMERS_SET_TIMER_NAME && STimer_State != STIMER_TIMERS_TIMER_MOTIVATION_ADD)
//  {
//    err_code = app_timer_start(sleep_timer_id, TIME_BEFORE_SLEEP, NULL);
//    APP_ERROR_CHECK(err_code);
//  }
//}
//
//static void button_handler(uint8_t button_no, uint8_t button_action) {
//  uint32_t err_code;
//
//  err_code = app_timer_stop(sleep_timer_id);
//  APP_ERROR_CHECK(err_code);
//
//  if (STimer_State == STIMER_SLP) {
//    preparing_to_wakeup();
//    STimer_State = STIMER_INITIAL_STATE;
//    return;
//  }
//
//  if (STimer_State == STIMER_SLP_POMODORO) {
//    preparing_to_wakeup();
//    STimer_State = STIMER_POMODORO_MAIN_SCREEN;
//    return;
//  }
//
//  if(STimer_State == STIMER_SLP_POMODORO_FIN)
//  {
//    preparing_to_wakeup();
//    STimer_State = STIMER_POMODORO_FINISH;
//    return;
//  }
//  
//  if (button_action == APP_BUTTON_PUSH) {
//    switch (button_no) {
//
//    case BTN_ID_MENU:
//    case BTN_ID_CHOOSE:
//    case BTN_ID_UP:
//      longpush = false;
//      err_code = app_timer_start(longpush_detected_timer_id, LONGPUSH_TIME, NULL);
//      APP_ERROR_CHECK(err_code);
//      break;
//
//    case BTN_ID_DOWN:
//    default:
//      break;
//    }
//  } else if (button_action == APP_BUTTON_RELEASE) {
//    switch (button_no) {
//
//    case BTN_ID_MENU:
//      err_code = app_timer_stop(longpush_detected_timer_id);
//      APP_ERROR_CHECK(err_code);
//
//      switch (STimer_State) {
//      case STIMER_INITIAL_STATE:
//        STimer_State = STIMER_MAIN_SCREEN;
//        break;
//
//      case STIMER_MAIN_SCREEN:
//        if(longpush)
//        {
//          longpush = false;
//          STimer_State = STIMER_TIMER_RESET;
//        }
//        else
//	{
//	  currentMenuItemsCount = MENU_ITEM_COUNT;
//          menuSelectedItemNum = 0;
//          STimer_State = STIMER_MENU;
//	}
//        break;
////===== POMODORO STATES BUTTON MENU START ============
//      case STIMER_POMODORO_CONFIRM_START:
//	  pomodoroPrepareAndStart();
//	  STimer_State = STIMER_POMODORO_MAIN_SCREEN;
//	break;
//      case STIMER_POMODORO_MAIN_SCREEN:
//        STimer_State = STIMER_POMODORO_CONFIRM_BACK;
//        break;
//      case STIMER_POMODORO_CONFIRM_BACK:
//        STimer_State = STIMER_POMODORO_MAIN_SCREEN;
//        break;
//      case STIMER_POMODORO_FINISH:
//        STimer_State = STIMER_MAIN_SCREEN;
//        break;
////===== POMODORO STATES BUTTON MENU END ============
//      case STIMER_TIMER_RESET:
//      case STIMER_TIMER_MOTIVATION:
//      case STIMER_MENU:
//      case STIMER_LANG_SELECT:
//        STimer_State = STIMER_MAIN_SCREEN;
//        break;
//
//      case STIMER_TIMERS_LIST:    //screen with timers list
//	menuSelectedItemNum = 0;
//	STimer_State = STIMER_MAIN_SCREEN;
//	break;
//
//      case STIMER_TIMERS_TIMER_MENU:   //menu for selected timer
//	currentMenuItemsCount = MAX_TIMERS_COUNT;
//	menuSelectedItemNum = 0;
//        selectedTimer = 0;
//	STimer_State = STIMER_TIMERS_LIST;
//	break;
//
//      case STIMER_TIMERS_TIMER_CONFIRM_ACTIVATE:   //confirm activation
//	timerBaseActivateTimer(selectedTimer);
//	STimer_State = STIMER_MAIN_SCREEN;
//	break;
//
//      case STIMER_TIMERS_SET_TIMER_NAME:   //set name for timer
//	if(longpush)
//	{
//	  longpush = false;
//	  if(timerBaseIsTimer(selectedTimer))
//	    timerBaseChangeTimerName(selectedTimer, newTimerName);
//	  else
//	    timerBaseAddNewTimer(newTimerName);
//	}
//        currentMenuItemsCount = MENU_ADD_TIMER_COUNT;
//	menuSelectedItemNum = 0;
//	STimer_State = STIMER_TIMERS_TIMER_MENU;
//	break;
//
//      case STIMER_TIMERS_SET_TIMER_MOTIVATION:	  //menu to add / view / delete motivation
//	currentMenuItemsCount = MENU_ADD_TIMER_COUNT;
//	menuSelectedItemNum = 0;
//	STimer_State = STIMER_TIMERS_TIMER_MENU;
//	break;
//
//      case STIMER_TIMERS_TIMER_MOTIVATION_ADD:  //screen where add motivation
//	if(longpush)
//	{
//	  longpush = false;
//	  timerBaseAddMotivationToTimer(selectedTimer, newMotivation);
//	}
//        currentMenuItemsCount = MENU_MOTIVATION_COUNT;
//        menuSelectedItemNum = 0;
//	STimer_State = STIMER_TIMERS_SET_TIMER_MOTIVATION;
//	break;
//
//      case STIMER_TIMERS_TIMER_MOTIVATION_LIST:  //VIEW/DELETE pressed, show mot. list
//	currentMenuItemsCount = MENU_MOTIVATION_COUNT;
//        menuSelectedItemNum = 0;
//	STimer_State = STIMER_TIMERS_SET_TIMER_MOTIVATION;
//	break;
//
//      case STIMER_TIMERS_TIMER_MOTIVATION_VIEW: //view selected motivation
//	currentMenuItemsCount = timerBaseGetTimerMotivationsNum(selectedTimer);
//	menuSelectedItemNum = 0;
//	STimer_State = STIMER_TIMERS_TIMER_MOTIVATION_LIST;
//	break;
//      
//      case STIMER_TIMERS_TIMER_MOTIVATION_CONFIRM_DELETE:
//	timerBaseDelMotivationFromTimer(selectedTimer, selectedMotivation);
//        currentMenuItemsCount = MENU_MOTIVATION_COUNT;
//        menuSelectedItemNum = 0;
//	STimer_State = STIMER_TIMERS_SET_TIMER_MOTIVATION;
//	break;
//
//      case STIMER_TIMERS_TIMER_CONFIRM_DELETE:
//	timerBaseDelTimer(selectedTimer);
//        currentMenuItemsCount = MAX_TIMERS_COUNT;
//        menuSelectedItemNum = 0;
//	STimer_State = STIMER_TIMERS_LIST;
//	break;
//
//      case STIMER_SET_MENU:
//	currentMenuItemsCount = MENU_ITEM_COUNT;
//        menuSelectedItemNum = 0;
//        STimer_State = STIMER_MENU;
//        break;
//      case STIMER_SET_TIME:
//      case STIMER_LAST_UPD:
//      case STIMER_LANG_MENU:
//      case STIMER_RESET:
//        currentMenuItemsCount = MENU_SETTINGS_ITEM_COUNT;
//        menuSelectedItemNum = 0;
//        STimer_State = STIMER_SET_MENU;
//        break;
//
//      case STIMER_BRIGHT:
//        if(oldBrightnessLevel != brightnessLevel) 
//        {
//	  menuSettingsBrightness(oldBrightnessLevel);
//          brightnessLevel = oldBrightnessLevel;
//        }
//	currentMenuItemsCount = MENU_SETTINGS_ITEM_COUNT;
//        menuSelectedItemNum = 0;
//        STimer_State = STIMER_SET_MENU;
//        break;
//      case STIMER_SLP_POMODORO:
//      case STIMER_SLP_POMODORO_FIN:
//      default:
//        break;
//      }
//      break;
//    case BTN_ID_CHOOSE:
//      err_code = app_timer_stop(longpush_detected_timer_id);
//      APP_ERROR_CHECK(err_code);
//
//        switch (STimer_State) {
//        case STIMER_INITIAL_STATE:
//          STimer_State = STIMER_MAIN_SCREEN;
//          break;
//        case STIMER_MAIN_SCREEN:
//          if (timerBaseGetActiveTimersCount() > 0)
//	  {
//	    currentMenuItemsCount = timerBaseGetTimerMotivationsNLC(currentShownTimer, selectedMotivation) / MAX_SHOWN_STRINGS+1;
//	    menuSelectedItemNum = 0;
//            STimer_State = STIMER_TIMER_MOTIVATION;
//	  }
//          break;
//        case STIMER_TIMER_RESET:
//	  timerBaseResetTimer();
//          STimer_State = STIMER_MAIN_SCREEN;
//          break;
//
//        case STIMER_MENU:
//          switch (menuSelectedItemNum) {
//          case 0:
//	    currentMenuItemsCount = MAX_TIMERS_COUNT;
//            menuSelectedItemNum = 0;
//            STimer_State = STIMER_TIMERS_LIST;
//            break;
//          case 1:
//	    menuSelectedItemNum = 0;
//            STimer_State = STIMER_POMODORO_CONFIRM_START;
//            break;
//          case 2:
//	    currentMenuItemsCount = MENU_SETTINGS_ITEM_COUNT;
//            menuSelectedItemNum = 0;
//            STimer_State = STIMER_SET_MENU;
//            break;
//          default:
//            break;
//          }
//          break;
////===== POMODORO STATES BUTTON CHOOSE START ============
//	case STIMER_POMODORO_CONFIRM_START:
//	  STimer_State = STIMER_MAIN_SCREEN;
//	  break;
//	case STIMER_POMODORO_MAIN_SCREEN:
//	  pomodoroPauseResume();
//          scrPomodoroMain(true);
//	  break;
//	case STIMER_POMODORO_CONFIRM_BACK:
//	  pomodoroStop();
//	  STimer_State = STIMER_MAIN_SCREEN;
//	  break;
////===== POMODORO STATES BUTTON CHOOSE END ============
//       
////===== TIMER BASE CONTROL SECTION START BUTTON CHOOSE ========
//	case STIMER_TIMER_MOTIVATION:
//	  menuSelectedItemNum = 0;
//          selectedMotivation++;
//	  if(selectedMotivation == timerBaseGetTimerMotivationsNum(activeTimers[currentShownTimer]))
//	    selectedMotivation = 0;
//	  break;
//
//	case STIMER_TIMERS_LIST:                   //screen with timers list
//	  selectedTimer = menuSelectedItemNum;
//	  currentMenuItemsCount = MENU_ADD_TIMER_COUNT;
//	  menuSelectedItemNum = 0;
//	  STimer_State = STIMER_TIMERS_TIMER_MENU;
//	  break;
//        case STIMER_TIMERS_TIMER_MENU:             //menu for selected timer
//	  switch(menuSelectedItemNum)
//	  {
//	    case 0: //activate
//	      if(timerBaseIsTimer(selectedTimer))
//		STimer_State = STIMER_TIMERS_TIMER_CONFIRM_ACTIVATE;
//	      break;
//	    case 1: //name
//	      if(timerBaseIsTimer(selectedTimer))
//	      {
//		strcpy(newTimerName, timerBaseGetTimerName(selectedTimer));
//		newTimerNameLenght = strlen(newTimerName);
//	      }
//	      else
//	      {
//		newTimerName = (char *)malloc(MAX_TIMER_NAME_LENGTH*sizeof(char));
//                for(uint8_t i = 0; i < MAX_TIMER_NAME_LENGTH-1; i++)
//		  newTimerName[i] = '\0';
//		newTimerName[MAX_TIMER_NAME_LENGTH-1] = '\0';
//		newTimerNameLenght = 1;
//	      }
//	      selectedLetter = 0;
//	      STimer_State = STIMER_TIMERS_SET_TIMER_NAME;
//	      break;
//	    case 2: //motivation
//	      if(timerBaseIsTimer(selectedTimer))
//	      {
//		currentMenuItemsCount = MENU_MOTIVATION_COUNT;
//		menuSelectedItemNum = 0;
//		STimer_State = STIMER_TIMERS_SET_TIMER_MOTIVATION;
//	      }
//	      break;
//	    case 3: //delete
//	      if(timerBaseIsTimer(selectedTimer))
//		STimer_State = STIMER_TIMERS_TIMER_CONFIRM_DELETE;
//	      break;
//	    default:
//	      break;
//	  }
//	  break;
//	case STIMER_TIMERS_TIMER_CONFIRM_ACTIVATE: //confirm activation NOTE: button says: NO
//	  STimer_State = STIMER_TIMERS_TIMER_MENU;
//	  break;
//	case STIMER_TIMERS_SET_TIMER_MOTIVATION:   //menu to add / view / delete motivation
//	  switch(menuSelectedItemNum)
//	  {
//	    case 0: //add
//	      if(timerBaseGetTimerMotivationsNum(selectedTimer) < MAX_MOTIVATION_COUNT)
//	      {
//		for(uint8_t i = 0; i < MAX_MOTIVATION_LENGTH; i++)
//		  newMotivation[i] = '\0';
//		newMotivationLength = 1;
//		STimer_State = STIMER_TIMERS_TIMER_MOTIVATION_ADD;    //screen where add motivation
//		selectedLetter = 0;
//	      }
//	      break;
//	    case 1: //view / delete
//	      if(timerBaseGetTimerMotivationsNum(selectedTimer) != 0)
//	      {
//		currentMenuItemsCount = timerBaseGetTimerMotivationsNum(selectedTimer);
//		menuSelectedItemNum = 0;
//		STimer_State = STIMER_TIMERS_TIMER_MOTIVATION_LIST;  //VIEW/DELETE pressed, show mot. list
//	      }
//	      break;
//	    default:
//	      break;
//	  }
//	  break;
//	case STIMER_TIMERS_TIMER_MOTIVATION_LIST:  //CHOOSE pressed, show motivation
//	  selectedMotivation = menuSelectedItemNum;
//          currentMenuItemsCount = timerBaseGetTimerMotivationsNLC(selectedTimer, selectedMotivation) / MAX_SHOWN_STRINGS + 1;
//          menuSelectedItemNum = 0;
//	  STimer_State = STIMER_TIMERS_TIMER_MOTIVATION_VIEW;  //view selected motivation
//	  break;
//
//	case STIMER_TIMERS_SET_TIMER_NAME:          //set name for timer
//	  if(longpush)
//	  {
//	    longpush = false;
//	    if(newTimerNameLenght > 0)
//	    {
//	      selectedLetter = -2;
//	      newTimerNameLenght--;
//	    }
//	  }
//	  else
//	    if (newTimerNameLenght < MAX_TIMER_NAME_LENGTH-1)
//	    {
//	      newTimerNameLenght++;
//	      selectedLetter = 0;
//	    }
//	  break;
//
//      case STIMER_TIMERS_TIMER_MOTIVATION_ADD:  //screen where add motivation
//	if(longpush)
//	  {
//	    longpush = false;
//	    if(newMotivationLength > 0)
//	    {
//	      selectedLetter = -2;
//	      newMotivationLength--;
//	    }
//	  }
//	  else
//	    if (newMotivationLength < MAX_MOTIVATION_LENGTH-1)
//	    {
//	      newMotivationLength++;
//	      selectedLetter = 0;
//	    }
//	  break;
//	break;
//
//      case STIMER_TIMERS_TIMER_MOTIVATION_VIEW: //view selected motivation
//	STimer_State = STIMER_TIMERS_TIMER_MOTIVATION_CONFIRM_DELETE;
//	break;
//
//      case STIMER_TIMERS_TIMER_MOTIVATION_CONFIRM_DELETE:
//	STimer_State = STIMER_TIMERS_TIMER_MOTIVATION_VIEW;
//	break;
//
//      case STIMER_TIMERS_TIMER_CONFIRM_DELETE:
//	STimer_State = STIMER_TIMERS_TIMER_MENU;
//	break;
////===== TIMER BASE CONTROL SECTION END BUTTON CHOOSE ========
//       
//        case STIMER_SET_MENU:
//          switch (menuSelectedItemNum) {
//          case 0:
//	    currentMenuItemsCount = MENU_LANGUAGE_COUNT;
//            menuSelectedItemNum = 0;
//            STimer_State = STIMER_LANG_MENU;
//            break;
//          case 1:
//	    set_date_time_choose();
//            STimer_State = STIMER_SET_TIME;
//            break;
//          case 2:
//	    oldBrightnessLevel = brightnessLevel;
//            STimer_State = STIMER_BRIGHT;
//            break;
//          case 3:
//            STimer_State = STIMER_LAST_UPD;
//            break;
//          case 4:
//            STimer_State = STIMER_RESET;
//            break;
//          default:
//            break;
//          }
//          break;
//        case STIMER_SET_TIME:
//          set_date_time_choose();
//          break;
//        case STIMER_LANG_MENU:
//          STimer_State = STIMER_LANG_SELECT;
//          break;
//        case STIMER_LANG_SELECT:
//	  currLang_id = selectedLang_id;
//          currentMenuItemsCount = MENU_SETTINGS_ITEM_COUNT;
//           menuSelectedItemNum = 0;
//          STimer_State = STIMER_SET_MENU;
//          break;
//        case STIMER_RESET:
//          powerOff();
//          break;
//        case STIMER_BRIGHT:
//	  currentMenuItemsCount = MENU_SETTINGS_ITEM_COUNT;
//          menuSelectedItemNum = 0;
//          STimer_State = STIMER_SET_MENU;
//          break;
//	case STIMER_SLP_POMODORO:
//	case STIMER_SLP_POMODORO_FIN:
//        case STIMER_POMODORO_FINISH:
//        case STIMER_LAST_UPD:
//        default:
//          break;
//        }
//      
//      break;
//    case BTN_ID_UP:
//      err_code = app_timer_stop(longpush_detected_timer_id);
//      APP_ERROR_CHECK(err_code);
//
//      if (longpush) { //sleep, not power off
//        longpush = false;
//        err_code = app_timer_start(sleep_timer_id, APP_TIMER_TICKS(BUTTON_DEBOUNCE_DELAY+1), NULL);
//        APP_ERROR_CHECK(err_code);
//      } else {
//        switch (STimer_State) {
//
//        case STIMER_SET_TIME:
//          set_date_time_up();
//          break;
//
//        case STIMER_BRIGHT:
//          brightnessLevel++;
//          if (brightnessLevel >= BRIGHTNESS_LEVEL_COUNT)
//            brightnessLevel = BRIGHTNESS_LEVEL_COUNT - 1;
//          break;
//
//        case STIMER_MENU:
//        case STIMER_SET_MENU:
//        case STIMER_LANG_MENU:
//	case STIMER_TIMERS_TIMER_MOTIVATION_VIEW:
//        case STIMER_TIMER_MOTIVATION:
//        case STIMER_TIMERS_LIST:                   //screen with timers list
//        case STIMER_TIMERS_TIMER_MENU:             //menu for selected timer
//	case STIMER_TIMERS_SET_TIMER_MOTIVATION:   //menu to add / view / delete motivation
//	case STIMER_TIMERS_TIMER_MOTIVATION_LIST:  //VIEW/DELETE pressed, show mot. list
//	  if(menuSelectedItemNum > 0)
//	    menuSelectedItemNum--;
//          break;
//
//	case STIMER_TIMERS_TIMER_MOTIVATION_ADD:   //screen where add motivation
//	case STIMER_TIMERS_SET_TIMER_NAME:
//	  selectedLetter++;
//          switch(currLang_id) {
//            case 0:
//	      if(selectedLetter == LETTERS_ENG_COUNT)
//	        selectedLetter = 0;
//              break;
//            case 1:
//	      if(selectedLetter == LETTERS_ESP_COUNT)
//	        selectedLetter = 0;
//              break;
//            case 2:
//	      if(selectedLetter == LETTERS_FRA_COUNT)
//	        selectedLetter = 0;
//              break;
//            default:
//	      if(selectedLetter == LETTERS_ENG_COUNT)
//	        selectedLetter = 0;
//              break;
//	  }
//          break;
//
//        case STIMER_MAIN_SCREEN:
//	  currentShownTimer--;
//	  if(currentShownTimer < 0)
//	    currentShownTimer = 0;
//	  break;
//
//        case STIMER_TIMER_RESET:
//        case STIMER_POMODORO_CONFIRM_START:
//	case STIMER_POMODORO_MAIN_SCREEN:
//	case STIMER_POMODORO_CONFIRM_BACK:
//	case STIMER_POMODORO_FINISH:
//	case STIMER_TIMERS_TIMER_CONFIRM_ACTIVATE:
//	case STIMER_TIMERS_TIMER_MOTIVATION_CONFIRM_DELETE:
//	case STIMER_TIMERS_TIMER_CONFIRM_DELETE:
//        case STIMER_LANG_SELECT:
//        case STIMER_LAST_UPD:
//        case STIMER_RESET:
//        default:
//          break;
//        }
//      }
//      break;
//    case BTN_ID_DOWN:
//      switch (STimer_State) {
//      case STIMER_INITIAL_STATE:
//        STimer_State = STIMER_MAIN_SCREEN;
//        break;
//
//      case STIMER_MENU:
//      case STIMER_SET_MENU:
//      case STIMER_LANG_MENU:
//      case STIMER_TIMERS_TIMER_MOTIVATION_VIEW:
//      case STIMER_TIMER_MOTIVATION:
//      case STIMER_TIMERS_LIST:                   //screen with timers list
//      case STIMER_TIMERS_TIMER_MENU:             //menu for selected timer
//      case STIMER_TIMERS_SET_TIMER_MOTIVATION:   //menu to add / view / delete motivation
//      case STIMER_TIMERS_TIMER_MOTIVATION_LIST:  //VIEW/DELETE pressed, show mot. list
//        if (menuSelectedItemNum < currentMenuItemsCount-1)
//	  menuSelectedItemNum++;
//        break;
//
//      case STIMER_SET_TIME:
//        set_date_time_down();
//        break;
//
//      case STIMER_BRIGHT:
//        brightnessLevel--;
//        if (brightnessLevel < 0)
//          brightnessLevel = 0;
//        break;
//
//      case STIMER_TIMERS_TIMER_MOTIVATION_ADD:   //screen where add motivation
//      case STIMER_TIMERS_SET_TIMER_NAME:
//	selectedLetter--;
//          switch(currLang_id) {
//            case 0:
//	      if(selectedLetter < 0)
//	        selectedLetter = LETTERS_ENG_COUNT - 1;
//              break;
//            case 1:
//	      if(selectedLetter < 0)
//	        selectedLetter = LETTERS_ESP_COUNT - 1;
//              break;
//            case 2:
//	      if(selectedLetter < 0)
//	        selectedLetter = LETTERS_FRA_COUNT - 1;
//              break;
//            default:
//	      if(selectedLetter < 0)
//	        selectedLetter = LETTERS_ENG_COUNT - 1;
//              break;
//	  }
//	break;
//
//      case STIMER_MAIN_SCREEN:
//	currentShownTimer++;
//	if(currentShownTimer == activeTimersNum)
//	  currentShownTimer = activeTimersNum-1;
//	break;
//
//      case STIMER_TIMER_RESET:
//      case STIMER_POMODORO_CONFIRM_START:
//      case STIMER_POMODORO_MAIN_SCREEN:
//      case STIMER_POMODORO_CONFIRM_BACK:
//      case STIMER_POMODORO_FINISH:
//      case STIMER_TIMERS_TIMER_CONFIRM_ACTIVATE:
//      case STIMER_TIMERS_TIMER_MOTIVATION_CONFIRM_DELETE:
//      case STIMER_TIMERS_TIMER_CONFIRM_DELETE:
//      case STIMER_LANG_SELECT:
//      case STIMER_LAST_UPD:
//      case STIMER_RESET:
//        break;
//      default:
//        break;
//      }
//      break;
//    default:
//      return;
//    }
//    stimer_states();
//  }
//}

//void sleep_timer_handler(void *p_context) {
//UNUSED_PARAMETER(p_context);
//  uint32_t err_code;
//
//  ssd1306_clear_display();
//  ssd1306_display();
//
//  if ((STimer_State == STIMER_POMODORO_CONFIRM_BACK) || (STimer_State == STIMER_POMODORO_MAIN_SCREEN))
//    STimer_State = STIMER_SLP_POMODORO;
//  else
//    if(STimer_State == STIMER_POMODORO_FINISH)
//      STimer_State = STIMER_SLP_POMODORO_FIN;
//    else
//      STimer_State = STIMER_SLP;
//
//  menuSelectedItemNum = 0;
//
//  set_date_time_state = SET_DATE_INIT;
//
//  preparing_to_sleep();
//  err_code = app_timer_stop(sleep_timer_id);
//  APP_ERROR_CHECK(err_code);
//
//  NRF_UART0->TASKS_STOPTX = 1;
//  NRF_UART0->TASKS_STOPRX = 1;
//  NRF_UART0->ENABLE = 0;
//
//  while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0) {
//    //Do nothing.
//  }
//
//  NRF_CLOCK->TASKS_HFCLKSTOP = 1;
//  NRF_POWER->TASKS_LOWPWR = 1;
//}

//static void create_timers() {
//  uint32_t err_code;
//
//  // Create timers
//  err_code = app_timer_create(&sleep_timer_id,
//      APP_TIMER_MODE_REPEATED,
//      sleep_timer_handler);
//  APP_ERROR_CHECK(err_code);
//
//  err_code = app_timer_create(&longpush_detected_timer_id,
//      APP_TIMER_MODE_REPEATED,
//      button_longpush_event_handler);
//  APP_ERROR_CHECK(err_code);
//
//  err_code = app_timer_create(&pomodoro_timer_id,
//      APP_TIMER_MODE_REPEATED,
//      pomodoro_event_handler);
//  APP_ERROR_CHECK(err_code);
//
//  err_code = app_timer_create(&main_app_timer_id,
//      APP_TIMER_MODE_REPEATED,
//      time_change_event_handler);
//  APP_ERROR_CHECK(err_code);
//}

static void lfclk_config(void) {
  NRF_CLOCK->LFCLKSRC = (CLOCK_LFCLKSRC_SRC_Xtal << CLOCK_LFCLKSRC_SRC_Pos);
  NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
  NRF_CLOCK->TASKS_LFCLKSTART = 1;
  while (NRF_CLOCK->EVENTS_LFCLKSTARTED == 0) {
    //Do nothing.
  }
}

void e_paper_initialize() {

    u8g2_nrf52_hal.clk   = SPI_SCL;
    u8g2_nrf52_hal.mosi  = SPI_MOSI;
    u8g2_nrf52_hal.cs    = EINK_CS;
    u8g2_nrf52_hal.dc    = EINK_DC;
    u8g2_nrf52_hal.reset = EINK_RES;
    u8g2_nrf52_hal.busy  = EINK_BUSY;
    
    u8g2_nrf52_hal_init(u8g2_nrf52_hal);

    u8g2_nrf52_hard_reset();

    u8g2_Setup_il3895_250x128_f(&u8g2, U8G2_R0, u8g2_nrf52_spi_byte_cb, u8g2_nrf52_gpio_and_delay_cb);
    
    nrf_delay_ms(200);
    u8g2_InitDisplay(&u8g2);
    nrf_delay_ms(1620);

    u8g2_SetPowerSave(&u8g2, 1); // wake up display
    nrf_delay_ms(200);
    u8g2_ClearBuffer(&u8g2);
    u8g2_ClearDisplay(&u8g2);
    nrf_delay_ms(1620);

    // временное решение. удалить после доступности нужного кода
    const char* currTime  = "06:47 PM";
    const char* str   = "Abyss";
    const char* strA  = "Action";
    const char* str1  = "show";
    const char* str00 = "synonyms: chasm, gorge, ravine,";
    const char* str01 = "canyon, fissure, crevasse, pit,";
    const char* str02 = "rift, hole, gulf, cavity, void,";
    const char* str03 = "bottomless pit";
    const char* strA00 = "the fact or process of doing";
    const char* strA01 = "something, typically to achieve";
    const char* strA02 = "an aim";
    const char* strA03 = "synonyms: measures, steps,";
    const char* strA04 = "activity, movement, work";
    const char* str10 = "back";
    const char* str14 = "select";
    const char* str11 = "again";
    const char* str12 = "good";
    const char* str13 = "easy";
    const char* str2  = "MENU";
    const char* str21 = "* CURRENT DECK";
    const char* str22 = "  CHANGE DECK";
    const char* str23 = "  STATISTICS";
    const char* str24 = "  SETTINGS";
    const char* str25 = "  BLUETOOTH SYNC";
    const char* str26 = "  SWITCH OFF";
    uint8_t charge = 65;
    //==========================================================

    // battery body
    u8g2_DrawFrame(&u8g2, 0, 6, 14, 8);
    u8g2_DrawBox(&u8g2, 14, 8, 2, 4);
    // charge lvl
    u8g2_DrawBox(&u8g2, 2, 8, charge / 10, 4); //(uint8_t)(charge / 10)
    // show time
    u8g2_SetFont(&u8g2, font_currTime);
    u8g2_DrawStr(&u8g2, 250 - u8g2_GetStrWidth(&u8g2, currTime), 6+7, currTime);
    // show card word
    u8g2_SetFont(&u8g2, u8g2_font_9x15_tf);
    u8g2_DrawStr(&u8g2, 125 - u8g2_GetStrWidth(&u8g2, strA)/2, 6+15 + 17, strA);
    // footer buttons
    u8g2_DrawBox(&u8g2, 0, 128-11, 250, 11);
    u8g2_SetFont(&u8g2, u8g2_font_6x10_tf);
    u8g2_SetDrawColor(&u8g2, 0);
    u8g2_DrawStr(&u8g2, 125 - u8g2_GetStrWidth(&u8g2, str1)/2, 128-1, str1);
    u8g2_SetDrawColor(&u8g2, 1);
    // send buffer + delay for blinky LUT
    u8g2_SendBuffer(&u8g2);
    nrf_delay_ms(1620);

    nrf_delay_ms(3000);

//    u8g2_ClearBuffer(&u8g2);
//    u8g2_ClearDisplay(&u8g2);
//    nrf_delay_ms(1620);

    // battery body
//    u8g2_DrawFrame(&u8g2, 0, 6, 14, 8);
//    u8g2_DrawBox(&u8g2, 14, 8, 2, 4);
//    // charge lvl
//    u8g2_DrawBox(&u8g2, 2, 8, 90 / 10, 4); //(uint8_t)(charge / 10)
//    
//    // show time
//    u8g2_SetFont(&u8g2, font_currTime);
//    u8g2_DrawStr(&u8g2, 250 - u8g2_GetStrWidth(&u8g2, currTime), 6+7, currTime);
    // show card content
    u8g2_DrawHLine(&u8g2, 0, 6+15+17 + 10, 250);
    u8g2_SetFont(&u8g2, u8g2_font_8x13_tf);
    u8g2_DrawStr(&u8g2, 2, 6+15+17+10 + 12, strA00);
    u8g2_DrawStr(&u8g2, 2, 6+15+17+10 + 12+12, strA01);
    u8g2_DrawStr(&u8g2, 2, 6+15+17+10 + 12+12+12, strA02);
    u8g2_DrawStr(&u8g2, 2, 6+15+17+10 + 12+12+12+12, strA03);
    u8g2_DrawStr(&u8g2, 2, 6+15+17+10 + 12+12+12+12+12, strA04);
    // show footer buttons
    u8g2_DrawBox(&u8g2, 0, 128-11, 250, 11);
    u8g2_SetFont(&u8g2, u8g2_font_6x10_tf);
    u8g2_SetDrawColor(&u8g2, 0);
    u8g2_DrawStr(&u8g2, 20, 128-3, str11);
    u8g2_DrawStr(&u8g2, 125 - u8g2_GetStrWidth(&u8g2, str12)/2, 128-3, str12);
    u8g2_DrawStr(&u8g2, 250-20 - u8g2_GetStrWidth(&u8g2, str13), 128-3, str13);
    u8g2_SetDrawColor(&u8g2, 1);
    // send buffer + delay for blinky LUT
    u8g2_SendBuffer(&u8g2);
    nrf_delay_ms(1620);

    nrf_delay_ms(3000);

    u8g2_ClearBuffer(&u8g2);
//    u8g2_ClearDisplay(&u8g2);
//    nrf_delay_ms(1620);
    // battery body
    u8g2_DrawFrame(&u8g2, 0, 6, 14, 8);
    u8g2_DrawBox(&u8g2, 14, 8, 2, 4);
    // charge lvl
    u8g2_DrawBox(&u8g2, 2, 8, charge / 10, 4); //(uint8_t)(charge / 10)
    // show time
    u8g2_SetFont(&u8g2, font_currTime);
    u8g2_DrawStr(&u8g2, 250 - u8g2_GetStrWidth(&u8g2, currTime), 6+7, currTime);
    u8g2_DrawStr(&u8g2, 20, 6+7, str2); // header menu navigator
    // show menu
    u8g2_SetFont(&u8g2, u8g2_font_9x15_tf);
    u8g2_DrawStr(&u8g2, 2, 6+14 + 14, str21);
    u8g2_DrawStr(&u8g2, 2, 6+14 + 14+14, str22);
    u8g2_DrawStr(&u8g2, 2, 6+14 + 14+14+14, str23);
    u8g2_DrawStr(&u8g2, 2, 6+14 + 14+14+14+14, str24);
    u8g2_DrawStr(&u8g2, 2, 6+14 + 14+14+14+14+14, str25);
    u8g2_DrawStr(&u8g2, 2, 6+14 + 14+14+14+14+14+14, str26);
    // show footer buttons
    u8g2_DrawBox(&u8g2, 0, 128-11, 250, 11);
    u8g2_SetFont(&u8g2, font_footer/*u8g2_font_6x10_tf*/);
    u8g2_SetDrawColor(&u8g2, 0);
    u8g2_DrawStr(&u8g2, 20, 128-3, str10);
    u8g2_DrawStr(&u8g2, 125 - u8g2_GetStrWidth(&u8g2, str14)/2, 128-3, str14);
    u8g2_SetDrawColor(&u8g2, 1);

    

//    u8g2_SendBuffer(&u8g2);
//    nrf_delay_ms(1620);
//    u8g2_DrawTriangle(&u8g2, 8, 34+6, 60, 34+6, 30, 50);

//    u8g2_SetFont(&u8g2, u8g2_font_wqy16_t_chinese2);
//    u8g2_DrawUTF8(&u8g2, 2,17+6,"Hi, 你好世界!");
//    u8g2_SetFont(&u8g2, u8g2_font_cu12_t_hebrew);
//    const char* hello = "העלא וועלט!";
//    u8g2_DrawExtUTF8(&u8g2, 249, 70, 1, NULL, hello);
//    u8g2_DrawBitmap(&u8g2, 25, 55, 5, 48, logo);
//    u8g2_DrawBitmap(&u8g2, 241, 7, 1, 8, arrow_up_bmp);

//    u8g2_SetDrawColor(&u8g2, 0);
//    u8g2_DrawBox(&u8g2, 126, 120, 8,8);

//    u8g2_hal_busy_wait();
    u8g2_SendBuffer(&u8g2);
     nrf_delay_ms(10620);
     u8g2_ClearDisplay(&u8g2);
}

/**
 * @brief Function for application main entry.
 */
int main(void) {

  nrf_gpio_cfg_output(LED_PIN);
  nrf_gpio_cfg_output(DC_ON);
  nrf_gpio_cfg_output(VIBRO_PIN);
  nrf_gpio_pin_set(DC_ON);

  //STimer_State = STIMER_INITIAL_STATE;
  uint32_t err_code = NRF_SUCCESS;

//  nrf_gpio_cfg_output(INPUT_VOLTAGE_PIN);
//  nrf_gpio_pin_set(INPUT_VOLTAGE_PIN);

  lfclk_config();

//  err_code = app_timer_init();
//  APP_ERROR_CHECK(err_code);


  NRF_POWER->RESETREAS = 1;

//  application_init();
//  enableButtons(false);

//  nrf_cal_init();
//  nrf_cal_set_time(2018, 5, 8, 15, 25, 0);
//  nrf_cal_set_callback(calendar_updated, 60);
//  calendar_updated();

//  battery_voltage_get(&battery_voltage);
nrf_gpio_pin_clear(LED_PIN);
//nrf_gpio_pin_set(VIBRO_PIN);
//    nrf_delay_ms(1000);
//    nrf_gpio_pin_clear(VIBRO_PIN);
//buzzer(BUZZER_PIN, soundLogo);
nrf_gpio_pin_set(LED_PIN);

  e_paper_initialize();
  //ssd1306_clear_display();
nrf_gpio_pin_clear(LED_PIN);
//buzzer(BUZZER_PIN, soundLogo);
nrf_gpio_pin_set(LED_PIN);
//  create_timers();
//
//  logoScreen();
  //buzzer(BUZZER_PIN, soundLogo);

//  enableButtons(true);
//
//  err_code = app_timer_start(main_app_timer_id,APP_TIMER_TICKS(60000),NULL);
//  APP_ERROR_CHECK(err_code);
//
//  timerBaseCreate();
//
//  stimer_states();
nrf_gpio_pin_clear(LED_PIN);
//buzzer(BUZZER_PIN, soundLogo);
nrf_gpio_pin_set(LED_PIN);
  while (true) {
    sd_app_evt_wait();
  }
}