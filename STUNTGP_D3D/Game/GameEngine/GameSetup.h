#ifndef GAMESETUP_H
#define GAMESETUP_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

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
extern DWORD g_61c508;
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
    BYTE unk034[0x104];    // 0x034
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

#endif /* GAMESETUP_H */
