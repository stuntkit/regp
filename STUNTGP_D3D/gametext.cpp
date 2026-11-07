#include "gametext.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "Game/GameEngine/io_wad.h"
#include "Game/GameEngine/GameUpdate.h"
#include "sprite.h"

extern BYTE g_62dcf0[256];
void FUN_441ec0();
void FUN_442490();
void FUN_442be0();

// GLOBAL: STUNTGP_D3D 0x6126a0
char g_6126a0[0x100];

// GLOBAL: STUNTGP_D3D 0x46e780
const TextKey c_46e780[105] = {
    // STRING: STUNTGP_D3D 0x4835e4
    {"text_race_results", 0x1},
    // STRING: STUNTGP_D3D 0x4835f8
    {"text_race_fastestlaptimes", 0x2},
    // STRING: STUNTGP_D3D 0x483614
    {"text_race_racetimes", 0x3},
    // STRING: STUNTGP_D3D 0x483628
    {"text_race_aeromiles", 0x4},
    // STRING: STUNTGP_D3D 0x48363c
    {"text_press_to_continue", 0x5},
    // STRING: STUNTGP_D3D 0x483654
    {"text_please_wait", 0x6},
    // STRING: STUNTGP_D3D 0x483668
    {"text_wrong_way", 0x7},
    // STRING: STUNTGP_D3D 0x483678
    {"text_pause_continue", 0x8},
    // STRING: STUNTGP_D3D 0x48368c
    {"text_pause_restart", 0x9},
    // STRING: STUNTGP_D3D 0x4836a0
    {"text_pause_exitrace", 0xa},
    // STRING: STUNTGP_D3D 0x4836b4
    {"text_pause_retire", 0xb},
    // STRING: STUNTGP_D3D 0x4836c8
    {"text_pause_fxvolume", 0xc},
    // STRING: STUNTGP_D3D 0x4836dc
    {"text_pause_musicvolume", 0xd},
    // STRING: STUNTGP_D3D 0x4836f4
    {"text_pause_detail", 0xe},
    // STRING: STUNTGP_D3D 0x483708
    {"text_pause_cameramode", 0xf},
    // STRING: STUNTGP_D3D 0x483720
    {"text_please_wait_4_others_2_finish", 0x10},
    // STRING: STUNTGP_D3D 0x483744
    {"text_is_out_of_the_race", 0x11},
    // STRING: STUNTGP_D3D 0x48375c
    {"text_beat_the_laprecord_ghost", 0x12},
    // STRING: STUNTGP_D3D 0x48377c
    {"text_you_have_beaten_your_userghost", 0x13},
    // STRING: STUNTGP_D3D 0x4837a0
    {"text_you_have_beaten_the_goldenghost", 0x14},
    // STRING: STUNTGP_D3D 0x4837c8
    {"text_is_recharging_in_pitlane", 0x15},
    // STRING: STUNTGP_D3D 0x4837e8
    {"text_is_running_on_fumes", 0x16},
    // STRING: STUNTGP_D3D 0x483804
    {"text_rejoins_the_race", 0x17},
    // STRING: STUNTGP_D3D 0x48381c
    {"text_takes_the_lead", 0x18},
    // STRING: STUNTGP_D3D 0x483830
    {"text_is", 0x19},
    // STRING: STUNTGP_D3D 0x483838
    {"text_seconds", 0x1a},
    // STRING: STUNTGP_D3D 0x483848
    {"text_ahead", 0x1b},
    // STRING: STUNTGP_D3D 0x483854
    {"text_behind", 0x1c},
    // STRING: STUNTGP_D3D 0x483860
    {"text_up", 0x1d},
    // STRING: STUNTGP_D3D 0x483868
    {"text_down", 0x1e},
    // STRING: STUNTGP_D3D 0x483874
    {"text_stunt_backflip_360", 0x1f},
    // STRING: STUNTGP_D3D 0x48388c
    {"text_stunt_backflip_720", 0x20},
    // STRING: STUNTGP_D3D 0x4838a4
    {"text_stunt_backflip_1080", 0x21},
    // STRING: STUNTGP_D3D 0x4838c0
    {"text_stunt_frontflip_360", 0x22},
    // STRING: STUNTGP_D3D 0x4838dc
    {"text_stunt_frontflip_720", 0x23},
    // STRING: STUNTGP_D3D 0x4838f8
    {"text_stunt_frontflip_1080", 0x24},
    // STRING: STUNTGP_D3D 0x483914
    {"text_stunt_twistleft_360", 0x25},
    // STRING: STUNTGP_D3D 0x483930
    {"text_stunt_twistleft_720", 0x26},
    // STRING: STUNTGP_D3D 0x48394c
    {"text_stunt_twistleft_1080", 0x27},
    // STRING: STUNTGP_D3D 0x483968
    {"text_stunt_twistright_360", 0x28},
    // STRING: STUNTGP_D3D 0x483984
    {"text_stunt_twistright_720", 0x29},
    // STRING: STUNTGP_D3D 0x4839a0
    {"text_stunt_twistright_1080", 0x2a},
    // STRING: STUNTGP_D3D 0x4839bc
    {"text_stunt_loop", 0x2b},
    // STRING: STUNTGP_D3D 0x4839cc
    {"text_challenge_start", 0x2c},
    // STRING: STUNTGP_D3D 0x4839e4
    {"text_challenge_finished", 0x2d},
    // STRING: STUNTGP_D3D 0x4839fc
    {"text_final_lap", 0x2e},
    // STRING: STUNTGP_D3D 0x483a0c
    {"text_stunt_2wheel_front", 0x2f},
    // STRING: STUNTGP_D3D 0x483a24
    {"text_stunt_2wheel_rear", 0x30},
    // STRING: STUNTGP_D3D 0x483a3c
    {"text_stunt_2wheel_left", 0x31},
    // STRING: STUNTGP_D3D 0x483a54
    {"text_stunt_2wheel_right", 0x32},
    // STRING: STUNTGP_D3D 0x483a6c
    {"text_car_cameramode_min", 0x33},
    // STRING: STUNTGP_D3D 0x483a84
    {"text_car_cameramode_med", 0x34},
    // STRING: STUNTGP_D3D 0x483a9c
    {"text_car_cameramode_max", 0x35},
    // STRING: STUNTGP_D3D 0x483ab4
    {"text_car_cameramode_auto", 0x36},
    // STRING: STUNTGP_D3D 0x483ad0
    {"text_trick_start", 0x37},
    // STRING: STUNTGP_D3D 0x483ae4
    {"text_stunt_barrel_roll", 0x38},
    // STRING: STUNTGP_D3D 0x483afc
    {"text_insert_controller", 0x39},
    // STRING: STUNTGP_D3D 0x483b14
    {"text_controller_removed", 0x3a},
    // STRING: STUNTGP_D3D 0x483b2c
    {"text_controller_1P_removed", 0x3b},
    // STRING: STUNTGP_D3D 0x483b48
    {"text_controller_2P_removed", 0x3c},
    // STRING: STUNTGP_D3D 0x483b64
    {"text_controller_3P_removed", 0x3d},
    // STRING: STUNTGP_D3D 0x483b80
    {"text_controller_4P_removed", 0x3e},
    // STRING: STUNTGP_D3D 0x483b9c
    {"text_controller_A_removed", 0x3f},
    // STRING: STUNTGP_D3D 0x483bb8
    {"text_controller_B_removed", 0x40},
    // STRING: STUNTGP_D3D 0x483bd4
    {"text_insert_controller_port_a", 0x41},
    // STRING: STUNTGP_D3D 0x483bf4
    {"text_insert_controller_port_b", 0x42},
    // STRING: STUNTGP_D3D 0x483c14
    {"text_insert_controller_port_c", 0x43},
    // STRING: STUNTGP_D3D 0x483c34
    {"text_insert_controller_port_d", 0x44},
    // STRING: STUNTGP_D3D 0x483c54
    {"text_insert_controller_port_1", 0x45},
    // STRING: STUNTGP_D3D 0x483c74
    {"text_insert_controller_port_2", 0x46},
    // STRING: STUNTGP_D3D 0x483c94
    {"text_insert_cd", 0x47},
    // STRING: STUNTGP_D3D 0x483ca4
    {"text_readerror", 0x48},
    // STRING: STUNTGP_D3D 0x483cb4
    {"text_paused", 0x49},
    // STRING: STUNTGP_D3D 0x483cc0
    {"text_stunt_powerslide", 0x4a},
    // STRING: STUNTGP_D3D 0x483cd8
    {"text_stunt_slide", 0x4b},
    // STRING: STUNTGP_D3D 0x483cec
    {"text_stunt_grind", 0x4c},
    // STRING: STUNTGP_D3D 0x483d00
    {"text_stunt_hop", 0x4d},
    // STRING: STUNTGP_D3D 0x483d10
    {"text_stunt_air", 0x4e},
    // STRING: STUNTGP_D3D 0x483d20
    {"text_stunt_bigair", 0x4f},
    // STRING: STUNTGP_D3D 0x483d34
    {"text_stunt_blastoff", 0x50},
    // STRING: STUNTGP_D3D 0x483d48
    {"text_stunt_nosedown", 0x51},
    // STRING: STUNTGP_D3D 0x483d5c
    {"text_stunt_noseup", 0x52},
    // STRING: STUNTGP_D3D 0x483d70
    {"text_stunt_twistleft", 0x53},
    // STRING: STUNTGP_D3D 0x483d88
    {"text_stunt_twistright", 0x54},
    // STRING: STUNTGP_D3D 0x483da0
    {"text_stunt_twistcombo", 0x55},
    // STRING: STUNTGP_D3D 0x483db8
    {"text_stunt_freestyle", 0x56},
    // STRING: STUNTGP_D3D 0x483dd0
    {"text_stunt_freestylecombo", 0x57},
    // STRING: STUNTGP_D3D 0x483dec
    {"text_stunt_stream", 0x58},
    // STRING: STUNTGP_D3D 0x483e00
    {"text_stunt_longstream", 0x59},
    // STRING: STUNTGP_D3D 0x483e18
    {"text_stunt_flip", 0x5a},
    // STRING: STUNTGP_D3D 0x483e28
    {"text_stunt_halftwistleft", 0x5b},
    // STRING: STUNTGP_D3D 0x483e44
    {"text_stunt_halftwistright", 0x5c},
    // STRING: STUNTGP_D3D 0x483e60
    {"text_stunt_burnrubber", 0x5d},
    // STRING: STUNTGP_D3D 0x483e78
    {"text_stunt_smartstart", 0x5e},
    // STRING: STUNTGP_D3D 0x483e90
    {"text_press_enter", 0x5f},
    // STRING: STUNTGP_D3D 0x483ea4
    {"text_press_start", 0x60},
    // STRING: STUNTGP_D3D 0x483eb8
    {"text_challenge_hurry", 0x61},
    // STRING: STUNTGP_D3D 0x483ed0
    {"text_timetrial_start", 0x62},
    // STRING: STUNTGP_D3D 0x483ee8
    {"text_player_1_paused", 0x63},
    // STRING: STUNTGP_D3D 0x483f00
    {"text_player_2_paused", 0x64},
    // STRING: STUNTGP_D3D 0x483f18
    {"text_player_3_paused", 0x65},
    // STRING: STUNTGP_D3D 0x483f30
    {"text_player_4_paused", 0x66},
    // STRING: STUNTGP_D3D 0x483f48
    {"text_controller_removed_dc", 0x67},
    // STRING: STUNTGP_D3D 0x483f64
    {"text_demo_play", 0x68},
    {NULL, 0},
};

