#ifndef __STIMER_LANGUAGE_H
#define __STIMER_LANGUAGE_H

uint8_t selectedLang_id = 0;
uint8_t currLang_id = 0;

char tMenu[]                   = "MENU";
char tRecord[]                 = "RECORD";
char tMotivation[]             = "MOTIVATION";
char tMinutes[]                = "MIN";
char tLeft[]                   = "LEFT";

char *tMenuItemQLang[3]        = {"English", "Spanish", "French"};

#define MENU_ITEM_COUNT          3
#define MENU_SETTINGS_ITEM_COUNT 5
#define MENU_ADD_TIMER_COUNT     4
#define MENU_LANGUAGE_COUNT      3
#define MENU_MOTIVATION_COUNT    2
//#define LETTERS2_COUNT          68

char *tMenuMainItems[MENU_ITEM_COUNT]		      = {" Timers", " Pomodoro 25 min", " Settings"};
char *tMenuSettingsItems[MENU_SETTINGS_ITEM_COUNT]    = {" Language", " Date and Time", " Brightness", " Last update", " Reset the Device"};
char *tMenuAddTimerItems[MENU_ADD_TIMER_COUNT]	      = {" Activate", " Name", " Motivation", " Delete"};
char *tMenuMotivationItems[MENU_MOTIVATION_COUNT]     = {" Add", " View/Delete"};
char *tMenuLanguageItems[MENU_LANGUAGE_COUNT]	      = {"  English", "  Spanish", "  French"};

#define LETTERS_ENG_COUNT                 43
char *letters_eng[LETTERS_ENG_COUNT]   = {" ", "A", "B", "C", "D", "E", "F", "G", "H", "I", 
                                          "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S",
                                          "T", "U", "V", "W", "X", "Y", "Z", ".", ",", "-", 
                                          "?", "!", ":", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

#define LETTERS_ESP_COUNT                 52
char *letters_esp[LETTERS_ESP_COUNT]   = {" ", "A", "\xA0", "B", "C", "D", "E", "\x82", "F", "G", 
                                          "H", "I", "\xA1", "J", "K", "L", "M", "N", "\xA5", "O", 
                                          "\xA2", "P", "Q", "R", "S", "T", "U", "\xA3", "\x9A", "V", 
                                          "W", "X", "Y", "Z", ".", ",", "-", "\xA8", "?", "\xAD", 
                                          "!", ":", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

#define LETTERS_FRA_COUNT                 57
char *letters_fra[LETTERS_FRA_COUNT]   = {" ", "A", "\xA0", "\x85", "B", "C", "\x80", "D", "E", "\x82", 
                                          "\x8A", "\x88", "F", "G", "H", "I", "\xa1", "\x8D", "J", "K", 
                                          "L", "M", "N", "O", "\xA2", "\x95", "\x93", "P", "Q", "R", "S", "T", "U", 
                                          "\xa3", "\x97", "\x96", "V", "W", "X", "Y", "Z", ".", ",", 
                                          "-", "?", "!", ":", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

//char *letters2[LETTERS2_COUNT] = {" ","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","-",".",",","0","1","2","3","4","5","6","7","8","9",":","!"};

char *listHours[13] = {"00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};
char *listMonth[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sen", "Oct", "Nov", "Dec"};

char tBbuttonAnother[]         = "ANOTHER";
char tButtonBack[]             = "BACK";
char tButtonChoose[]           = "CHOOSE";
char tButtonMenu[]             = "MENU";
char tButtonNext[]             = "NEXT";
char tButtonSave[]             = "SAVE";
char tButtonMenuReset[]        = "MNU/RST";
char tButtonNextSave[]         = "NEXT/SAVE";
char tButtonNextBackspace[]    = "NEXT/BS";
char tButtonBackSave[]         = "BACK/SAVE";
char tButtonNo[]               = "NO";
char tButtonPause[]            = "PAUSE";
char tButtonRecord[]           = "RECORD";
char tButtonMotivation[]       = "MOTIVATION";
char tButtonYes[]              = "YES";
char tButtonResume[]           = "RESUME";
char tButtonDelete[]	       = "DELETE";

char strAdd[]		       = "ADD";
char strViewDel[]	       = "VIEW/DEL";

char tMenuStripAddTimer[]      = "ADD TIMER";
char tMenuStripAddTList[]      = "ADD TIMER: LIST";
char tMenuStripAddTNew[]       = "ADD TIMER: CREATE";
char tMenuStripDeleteTimer[]   = "DELETE TIMER";
char tMenuStripTimerList[]     = "TIMERS";
char tMenuStripAddTimerName[]  = "NAME";
char tMenuStripMotivation[]    = "MOTIVATION";
char tMenuStripPomodoro[]      = "POMODORO 25 MIN";
char tMenuStripSettings[]      = "SETTINGS";
char tMenuStripSetTime[]       = "SETTINGS: TIME";
char tMenuStripSetDate[]       = "SETTINGS: DATE";
char tMenuStripUpdate[]        = "SETTINGS: LAST UPDATE";
char tMenuStripLanguage[]      = "SETTINGS: LANGUAGE";
char tMenuStripBrightness[]    = "SETTINGS: BRIGHTNESS";
char tMenuStripReset[]         = "SETTINGS: RESET";

char tQuestionAdd[]            = "ADD?";
char tQuestionBack[]           = "BACK?";
char tQuestionDelete[]         = "DELETE?";
char tQuestionStartP[]         = "START?";
char tQuestionReset[]          = "RESET?";
char tQuestionChLang[]         = "Change language to";

char tDefaultTimerName[]       = "TIMER #";

#endif