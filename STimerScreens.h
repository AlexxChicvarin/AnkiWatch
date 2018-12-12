#ifndef __STIMER_SCREENS_H
#define __STIMER_SCREENS_H

#include "STimerLanguage.h"
#include "STimerInterface.h"
#include "STimerTimerBase.h"

//===== MENU ITEM SELECTOR SECTION START ======
#define MAX_SHOWN_STRINGS       3
uint8_t menuSelectedItemNum   = 0;
uint8_t currentMenuItemsCount = 0;
//===== MENU ITEM SELECTOR SECTION END ========

//===== TIMER BASE SECTION START =====
uint8_t selectedTimer	    = 0;
uint8_t selectedMotivation  = 0;
int8_t selectedLetter       = 0;
uint8_t newTimerNameLenght  = 0;
uint8_t newMotivationLength = 0;
char* newTimerName;
char newMotivation[MAX_MOTIVATION_LENGTH];
//===== TIMER BASE SECTION END =======

void logoScreen() {
  ssd1306_clear_display();
  ssd1306_draw_bitmap(44, 0, logo, 40, 48, WHITE);
  ssd1306_display();
}


void startScreen(char* curTime, char* curDay, char* curMonth, char* curYear) {
  ssd1306_clear_display();
  battery(battery_level);
  ssd1306_set_font(&FreeSerif9pt7b);
  ssd1306_set_textcolor(WHITE);
  ssd1306_set_cursor(0, 16);
  ssd1306_set_textsize(3);
  ssd1306_puts(curTime);
  ssd1306_set_textsize(2);
  ssd1306_set_cursor(0, 48);
  ssd1306_puts(curDay);
  ssd1306_set_cursor(33, 48);
  ssd1306_puts(curMonth);
  ssd1306_set_cursor(78, 48);
  ssd1306_puts(curYear);
  ssd1306_display();
  ssd1306_set_font(NULL);
}

void timerScreen(uint8_t currShownTimer, uint8_t actTimersCount) {
    ssd1306_clear_display();
    battery(battery_level);
    if (actTimersCount == 0) {
        ssd1306_set_textsize(1);
        ssd1306_set_textcolor(WHITE);
        ssd1306_set_cursor(0, 0);
        ssd1306_putstring("0/0");
        ssd1306_draw_bitmap(44, 0, logo, 40, 48, WHITE);
        buttonMenu();
    } else {
        timerNumber(currShownTimer+1, actTimersCount);
        ssd1306_set_cursor(0, 17);
        ssd1306_set_textsize(1);
	
        ssd1306_puts(timerBaseGetTimerName(activeTimers[currShownTimer]));
        ssd1306_set_cursor(0, 30);
        ssd1306_puts(timerBaseGetTimerTime(activeTimers[currShownTimer], 1));
        ssd1306_set_cursor(0, 40);
        ssd1306_puts(timerBaseGetTimerTime(activeTimers[currShownTimer], 2));
        ssd1306_puts(timerBaseGetTimerTime(activeTimers[currShownTimer], 3));
        buttonMotivation();
        buttonMenuReset();
    }
    ssd1306_display();
}

void timerResetScreen() {
  ssd1306_clear_display();
  ssd1306_set_textcolor(WHITE);
  ssd1306_set_cursor(0, 8);
  ssd1306_puts("Are you shure want to reset this timer?");
  QuestionButtons(tQuestionReset);
  buttonNoLeft();
  buttonYesRight();
  ssd1306_display();
}

//small helper
char* stringAtNum(char* string, uint8_t strNLC, uint8_t num)
{
  static char result[19];
  uint8_t s = 0;
  uint8_t r = 0;

  for(uint8_t n = 0; n < strNLC; n++)
  {
    for(uint8_t i = 0; i < 19; i++)
    {
      if(string[s] == '\n' || string[s] == '\0')
      {
	s++;
        break;
      }
      result[r++] = string[s];
      s++;
    }
    if(n != num)
    {
      for(uint8_t j = 0; j < 19; j++)
	result[j] = ' ';
      r = 0;
    }
    else
      break;
  }
  result[r] = '\0';
  
  return result;
}