// Free space left in the string pool; strings are packed downwards from its end.
// GLOBAL: STUNTGP_D3D 0x4835dc
int g_4835dc = 0x3000;

// GLOBAL: STUNTGP_D3D 0x4835e0
int g_4835e0 = 1;

struct GameplayKey
{
    const char *name;
    float scale;
    int id;
};

// Entries are removed as they are matched, so the file is only parsed once.
// GLOBAL: STUNTGP_D3D 0x482718
int g_482718 = 1;

// GLOBAL: STUNTGP_D3D 0x48271c
int g_48271c = 0x94;

// GLOBAL: STUNTGP_D3D 0x482720
TextKey g_482720[37] = {
    // STRING: STUNTGP_D3D 0x482848
    {"score_backflip_360", 0x1},
    // STRING: STUNTGP_D3D 0x48285c
    {"score_backflip_720", 0x2},
    // STRING: STUNTGP_D3D 0x482870
    {"score_backflip_1080", 0x3},
    // STRING: STUNTGP_D3D 0x482884
    {"score_frontflip_360", 0x4},
    // STRING: STUNTGP_D3D 0x482898
    {"score_frontflip_720", 0x5},
    // STRING: STUNTGP_D3D 0x4828ac
    {"score_frontflip_1080", 0x6},
    // STRING: STUNTGP_D3D 0x4828c4
    {"score_twistright_360", 0x7},
    // STRING: STUNTGP_D3D 0x4828dc
    {"score_twistright_720", 0x8},
    // STRING: STUNTGP_D3D 0x4828f4
    {"score_twistright_1080", 0x9},
    // STRING: STUNTGP_D3D 0x48290c
    {"score_twistleft_360", 0xa},
    // STRING: STUNTGP_D3D 0x482920
    {"score_twistleft_720", 0xb},
    // STRING: STUNTGP_D3D 0x482934
    {"score_twistleft_1080", 0xc},
    // STRING: STUNTGP_D3D 0x48294c
    {"score_noseup", 0xd},
    // STRING: STUNTGP_D3D 0x48295c
    {"score_nosedown", 0xe},
    // STRING: STUNTGP_D3D 0x48296c
    {"score_halftwist_left", 0xf},
    // STRING: STUNTGP_D3D 0x482984
    {"score_halftwist_right", 0x10},
    // STRING: STUNTGP_D3D 0x48299c
    {"score_twist_combo", 0x11},
    // STRING: STUNTGP_D3D 0x4829b0
    {"score_flip_combo", 0x12},
    // STRING: STUNTGP_D3D 0x4829c4
    {"score_freestyle", 0x13},
    // STRING: STUNTGP_D3D 0x4829d4
    {"score_freestyle_combo", 0x14},
    // STRING: STUNTGP_D3D 0x4829ec
    {"score_slide", 0x15},
    // STRING: STUNTGP_D3D 0x4829f8
    {"score_powerslide", 0x16},
    // STRING: STUNTGP_D3D 0x482a0c
    {"score_stream", 0x17},
    // STRING: STUNTGP_D3D 0x482a1c
    {"score_superstream", 0x18},
    // STRING: STUNTGP_D3D 0x482a30
    {"score_trickstart", 0x19},
    // STRING: STUNTGP_D3D 0x482a44
    {"score_barrelroll", 0x1a},
    // STRING: STUNTGP_D3D 0x482a58
    {"score_grind", 0x1b},
    // STRING: STUNTGP_D3D 0x482a64
    {"score_flightheight_1", 0x1c},
    // STRING: STUNTGP_D3D 0x482a7c
    {"score_flightheight_2", 0x1d},
    // STRING: STUNTGP_D3D 0x482a94
    {"score_flightheight_3", 0x1e},
    // STRING: STUNTGP_D3D 0x482aac
    {"score_flightheight_4", 0x1f},
    // STRING: STUNTGP_D3D 0x482ac4
    {"score_loopdeloop", 0x20},
    // STRING: STUNTGP_D3D 0x482ad8
    {"score_twowheel_left", 0x21},
    // STRING: STUNTGP_D3D 0x482aec
    {"score_twowheel_right", 0x22},
    // STRING: STUNTGP_D3D 0x482b04
    {"score_twowheel_front", 0x23},
    // STRING: STUNTGP_D3D 0x482b1c
    {"score_twowheel_rear", 0x24},
    {NULL, 0},
};

