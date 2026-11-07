#ifndef TIMER_H
#define TIMER_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern DWORD g_612d00;
extern DWORD g_612d04;
extern DWORD g_612d08;
extern DWORD g_612d0c;

DWORD Timer_GetCounter();
void Timer_Init();
#endif /* TIMER_H */