void timerMotivationScreen(bool fromMenu, int selectedScreen, bool confDel) {
  ssd1306_clear_display();
  if(fromMenu) menuStrip();
  battery(battery_level);
  arrows();
  
  char t[3], title[22];
  strcpy(title, tMenuStripMotivation);
  strcat(title, " ");
  itoa(selectedMotivation+1, t, 10);
  strcat(title, t);
  if(fromMenu) menuString(title);
  char* motiv = timerBaseGetMotivation(fromMenu ? selectedTimer : activeTimers[currentShownTimer], selectedMotivation);

  int count_of_strings = timerBaseGetTimerMotivationsNLC(fromMenu ? selectedTimer : activeTimers[currentShownTimer], selectedMotivation);
  currentMenuItemsCount = count_of_strings;
  int displaedNum = (count_of_strings > (selectedScreen+1)*MAX_SHOWN_STRINGS) ? (selectedScreen+1)*MAX_SHOWN_STRINGS : count_of_strings;
  for(int i = selectedScreen*MAX_SHOWN_STRINGS; i < displaedNum; i++)
      menuItem(stringAtNum(motiv, count_of_strings, i), i - selectedScreen*MAX_SHOWN_STRINGS+1, false);
  if (count_of_strings > (selectedScreen+1)*MAX_SHOWN_STRINGS) 
      menuContinued();

  if(!confDel)
  {
    buttonBack();
    fromMenu ? buttonDelete() : buttonAnother();
  }
  else
  {
    QuestionButtons(tQuestionDelete);
    buttonYesLeft();
    buttonNoRight();
  }
  ssd1306_display();
}

void menuScreen(uint8_t selectedItemNum, uint8_t menuItemsCount) {
    ssd1306_clear_display();
    menuStrip();
    battery(battery_level);
    arrows();
    for(uint8_t i=0; i < menuItemsCount; i++)
        menuItem(tMenuMainItems[i], i, (selectedItemNum == i));// ? true : false
//  menuContinued();
    buttonBack();
    buttonChoose();
    ssd1306_display();
}

void menuTimerMenuScreen(uint8_t selectedTimer, uint8_t selectedItemNum, uint8_t menuItemsCount)
{
    ssd1306_clear_display();
    menuStrip();
    battery(battery_level);
    arrows();
    menuString(timerBaseGetTimerName(selectedTimer));
    if (selectedItemNum < MAX_SHOWN_STRINGS)
    {
        for(int i=0; i<MAX_SHOWN_STRINGS; i++)
            menuItem(tMenuAddTimerItems[i], i+1, (selectedItemNum == i));// ? true : false
        menuContinued();
    }
    else
    {
        menuItem(tMenuAddTimerItems[3], 1, (selectedItemNum == 3));// ? true : false
    }
    buttonBack();
    buttonChoose();
    ssd1306_display();
}

void menuMotivMenuScreen(uint8_t selectedTimer, uint8_t selectedItemNum, uint8_t menuItemsCount)
{
    ssd1306_clear_display();
    menuStrip();
    battery(battery_level);
    arrows();
    char title[22];
    strncpy(title, timerBaseGetTimerName(selectedTimer), 10);
    strcat(title, "/");
    strcat(title, tMenuStripMotivation);
    menuString(title);
    for(uint8_t i = 0; i < menuItemsCount; i++)
        menuItem(tMenuMotivationItems[i], i+1, (selectedItemNum == i));// ? true : false
    buttonBack();
    buttonChoose();
    ssd1306_display();
}

void menuTimersListScreen(uint8_t selectedItemNum, uint8_t menuItemsCount) {
    ssd1306_clear_display();
    menuStrip();
    battery(battery_level);
    arrows();
    menuString(tMenuStripTimerList);
    int count_of_timers = menuItemsCount;
    int screenNum = (int)(selectedItemNum / MAX_SHOWN_STRINGS);
    int displaedNum = (count_of_timers > (screenNum+1)*MAX_SHOWN_STRINGS) ? (screenNum+1)*MAX_SHOWN_STRINGS : count_of_timers;
    for(int i = screenNum*MAX_SHOWN_STRINGS; i < displaedNum; i++)
        menuItem( timerBaseGetTimerName(i), i - screenNum*MAX_SHOWN_STRINGS+1, (selectedItemNum == i));// ? true : false
    if (count_of_timers > (screenNum+1)*MAX_SHOWN_STRINGS) 
        menuContinued();
    buttonBack();
    buttonChoose();
    ssd1306_display();
}