// GLOBAL: STUNTGP_D3D 0x482f38
int g_482f38 = 1;

// GLOBAL: STUNTGP_D3D 0x482f3c
int g_482f3c = 0x7c;

// GLOBAL: STUNTGP_D3D 0x482f40
GameplayKey g_482f40[31] = {
    // STRING: STUNTGP_D3D 0x4830b4
    {"human_replace_energy", 10.0f, 0x1},
    // STRING: STUNTGP_D3D 0x4830cc
    {"human_stunt_energy_award", 1.0f, 0x2},
    // STRING: STUNTGP_D3D 0x4830e8
    {"cpu_replace_energy", 10.0f, 0x3},
    // STRING: STUNTGP_D3D 0x4830fc
    {"cpu_stunt_energy_award", 1.0f, 0x4},
    // STRING: STUNTGP_D3D 0x483114
    {"car_pitlane_speed", 0.4629629850387573f, 0x5},
    // STRING: STUNTGP_D3D 0x483128
    {"car_pitlane_recharge_total", 10.0f, 0x6},
    // STRING: STUNTGP_D3D 0x483144
    {"car_victorylap_speed", 0.4629629850387573f, 0x7},
    // STRING: STUNTGP_D3D 0x48315c
    {"car_rollingstart_speed", 0.4629629850387573f, 0x8},
    // STRING: STUNTGP_D3D 0x483174
    {"cpu_skill_collision_nrg_scale", 0.009999999776482582f, 0x9},
    // STRING: STUNTGP_D3D 0x483194
    {"cpu_skill_engine_nrg_scale", 0.009999999776482582f, 0xa},
    // STRING: STUNTGP_D3D 0x4831b0
    {"cpu_skill_boost_nrg_scale", 0.009999999776482582f, 0xb},
    // STRING: STUNTGP_D3D 0x4831cc
    {"cpu_skill_boostusage_scale", 0.009999999776482582f, 0xc},
    // STRING: STUNTGP_D3D 0x4831e8
    {"cpu_skill_engine_torque_scale", 0.009999999776482582f, 0xd},
    // STRING: STUNTGP_D3D 0x483208
    {"cpu_skill_aerodrag_scale", 0.009999999776482582f, 0xe},
    // STRING: STUNTGP_D3D 0x483224
    {"cpu_skill_torquemap3_select", 1.0f, 0xf},
    // STRING: STUNTGP_D3D 0x483240
    {"cpu_skill_torquemap2_select", 1.0f, 0x10},
    // STRING: STUNTGP_D3D 0x48325c
    {"cpu_skill_torquemap1_select", 1.0f, 0x11},
    // STRING: STUNTGP_D3D 0x483278
    {"cpu_catchup_distance_behind_max", 100.0f, 0x12},
    // STRING: STUNTGP_D3D 0x483298
    {"cpu_catchup_distance_behind_skill_maxsub", 0.009999999776482582f, 0x13},
    // STRING: STUNTGP_D3D 0x4832c4
    {"cpu_catchup_distance_ahead_max", 100.0f, 0x14},
    // STRING: STUNTGP_D3D 0x4832e4
    {"cpu_catchup_distance_ahead_skill_maxsub", 0.009999999776482582f, 0x15},
    // STRING: STUNTGP_D3D 0x48330c
    {"cpu_catchup_setup_scale", 0.009999999776482582f, 0x16},
    // STRING: STUNTGP_D3D 0x483324
    {"human_catchup_distance_behind_max", 100.0f, 0x17},
    // STRING: STUNTGP_D3D 0x483348
    {"human_catchup_setup_scale", 0.009999999776482582f, 0x18},
    // STRING: STUNTGP_D3D 0x483364
    {"collision_energy_min", 10.0f, 0x19},
    // STRING: STUNTGP_D3D 0x48337c
    {"collision_energy_max", 10.0f, 0x1a},
    // STRING: STUNTGP_D3D 0x483394
    {"collision_energy_scale", 1.0f, 0x1b},
    // STRING: STUNTGP_D3D 0x4833ac
    {"collision_energy_impact_limit", 10.0f, 0x1c},
    // STRING: STUNTGP_D3D 0x4833cc
    {"collision_energy_impact_timedelay", 60.0f, 0x1d},
    // STRING: STUNTGP_D3D 0x4833f0
    {"cpu_autobraking_disable", 1.0f, 0x1e},
    {NULL, 0, 0},
};

