#include "GameUpdate.h"

#include <cmath>
#include <cstring>

#include "../../globals.h"
#include "../../input.h"

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

// FUNCTION: STUNTGP_D3D 0x40c750
void FUN_40c750(Controller *c)
{
    if (g_612be8 == 1)
    {
        if (g_61294c == 1)
        {
            FUN_442350();
        }
        else
        {
            g_61b744 = c;
            FUN_4422c0();
        }
    }
}

// Analogue pad: scale the stick to +-255 and split it into the four direction controls.
// FUNCTION: STUNTGP_D3D 0x40c780
void FUN_40c780(Controller *c)
{
    Car *car = &g_49a1f8[c->unk018];
    float scale = 263.0f / c->state.range;
    int x = c->state.x * scale;
    int y = c->state.y * scale;
    if (x < -255)
    {
        x = -255;
    }
    else if (x > 255)
    {
        x = 255;
    }
    if (y < -255)
    {
        y = -255;
    }
    else if (y > 255)
    {
        y = 255;
    }
    if (y >= 0)
    {
        car->controls[0] = 0;
    }
    else
    {
        car->controls[0] = -y;
    }
    if (y <= 0)
    {
        car->controls[1] = 0;
    }
    else
    {
        car->controls[1] = y;
    }
    if (x >= 0)
    {
        car->controls[3] = 0;
    }
    else
    {
        car->controls[3] = -x;
    }
    if (x <= 0)
    {
        car->controls[2] = 0;
    }
    else
    {
        car->controls[2] = x;
    }
    if (c->state.buttons[car->keyMap[4]])
    {
        car->controls[4] = 0xff;
    }
    if (c->state.buttons[car->keyMap[5]])
    {
        car->controls[5] = 0xff;
    }
    if (c->state.buttons[car->keyMap[6]])
    {
        car->controls[6] = 0xff;
    }
    if (c->state.buttons[car->keyMap[7]])
    {
        car->controls[7] = 0xff;
    }
    if (c->state.buttons[car->keyMap[8]])
    {
        car->controls[8] = 0xff;
    }
    if (c->state.buttons[car->keyMap[9]])
    {
        car->controls[9] = 0xff;
    }
    InputState *s = &c->state;
    if (s->buttons[car->keyMap[12]] && !s->prevButtons[car->keyMap[12]])
    {
        FUN_40c750(c);
    }
}

// FUNCTION: STUNTGP_D3D 0x40c8f0
void FUN_40c8f0(Controller *c)
{
    Car *car = &g_49a1f8[c->unk018];
    if (car->keyMap[0] && (g_62d480[car->keyMap[0]] & 0x80))
    {
        car->controls[0] = 0xff;
    }
    if (car->keyMap[1] && !car->controls[0] && (g_62d480[car->keyMap[1]] & 0x80))
    {
        car->controls[1] = 0xff;
    }
    if (car->keyMap[3] && (g_62d480[car->keyMap[3]] & 0x80))
    {
        car->controls[3] = 0xff;
    }
    if (car->keyMap[2] && !car->controls[3] && (g_62d480[car->keyMap[2]] & 0x80))
    {
        car->controls[2] = 0xff;
    }
    if (car->keyMap[4] && (g_62d480[car->keyMap[4]] & 0x80))
    {
        car->controls[4] = 0xff;
    }
    if (car->keyMap[5] && (g_62d480[car->keyMap[5]] & 0x80))
    {
        car->controls[5] = 0xff;
    }
    if (car->keyMap[6] && (g_62d480[car->keyMap[6]] & 0x80))
    {
        car->controls[6] = 0xff;
    }
    if (car->keyMap[7] && (g_62d480[car->keyMap[7]] & 0x80))
    {
        car->controls[7] = 0xff;
    }
    if (car->keyMap[8] && (g_62d480[car->keyMap[8]] & 0x80))
    {
        car->controls[8] = 0xff;
    }
    if (car->keyMap[9] && (g_62d480[car->keyMap[9]] & 0x80))
    {
        car->controls[9] = 0xff;
    }
    if (((g_62d480[VK_ESCAPE] & 0x80) && !(g_62dcf0[VK_ESCAPE] & 0x80)) ||
        ((g_62d480[car->keyMap[12]] & 0x80) && !(g_62dcf0[car->keyMap[12]] & 0x80)))
    {
        FUN_40c750(c);
    }
}