void menuMotivationsListScreen(uint8_t selectedItemNum, uint8_t menuItemsCount) {
    ssd1306_clear_display();
    menuStrip();
    battery(battery_level);
    arrows();
    char title[22];
    strcpy(title, tMenuStripMotivation);
    strcat(title, "/");
    strcat(title, strViewDel);
    menuString(title);
    char t[3], str1[14];
    int count_of_motivations = menuItemsCount;
    int screenNum = (int)(selectedItemNum / MAX_SHOWN_STRINGS);
    int displaedNum = (count_of_motivations > (screenNum+1)*MAX_SHOWN_STRINGS) ? (screenNum+1)*MAX_SHOWN_STRINGS : count_of_motivations;
    for(int i = screenNum*MAX_SHOWN_STRINGS; i < displaedNum; i++)
    {
	itoa(i+1,t,10);
	strcpy(str1,tMotivation); strcat(str1," "); strcat(str1,t);
        menuItem( str1 , i - screenNum*MAX_SHOWN_STRINGS+1, (selectedItemNum == i));// ? true : false
    }
    if (count_of_motivations > (screenNum+1)*MAX_SHOWN_STRINGS) 
        menuContinued();
    buttonBack();
    buttonChoose();
    ssd1306_display();
}

void menuTimerActivateScreen(int selectedItemNum) {
    ssd1306_clear_display();
    menuStrip();
    battery(battery_level);
    menuString(tMenuStripAddTimer);
    ssd1306_set_cursor(16, 28);
    ssd1306_puts(timerBaseGetTimerName(selectedItemNum));
    QuestionButtons(tQuestionAdd);
    buttonYesLeft();
    buttonNoRight();
    ssd1306_display();
}

void menuAddNewTimerScreen(int selectedLetter, uint8_t stringLenght, uint8_t selectedTimer) {
    ssd1306_clear_display();
    menuStrip();
    battery(battery_level);
    arrows();
    char t[3], title[22];
    strcpy(title, tMenuStripTimerList);
    strcat(title, "/");
    if(timerBaseIsTimer(selectedTimer))
      strncat(title, timerBaseGetTimerName(selectedTimer), 9);
    else
    {
      strcat(title, tDefaultTimerName);
      itoa(selectedTimer+1, t, 10);
      strcat(title, t);
    }
      strcat(title, "/");
    strcat(title, tMenuStripAddTimerName);
    menuString(title);
    ssd1306_set_cursor(0, 32);
    ssd1306_set_textsize(1);
    ssd1306_set_textcolor(WHITE);
    ssd1306_putstring(newTimerName);
    ssd1306_set_textcolor_bg(BLACK, WHITE);
    ssd1306_set_cursor((stringLenght-1)*6, 32);
    switch(currLang_id) {
      case 0:
        ssd1306_puts(letters_eng[selectedLetter]);
        break;
      case 1:
        ssd1306_puts(letters_esp[selectedLetter]);
        break;
      case 2:
        ssd1306_puts(letters_fra[selectedLetter]);
        break;
      default:
        ssd1306_puts(letters_eng[selectedLetter]);
        break;      
    }
    ssd1306_set_textcolor(WHITE);
    ssd1306_draw_line(0, 42, 108, 42, WHITE); 
    ssd1306_draw_line(0, 43, 108, 43, WHITE); 
    ssd1306_set_textsize(1);
    buttonBackSave();
    buttonNextBackspace();
    ssd1306_display();
}

void menuAddNewMotivationScreen(int selectedLetter, uint8_t stringLenght, uint8_t selectedTimer) {
    ssd1306_clear_display();
    menuStrip();
    battery(battery_level);
    arrows();
    char t[3], title[22];
    strcpy(title, tMenuStripMotivation);
    strcat(title, "/");
    strcat(title, strAdd);
    strcat(title, "/");
    itoa(timerBaseGetTimerMotivationsNum(selectedTimer)+1, t, 10);
    strcat(title, t);
    menuString(title);
    ssd1306_set_textcolor(WHITE);
    ssd1306_set_cursor(1,18);
    for(uint8_t i = (stringLenght>72 ? 73 : 1); i < stringLenght; i++)
    {
      if(i % 18 == 1)
	ssd1306_set_cursor(1, 18 + ( ((i<=72) ? i : i-72) / 18)*8);
      ssd1306_write(newMotivation[i-1]);
    }
    ssd1306_set_textcolor_bg(BLACK, WHITE);
    switch(currLang_id) {
      case 0:
        ssd1306_puts(letters_eng[selectedLetter]);
        break;
      case 1:
        ssd1306_puts(letters_esp[selectedLetter]);
        break;
      case 2:
        ssd1306_puts(letters_fra[selectedLetter]);
        break;
      default:
        ssd1306_puts(letters_eng[selectedLetter]);
        break;      
    }
    ssd1306_set_textcolor(WHITE);
    buttonBackSave();
    buttonNextBackspace();
    ssd1306_display();
}