// GLOBAL: STUNTGP_D3D 0x60d688
int g_60d688[37];

// GLOBAL: STUNTGP_D3D 0x60f2d0
float g_60f2d0[31];

// GLOBAL: STUNTGP_D3D 0x60f350
TextKey g_60f350[105];

// GLOBAL: STUNTGP_D3D 0x60f6a0
char g_60f6a0[0x3000];

// GLOBAL: STUNTGP_D3D 0x6127a0
char *g_6127a0[105];

// GLOBAL: STUNTGP_D3D 0x612944
int g_612944;

// FUNCTION: STUNTGP_D3D 0x443bd0
void Scores_Load()
{
    char key[64];
    char value[256];
    int pos = 0;
    int count = 0;
    char *text;

    memset(g_60d688, 0, sizeof(g_60d688));
    while (g_482720[count].name)
    {
        count++;
    }
    // STRING: STUNTGP_D3D 0x482b30
    text = Csv_Load("Config\\Scores.csv");
    while (Csv_ReadField(key, text, &pos))
    {
        if (!Csv_ReadField(value, text, &pos))
        {
            break;
        }
        while (text[pos] != 0 && text[pos] != '\n')
        {
            pos++;
        }
        Csv_SkipBlankLines(text, &pos);
        count = Scores_Assign(key, value, count);
    }
    free(text);
    g_482718 = 0;
}

