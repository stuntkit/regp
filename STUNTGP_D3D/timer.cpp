#include "timer.h"

extern DWORD g_612d00;

extern DWORD g_612d04;

// Performance counter ticks per 1/60 s.
extern DWORD g_612d08;

// GLOBAL: STUNTGP_D3D 0x612d0c
DWORD g_612d0c;

// FUNCTION: STUNTGP_D3D 0x434820
DWORD Timer_GetCounter()
{
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return counter.LowPart;
}

// FUNCTION: STUNTGP_D3D 0x434840
void Timer_Init()
{
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    g_612d0c = frequency.LowPart;
    g_612d08 = frequency.LowPart / 60;
    g_612d00 = Timer_GetCounter();
    g_612d04 = Timer_GetCounter();
}