// Digital pad: the stick only counts once it leaves the dead zone.
// FUNCTION: STUNTGP_D3D 0x40ca60
void FUN_40ca60(Controller *c)
{
    Car *car = &g_49a1f8[c->unk018];
    int deadZone = c->state.range >> 1;
    if (c->state.buttons[car->keyMap[0]])
    {
        car->controls[0] = 0xff;
    }
    if (c->state.buttons[car->keyMap[1]])
    {
        car->controls[1] = 0xff;
    }
    if (car->keyMap[2] && c->state.x < -deadZone)
    {
        car->controls[2] = 0xff;
    }
    if (car->keyMap[3] && c->state.x > deadZone)
    {
        car->controls[3] = 0xff;
    }
    if (c->state.buttons[car->keyMap[4]])
    {
        car->controls[4] = 0xff;
    }
    if (c->state.buttons[car->keyMap[5]])
    {
        car->controls[5] = 0xff;
    }
    if (c->state.buttons[car->keyMap[6]])
    {
        car->controls[6] = 0xff;
    }
    if (c->state.buttons[car->keyMap[7]])
    {
        car->controls[7] = 0xff;
    }
    if (c->state.buttons[car->keyMap[8]])
    {
        car->controls[8] = 0xff;
    }
    if (c->state.buttons[car->keyMap[9]])
    {
        car->controls[9] = 0xff;
    }
    InputState *s = &c->state;
    if (s->buttons[car->keyMap[12]] && !s->prevButtons[car->keyMap[12]])
    {
        FUN_40c750(c);
    }
}

// Latches the per-controller direction/button bits used by the menus.
// FUNCTION: STUNTGP_D3D 0x40d860
void FUN_40d860()
{
    for (int i = 0; i < 4; i++)
    {
        if (g_62d580[i].active == 1 && g_62d580[i].unk008 == 0)
        {
            memcpy(g_62d580[i].prevKeys, g_62d580[i].keys, 7);
            memset(g_62d580[i].keys, 0, 7);
            switch (g_62d580[i].type)
            {
            case 1:
                if (g_612be8 == 1)
                {
                    if (g_62d480[VK_ESCAPE] & 0x80)
                    {
                        g_62d580[i].keys[6] = 1;
                    }
                    else
                    {
                        g_62d580[i].keys[6] = 0;
                    }
                }
                if (g_62d480[VK_RETURN] & 0x80)
                {
                    g_62d580[i].keys[4] = 1;
                }
                else
                {
                    g_62d580[i].keys[4] = 0;
                }
                if (g_62d480[VK_ESCAPE] & 0x80)
                {
                    g_62d580[i].keys[5] = 1;
                }
                else
                {
                    g_62d580[i].keys[5] = 0;
                }
                g_62d580[i].keys[0] = g_62d480[VK_LEFT] >> 7;
                if (g_62d480[VK_RIGHT] & 0x80)
                {
                    g_62d580[i].keys[1] = 1;
                }
                else
                {
                    g_62d580[i].keys[1] = 0;
                }
                if (g_62d480[VK_UP] & 0x80)
                {
                    g_62d580[i].keys[2] = 1;
                }
                else
                {
                    g_62d580[i].keys[2] = 0;
                }
                if (g_62d480[VK_DOWN] & 0x80)
                {
                    g_62d580[i].keys[3] = 1;
                }
                else
                {
                    g_62d580[i].keys[3] = 0;
                }
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                int deadZone = g_62d580[i].state.range >> 1;
                g_576b6c = &g_62d580[i].state;
                if (g_576b6c->buttons[g_473978[0][12]])
                {
                    g_62d580[i].keys[6] = 1;
                }
                else
                {
                    g_62d580[i].keys[6] = 0;
                }
                if (g_576b6c->buttons[g_473978[0][10]])
                {
                    g_62d580[i].keys[4] = 1;
                }
                else
                {
                    g_62d580[i].keys[4] = 0;
                }
                if (g_576b6c->buttons[g_473978[0][11]])
                {
                    g_62d580[i].keys[5] = 1;
                }
                else
                {
                    g_62d580[i].keys[5] = 0;
                }
                if (g_576b6c->x > deadZone)
                {
                    g_62d580[i].keys[1] = 1;
                }
                else
                {
                    g_62d580[i].keys[1] = 0;
                }
                g_62d580[i].keys[0] = g_576b6c->x < -deadZone;
                if (g_62d580[i].state.y > deadZone)
                {
                    g_62d580[i].keys[3] = 1;
                }
                else
                {
                    g_62d580[i].keys[3] = 0;
                }
                if (g_62d580[i].state.y < -deadZone)
                {
                    g_62d580[i].keys[2] = 1;
                }
                else
                {
                    g_62d580[i].keys[2] = 0;
                }
                break;
            }
        }
    }
}