// FUNCTION: STUNTGP_D3D 0x443ca0
int Scores_Assign(char *key, char *value, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(g_482720[i].name, key) == 0)
        {
            g_60d688[g_482720[i].id] = Scores_Parse(value);
            for (; i < count - 1; i++)
            {
                g_482720[i] = g_482720[i + 1];
            }
            return count - 1;
        }
    }
    return count;
}

// FUNCTION: STUNTGP_D3D 0x443d50
int Scores_Parse(char *str)
{
    g_48271c -= 4;
    if (g_48271c < 0)
    {
        return 0;
    }
    return atol(str);
}

// FUNCTION: STUNTGP_D3D 0x443d70
void Scores_LoadIfNeeded()
{
    if (g_482718)
    {
        Scores_Load();
    }
}

// FUNCTION: STUNTGP_D3D 0x443d80
void FUN_443d80()
{
    g_612948.unk001c = 1;
    g_612948.unk0020 = 1;
}

// GLOBAL: STUNTGP_D3D 0x60d71c
int g_60d71c;

void FUN_449c60();

// FUNCTION: STUNTGP_D3D 0x443d90
void FUN_443d90()
{
    Car *car = g_4d5bb8;
    memset(&car->race, 0, 0x70);
    car->race.unk1c = 0;
    car->race.unk30 = 0;
    car->race.unk4c[0] = 0;
    car->race.unk04 = 0;
    car->race.unk4c[7] = 0;
    g_60d71c = 0;
    FUN_449c60();
}

