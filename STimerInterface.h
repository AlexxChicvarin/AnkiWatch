#ifndef __STIMER_INTERFACE_H
#define __STIMER_INTERFACE_H

#include "u8g2.h"
#include "AnkiUsedFonts.h"
#include <stdint.h>
#include "string.h"

char* menu_header_string = "";
#define STR_POS_LEFT   0
#define STR_SET_RIGHT  1
#define STR_SET_CENTER 2

#define pos_leftBtn   20
#define pos_centerBtn 125
#define pos_rightBtn  30  // реально кнопка тут: 250 - pos_rightBtn

uint8_t comp_x_pos(uint8_t dir, uint8_t base_x, const char* str)
{
  uint8_t result_x;

  switch(dir) {
    case STR_POS_LEFT:
      result_x = base_x;
      break;
    case STR_SET_RIGHT:
      result_x = base_x - u8g2_GetStrWidth(&u8g2, str);
      break;
    case STR_SET_CENTER:
      result_x = 250 - base_x - u8g2_GetStrWidth(&u8g2, str)/2;
      break;
    default:
      result_x = 0;
      break;
  }

  return result_x;
}

// отображалка времени
void timeStrip(const char* currTime)
{
    u8g2_SetFont(&u8g2, font_currTime);
    u8g2_DrawStr(&u8g2, comp_x_pos(STR_SET_RIGHT, 0, currTime), 6+7, currTime); //250 - u8g2_GetStrWidth(&u8g2, currTime)
}

// отображалка заряда батареи
void battery(const uint8_t charge) {
    // battery body
    u8g2_DrawFrame(&u8g2, 0, 6, 14, 8);
    u8g2_DrawBox(&u8g2, 14, 8, 2, 4);
    // charge lvl
    u8g2_DrawBox(&u8g2, 2, 8, charge / 10, 4);
}

// отображалка текущей позиции в меню
// TODO: больше логики! не хочу пересобирать постоянно эту строку в скринах. можно проще
// можно тут это всё делать
void menuNavigator(const char* str)
{
    if(strcmp(str,""))
    {
      strcat(menu_header_string, "\\");
      strcat(menu_header_string, str);
    }
    else
      strcpy(menu_header_string, str);
    
    u8g2_SetFont(&u8g2, font_header);
    u8g2_DrawStr(&u8g2, 20, 6+7, menu_header_string);
}

// верхняя часть экрана. батарея, время, позиция в меню
void screen_header(const uint8_t charge, const char* currTime, const char* menuCurrDir)
{
    battery(charge);
    menuNavigator(menuCurrDir);
    timeStrip(currTime);
}

// нижняя часть экрана. кнопки
// TODO: найти позицию середины кнопок для более адекватного расположения
// TODO: подумать над нормальной передачей
void screen_footer(const char* leftBtn, const char* centerBtn, const char* rightBtn)
{
    u8g2_DrawBox(&u8g2, 0, 128-11, 250, 11); // TODO: не 11 а font_height+2. Найти как!!!!!!
    u8g2_SetFont(&u8g2, font_footer);
    u8g2_SetDrawColor(&u8g2, 0);
    // BaseLine этого фонта хз где, поэтому 128-3
    // TODO: как-то привязаться к BaseLine  фонта
    // strcmp = 0 если str1 = str2
    // TODO: strlen() != 0 ?????????? strchr(str1, '\0') != 0 ???????? 
    if(strcmp(leftBtn,""))   u8g2_DrawStr(&u8g2, comp_x_pos(STR_POS_LEFT,   pos_leftBtn,   leftBtn),   128-3, leftBtn);
    if(strcmp(centerBtn,"")) u8g2_DrawStr(&u8g2, comp_x_pos(STR_SET_CENTER, pos_centerBtn, centerBtn), 128-3, centerBtn); //125 - u8g2_GetStrWidth(&u8g2, centerBtn)/2
    if(strcmp(rightBtn,""))  u8g2_DrawStr(&u8g2, comp_x_pos(STR_SET_RIGHT,  pos_rightBtn,  rightBtn),  128-3, rightBtn); //250-20 - u8g2_GetStrWidth(&u8g2, rightBtn)
    u8g2_SetDrawColor(&u8g2, 1);
}