// Copies each controller's input into the car it drives.
// FUNCTION: STUNTGP_D3D 0x40dad0
void FUN_40dad0()
{
    if (g_61294c == 1)
    {
        FUN_40d860();
        return;
    }
    Controller *c = g_62d580;
    for (int i = 0; i < 4; c++, i++)
    {
        if (c->active == 1 && c->unk008 == 0 && c->unk018 != 0xffff)
        {
            memcpy(g_62d580[i].prevKeys, g_62d580[i].keys, 7);
            memset(g_62d580[i].keys, 0, 7);
            g_4d5bb8 = &g_49a1f8[c->unk018];
            if (g_4d5bb8->unk2280)
            {
                memcpy(g_4d5bb8->prevControls, g_4d5bb8->controls, 10);
                memset(g_4d5bb8->controls, 0, 10);
                g_576b6c = &c->state;
                switch (g_62d580[i].type)
                {
                case 1:
                    g_4d5bb8->inputMode = 2;
                    g_4d5bb8->unk254 = 1.0f;
                    memcpy(g_4d5bb8->keyMap, g_473908[c->keyMap], 13);
                    FUN_40c8f0(c);
                    break;
                case 2:
                    g_4d5bb8->inputMode = 0;
                    g_4d5bb8->unk254 = 1.0f;
                    memcpy(g_4d5bb8->keyMap, g_473940[c->keyMap], 13);
                    FUN_40c780(c);
                    break;
                case 3:
                    g_4d5bb8->inputMode = 3;
                    g_4d5bb8->unk254 = 0.8f;
                    memcpy(g_4d5bb8->keyMap, g_4739b0[c->keyMap], 13);
                    FUN_40c780(c);
                    break;
                case 5:
                    g_4d5bb8->inputMode = 1;
                    g_4d5bb8->unk254 = 1.0f;
                    memcpy(g_4d5bb8->keyMap, g_473978[c->keyMap], 13);
                    FUN_40c780(c);
                    break;
                case 4:
                case 6:
                    g_4d5bb8->inputMode = 4;
                    g_4d5bb8->unk254 = 1.0f;
                    memcpy(g_4d5bb8->keyMap, g_4739e8[c->keyMap], 13);
                    FUN_40ca60(c);
                    break;
                }
                if (g_62d580[i].unk020 == 2)
                {
                    FUN_410a10(i);
                }
            }
        }
    }
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
    for (int i = 0; i < 4; c++, i++)
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