// FUNCTION: STUNTGP_D3D 0x445610
void FUN_445610()
{
}

// FUNCTION: STUNTGP_D3D 0x445620
void Gameplay_Load()
{
    char key[64];
    char value[256];
    int pos = 0;
    int count = 0;
    char *text;

    memset(g_60f2d0, 0, sizeof(g_60f2d0));
    while (g_482f40[count].name)
    {
        count++;
    }
    // STRING: STUNTGP_D3D 0x483408
    text = Csv_Load("Config\\Gameplay.csv");
    while (Csv_ReadField(key, text, &pos))
    {
        if (!Csv_ReadField(value, text, &pos))
        {
            break;
        }
        while (text[pos] != 0 && text[pos] != '\n')
        {
            pos++;
        }
        Csv_SkipBlankLines(text, &pos);
        count = Gameplay_Assign(key, value, count);
    }
    free(text);
    g_482f38 = 0;
}

// FUNCTION: STUNTGP_D3D 0x4456f0
int Gameplay_Assign(char *key, char *value, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(g_482f40[i].name, key) == 0)
        {
            g_60f2d0[g_482f40[i].id] = Gameplay_Parse(value, &g_482f3c) * g_482f40[i].scale;
            for (; i < count - 1; i++)
            {
                g_482f40[i] = g_482f40[i + 1];
            }
            return count - 1;
        }
    }
    return count;
}

