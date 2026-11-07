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
