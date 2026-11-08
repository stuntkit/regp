#ifndef GAMESETUP_H
#define GAMESETUP_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "../../sprite.h"

struct Car;

struct Unk4d5cc0
{
    short unk00;
    BYTE unk02[0x1a];
    DWORD unk1c;
    WORD unk20;
    WORD unk22;
    WORD unk24;
    WORD unk26;
    BYTE unk28[0x14];
    int unk3c;
    BYTE unk40[0x19d00 - 0x40];
};

// 8-byte face record of the dynamic mesh built by FUN_4342e0.
struct MeshFace
{
    BYTE count; // 0x00
    BYTE unk01; // 0x01
    BYTE unk02; // 0x02
    BYTE flags; // 0x03
    WORD unk04; // 0x04
    WORD index; // 0x06, first entry in the index buffer
};

struct MeshUv
{
    float u;     // 0x00
    float v;     // 0x04
    WORD point;  // 0x08
    WORD unk0a;  // 0x0a
    DWORD color; // 0x0c
};

// Queued polygon for the render lists, 20 bytes. poly's first byte is its vertex count, the
// second its texture slot.
struct PolyRef
{
    DWORD *poly; // 0x00
    WORD *ref;   // 0x04
    BYTE *src;   // 0x08, 16-byte entries: u, v, vertex index, colour
    int verts;   // 0x0c, 32-byte transformed vertices
    int unk10;   // 0x10
};

// Scene to load into g_636418[slot]; the list ends at id 0.
struct SceneLoad
{
    int id;   // 0x00
    int slot; // 0x04
};

extern SceneLoad g_58c540[24];
extern int g_58c808;
extern int g_58c234;

extern int g_589e08;
extern int g_624984;

void FUN_401de0();
void FUN_40a2f0();
void FUN_40d500();
void FUN_40e050();
void FUN_413670();
void FUN_4199a0();
void FUN_424c30(int param);
void FUN_425ad0();
void FUN_4277d0();
void FUN_429a40();
void FUN_42b040();
void FUN_42dcf0();
void FUN_42e800();
void FUN_42e820();
extern int g_624988;
extern int g_62498c;
void FUN_429510();
void FUN_42e6e0();
void FUN_43d0b0();
void FUN_43d1b0();
void FUN_43d1d0();
void FUN_43d1f0();
int FUN_43d420();
void FUN_445fa0();
void FUN_4469f0();
void FUN_45ec30();
struct RaceResult
{
    int unk00; // 0x00
    int unk04; // 0x04
    int unk08; // 0x08
    int unk0c; // 0x0c
    int unk10; // 0x10
    int unk14; // 0x14
};

// Per-player race slot, one per car.
struct RaceEntry
{
    int type;              // 0x000
    int unk004;            // 0x004
    int unk008;            // 0x008
    int unk00c;            // 0x00c
    BYTE unk010[0x14];     // 0x010
    int unk024;            // 0x024
    int unk028;            // 0x028
    int unk02c;            // 0x02c
    int unk030;            // 0x030
    int unk034;            // 0x034
    float unk038;          // 0x038
    float unk03c;          // 0x03c
    float unk040;          // 0x040
    float unk044;          // 0x044
    float unk048;          // 0x048
    float unk04c;          // 0x04c
    float unk050;          // 0x050
    float unk054;          // 0x054
    float unk058;          // 0x058
    float unk05c;          // 0x05c
    int unk060;            // 0x060
    BYTE unk064[0x4];      // 0x064
    int unk068;            // 0x068
    unsigned int unk06c;   // 0x06c, entries used in unk080
    float unk070;          // 0x070
    float unk074;          // 0x074
    float unk078;          // 0x078
    float unk07c;          // 0x07c
    float unk080[8];       // 0x080
    float unk0a0;          // 0x0a0
    float unk0a4;          // 0x0a4
    float unk0a8;          // 0x0a8
    float unk0ac;          // 0x0ac, suspension: travel, damping, stiffness in then out
    float unk0b0;          // 0x0b0
    float unk0b4;          // 0x0b4
    float unk0b8;          // 0x0b8
    float unk0bc;          // 0x0bc
    float unk0c0;          // 0x0c0
    BYTE unk0c4[0x4];      // 0x0c4
    float unk0c8;          // 0x0c8
    float unk0cc;          // 0x0cc
    float unk0d0;          // 0x0d0
    float unk0d4;          // 0x0d4
    float unk0d8;          // 0x0d8
    float unk0dc;          // 0x0dc
    float unk0e0;          // 0x0e0
    float unk0e4;          // 0x0e4
    float unk0e8;          // 0x0e8
    float unk0ec;          // 0x0ec
    float unk0f0;          // 0x0f0
    float unk0f4;          // 0x0f4
    float unk0f8;          // 0x0f8
    float unk0fc;          // 0x0fc
    float unk100;          // 0x100
    float unk104;          // 0x104
    float unk108;          // 0x108
    float unk10c;          // 0x10c
    float unk110;          // 0x110
    float unk114;          // 0x114
    float unk118;          // 0x118
    DWORD unk11c[7];       // 0x11c, copied to CarRace::unk80
    RaceResult result;     // 0x138
};