void menuDeleteTimerScreen(int selectedTimer) {
    ssd1306_clear_display();
    menuStrip();
    battery(battery_level);
    menuString(tMenuStripDeleteTimer);
    ssd1306_set_cursor(16, 28);
    ssd1306_puts( timerBaseGetTimerName(selectedTimer)  /*timerBase[selectedItemNum].timerName*/);
    QuestionButtons(tQuestionDelete);
    buttonYesLeft();
    buttonNoRight();
    ssd1306_display();
}

void scrPomodoroConfirmStart() {
  ssd1306_clear_display();
  menuStrip();
  battery(battery_level);
  menuString(tMenuStripPomodoro);
  ssd1306_draw_bitmap(53, 17, pomodoro_bmp, 32, 32, WHITE);
  QuestionButtons(tQuestionStartP);
  buttonYesLeft();
  buttonNoRight();
  ssd1306_display();
}

void scrPomodoroAnimation() {
  ssd1306_clear_display();
  menuStrip();
  battery(battery_level);
  menuString(tMenuStripPomodoro);
  ssd1306_draw_bitmap(53, 17, pomodoro_bmp, 32, 32, WHITE);
  ssd1306_display();
  for (uint8_t dx = 0; dx < 48;  dx += 3) {
    ssd1306_draw_bitmap(53 - dx, 17, pomodoro_bmp, 32, 32, BLACK);
    ssd1306_draw_bitmap(53 - dx - 3, 17, pomodoro_bmp, 32, 32, WHITE);
    ssd1306_display();
  }
}

void scrPomodoroMain(bool inMainActivity) {
  ssd1306_clear_display();
  menuStrip();
  battery(battery_level);
  menuString(tMenuStripPomodoro);
  ssd1306_draw_bitmap(5, 17, pomodoro_bmp, 32, 32, WHITE);
  ssd1306_set_textsize(3);
  ssd1306_set_cursor(46, 23);
  char pomodoroTimeC[3];
  itoa(pomodoroShownTime, pomodoroTimeC, 10);
  ssd1306_putstring(pomodoroTimeC);
  ssd1306_set_textsize(1);
  ssd1306_set_cursor(85, 23);
  ssd1306_puts(tMinutes);
  ssd1306_set_cursor(85, 37);
  ssd1306_puts(tLeft);
  if(inMainActivity)
  {
    buttonBack();
    (pomodoroInPause) ? buttonResume() : buttonPause();
  }
  else
  {
    QuestionButtons(tQuestionBack);
    buttonNoLeft();
    buttonYesRight();
  }
  ssd1306_display();
}

void scrPomodoroFinish() {
  ssd1306_clear_display();
  menuStrip();
  battery(battery_level);
  menuString(tMenuStripPomodoro);
  ssd1306_draw_bitmap(5, 17, pomodoro_bmp, 32, 32, WHITE);
  ssd1306_set_textsize(3);
  ssd1306_set_cursor(46, 23);
  char pomodoroTimeC[3];
  itoa(pomodoroShownTime, pomodoroTimeC, 10);
  ssd1306_putstring(pomodoroTimeC);
  ssd1306_set_textsize(1);
  ssd1306_set_cursor(85, 23);
  ssd1306_puts(tMinutes);
  ssd1306_set_cursor(85, 37);
  ssd1306_puts(tLeft);
  buttonBack();
  ssd1306_display();
}

void menuSettingsScreen(int selectedItemNum, uint8_t menuItemsCount) {
    ssd1306_clear_display();
    menuStrip();
    battery(battery_level);
    arrows();
    menuString(tMenuStripSettings);
    if (selectedItemNum < MAX_SHOWN_STRINGS)
    {
        for(int i=0; i<MAX_SHOWN_STRINGS; i++)
            menuItem(tMenuSettingsItems[i], i+1, (selectedItemNum == i));// ? true : false
        menuContinued();
    }
    else
    {
        menuItem(tMenuSettingsItems[3], 1, (selectedItemNum == 3));// ? true : false
        menuItem(tMenuSettingsItems[4], 2, (selectedItemNum == 4));// ? true : false
    }
    buttonBack();
    buttonChoose();
    ssd1306_display();
}