// FUNCTION: STUNTGP_D3D 0x4457c0
float Gameplay_Parse(char *str, int *pool)
{
    *pool -= 4;
    if (*pool < 0)
    {
        return 0.0f;
    }
    float result = atof(str);
    return result;
}

// FUNCTION: STUNTGP_D3D 0x4457e0
void Gameplay_LoadIfNeeded()
{
    if (g_482f38)
    {
        Gameplay_Load();
        FUN_445610();
    }
}

struct ScreenTile
{
    float x;
    float y;
    float width;
    float height;
};

// GLOBAL: STUNTGP_D3D 0x4834e0
ScreenTile g_4834e0[4] = {
    {0.0f, 0.0f, 256.0f, 256.0f},
    {256.0f, 0.0f, 256.0f, 256.0f},
    {0.0f, 256.0f, 256.0f, 224.0f},
    {256.0f, 256.0f, 256.0f, 224.0f},
};

// Draws a full-screen picture from four consecutive 256x256 textures.
// FUNCTION: STUNTGP_D3D 0x445800
void FUN_445800()
{
    int texture = g_612948.unk8ce0;
    memset(&g_spriteDesc, 0, sizeof(g_spriteDesc));
    g_spriteDesc.flags = 2;
    g_spriteDesc.z = 0.94f;
    g_spriteDesc.u0 = 1.0f;
    g_spriteDesc.v0 = 1.0f;
    g_spriteDesc.u1 = 1020.0f;
    g_spriteDesc.v1 = 1020.0f;
    g_spriteDesc.blendMode = 0x20;
    ScreenTile *tile = g_4834e0;
    for (int i = 0; i < 4; i++, tile++)
    {
        g_spriteDesc.x = tile->x + 64.0f;
        g_spriteDesc.y = tile->y;
        g_spriteDesc.width = tile->width;
        g_spriteDesc.height = tile->height;
        g_spriteDesc.texture = texture;
        FUN_432e00(&g_spriteDesc);
        texture++;
    }
}

void FUN_432a60();
void FUN_433ee0();
void FUN_4328c0(int color);
void FUN_42e420();
void FUN_442a00();
void FUN_442a20();
void FUN_431a80();
void FUN_433f20();

// FUNCTION: STUNTGP_D3D 0x4458b0
void FUN_4458b0()
{
    g_612948.frameCount++;
    FUN_432a60();
    FUN_433ee0();
    FUN_4328c0(0);
    FUN_42e420();
    FUN_442a00();
    FUN_445800();
    FUN_442a20();
    FUN_431a80();
    FUN_433f20();
}

// FUNCTION: STUNTGP_D3D 0x4458f0
void FUN_4458f0()
{
    FUN_442490();
    while (g_612948.unk03b8 < g_612948.unk03bc)
    {
        FUN_442be0();
        FUN_441ec0();
        memcpy(g_62dcf0, g_62d480, sizeof(g_62dcf0));
    }
}

// FUNCTION: STUNTGP_D3D 0x445ae0
int Csv_SkipBlankLines(char *text, int *pos)
{
    int newline = 0;
    for (;;)
    {
        char c = text[*pos];
        if (!Csv_IsBlank(c) && !Csv_IsNewline(c))
        {
            return newline;
        }
        if (Csv_IsNewline(c))
        {
            newline = 1;
        }
        (*pos)++;
    }
}

