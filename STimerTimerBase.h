#ifndef __STIMER_TIMERBASE_H
#define __STIMER_TIMERBASE_H

#define MAX_TIMERS_COUNT       20
#define MAX_TIMER_NAME_LENGTH  19
#define MAX_MOTIVATION_COUNT   100
#define MAX_MOTIVATION_LENGTH  145
#include <stdint.h>
#include <stdlib.h>
#include "string.h"
#include "STimerLanguage.h"

struct oneTimer {
  char *timerName;
  uint32_t currTime;
  uint32_t lastTime;
  uint32_t recordTime;
  char *motivations[MAX_MOTIVATION_COUNT];
  uint8_t motivationsNum;
  uint8_t motivationNLC[MAX_MOTIVATION_COUNT];
};

  struct oneTimer* timers[MAX_TIMERS_COUNT];
  int8_t currentShownTimer = -1;
  uint8_t timersInBase = 0;
  uint8_t activeTimersNum = 0;
  int8_t activeTimers[MAX_TIMERS_COUNT];

void timerBaseCreate()
{
  for(uint8_t i = 0; i < MAX_TIMERS_COUNT; i++)
  {
    activeTimers[i] = -1;
    timers[i] = NULL;
  }
}

void timerBaseAddNewTimer(const char* name)
{
  if(timersInBase < MAX_TIMERS_COUNT)
  {
    uint8_t nameLen = strlen(name);
    timers[timersInBase] = (struct oneTimer*)malloc(sizeof(struct oneTimer));
    timers[timersInBase]->timerName = (char*)malloc(nameLen+1);
    strcpy(timers[timersInBase]->timerName, name);
    timers[timersInBase]->currTime = 0;
    timers[timersInBase]->lastTime = 0;
    timers[timersInBase]->recordTime = 0;
    timers[timersInBase]->motivationsNum = 0;
    for(uint8_t i = 0; i < MAX_MOTIVATION_COUNT; i++)
    {
      timers[timersInBase]->motivations[i] = NULL;
      timers[timersInBase]->motivationNLC[i] = 0;
    }
    timersInBase++;
  }
}

void timerBaseChangeTimerName(uint8_t timerNum, const char* newName)
{
  free(timers[timerNum]->timerName);
  uint8_t nameLen = strlen(newName);
  timers[timerNum]->timerName = (char*)malloc(nameLen+1);
  strcpy(timers[timerNum]->timerName, newName);
}

void timerBaseDelTimer(uint8_t timerNum)
{
  uint8_t deletedActiveTimerNum = -1;
  if(timerNum >= 0 && timerNum < timersInBase)
  {
    for(uint8_t i = 0; i < activeTimersNum; i++) 
      if(activeTimers[i] == timerNum) {
	activeTimers[i] = -1;
        deletedActiveTimerNum = i;
      }
    if (deletedActiveTimerNum >= 0) {
      if(activeTimersNum != MAX_TIMERS_COUNT-1)
        for(uint8_t i = deletedActiveTimerNum; i < MAX_TIMERS_COUNT-1; i++)
	  activeTimers[i] = activeTimers[i+1];
      activeTimersNum--;    
    }

    free(timers[timerNum]);
    timers[timerNum] = NULL;
    if(timerNum != MAX_TIMERS_COUNT-1)
    {
      for(uint8_t i = timerNum; i < timersInBase; i++)
	timers[i] = timers[i+1];
    }
    free(timers[timersInBase-1]);
    timers[timersInBase-1] = NULL;
    timersInBase--;
    for(uint8_t i = 0; i < activeTimersNum; i++)
      if (activeTimers[i] > timerNum)
        activeTimers[i]--;
    if(activeTimersNum == 0)
      currentShownTimer = -1;
    else
      currentShownTimer = 0;
  }
}

void timerBaseActivateTimer(uint8_t timerNum)
{
  activeTimers[activeTimersNum++] = timerNum;
  currentShownTimer = activeTimersNum-1/*0*/;
}

void timerBaseAddMotivationToTimer(uint8_t timerNum, const char* motivation)
{
  if(timers[timerNum] != NULL && timers[timerNum]->motivationsNum < MAX_MOTIVATION_COUNT)
    {
      uint8_t motLen = strlen(motivation);
      char* str1;
      str1 = (char*)malloc(motLen+1);
      strcpy(str1, motivation);

      uint8_t nlc = 1;
      if(motLen >= 19)
      {
	uint8_t i = 0;
	while(i <= motLen-19)
	{
	  i += 19;
	  while(str1[i] != ' ')
	    { i--; }
	  str1[i++] = '\n';
	  nlc++;
	}
	str1[motLen] = '\0';
      }
      
      timers[timerNum]->motivations[timers[timerNum]->motivationsNum] = (char*)malloc(motLen+1);
      strcpy(timers[timerNum]->motivations[timers[timerNum]->motivationsNum], str1);
      timers[timerNum]->motivationNLC[timers[timerNum]->motivationsNum] = nlc;
      timers[timerNum]->motivationsNum++;
      free(str1);
    }
}