void menuSettingsTimeScreen(int sel, int hour, int min, int ampm) {
    char hourC[3], minC[3];
    itoa(min, minC, 10);
    itoa(hour, hourC, 10);
  
    ssd1306_clear_display();
    menuStrip();
    battery(battery_level);
    arrows();
    menuString(tMenuStripSetTime);
    ssd1306_set_textcolor(WHITE);
    ssd1306_set_textsize(2);

    // Hour input section
    if (sel == 1) ssd1306_set_textcolor_bg(BLACK, WHITE);
    if (hour < 10)
        ssd1306_set_cursor(20, 22);
    else
        ssd1306_set_cursor(13, 22);
    ssd1306_puts(hourC);
    ssd1306_draw_line(8, 42, 33, 42, WHITE);
    ssd1306_draw_line(8, 43, 33, 43, WHITE);
    ssd1306_set_textcolor(WHITE);

    // Minutes input section
    if (sel == 2) ssd1306_set_textcolor_bg(BLACK, WHITE);
    if (min < 10)
       ssd1306_set_cursor(55, 22);
    else
       ssd1306_set_cursor(45, 22);
    ssd1306_puts(minC);
    ssd1306_draw_line(43, 42, 68, 42, WHITE);
    ssd1306_draw_line(43, 43, 68, 43, WHITE);
    ssd1306_set_textcolor(WHITE);

    // AM/PM input section
    if (sel == 3) ssd1306_set_textcolor_bg(BLACK, WHITE);
    ssd1306_set_cursor(80, 22);
    if (ampm == 0)
        ssd1306_puts("AM");
    else
        ssd1306_puts("PM");
    ssd1306_draw_line(78, 42, 103, 42, WHITE);
    ssd1306_draw_line(78, 43, 103, 43, WHITE);
    ssd1306_set_textcolor(WHITE);

    ssd1306_set_textsize(1);
    buttonBack();
    buttonNext();
    ssd1306_display();
}

void menuSettingsDateScreen(int sel, int day, int month, int year) {
    char dayC[3], yearC[5];
    itoa(day, dayC, 10);
    itoa(year, yearC, 10);

    ssd1306_clear_display();
    menuStrip();
    battery(battery_level);
    arrows();
    menuString(tMenuStripSetDate);
    ssd1306_set_textcolor(WHITE);
    ssd1306_set_textsize(2);

    // Day input section
    if (sel == 4) ssd1306_set_textcolor_bg(BLACK, WHITE);
    if (day < 10)
        ssd1306_set_cursor(10, 22);
    else
        ssd1306_set_cursor(00, 22);
    ssd1306_puts(dayC);
    ssd1306_draw_line(0, 42, 23, 42, WHITE);
    ssd1306_draw_line(0, 43, 23, 43, WHITE);
    ssd1306_set_textcolor(WHITE);

    // Month input section
    if (sel == 5) ssd1306_set_textcolor_bg(BLACK, WHITE);
    ssd1306_set_cursor(30, 22);
    ssd1306_puts(listMonth[month]);
    ssd1306_draw_line(28, 42, 65, 42, WHITE);
    ssd1306_draw_line(28, 43, 65, 43, WHITE);
    ssd1306_set_textcolor(WHITE);

    // Year input section
    if (sel == 6) ssd1306_set_textcolor_bg(BLACK, WHITE);
    ssd1306_set_cursor(70, 22);
    ssd1306_puts(yearC);
    ssd1306_draw_line(70, 42, 116, 42, WHITE);
    ssd1306_draw_line(70, 43, 116, 43, WHITE);
    ssd1306_set_textcolor(WHITE);

    ssd1306_set_textsize(1);
    buttonBack();
    if(sel == 6)
      buttonSave();
    else
      buttonNext();
    ssd1306_display();
}

void menuSettingsLastUpdScreen() {
  ssd1306_clear_display();
  menuStrip();
  battery(battery_level);
  menuString(tMenuStripUpdate);
  ssd1306_set_cursor(31, 24);
  ssd1306_puts(last_upd[0]);
  ssd1306_set_cursor(35, 36);
  ssd1306_puts(last_upd[1]);
  buttonBack();
  ssd1306_display();
}

