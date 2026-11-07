#include "GameUpdate.h"

#include <cmath>
#include <cstring>

#include "../../globals.h"

// Rows are indexed by Controller::keyMap. Columns 0-3 are up/down/left/right,
// 10 and 12 are the menu keys (return/escape on the keyboard map).

// GLOBAL: STUNTGP_D3D 0x473908
BYTE g_473908[4][13] = {
    {0x26, 0x28, 0x25, 0x27, 0x20, 0x10, 0x10, 0x10, 0x11, 0x0d, 0x0d, 0x1b, 0x1b},
    {0x26, 0x28, 0x25, 0x27, 0x20, 0x11, 0x11, 0x11, 0x10, 0x0d, 0x0d, 0x1b, 0x1b},
    {0x26, 0x28, 0x25, 0x27, 0x20, 0x10, 0x10, 0x10, 0x0d, 0x11, 0x0d, 0x1b, 0x1b},
    {0x26, 0x28, 0x25, 0x27, 0x20, 0x0d, 0x0d, 0x0d, 0x11, 0x10, 0x0d, 0x1b, 0x1b},
};

// GLOBAL: STUNTGP_D3D 0x473940
BYTE g_473940[4][13] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x03, 0x01, 0x00, 0x01, 0x01},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x02, 0x01, 0x00, 0x01, 0x01},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x01, 0x03, 0x00, 0x01, 0x01},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x03, 0x02, 0x00, 0x01, 0x01},
};

// GLOBAL: STUNTGP_D3D 0x473978
BYTE g_473978[4][13] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x03, 0x01, 0x00, 0x01, 0x01},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x02, 0x01, 0x00, 0x01, 0x01},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x01, 0x03, 0x00, 0x01, 0x01},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x03, 0x02, 0x00, 0x01, 0x01},
};

// GLOBAL: STUNTGP_D3D 0x4739b0
BYTE g_4739b0[4][13] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x03, 0x01, 0x00, 0x01, 0x01},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x02, 0x01, 0x00, 0x01, 0x01},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x01, 0x03, 0x00, 0x01, 0x01},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x03, 0x02, 0x00, 0x01, 0x01},
};

// GLOBAL: STUNTGP_D3D 0x4739e8
BYTE g_4739e8[4][13] = {
    {0x26, 0x28, 0x25, 0x27, 0x00, 0x02, 0x02, 0x02, 0x03, 0x01, 0x00, 0x01, 0x01},
    {0x26, 0x28, 0x25, 0x27, 0x00, 0x03, 0x03, 0x03, 0x02, 0x01, 0x00, 0x01, 0x01},
    {0x26, 0x28, 0x25, 0x27, 0x00, 0x02, 0x02, 0x02, 0x01, 0x03, 0x00, 0x01, 0x01},
    {0x26, 0x28, 0x25, 0x27, 0x00, 0x01, 0x01, 0x01, 0x03, 0x02, 0x00, 0x01, 0x01},
};

// GLOBAL: STUNTGP_D3D 0x576618
InputSlot g_576618[10];

// GLOBAL: STUNTGP_D3D 0x61b744
Controller *g_61b744;

// GLOBAL: STUNTGP_D3D 0x612950
int g_612950;

// GLOBAL: STUNTGP_D3D 0x612958
int g_612958;

// GLOBAL: STUNTGP_D3D 0x61295c
int g_61295c;

// GLOBAL: STUNTGP_D3D 0x612964
int g_612964;

// GLOBAL: STUNTGP_D3D 0x612968
int g_612968;

// GLOBAL: STUNTGP_D3D 0x61296c
int g_61296c;

// GLOBAL: STUNTGP_D3D 0x612970
int g_612970;

// GLOBAL: STUNTGP_D3D 0x62d580
Controller g_62d580[4];

// Previous frame's keyboard state, copied from g_62d480.
// GLOBAL: STUNTGP_D3D 0x62dcf0
BYTE g_62dcf0[256];

// STUB: STUNTGP_D3D 0x40d860
void FUN_40d860()
{
}