//void timerNumber(int timerNum, int timerTotal) {
//  char timerNumC[3];
//  char timerTotalC[3];
//  ssd1306_set_textsize(1);
//  ssd1306_set_textcolor(WHITE);
//  ssd1306_set_cursor(0, 0);
//  itoa(timerNum, timerNumC, 10);
//  ssd1306_putstring(timerNumC);
//  ssd1306_putstring("/");
//  itoa(timerTotal, timerTotalC, 10);
//  ssd1306_putstring(timerTotalC);
//  timeStrip();
//}
//
//void menuStrip() {
//  ssd1306_set_textsize(1);
//  ssd1306_set_textcolor(WHITE);
//  ssd1306_set_cursor(0, 0);
//  ssd1306_putstring(tMenu);
//  timeStrip();
//}
//
//void arrows() {
//  ssd1306_draw_bitmap(118, 18, arrow_up_bmp, 8, 8, WHITE);
//  ssd1306_draw_bitmap(118, 40, arrow_down_bmp, 8, 8, WHITE);
//}



//void menuString(char* menu) {
//  ssd1306_set_cursor(1, 9);
//  ssd1306_set_textcolor(BLACK);
//  ssd1306_fill_rect(0, 8, 128, 9, WHITE);
//  ssd1306_puts(menu);
//  ssd1306_set_textcolor(WHITE);
//}
//
//void menuItem(char* itemName, uint8_t itemNumber, bool isSelected) {
//  ssd1306_set_cursor(1, 9 + itemNumber * 10);
//  if (isSelected) {
//    ssd1306_set_textcolor(BLACK);
//    ssd1306_fill_rect(0, 8 + itemNumber * 10, 116, 9, WHITE);
//  }
//  else {
//    ssd1306_set_textcolor(WHITE);
//    ssd1306_fill_rect(0, 8 + itemNumber * 10, 116, 9, BLACK);
//  }
//  ssd1306_puts(itemName);
//  ssd1306_set_textcolor(WHITE);
//}
//
//void menuContinued() {
//  ssd1306_set_cursor(24, 44);
//  ssd1306_puts("...");
//}
//
//void QuestionButtons(char* tQuestion) {
//  int xpos = (128 - 6 * sizeof(tQuestion))/2 - 3;
//  ssd1306_set_cursor(xpos, 52);
//  ssd1306_puts(tQuestion);
//}
//
//void buttonAnother() {
//  ssd1306_fill_rect(83, 56, 45, 8, WHITE);
//  ssd1306_set_textcolor(BLACK);
//  ssd1306_set_cursor(85, 57);
//  ssd1306_puts(tBbuttonAnother);
//  ssd1306_set_textcolor(WHITE);
//}
//
//void buttonMotivation() {
//  ssd1306_fill_rect(65, 56, 63, 8, WHITE);
//  ssd1306_set_textcolor(BLACK);
//  ssd1306_set_cursor(67, 57);
//  ssd1306_puts(tButtonMotivation);
//  ssd1306_set_textcolor(WHITE);
//}
//
//void buttonMenuReset() {
//  ssd1306_fill_rect(0, 56, 45, 8, WHITE);
//  ssd1306_set_textcolor(BLACK);
//  ssd1306_set_cursor(2, 57);
//  ssd1306_puts(tButtonMenuReset);
//  ssd1306_set_textcolor(WHITE);
//}
//
//void buttonBackSave() {
//  ssd1306_fill_rect(0, 56, 55, 8, WHITE);
//  ssd1306_set_textcolor(BLACK);
//  ssd1306_set_cursor(2, 57);
//  ssd1306_puts(tButtonBackSave);
//  ssd1306_set_textcolor(WHITE);
//}
//
//void buttonMenu() {
//  ssd1306_fill_rect(0, 56, 45, 8, WHITE);
//  ssd1306_set_textcolor(BLACK);
//  ssd1306_set_cursor(11, 57);
//  ssd1306_puts(tButtonMenu);
//  ssd1306_set_textcolor(WHITE);
//}
//
//void buttonBack() {
//  ssd1306_fill_rect(0, 56, 45, 8, WHITE);
//  ssd1306_set_textcolor(BLACK);
//  ssd1306_set_cursor(11, 57);
//  ssd1306_puts(tButtonBack);
//  ssd1306_set_textcolor(WHITE);
//}
//
//void buttonYesRight() {
//  ssd1306_fill_rect(101, 56, 27, 8, WHITE);
//  ssd1306_set_textcolor(BLACK);
//  ssd1306_set_cursor(106, 57);
//  ssd1306_puts(tButtonYes);
//  ssd1306_set_textcolor(WHITE);
//}
//
//void buttonNext() {
//  ssd1306_fill_rect(83, 56, 45, 8, WHITE);
//  ssd1306_set_textcolor(BLACK);
//  ssd1306_set_cursor(94, 57);
//  ssd1306_puts(tButtonNext);
//  ssd1306_set_textcolor(WHITE);
//}
//
//void buttonSave() {
//  ssd1306_fill_rect(83, 56, 45, 8, WHITE);
//  ssd1306_set_textcolor(BLACK);
//  ssd1306_set_cursor(94, 57);
//  ssd1306_puts(tButtonSave);
//  ssd1306_set_textcolor(WHITE);
//}
//
//void buttonNextBackspace() {
//  ssd1306_fill_rect(83, 56, 45, 8, WHITE);
//  ssd1306_set_textcolor(BLACK);
//  ssd1306_set_cursor(85, 57);
//  ssd1306_puts(tButtonNextBackspace);
//  ssd1306_set_textcolor(WHITE);
//}
//
//void buttonYesLeft() {
//  ssd1306_fill_rect(0, 56, 27, 8, WHITE);
//  ssd1306_set_textcolor(BLACK);
//  ssd1306_set_cursor(5, 57);
//  ssd1306_puts(tButtonYes);
//  ssd1306_set_textcolor(WHITE);
//}
//
//void buttonNoRight() {
//  ssd1306_fill_rect(101, 56, 27, 8, WHITE);
//  ssd1306_set_textcolor(BLACK);
//  ssd1306_set_cursor(109, 57);
//  ssd1306_puts(tButtonNo);
//  ssd1306_set_textcolor(WHITE);
//}
//
//void buttonNoLeft() {
//  ssd1306_fill_rect(0, 56, 27, 8, WHITE);
//  ssd1306_set_textcolor(BLACK);
//  ssd1306_set_cursor(8, 57);
//  ssd1306_puts(tButtonNo);
//  ssd1306_set_textcolor(WHITE);
//}
//
//void buttonChoose() {
//  ssd1306_fill_rect(83, 56, 45, 8, WHITE);
//  ssd1306_set_textcolor(BLACK);
//  ssd1306_set_cursor(88, 57);
//  ssd1306_puts(tButtonChoose);
//  ssd1306_set_textcolor(WHITE);
//}
//
//void buttonResume() {
//  ssd1306_fill_rect(83, 56, 45, 8, WHITE);
//  ssd1306_set_textcolor(BLACK);
//  ssd1306_set_cursor(88, 57);
//  ssd1306_puts(tButtonResume);
//  ssd1306_set_textcolor(WHITE);
//}
//
//void buttonDelete()
//{
//  ssd1306_fill_rect(83, 56, 45, 8, WHITE);
//  ssd1306_set_textcolor(BLACK);
//  ssd1306_set_cursor(88, 57);
//  ssd1306_puts(tButtonDelete);
//  ssd1306_set_textcolor(WHITE);
//}
//
//void buttonPause() {
//  ssd1306_fill_rect(83, 56, 45, 8, WHITE);
//  ssd1306_set_textcolor(BLACK);
//  ssd1306_set_cursor(92, 57);
//  ssd1306_puts(tButtonPause);
//  ssd1306_set_textcolor(WHITE);
//}

#endif //__STIMER_INTERFACE_H