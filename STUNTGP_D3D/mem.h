#ifndef MEM_H
#define MEM_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void *Mem_Alloc(int size, int type);
int Mem_Free(void *ptr);
void Mem_FreeAll();
void Mem_Shutdown();
#endif /* MEM_H */
