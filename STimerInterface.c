#include <stdlib.h>

#include "ssd1306.h"
#include "STimerInterface.h"
//#include "STimerLanguage.h"
#include "STimerImages.h"


void timeStrip() {
  ssd1306_set_cursor(45, 0);
  ssd1306_puts("02:30PM");
}

void timerNumber(int timerNum, int timerTotal) {
  char* timerNumC;
  char* timerTotalC;
  ssd1306_set_textsize(1);
  ssd1306_set_textcolor(WHITE);
  ssd1306_set_cursor(0, 0);
  itoa(timerNum, timerNumC, 10);
  ssd1306_putstring(timerNumC);
  ssd1306_putstring("/");
  itoa(timerTotal, timerTotalC, 10);
  ssd1306_putstring(timerTotalC);
  timeStrip();
}

void menuStrip() {
  ssd1306_set_textsize(1);
  ssd1306_set_textcolor(WHITE);
  ssd1306_set_cursor(0, 0);
  ssd1306_putstring(tMenu);
  timeStrip();
}

void arrows() {
  ssd1306_draw_bitmap(118, 18, arrow_up_bmp, 8, 8, WHITE);
  ssd1306_draw_bitmap(118, 40, arrow_down_bmp, 8, 8, WHITE);
}

void battery(int charge) {
  switch (charge) {
    case 0:
      ssd1306_draw_bitmap(103, 0, battery0_bmp, 24, 7, WHITE);
      break;
    case 1:
      ssd1306_draw_bitmap(103, 0, battery1_bmp, 24, 7, WHITE);
      break;
    case 2:
      ssd1306_draw_bitmap(103, 0, battery2_bmp, 24, 7, WHITE);
      break;
    case 3:
      ssd1306_draw_bitmap(103, 0, battery3_bmp, 24, 7, WHITE);
      break;
    case 4:
      ssd1306_draw_bitmap(103, 0, battery4_bmp, 24, 7, WHITE);
      break;
    case 5:
      ssd1306_draw_bitmap(103, 0, battery5_bmp, 24, 7, WHITE);
      break;
  }
}

void menuString(char* menu) {
  ssd1306_set_cursor(1, 9);
  ssd1306_set_textcolor(BLACK);
  ssd1306_fill_rect(0, 8, 128, 9, WHITE);
  ssd1306_puts(menu);
  ssd1306_set_textcolor(WHITE);
}

void menuItem(char* itemName, int itemNumber, int isSelected) {
  ssd1306_set_cursor(1, 9 + itemNumber * 10);
  if (isSelected == 1) {
    ssd1306_set_textcolor(BLACK);
    ssd1306_fill_rect(0, 8 + itemNumber * 10, 116, 9, WHITE);
  }
  else {
    ssd1306_set_textcolor(WHITE);
    ssd1306_fill_rect(0, 8 + itemNumber * 10, 116, 9, BLACK);
  }
  ssd1306_puts(itemName);
  ssd1306_set_textcolor(WHITE);
}

void menuContinued() {
  ssd1306_set_cursor(0, 44);
  ssd1306_puts("    ...");
}

void QuestionButtons(char* tQuestion) {
//  int xpos = (128 - 5 * tQuestion.length())/2 - 2;
  int xpos = (128 - 5 * sizeof(tQuestion))/2 - 2;
  
  ssd1306_set_cursor(xpos, 52);
  ssd1306_puts(tQuestion);
}

void buttonAnother() {
  ssd1306_fill_rect(83, 55, 45, 9, WHITE);
  ssd1306_set_textcolor(BLACK);
  ssd1306_set_cursor(85, 56);
  ssd1306_puts(tBbuttonAnother);
  ssd1306_set_textcolor(WHITE);
}

void buttonMenuReset() {
  ssd1306_fill_rect(0, 55, 45, 9, WHITE);
  ssd1306_set_textcolor(BLACK);
  ssd1306_set_cursor(2, 56);
  ssd1306_puts(tButtonMenuReset);
  ssd1306_set_textcolor(WHITE);
}

void buttonBack() {
  ssd1306_fill_rect(0, 55, 45, 9, WHITE);
  ssd1306_set_textcolor(BLACK);
  ssd1306_set_cursor(11, 56);
  ssd1306_puts(tButtonBack);
  ssd1306_set_textcolor(WHITE);
}

void buttonYesRight() {
  ssd1306_fill_rect(101, 55, 27, 9, WHITE);
  ssd1306_set_textcolor(BLACK);
  ssd1306_set_cursor(106, 56);
  ssd1306_puts(tButtonYes);
  ssd1306_set_textcolor(WHITE);
}

void buttonYesLeft() {
  ssd1306_fill_rect(0, 55, 27, 9, WHITE);
  ssd1306_set_textcolor(BLACK);
  ssd1306_set_cursor(5, 56);
  ssd1306_puts(tButtonYes);
  ssd1306_set_textcolor(WHITE);
}

void buttonNoRight() {
  ssd1306_fill_rect(101, 55, 27, 9, WHITE);
  ssd1306_set_textcolor(BLACK);
  ssd1306_set_cursor(109, 56);
  ssd1306_puts(tButtonNo);
  ssd1306_set_textcolor(WHITE);
}

void buttonNoLeft() {
  ssd1306_fill_rect(0, 55, 27, 9, WHITE);
  ssd1306_set_textcolor(BLACK);
  ssd1306_set_cursor(8, 56);
  ssd1306_puts(tButtonNo);
  ssd1306_set_textcolor(WHITE);
}

void buttonNextSave() {
  ssd1306_fill_rect(71, 55, 57, 9, WHITE);
  ssd1306_set_textcolor(BLACK);
  ssd1306_set_cursor(73, 56);
  ssd1306_puts(tButtonNextSave);
  ssd1306_set_textcolor(WHITE);
}

void buttonChoose() {
  ssd1306_fill_rect(83, 55, 45, 9, WHITE);
  ssd1306_set_textcolor(BLACK);
  ssd1306_set_cursor(88, 56);
  ssd1306_puts(tButtonChoose);
  ssd1306_set_textcolor(WHITE);
}

void buttonRecord() {
  ssd1306_fill_rect(83, 55, 45, 9, WHITE);
  ssd1306_set_textcolor(BLACK);
  ssd1306_set_cursor(88, 56);
  ssd1306_puts(tButtonRecord);
  ssd1306_set_textcolor(WHITE);
}

void buttonPause() {
  ssd1306_fill_rect(83, 55, 45, 9, WHITE);
  ssd1306_set_textcolor(BLACK);
  ssd1306_set_cursor(92, 56);
  ssd1306_puts(tButtonPause);
  ssd1306_set_textcolor(WHITE);
}