// Race state, cleared as one block by FUN_43a720.
struct RaceState
{
    int unk000;             // 0x000
    DWORD music;            // 0x004
    DWORD sfx;              // 0x008
    DWORD unk00c;           // 0x00c
    int unk010;             // 0x010
    int unk014;             // 0x014
    int unk018;             // 0x018
    int unk01c;             // 0x01c
    int unk020;             // 0x020
    int unk024[4];          // 0x024
    int unk034;             // 0x034
    DWORD unk038;           // 0x038
    int unk03c[4];          // 0x03c
    int unk04c;             // 0x04c
    int unk050;             // 0x050
    int unk054;             // 0x054
    int unk058;             // 0x058
    RaceEntry entries[6];   // 0x05c
    int unk83c;             // 0x83c
    int unk840;             // 0x840
    int unk844;             // 0x844
    int unk848;             // 0x848
    int unk84c;             // 0x84c
    Unk4d5cc0 *unk850;      // 0x850
    int unk854;             // 0x854
    int unk858;             // 0x858
    int unk85c;             // 0x85c
    Unk4d5cc0 *unk860;      // 0x860
    int unk864;             // 0x864
};

extern RaceState g_60d730;

// 16 screen-space effect slots; unk00 is 1 while a slot is in use.
struct Unk496990
{
    int unk00;        // 0x00
    Car *unk04;       // 0x04
    int unk08;        // 0x08
    int unk0c;        // 0x0c
    int unk10;        // 0x10
    float unk14;      // 0x14
    float unk18;      // 0x18
    int unk1c;        // 0x1c
    BYTE unk20[0x4];  // 0x20
    float unk24;      // 0x24
    DWORD unk28;      // 0x28, frames alive
    int unk2c;        // 0x2c
    BYTE unk30[0x4];  // 0x30
    int unk34;        // 0x34
    char unk38[0x8];  // 0x38, score text
    int unk40;        // 0x40
    float unk44;      // 0x44
    float unk48;      // 0x48
    float unk4c;      // 0x4c
    float unk50;      // 0x50
    float unk54;      // 0x54
    float unk58;      // 0x58
    float unk5c;      // 0x5c
    BYTE unk60[0x4];  // 0x60
    float unk64;      // 0x64
    float unk68;      // 0x68
    float unk6c;      // 0x6c
    float unk70;      // 0x70
    float unk74;      // 0x74
    float unk78;      // 0x78
    DWORD unk7c;      // 0x7c, colours
    DWORD unk80;      // 0x80
    DWORD unk84;      // 0x84
    int unk88;        // 0x88
    int unk8c;        // 0x8c
    int unk90;        // 0x90
    int unk94;        // 0x94
    int unk98;        // 0x98
    int unk9c;        // 0x9c
    float unka0;      // 0xa0
    float unka4;      // 0xa4
    float unka8;      // 0xa8
    SpriteDesc sprite; // 0xac
};

extern Unk496990 g_496990[16];

#endif /* GAMESETUP_H */