// FUNCTION: STUNTGP_D3D 0x4243f0
void FUN_4243f0()
{
    for (unsigned int i = 0; i < 10; i++)
    {
        if (g_576618[i].present == 1)
        {
            switch (g_576618[i].type)
            {
            case 1:
                if (i == 0)
                {
                    FUN_45ec00();
                }
                break;
            case 2:
                FUN_424520(i);
                break;
            case 3:
                FUN_424520(i);
                break;
            case 4:
                FUN_424520(i);
                break;
            case 5:
                FUN_424520(i);
                break;
            case 6:
                FUN_424520(i);
                break;
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x4244c0
void FUN_4244c0()
{
    for (int i = 0; i < 4; i++)
    {
        g_62d580[i].prevActive = g_62d580[i].active;
        g_62d580[i].active = g_576618[i].present;
        g_62d580[i].type = g_576618[i].type;
        if (g_576618[i].present == 1 && g_576618[i].type >= 2 && g_576618[i].type <= 6)
        {
            g_62d580[i].state = g_576618[i].state;
            g_62d580[i].unk028 = g_62d580[i].unk024;
            g_62d580[i].unk024 = g_576618[i].unk08;
        }
    }
}

// STUB: STUNTGP_D3D 0x424520
int FUN_424520(int index)
{
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x45ec00
void FUN_45ec00()
{
    GetKeyboardState(g_62d480);
}

// FUNCTION: STUNTGP_D3D 0x45ec20
void FUN_45ec20()
{
}

// FUNCTION: STUNTGP_D3D 0x45ee60
void FUN_45ee60()
{
    if (g_612be8 == 1)
    {
        g_61295c = 0;
        Controller *c = g_62d580;
        for (unsigned int i = 0; i < 4; i++, c++)
        {
            if (c->unk018 != 0xffff)
            {
                if (c->active == 0)
                {
                    g_61295c = 1;
                }
                if (c->active == 0 && c->prevActive == 1)
                {
                    g_612950 = g_61294c;
                    if (!g_612950)
                    {
                        FUN_4422c0();
                        g_61b744 = &g_62d580[i];
                    }
                    return;
                }
                if (c->active == 1 && c->prevActive == 0)
                {
                    if (g_612950 != 1)
                    {
                        FUN_442350();
                    }
                    return;
                }
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x45ef00
void FUN_45ef00()
{
    Controller *c = g_62d580;
    for (int i = 0; i < 4; i++, c++)
    {
        if (c->active == 1 && c->unk024 != c->unk028)
        {
            c->unk020 = c->unk024;
            c->unk028 = c->unk024;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x45ef30
void FUN_45ef30(Controller *c, BYTE *map)
{
    int deadZone = c->state.range / 2;
    if (fabs(c->state.y) > deadZone)
    {
        g_612970 = 1;
    }
    else if (fabs(c->state.x) > deadZone || c->state.buttons[map[4]] ||
        c->state.buttons[map[5]] || c->state.buttons[map[6]] || c->state.buttons[map[7]] ||
        c->state.buttons[map[8]] || c->state.buttons[map[9]] || c->state.buttons[map[10]] ||
        c->state.buttons[map[11]] || c->state.buttons[map[12]])
    {
        g_612970 = 1;
    }
    if (c->state.buttons[map[12]] || c->state.buttons[map[10]])
    {
        g_612968 = 1;
    }
}

// FUNCTION: STUNTGP_D3D 0x45f020
void FUN_45f020(Controller *c, BYTE *map)
{
    if ((g_62d480[map[0]] & 0x80) || (g_62d480[map[1]] & 0x80) || (g_62d480[map[3]] & 0x80) ||
        (g_62d480[map[2]] & 0x80) || (g_62d480[map[4]] & 0x80) || (g_62d480[map[5]] & 0x80) ||
        (g_62d480[map[6]] & 0x80) || (g_62d480[map[7]] & 0x80) || (g_62d480[map[8]] & 0x80) ||
        (g_62d480[map[9]] & 0x80) || (g_62d480[map[10]] & 0x80) || (g_62d480[map[11]] & 0x80) ||
        (g_62d480[map[12]] & 0x80))
    {
        g_612970 = 1;
    }
    if ((g_62d480[map[12]] & 0x80) || (g_62d480[map[10]] & 0x80))
    {
        g_612968 = 1;
    }
}

// FUNCTION: STUNTGP_D3D 0x45f110
void FUN_45f110()
{
    g_612964 = g_612968;
    g_612968 = 0;
    g_61296c = g_612970;
    g_612970 = 0;
    unsigned int i = 0;
    Controller *c = g_62d580;
    while (i < 4 && g_612968 != 1)
    {
        if (c->active == 1)
        {
            c->mode = 0;
            switch (c->type)
            {
            case 1:
                c->mode = 5;
                FUN_45f020(c, g_473908[c->keyMap]);
                break;
            case 2:
                c->mode = 2;
                FUN_45ef30(c, g_473940[c->keyMap]);
                break;
            case 3:
                c->mode = 1;
                FUN_45ef30(c, g_4739b0[c->keyMap]);
                break;
            case 5:
                c->mode = 4;
                FUN_45ef30(c, g_473978[c->keyMap]);
                break;
            case 4:
            case 6:
                c->mode = 3;
                FUN_45ef30(c, g_4739e8[c->keyMap]);
                break;
            }
        }
        c++;
        i++;
    }
}

// FUNCTION: STUNTGP_D3D 0x45f210
void FUN_45f210()
{
    g_612958 = 0;
    memcpy(g_62dcf0, g_62d480, sizeof(g_62dcf0));
    FUN_4243f0();
    FUN_4244c0();
    FUN_45ef00();
    FUN_45f110();
    FUN_45ec20();
    FUN_45ee60();
}
