#include <cstdlib>
#include <cstring>

#define MEM_SIZE 384

enum MemAllocType
{
    MEM_NORMAL,
    MEM_RESILIENT
};

// Mem_Alloc allocated size +0x24 B to return 32 B aligned memory pointer
// why 0x24 and not 0x20 - dunno
struct Mem_Entry
{
    void *data;
    void *dataWithPadding;
    size_t totalSize;
    size_t size;       // just te data without the 0x24 B padding
    MemAllocType type; // unused?
    int number;        // numer of the allocation
};

void *Mem_Alloc(size_t size, MemAllocType type);
void Mem_CleanupMemoryManager();
void Mem_CleanupMemoryManager_Once();
size_t Mem_Free(void *mem);
void Mem_FreeAllMemory();
void Mem_InitMemoryManager();
void Mem_InitMemoryManager_Once();
