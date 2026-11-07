#include "random.h"

#include <stdlib.h>
#include <time.h>

// FUNCTION: STUNTGP_D3D 0x42f190
void Random_Seed(unsigned int seed)
{
    srand(seed);
}

// FUNCTION: STUNTGP_D3D 0x42f1a0
void Random_SeedFromTime()
{
    Random_Seed(time(NULL));
}

// Signed random value in roughly [-range/2, range/2].
// FUNCTION: STUNTGP_D3D 0x42f1f0
int FUN_42f1f0(int range)
{
    return (rand() - 0x3fff) * range / 0x7fff;
}
