#include "timer.h"

#include <stdio.h>

extern DWORD g_612d00;

extern DWORD g_612d04;

// Performance counter ticks per 1/60 s.
extern DWORD g_612d08;

// GLOBAL: STUNTGP_D3D 0x612d0c
DWORD g_612d0c;

// GLOBAL: STUNTGP_D3D 0x5da2e4
FILE *g_5da2e4;

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

// FUNCTION: STUNTGP_D3D 0x434890
void FUN_434890()
{
    // STRING: STUNTGP_D3D 0x478980
    fprintf(g_5da2e4, "***********************************************************************\n");
    // STRING: STUNTGP_D3D 0x4789cc
    fprintf(g_5da2e4, "*                                                                     *\n");
    // STRING: STUNTGP_D3D 0x478a18
    fprintf(g_5da2e4, "*                  SGP Config File (Text Version)                     *\n");
    // STRING: STUNTGP_D3D 0x478a64
    fprintf(g_5da2e4, "*                      (C) Pete Opdam                                 *\n");
    // STRING: STUNTGP_D3D 0x478ab0
    fprintf(g_5da2e4, "*                                                                     *\n");
    // STRING: STUNTGP_D3D 0x478afc
    fprintf(g_5da2e4, "***********************************************************************\n");
}

// FUNCTION: STUNTGP_D3D 0x434900
void FUN_434900(float *values, DWORD count)
{
    // STRING: STUNTGP_D3D 0x478b48
    fprintf(g_5da2e4, " ");
    int n = 0;
    for (DWORD i = 0; i < count; i++)
    {
        // STRING: STUNTGP_D3D 0x478b4c
        fprintf(g_5da2e4, "%8f, ", values[i]);
        n++;
        if (!(n & 7))
        {
            // STRING: STUNTGP_D3D 0x478b54
            fprintf(g_5da2e4, "\n ");
        }
    }
    // STRING: STUNTGP_D3D 0x478b58
    fprintf(g_5da2e4, "\n");
}