void timerBaseDelMotivationFromTimer(uint8_t timerNum, uint8_t motNum)
{
  if(timers[timerNum] != NULL && timers[timerNum]->motivations[motNum] != NULL)
  {
    free(timers[timerNum]->motivations[motNum]);
    timers[timerNum]->motivationsNum--;
    for(uint8_t i = motNum; i < MAX_MOTIVATION_COUNT-1; i++)
      timers[timerNum]->motivations[i] = timers[timerNum]->motivations[i+1];
  }
}

char* timerBaseGetMotivation(uint8_t timerNum, uint8_t motNum)
{
  if(timers[timerNum] != NULL && timers[timerNum]->motivations[motNum] != NULL)
  {
    uint8_t motLen = strlen(timers[timerNum]->motivations[motNum]);
    char * motivation = (char*)malloc(motLen+1);
    strcpy(motivation, timers[timerNum]->motivations[motNum]);
    return motivation;
  }
}

uint8_t timerBaseGetTimerMotivationsNum(uint8_t timerNum)
{
  uint8_t result = 0;

  if(timers[timerNum] != NULL)
    result = timers[timerNum]->motivationsNum;
  
  return result;
}

uint8_t timerBaseGetTimerMotivationsNLC(uint8_t timerNum, uint8_t motNum)
{
  uint8_t result = 0;

  if(timers[timerNum] != NULL && timers[timerNum]->motivations[motNum] != NULL)
    result = timers[timerNum]->motivationNLC[motNum];

  return result;
}

char* timerBaseGetTimerName(uint8_t timerNum)
{
  static char result[MAX_TIMER_NAME_LENGTH];

  if(timers[timerNum] != NULL)
  {
    strcpy(result, timers[timerNum]->timerName);
  }
  else
  {
    strcpy(result, tDefaultTimerName);
    char t[3];
    itoa(timerNum+1, t, 10);
    strcat(result, t);
  }

  return result;
}

char* timerBaseGetTimerTime(uint8_t timerNum, uint8_t type)
{
    static char timeString[19];
    char temp[2];
    uint8_t days, hours, min;
    uint32_t time;
    switch(type) {
        case 1:
            strcpy(timeString, "   CUR: ");
	    time = timers[timerNum]->currTime;
            break;
        case 2:
            strcpy(timeString, "  LAST: ");
	    time = timers[timerNum]->lastTime;
            break;
        case 3:
            strcpy(timeString, "   REC: ");
	    time = timers[timerNum]->recordTime;
            break;
        default:
            strcpy(timeString, "        ");
            break;
    }

    min = time % 60;
    hours = (time / 60) % 24;
    days =  (time / 60) / 24;

    itoa(days, temp, 10);
    if (days < 10) {
        timeString[8] = '0';
        timeString[9] = temp[0];
    } else {
        timeString[8] = temp[0];
        timeString[9] = temp[1];
    }
    timeString[10] = 'd';
    timeString[11] = ':';
    itoa(hours, temp, 10);
    if (hours < 10) {
        timeString[12] = '0';
        timeString[13] = temp[0];
    } else {
        timeString[12] = temp[0];
        timeString[13] = temp[1];
    }
    timeString[14] = 'h';
    timeString[15] = ':';
    itoa(min, temp, 10);
    if (min < 10) {
        timeString[16] = '0';
        timeString[17] = temp[0];
    } else { 
        timeString[16] = temp[0];
        timeString[17] = temp[1];
    }
    timeString[18] = 'm';
    timeString[19] = '\0';
    return timeString;
}

void timerBaseResetTimer()
{
  uint8_t cST = activeTimers[currentShownTimer];
  timers[cST]->lastTime = timers[cST]->currTime;
  if(timers[cST]->recordTime < timers[cST]->lastTime)
    timers[cST]->recordTime = timers[cST]->lastTime;
  timers[cST]->currTime = 0;
}

bool timerBaseIsTimer(uint8_t timerNum)
{
  if(timers[timerNum] != NULL)
    return  true;
  return false;
}

uint8_t timerBaseGetActiveTimersCount()
{
  return activeTimersNum;
}

uint8_t timerBaseGetTimersInBaseCount()
{
  return timersInBase;
}

void timerBaseAddMinuteToActiveTimers()
{
  for(uint8_t i = 0; i < activeTimersNum; i++)
    timers[activeTimers[i]]->currTime++;
}

//check, if timer base is in File Data Storage
//bool isTimerBaseInFDS()
//{
//  return false;
//}
//
//void getTimerBaseFromFDS()
//{
//  //TODO: get timerBase from File Data Storage
//  return;
//}
//
//void setTimerBaseToFDS()
//{
//  //TODO: set timerBase to File Data Storage
//  return;
//}
//
//void eraseTimerBaseInFDS()
//{
//  if(isTimerBaseInFDS())
//  {
//    //TODO: erase timerBase in File Data Storage
//  }
//}
//
//void timerBaseSaveFDS()
//{
//  setTimerBaseToFDS();
//}
//
//void timerBaseClearFDS()
//{
//  eraseTimerBaseInFDS();
//}


#endif //__STIMER_TIMERBASE_H