void menuSettingsLanguage(uint8_t selectedItemNum, uint8_t menuItemsCount) {
    ssd1306_clear_display();
    menuStrip();
    battery(battery_level);
    arrows();
    menuString(tMenuStripLanguage);
    for(uint8_t i = 0; i < menuItemsCount; i++)
        menuItem(tMenuLanguageItems[i], i+1, (selectedItemNum == i));// ? true : false
    selectedLang_id = selectedItemNum;
    buttonBack();
    buttonChoose();
    ssd1306_display();
}


void menuSettingsLanguageSelect(int selectedItemNum) {
  ssd1306_clear_display();
  menuStrip();
  battery(battery_level);
  menuString(tMenuStripLanguage);
  ssd1306_set_cursor(10, 24);
  ssd1306_puts(tQuestionChLang);
  ssd1306_set_cursor(38, 38);
  ssd1306_putstring(tMenuItemQLang[selectedItemNum]);
  ssd1306_puts("?");
  buttonNoLeft();
  buttonYesRight();
  ssd1306_display();
}

void menuSettingsReset() {
  ssd1306_clear_display();
  menuStrip();
  battery(battery_level);
  menuString(tMenuStripReset);
  ssd1306_set_cursor(0, 24);
  ssd1306_puts("        RESET");
  ssd1306_set_cursor(0, 38);
  ssd1306_puts("     THE DEVICE?");
  buttonNoLeft();
  buttonYesRight();
  ssd1306_display();
}

void menuSettingsBrightness(int level) {
  ssd1306_clear_display();
  menuStrip();
  battery(battery_level);
  arrows();
  menuString(tMenuStripBrightness);
  switch (level) {
    case 6:
      ssd1306_fill_rect(85, 20, 8, 28, WHITE);
      ssd1306_fill_rect(75, 24, 8, 24, WHITE);
      ssd1306_fill_rect(65, 28, 8, 20, WHITE);
      ssd1306_fill_rect(55, 32, 8, 16, WHITE);
      ssd1306_fill_rect(45, 36, 8, 12, WHITE);
      ssd1306_fill_rect(35, 40, 8,  8, WHITE);
      ssd1306_fill_rect(25, 44, 8,  4, WHITE);
      ssd1306_contrast(255);
      break;
    case 5:
      ssd1306_fill_rect(75, 24, 8, 24, WHITE);
      ssd1306_fill_rect(65, 28, 8, 20, WHITE);
      ssd1306_fill_rect(55, 32, 8, 16, WHITE);
      ssd1306_fill_rect(45, 36, 8, 12, WHITE);
      ssd1306_fill_rect(35, 40, 8,  8, WHITE);
      ssd1306_fill_rect(25, 44, 8,  4, WHITE);
      ssd1306_contrast(210);
      break;
    case 4:
      ssd1306_fill_rect(65, 28, 8, 20, WHITE);
      ssd1306_fill_rect(55, 32, 8, 16, WHITE);
      ssd1306_fill_rect(45, 36, 8, 12, WHITE);
      ssd1306_fill_rect(35, 40, 8,  8, WHITE);
      ssd1306_fill_rect(25, 44, 8,  4, WHITE);
      ssd1306_contrast(170);
      break;
    case 3:
      ssd1306_fill_rect(55, 32, 8, 16, WHITE);
      ssd1306_fill_rect(45, 36, 8, 12, WHITE);
      ssd1306_fill_rect(35, 40, 8,  8, WHITE);
      ssd1306_fill_rect(25, 44, 8,  4, WHITE);
      ssd1306_contrast(130);
      break;
    case 2:
      ssd1306_fill_rect(45, 36, 8, 12, WHITE);
      ssd1306_fill_rect(35, 40, 8,  8, WHITE);
      ssd1306_fill_rect(25, 44, 8,  4, WHITE);
      ssd1306_contrast(80);
      break;
    case 1:
      ssd1306_fill_rect(35, 40, 8,  8, WHITE);
      ssd1306_fill_rect(25, 44, 8,  4, WHITE);
      ssd1306_contrast(40);
      break;
    case 0:
      ssd1306_fill_rect(25, 44, 8,  4, WHITE);
      ssd1306_contrast(0);
      break;
  }
  buttonNoLeft();
  buttonYesRight();
  ssd1306_display();
}

#endif