// FUNCTION: STUNTGP_D3D 0x445b40
int Csv_IsBlank(char c)
{
    if (c == ' ' || c == '\t')
    {
        return 1;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x445b60
int Csv_IsNewline(char c)
{
    if (c == '\r' || c == '\n')
    {
        return 1;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x445b80
int Csv_ReadField(char *out, char *text, int *pos)
{
    int len = 0;
    out[0] = 0;
    while (Csv_IsBlank(text[*pos]))
    {
        (*pos)++;
    }
    if (text[*pos] == 0)
    {
        return 0;
    }
    if (text[*pos] == '"')
    {
        (*pos)++;
        while (text[*pos] != '"' && text[*pos] != 0)
        {
            out[len++] = text[*pos];
            (*pos)++;
        }
        if (text[*pos] != '"')
        {
            return 0;
        }
        (*pos)++;
    }
    else
    {
        while (text[*pos] != ',' && !Csv_IsNewline(text[*pos]) && text[*pos] != 0)
        {
            out[len++] = text[*pos];
            (*pos)++;
        }
    }
    out[len] = 0;
    if (text[*pos] == ',')
    {
        (*pos)++;
    }
    return len;
}

// FUNCTION: STUNTGP_D3D 0x445c60
int Csv_ReadInt(int *value, char *text, int *pos)
{
    int len = Csv_ReadField(g_6126a0, text, pos);
    // STRING: STUNTGP_D3D 0x483f74
    if (sscanf(g_6126a0, "%d", value) == 1)
    {
        return len;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x445ca0
char *Csv_Load(char *name)
{
    char path[256];

    // STRING: STUNTGP_D3D 0x483f78
    sprintf(path, "%s\\%s", g_GameDirectory, name);
    int size = size_of_file(path);
    if (size <= 0)
    {
        return NULL;
    }
    char *text = (char *)malloc(size + 1);
    bload(path, text, size);
    text[size] = 0;
    return text;
}

// FUNCTION: STUNTGP_D3D 0x445d10
void Text_InitKeys()
{
    int i = 0;
    while (c_46e780[i].name)
    {
        g_60f350[i] = c_46e780[i];
        i++;
    }
    g_60f350[i] = c_46e780[i];
}

// FUNCTION: STUNTGP_D3D 0x445d70
void Text_LoadLanguage(int language)
{
    char key[64];
    char value[256];
    int pos = 0;
    int count = 0;
    char *text;

    memset(g_6127a0, 0, sizeof(g_6127a0));
    Text_InitKeys();
    while (g_60f350[count].name)
    {
        count++;
    }
    // STRING: STUNTGP_D3D 0x483f80
    text = Csv_Load("Config\\gametext.csv");
    while (Csv_ReadField(key, text, &pos))
    {
        for (int column = 0; column != language; column++)
        {
            if (!Csv_ReadField(value, text, &pos))
            {
                break;
            }
        }
        while (text[pos] != 0 && text[pos] != '\n')
        {
            pos++;
        }
        Csv_SkipBlankLines(text, &pos);
        count = Text_Assign(key, value, count);
    }
    free(text);
    g_612944 = language;
}

// FUNCTION: STUNTGP_D3D 0x445e60
int Text_Assign(char *key, char *value, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(g_60f350[i].name, key) == 0)
        {
            g_6127a0[g_60f350[i].id] = Text_AddString(value);
            for (; i < count - 1; i++)
            {
                g_60f350[i] = g_60f350[i + 1];
            }
            return count - 1;
        }
    }
    return count;
}

// FUNCTION: STUNTGP_D3D 0x445f10
char *Text_AddString(char *str)
{
    g_4835dc -= strlen(str) + 1;
    if (g_4835dc < 0)
    {
        return NULL;
    }
    char *dest = &g_60f6a0[g_4835dc];
    strcpy(dest, str);
    return dest;
}

// FUNCTION: STUNTGP_D3D 0x445f70
void FUN_445f70(int value)
{
    g_4835e0 = value;
}

// FUNCTION: STUNTGP_D3D 0x445f80
void FUN_445f80()
{
    if (g_4835e0 != g_612944)
    {
        Text_LoadLanguage(g_4835e0);
    }
}
