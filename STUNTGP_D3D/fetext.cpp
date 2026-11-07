#include "fetext.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gametext.h"
#include "globals.h"
#include "sprite.h"
#include "Game/GameEngine/MenuUpdate.h"
#include "Game/GameEngine/io_wad.h"

// Front-end string table, copied to g_606860 before each language load.
// GLOBAL: STUNTGP_D3D 0x479ac0
TextKey g_feTextKeys[732] = {
    // STRING: STUNTGP_D3D 0x47b1a4
    {"feText_Version", 0x1},
    // STRING: STUNTGP_D3D 0x47b1b4
    {"feText_Copyright", 0x2},
    // STRING: STUNTGP_D3D 0x47b1c8
    {"feText_InfoTrack", 0x22},
    // STRING: STUNTGP_D3D 0x47b1dc
    {"feText_InfoGhost", 0x23},
    // STRING: STUNTGP_D3D 0x47b1f0
    {"feText_InfoRecords", 0x24},
    // STRING: STUNTGP_D3D 0x47b204
    {"feText_InfoLap", 0x25},
    // STRING: STUNTGP_D3D 0x47b214
    {"feText_InfoRace", 0x26},
    // STRING: STUNTGP_D3D 0x47b224
    {"feText_InfoStunt", 0x27},
    // STRING: STUNTGP_D3D 0x47b238
    {"feText_Result1st", 0x3},
    // STRING: STUNTGP_D3D 0x47b24c
    {"feText_Result2nd", 0x4},
    // STRING: STUNTGP_D3D 0x47b260
    {"feText_Result3rd", 0x5},
    // STRING: STUNTGP_D3D 0x47b274
    {"feText_Result4th", 0x6},
    // STRING: STUNTGP_D3D 0x47b288
    {"feText_Result5th", 0x7},
    // STRING: STUNTGP_D3D 0x47b29c
    {"feText_Result6th", 0x8},
    // STRING: STUNTGP_D3D 0x47b2b0
    {"feText_ArcadePos", 0x9},
    // STRING: STUNTGP_D3D 0x47b2c4
    {"feText_ArcadeName", 0xa},
    // STRING: STUNTGP_D3D 0x47b2d8
    {"feText_ArcadeLap", 0xb},
    // STRING: STUNTGP_D3D 0x47b2ec
    {"feText_ArcadeAero", 0xc},
    // STRING: STUNTGP_D3D 0x47b300
    {"feText_ArcadeRace", 0xd},
    // STRING: STUNTGP_D3D 0x47b314
    {"feText_ArcadeScore", 0xe},
    // STRING: STUNTGP_D3D 0x47b328
    {"feText_ArcadeAwardPosition", 0xf},
    // STRING: STUNTGP_D3D 0x47b344
    {"feText_ArcadeAwardLap", 0x10},
    // STRING: STUNTGP_D3D 0x47b35c
    {"feText_ArcadeAwardRace", 0x11},
    // STRING: STUNTGP_D3D 0x47b374
    {"feText_ArcadeAwardStunt", 0x12},
    // STRING: STUNTGP_D3D 0x47b38c
    {"feText_ArcadeAwardAeroMiles", 0x13},
    // STRING: STUNTGP_D3D 0x47b3a8
    {"feText_AreYouSure", 0x14},
    // STRING: STUNTGP_D3D 0x47b3bc
    {"feText_Yes", 0x15},
    // STRING: STUNTGP_D3D 0x47b3c8
    {"feText_No", 0x16},
    // STRING: STUNTGP_D3D 0x47b3d4
    {"feText_Ok", 0x17},
    // STRING: STUNTGP_D3D 0x47b3e0
    {"feText_Race", 0x18},
    // STRING: STUNTGP_D3D 0x47b3ec
    {"feText_Quit", 0x19},
    // STRING: STUNTGP_D3D 0x47b3f8
    {"feText_Next", 0x1a},
    // STRING: STUNTGP_D3D 0x47b404
    {"feText_Dollars", 0x1b},
    // STRING: STUNTGP_D3D 0x47b414
    {"feText_Stunt", 0x1c},
    // STRING: STUNTGP_D3D 0x47b424
    {"feText_Grip", 0x1d},
    // STRING: STUNTGP_D3D 0x47b430
    {"feText_Power", 0x1e},
    // STRING: STUNTGP_D3D 0x47b440
    {"feText_PlayerUP", 0x1f},
    // STRING: STUNTGP_D3D 0x47b450
    {"feText_GhostLoad", 0x20},
    // STRING: STUNTGP_D3D 0x47b464
    {"feText_GhostSave", 0x21},
    // STRING: STUNTGP_D3D 0x47b478
    {"feText_TitleContinueKeyboard", 0x28},
    // STRING: STUNTGP_D3D 0x47b498
    {"feText_TitleContinueJoyPad", 0x29},
    // STRING: STUNTGP_D3D 0x47b4b4
    {"feText_TeamTitle", 0x2a},
    // STRING: STUNTGP_D3D 0x47b4c8
    {"feText_TeamHlp", 0x2b},
    // STRING: STUNTGP_D3D 0x47b4d8
    {"feText_SlotTitle", 0x2c},
    // STRING: STUNTGP_D3D 0x47b4ec
    {"feText_SlotContinueStr", 0x2d},
    // STRING: STUNTGP_D3D 0x47b504
    {"feText_SlotNewStr", 0x2e},
    // STRING: STUNTGP_D3D 0x47b518
    {"feText_SlotName1", 0x2f},
    // STRING: STUNTGP_D3D 0x47b52c
    {"feText_SlotName2", 0x30},
    // STRING: STUNTGP_D3D 0x47b540
    {"feText_SlotName3", 0x31},
    // STRING: STUNTGP_D3D 0x47b554
    {"feText_SlotName4", 0x32},
    // STRING: STUNTGP_D3D 0x47b568
    {"feText_SlotName5", 0x33},
    // STRING: STUNTGP_D3D 0x47b57c
    {"feText_SlotName6", 0x34},
    // STRING: STUNTGP_D3D 0x47b590
    {"feText_SlotName7", 0x35},
    // STRING: STUNTGP_D3D 0x47b5a4
    {"feText_SlotName8", 0x36},
    // STRING: STUNTGP_D3D 0x47b5b8
    {"feText_SlotFree", 0x37},
    // STRING: STUNTGP_D3D 0x47b5c8
    {"feText_SlotRace", 0x38},
    // STRING: STUNTGP_D3D 0x47b5d8
    {"feText_SlotScore", 0x39},
    // STRING: STUNTGP_D3D 0x47b5ec
    {"feText_SlotAction", 0x3a},
    // STRING: STUNTGP_D3D 0x47b600
    {"feText_SlotConfirm", 0x3b},
    // STRING: STUNTGP_D3D 0x47b614
    {"feText_SlotHelpEmpty", 0x3c},
    // STRING: STUNTGP_D3D 0x47b62c
    {"feText_SlotHelpInUse", 0x3d},
    // STRING: STUNTGP_D3D 0x47b644
    {"feText_MainTitle", 0x3e},
    // STRING: STUNTGP_D3D 0x47b658
    {"feText_MainSingleStr", 0x3f},
    // STRING: STUNTGP_D3D 0x47b670
    {"feText_MainSingleHlp", 0x40},
    // STRING: STUNTGP_D3D 0x47b688
    {"feText_MainMultiStr", 0x41},
    // STRING: STUNTGP_D3D 0x47b69c
    {"feText_MainMultiHlp", 0x42},
    // STRING: STUNTGP_D3D 0x47b6b0
    {"feText_MainCatalogueStr", 0x43},
    // STRING: STUNTGP_D3D 0x47b6c8
    {"feText_MainCatalogueHlp", 0x44},
    // STRING: STUNTGP_D3D 0x47b6e0
    {"feText_MainRecordsStr", 0x45},
    // STRING: STUNTGP_D3D 0x47b6f8
    {"feText_MainRecordsHlp", 0x46},
    // STRING: STUNTGP_D3D 0x47b710
    {"feText_MainOptionStr", 0x47},
    // STRING: STUNTGP_D3D 0x47b728
    {"feText_MainOptionHlp", 0x48},
    // STRING: STUNTGP_D3D 0x47b740
    {"feText_CampaignTitle", 0x9b},
    // STRING: STUNTGP_D3D 0x47b758
    {"feText_CampaignFirstRaceStr", 0x9c},
    // STRING: STUNTGP_D3D 0x47b774
    {"feText_CampaignNextRaceStr", 0x9d},
    // STRING: STUNTGP_D3D 0x47b790
    {"feText_CampaignRaceHlp", 0x9e},
    // STRING: STUNTGP_D3D 0x47b7a8
    {"feText_CampaignModifyStr", 0x9f},
    // STRING: STUNTGP_D3D 0x47b7c4
    {"feText_CampaignModifyHlp", 0xa0},
    // STRING: STUNTGP_D3D 0x47b7e0
    {"feText_CampaignChangeStr", 0xa1},
    // STRING: STUNTGP_D3D 0x47b7fc
    {"feText_CampaignChangeHlp", 0xa2},
    // STRING: STUNTGP_D3D 0x47b818
    {"feText_CampaignSaveStr", 0xa3},
    // STRING: STUNTGP_D3D 0x47b830
    {"feText_CampaignSaveHlp", 0xa4},
    // STRING: STUNTGP_D3D 0x47b848
    {"feText_CampaignQuitStr", 0xa5},
    // STRING: STUNTGP_D3D 0x47b860
    {"feText_CampaignQuitHlp", 0xa6},
    // STRING: STUNTGP_D3D 0x47b878
    {"feText_CampaignStandings", 0xa7},
    // STRING: STUNTGP_D3D 0x47b894
    {"feText_CampaignStatus", 0xa8},
    // STRING: STUNTGP_D3D 0x47b8ac
    {"feText_CampaignCPU", 0xa9},
    // STRING: STUNTGP_D3D 0x47b8c0
    {"feText_CampaignNAME", 0xaa},
    // STRING: STUNTGP_D3D 0x47b8d4
    {"feText_CampaignTEAM", 0xab},
    // STRING: STUNTGP_D3D 0x47b8e8
    {"feText_CampaignWON", 0xac},
    // STRING: STUNTGP_D3D 0x47b8fc
    {"feText_CampaignSCORE", 0xad},
    // STRING: STUNTGP_D3D 0x47b914
    {"feText_CampaignSTART", 0xae},
    // STRING: STUNTGP_D3D 0x47b92c
    {"feText_CampaignFunds", 0xaf},
    // STRING: STUNTGP_D3D 0x47b944
    {"feText_CampaignVehicle", 0xb0},
    // STRING: STUNTGP_D3D 0x47b95c
    {"feText_OptionsTitle", 0x49},
    // STRING: STUNTGP_D3D 0x47b970
    {"feText_OptionsCFGTitle", 0x4a},
    // STRING: STUNTGP_D3D 0x47b988
    {"feText_OptionsCFGStr", 0x4b},
    // STRING: STUNTGP_D3D 0x47b9a0
    {"feText_OptionsCFGHlp", 0x4c},
    // STRING: STUNTGP_D3D 0x47b9b8
    {"feText_OptionsSNDTitle", 0x4d},
    // STRING: STUNTGP_D3D 0x47b9d0
    {"feText_OptionsSNDStr", 0x4e},
    // STRING: STUNTGP_D3D 0x47b9e8
    {"feText_OptionsSNDHlp", 0x4f},
    // STRING: STUNTGP_D3D 0x47ba00
    {"feText_OptionsVIDTitle", 0x50},
    // STRING: STUNTGP_D3D 0x47ba18
    {"feText_OptionsVIDStr", 0x51},
    // STRING: STUNTGP_D3D 0x47ba30
    {"feText_OptionsVIDHlp", 0x52},
    // STRING: STUNTGP_D3D 0x47ba48
    {"feText_OptionsCTLTitle", 0x53},
    // STRING: STUNTGP_D3D 0x47ba60
    {"feText_OptionsCTLStr", 0x54},
    // STRING: STUNTGP_D3D 0x47ba78
    {"feText_OptionsCTLHlp", 0x55},
    // STRING: STUNTGP_D3D 0x47ba90
    {"feText_OptionsLoadStr", 0x56},
    // STRING: STUNTGP_D3D 0x47baa8
    {"feText_OptionsLoadHlp", 0x57},
    // STRING: STUNTGP_D3D 0x47bac0
    {"feText_OptionsSaveStr", 0x58},
    // STRING: STUNTGP_D3D 0x47bad8
    {"feText_OptionsSaveHlp", 0x59},
    // STRING: STUNTGP_D3D 0x47baf0
    {"feText_OptionsAutoOnStr", 0x5c},
    // STRING: STUNTGP_D3D 0x47bb08
    {"feText_OptionsAutoOffStr", 0x5d},
    // STRING: STUNTGP_D3D 0x47bb24
    {"feText_OptionsAutoHlp", 0x5e},
    // STRING: STUNTGP_D3D 0x47bb3c
    {"feText_OptionsResetStr", 0x5a},
    // STRING: STUNTGP_D3D 0x47bb54
    {"feText_OptionsResetHlp", 0x5b},
    // STRING: STUNTGP_D3D 0x47bb6c
    {"feText_OptionsLanguageStr", 0x5f},
    // STRING: STUNTGP_D3D 0x47bb88
    {"feText_OptionsLanguageHlp", 0x60},
    // STRING: STUNTGP_D3D 0x47bba4
    {"feText_OptionsEffect00Str", 0x61},
    // STRING: STUNTGP_D3D 0x47bbc0
    {"feText_OptionsEffect01Str", 0x62},
    // STRING: STUNTGP_D3D 0x47bbdc
    {"feText_OptionsEffect02Str", 0x63},
    // STRING: STUNTGP_D3D 0x47bbf8
    {"feText_OptionsEffect03Str", 0x64},
    // STRING: STUNTGP_D3D 0x47bc14
    {"feText_OptionsEffect04Str", 0x65},
    // STRING: STUNTGP_D3D 0x47bc30
    {"feText_OptionsEffect05Str", 0x66},
    // STRING: STUNTGP_D3D 0x47bc4c
    {"feText_OptionsEffect06Str", 0x67},
    // STRING: STUNTGP_D3D 0x47bc68
    {"feText_OptionsEffect07Str", 0x68},
    // STRING: STUNTGP_D3D 0x47bc84
    {"feText_OptionsEffect08Str", 0x69},
    // STRING: STUNTGP_D3D 0x47bca0
    {"feText_OptionsEffect09Str", 0x6a},
    // STRING: STUNTGP_D3D 0x47bcbc
    {"feText_OptionsEffect10Str", 0x6b},
    // STRING: STUNTGP_D3D 0x47bcd8
    {"feText_OptionsEffectHlp", 0x6c},
    // STRING: STUNTGP_D3D 0x47bcf0
    {"feText_OptionsMusic00Str", 0x6d},
    // STRING: STUNTGP_D3D 0x47bd0c
    {"feText_OptionsMusic01Str", 0x6e},
    // STRING: STUNTGP_D3D 0x47bd28
    {"feText_OptionsMusic02Str", 0x6f},
    // STRING: STUNTGP_D3D 0x47bd44
    {"feText_OptionsMusic03Str", 0x70},
    // STRING: STUNTGP_D3D 0x47bd60
    {"feText_OptionsMusic04Str", 0x71},
    // STRING: STUNTGP_D3D 0x47bd7c
    {"feText_OptionsMusic05Str", 0x72},
    // STRING: STUNTGP_D3D 0x47bd98
    {"feText_OptionsMusic06Str", 0x73},
    // STRING: STUNTGP_D3D 0x47bdb4
    {"feText_OptionsMusic07Str", 0x74},
    // STRING: STUNTGP_D3D 0x47bdd0
    {"feText_OptionsMusic08Str", 0x75},
    // STRING: STUNTGP_D3D 0x47bdec
    {"feText_OptionsMusic09Str", 0x76},
    // STRING: STUNTGP_D3D 0x47be08
    {"feText_OptionsMusic10Str", 0x77},
    // STRING: STUNTGP_D3D 0x47be24
    {"feText_OptionsMusicHlp", 0x78},
    // STRING: STUNTGP_D3D 0x47be3c
    {"feText_OptionsDetail00Str", 0x79},
    // STRING: STUNTGP_D3D 0x47be58
    {"feText_OptionsDetail01Str", 0x7a},
    // STRING: STUNTGP_D3D 0x47be74
    {"feText_OptionsDetail02Str", 0x7b},
    // STRING: STUNTGP_D3D 0x47be90
    {"feText_OptionsDetail03Str", 0x7c},
    // STRING: STUNTGP_D3D 0x47beac
    {"feText_OptionsDetail04Str", 0x7d},
    // STRING: STUNTGP_D3D 0x47bec8
    {"feText_OptionsDetail05Str", 0x7e},
    // STRING: STUNTGP_D3D 0x47bee4
    {"feText_OptionsDetail06Str", 0x7f},
    // STRING: STUNTGP_D3D 0x47bf00
    {"feText_OptionsDetail07Str", 0x80},
    // STRING: STUNTGP_D3D 0x47bf1c
    {"feText_OptionsDetail08Str", 0x81},
    // STRING: STUNTGP_D3D 0x47bf38
    {"feText_OptionsDetail09Str", 0x82},
    // STRING: STUNTGP_D3D 0x47bf54
    {"feText_OptionsDetail10Str", 0x83},
    // STRING: STUNTGP_D3D 0x47bf70
    {"feText_OptionsDetailHlp", 0x84},
    // STRING: STUNTGP_D3D 0x47bf88
    {"feText_OptionsStereoOFFStr", 0x85},
    // STRING: STUNTGP_D3D 0x47bfa4
    {"feText_OptionsStereoONStr", 0x86},
    // STRING: STUNTGP_D3D 0x47bfc0
    {"feText_OptionsStereoHlp", 0x87},
    // STRING: STUNTGP_D3D 0x47bfd8
    {"feText_OptionsRefreshStr", 0x8a},
    // STRING: STUNTGP_D3D 0x47bff4
    {"feText_OptionsRefreshHlp", 0x8b},
    // STRING: STUNTGP_D3D 0x47c010
    {"feText_OptionsAlignStr", 0x88},
    // STRING: STUNTGP_D3D 0x47c028
    {"feText_OptionsAlignHlp", 0x89},
    // STRING: STUNTGP_D3D 0x47c040
    {"feText_OptionsBitmapsStr", 0x8c},
    // STRING: STUNTGP_D3D 0x47c05c
    {"feText_OptionsBitmapsHlp", 0x8d},
    // STRING: STUNTGP_D3D 0x47c078
    {"feText_RefreshTitle", 0x8e},
    // STRING: STUNTGP_D3D 0x47c08c
    {"feText_Refresh50Str", 0x8f},
    // STRING: STUNTGP_D3D 0x47c0a0
    {"feText_Refresh50Hlp", 0x90},
    // STRING: STUNTGP_D3D 0x47c0b4
    {"feText_Refresh60Str", 0x91},
    // STRING: STUNTGP_D3D 0x47c0c8
    {"feText_Refresh60Hlp", 0x92},
    // STRING: STUNTGP_D3D 0x47c0dc
    {"feText_RefreshTestStr", 0x93},
    // STRING: STUNTGP_D3D 0x47c0f4
    {"feText_RefreshTestHlp", 0x94},
    // STRING: STUNTGP_D3D 0x47c10c
    {"feText_RefreshTestMIN", 0x95},
    // STRING: STUNTGP_D3D 0x47c124
    {"feText_RefreshTestTitle", 0x96},
    // STRING: STUNTGP_D3D 0x47c13c
    {"feText_RefreshTestWarning", 0x97},
    // STRING: STUNTGP_D3D 0x47c158
    {"feText_RefreshTestTesting", 0x98},
    // STRING: STUNTGP_D3D 0x47c174
    {"feText_RefreshTestResult", 0x99},
    // STRING: STUNTGP_D3D 0x47c190
    {"feText_RefreshTestMAX", 0x9a},
    // STRING: STUNTGP_D3D 0x47c1a8
    {"feText_SingleTitle", 0xb1},
    // STRING: STUNTGP_D3D 0x47c1bc
    {"feText_SingleArcadeStr", 0xb2},
    // STRING: STUNTGP_D3D 0x47c1d4
    {"feText_SingleArcadeHlp", 0xb3},
    // STRING: STUNTGP_D3D 0x47c1ec
    {"feText_SinglePracticeStr", 0xb4},
    // STRING: STUNTGP_D3D 0x47c208
    {"feText_SinglePracticeHlp", 0xb5},
    // STRING: STUNTGP_D3D 0x47c224
    {"feText_SingleTimeTrialStr", 0xb6},
    // STRING: STUNTGP_D3D 0x47c240
    {"feText_SingleTimeTrialHlp", 0xb7},
    // STRING: STUNTGP_D3D 0x47c25c
    {"feText_SingleStuntTrialStr", 0xb8},
    // STRING: STUNTGP_D3D 0x47c278
    {"feText_SingleStuntTrialHlp", 0xb9},
    // STRING: STUNTGP_D3D 0x47c294
    {"feText_SingleCampaign", 0xba},
    // STRING: STUNTGP_D3D 0x47c2ac
    {"feText_SingleCampaignHlp", 0xbb},
    // STRING: STUNTGP_D3D 0x47c2c8
    {"feText_MultiTitle", 0xbc},
    // STRING: STUNTGP_D3D 0x47c2dc
    {"feText_MultiRaceStr", 0xbd},
    // STRING: STUNTGP_D3D 0x47c2f0
    {"feText_MultiRaceHlp", 0xbe},
    // STRING: STUNTGP_D3D 0x47c304
    {"feText_MultiTournamentStr", 0xbf},
    // STRING: STUNTGP_D3D 0x47c320
    {"feText_MultiTournamentHlp", 0xc0},
    // STRING: STUNTGP_D3D 0x47c33c
    {"feText_PadsTitle", 0xc1},
    // STRING: STUNTGP_D3D 0x47c350
    {"feText_PadsController1", 0xc2},
    // STRING: STUNTGP_D3D 0x47c368
    {"feText_PadsController2", 0xc3},
    // STRING: STUNTGP_D3D 0x47c380
    {"feText_PadsController3", 0xc4},
    // STRING: STUNTGP_D3D 0x47c398
    {"feText_PadsController4", 0xc5},
    // STRING: STUNTGP_D3D 0x47c3b0
    {"feText_PadsNotConnected", 0xc6},
    // STRING: STUNTGP_D3D 0x47c3c8
    {"feText_PadsPressToJoin", 0xc7},
    // STRING: STUNTGP_D3D 0x47c3e0
    {"feText_PadsPleaseWait", 0xc8},
    // STRING: STUNTGP_D3D 0x47c3f8
    {"feText_PadsNotAvailable", 0xc9},
    // STRING: STUNTGP_D3D 0x47c410
    {"feText_PadsPlayer1", 0xca},
    // STRING: STUNTGP_D3D 0x47c424
    {"feText_PadsPlayer2", 0xcb},
    // STRING: STUNTGP_D3D 0x47c438
    {"feText_PadsPlayer3", 0xcc},
    // STRING: STUNTGP_D3D 0x47c44c
    {"feText_PadsPlayer4", 0xcd},
    // STRING: STUNTGP_D3D 0x47c460
    {"feText_PadsRequired", 0xce},
    // STRING: STUNTGP_D3D 0x47c474
    {"feText_PadsRequiredSequential", 0xcf},
    // STRING: STUNTGP_D3D 0x47c494
    {"feText_PadsHlp", 0xd0},
    // STRING: STUNTGP_D3D 0x47c4a4
    {"feText_CatalogTitle", 0xd1},
    // STRING: STUNTGP_D3D 0x47c4b8
    {"feText_CatalogBatteriesStr", 0xd2},
    // STRING: STUNTGP_D3D 0x47c4d4
    {"feText_CatalogTyresStr", 0xd3},
    // STRING: STUNTGP_D3D 0x47c4ec
    {"feText_CatalogHornsStr", 0xd4},
    // STRING: STUNTGP_D3D 0x47c504
    {"feText_CatalogBMSStr", 0xd5},
    // STRING: STUNTGP_D3D 0x47c51c
    {"feText_CatalogEnginesStr", 0xd6},
    // STRING: STUNTGP_D3D 0x47c538
    {"feText_CatalogSuspensionStr", 0xd7},
    // STRING: STUNTGP_D3D 0x47c554
    {"feText_CatalogGearsStr", 0xd8},
    // STRING: STUNTGP_D3D 0x47c56c
    {"feText_CatalogDriveStr", 0xd9},
    // STRING: STUNTGP_D3D 0x47c584
    {"feText_CatalogBrakesStr", 0xda},
    // STRING: STUNTGP_D3D 0x47c59c
    {"feText_CatalogBoostStr", 0xdb},
    // STRING: STUNTGP_D3D 0x47c5b4
    {"feText_CatalogChassisStr", 0xdc},
    // STRING: STUNTGP_D3D 0x47c5d0
    {"feText_CatalogCarsStr", 0xdd},
    // STRING: STUNTGP_D3D 0x47c5e8
    {"feText_CatalogTracksStr", 0xde},
    // STRING: STUNTGP_D3D 0x47c600
    {"feText_ModifyTitle", 0xdf},
    // STRING: STUNTGP_D3D 0x47c614
    {"feText_ModifyHlp", 0xe0},
    // STRING: STUNTGP_D3D 0x47c628
    {"feText_ModifyUpHlp", 0xe1},
    // STRING: STUNTGP_D3D 0x47c63c
    {"feText_ModifyDnHlp", 0xe2},
    // STRING: STUNTGP_D3D 0x47c650
    {"feText_ModifyCashHlp", 0xe3},
    // STRING: STUNTGP_D3D 0x47c668
    {"feText_ModifyComponent", 0xe4},
    // STRING: STUNTGP_D3D 0x47c680
    {"feText_ModifyCostNew", 0xe5},
    // STRING: STUNTGP_D3D 0x47c698
    {"feText_ModifySaleValue", 0xe6},
    // STRING: STUNTGP_D3D 0x47c6b0
    {"feText_ModifyBalance", 0xe7},
    // STRING: STUNTGP_D3D 0x47c6c8
    {"feText_ModifyRefund", 0xe8},
    // STRING: STUNTGP_D3D 0x47c6dc
    {"feText_BatteryName01", 0xe9},
    // STRING: STUNTGP_D3D 0x47c6f4
    {"feText_BatteryName02", 0xea},
    // STRING: STUNTGP_D3D 0x47c70c
    {"feText_BatteryName03", 0xeb},
    // STRING: STUNTGP_D3D 0x47c724
    {"feText_BatteryName04", 0xec},
    // STRING: STUNTGP_D3D 0x47c73c
    {"feText_BatteryName05", 0xed},
    // STRING: STUNTGP_D3D 0x47c754
    {"feText_BrakesName01", 0xee},
    // STRING: STUNTGP_D3D 0x47c768
    {"feText_BrakesName02", 0xef},
    // STRING: STUNTGP_D3D 0x47c77c
    {"feText_BrakesName03", 0xf0},
    // STRING: STUNTGP_D3D 0x47c790
    {"feText_BrakesName04", 0xf1},
    // STRING: STUNTGP_D3D 0x47c7a4
    {"feText_BrakesName05", 0xf2},
    // STRING: STUNTGP_D3D 0x47c7b8
    {"feText_ChassisName01", 0xf3},
    // STRING: STUNTGP_D3D 0x47c7d0
    {"feText_ChassisName02", 0xf4},
    // STRING: STUNTGP_D3D 0x47c7e8
    {"feText_ChassisName03", 0xf5},
    // STRING: STUNTGP_D3D 0x47c800
    {"feText_ChassisName04", 0xf6},
    // STRING: STUNTGP_D3D 0x47c818
    {"feText_ChassisName05", 0xf7},
    // STRING: STUNTGP_D3D 0x47c830
    {"feText_EngineName01", 0xf8},
    // STRING: STUNTGP_D3D 0x47c844
    {"feText_EngineName02", 0xf9},
    // STRING: STUNTGP_D3D 0x47c858
    {"feText_EngineName03", 0xfa},
    // STRING: STUNTGP_D3D 0x47c86c
    {"feText_EngineName04", 0xfb},
    // STRING: STUNTGP_D3D 0x47c880
    {"feText_EngineName05", 0xfc},
    // STRING: STUNTGP_D3D 0x47c894
    {"feText_GearsName01", 0xfd},
    // STRING: STUNTGP_D3D 0x47c8a8
    {"feText_GearsName02", 0xfe},
    // STRING: STUNTGP_D3D 0x47c8bc
    {"feText_GearsName03", 0xff},
    // STRING: STUNTGP_D3D 0x47c8d0
    {"feText_GearsName04", 0x100},
    // STRING: STUNTGP_D3D 0x47c8e4
    {"feText_GearsName05", 0x101},
    // STRING: STUNTGP_D3D 0x47c8f8
    {"feText_HornName01", 0x102},
    // STRING: STUNTGP_D3D 0x47c90c
    {"feText_HornName02", 0x103},
    // STRING: STUNTGP_D3D 0x47c920
    {"feText_HornName03", 0x104},
    // STRING: STUNTGP_D3D 0x47c934
    {"feText_HornName04", 0x105},
    // STRING: STUNTGP_D3D 0x47c948
    {"feText_HornName05", 0x106},
    // STRING: STUNTGP_D3D 0x47c95c
    {"feText_ShocksName01", 0x107},
    // STRING: STUNTGP_D3D 0x47c970
    {"feText_ShocksName02", 0x108},
    // STRING: STUNTGP_D3D 0x47c984
    {"feText_ShocksName03", 0x109},
    // STRING: STUNTGP_D3D 0x47c998
    {"feText_ShocksName04", 0x10a},
    // STRING: STUNTGP_D3D 0x47c9ac
    {"feText_ShocksName05", 0x10b},
    // STRING: STUNTGP_D3D 0x47c9c0
    {"feText_BMSName01", 0x10c},
    // STRING: STUNTGP_D3D 0x47c9d4
    {"feText_BMSName02", 0x10d},
    // STRING: STUNTGP_D3D 0x47c9e8
    {"feText_BMSName03", 0x10e},
    // STRING: STUNTGP_D3D 0x47c9fc
    {"feText_BMSName04", 0x10f},
    // STRING: STUNTGP_D3D 0x47ca10
    {"feText_BMSName05", 0x110},
    // STRING: STUNTGP_D3D 0x47ca24
    {"feText_TyresName01", 0x111},
    // STRING: STUNTGP_D3D 0x47ca38
    {"feText_TyresName02", 0x112},
    // STRING: STUNTGP_D3D 0x47ca4c
    {"feText_TyresName03", 0x113},
    // STRING: STUNTGP_D3D 0x47ca60
    {"feText_TyresName04", 0x114},
    // STRING: STUNTGP_D3D 0x47ca74
    {"feText_TyresName05", 0x115},
    // STRING: STUNTGP_D3D 0x47ca88
    {"feText_BoostName01", 0x116},
    // STRING: STUNTGP_D3D 0x47ca9c
    {"feText_BoostName02", 0x117},
    // STRING: STUNTGP_D3D 0x47cab0
    {"feText_BoostName03", 0x118},
    // STRING: STUNTGP_D3D 0x47cac4
    {"feText_BoostName04", 0x119},
    // STRING: STUNTGP_D3D 0x47cad8
    {"feText_BoostName05", 0x11a},
    // STRING: STUNTGP_D3D 0x47caec
    {"feText_DriveName01", 0x11b},
    // STRING: STUNTGP_D3D 0x47cb00
    {"feText_DriveName02", 0x11c},
    // STRING: STUNTGP_D3D 0x47cb14
    {"feText_DriveName03", 0x11d},
    // STRING: STUNTGP_D3D 0x47cb28
    {"feText_ComponentInfoMIN", 0x11e},
    // STRING: STUNTGP_D3D 0x47cb40
    {"feText_BatteryInfo01", 0x11f},
    // STRING: STUNTGP_D3D 0x47cb58
    {"feText_BatteryInfo02", 0x120},
    // STRING: STUNTGP_D3D 0x47cb70
    {"feText_BatteryInfo03", 0x121},
    // STRING: STUNTGP_D3D 0x47cb88
    {"feText_BatteryInfo04", 0x122},
    // STRING: STUNTGP_D3D 0x47cba0
    {"feText_BatteryInfo05", 0x123},
    // STRING: STUNTGP_D3D 0x47cbb8
    {"feText_BrakesInfo01", 0x124},
    // STRING: STUNTGP_D3D 0x47cbcc
    {"feText_BrakesInfo02", 0x125},
    // STRING: STUNTGP_D3D 0x47cbe0
    {"feText_BrakesInfo03", 0x126},
    // STRING: STUNTGP_D3D 0x47cbf4
    {"feText_BrakesInfo04", 0x127},
    // STRING: STUNTGP_D3D 0x47cc08
    {"feText_BrakesInfo05", 0x128},
    // STRING: STUNTGP_D3D 0x47cc1c
    {"feText_ChassisInfo01", 0x129},
    // STRING: STUNTGP_D3D 0x47cc34
    {"feText_ChassisInfo02", 0x12a},
    // STRING: STUNTGP_D3D 0x47cc4c
    {"feText_ChassisInfo03", 0x12b},
    // STRING: STUNTGP_D3D 0x47cc64
    {"feText_ChassisInfo04", 0x12c},
    // STRING: STUNTGP_D3D 0x47cc7c
    {"feText_ChassisInfo05", 0x12d},
    // STRING: STUNTGP_D3D 0x47cc94
    {"feText_EngineInfo01", 0x12e},
    // STRING: STUNTGP_D3D 0x47cca8
    {"feText_EngineInfo02", 0x12f},
    // STRING: STUNTGP_D3D 0x47ccbc
    {"feText_EngineInfo03", 0x130},
    // STRING: STUNTGP_D3D 0x47ccd0
    {"feText_EngineInfo04", 0x131},
    // STRING: STUNTGP_D3D 0x47cce4
    {"feText_EngineInfo05", 0x132},
    // STRING: STUNTGP_D3D 0x47ccf8
    {"feText_GearsInfo01", 0x133},
    // STRING: STUNTGP_D3D 0x47cd0c
    {"feText_GearsInfo02", 0x134},
    // STRING: STUNTGP_D3D 0x47cd20
    {"feText_GearsInfo03", 0x135},
    // STRING: STUNTGP_D3D 0x47cd34
    {"feText_GearsInfo04", 0x136},
    // STRING: STUNTGP_D3D 0x47cd48
    {"feText_GearsInfo05", 0x137},
    // STRING: STUNTGP_D3D 0x47cd5c
    {"feText_HornInfo01", 0x138},
    // STRING: STUNTGP_D3D 0x47cd70
    {"feText_HornInfo02", 0x139},
    // STRING: STUNTGP_D3D 0x47cd84
    {"feText_HornInfo03", 0x13a},
    // STRING: STUNTGP_D3D 0x47cd98
    {"feText_HornInfo04", 0x13b},
    // STRING: STUNTGP_D3D 0x47cdac
    {"feText_HornInfo05", 0x13c},
    // STRING: STUNTGP_D3D 0x47cdc0
    {"feText_ShocksInfo01", 0x13d},
    // STRING: STUNTGP_D3D 0x47cdd4
    {"feText_ShocksInfo02", 0x13e},
    // STRING: STUNTGP_D3D 0x47cde8
    {"feText_ShocksInfo03", 0x13f},
    // STRING: STUNTGP_D3D 0x47cdfc
    {"feText_ShocksInfo04", 0x140},
    // STRING: STUNTGP_D3D 0x47ce10
    {"feText_ShocksInfo05", 0x141},
    // STRING: STUNTGP_D3D 0x47ce24
    {"feText_BMSInfo01", 0x142},
    // STRING: STUNTGP_D3D 0x47ce38
    {"feText_BMSInfo02", 0x143},
    // STRING: STUNTGP_D3D 0x47ce4c
    {"feText_BMSInfo03", 0x144},
    // STRING: STUNTGP_D3D 0x47ce60
    {"feText_BMSInfo04", 0x145},
    // STRING: STUNTGP_D3D 0x47ce74
    {"feText_BMSInfo05", 0x146},
    // STRING: STUNTGP_D3D 0x47ce88
    {"feText_TyresInfo01", 0x147},
    // STRING: STUNTGP_D3D 0x47ce9c
    {"feText_TyresInfo02", 0x148},
    // STRING: STUNTGP_D3D 0x47ceb0
    {"feText_TyresInfo03", 0x149},
    // STRING: STUNTGP_D3D 0x47cec4
    {"feText_TyresInfo04", 0x14a},
    // STRING: STUNTGP_D3D 0x47ced8
    {"feText_TyresInfo05", 0x14b},
    // STRING: STUNTGP_D3D 0x47ceec
    {"feText_BoostInfo01", 0x14c},
    // STRING: STUNTGP_D3D 0x47cf00
    {"feText_BoostInfo02", 0x14d},
    // STRING: STUNTGP_D3D 0x47cf14
    {"feText_BoostInfo03", 0x14e},
    // STRING: STUNTGP_D3D 0x47cf28
    {"feText_BoostInfo04", 0x14f},
    // STRING: STUNTGP_D3D 0x47cf3c
    {"feText_BoostInfo05", 0x150},
    // STRING: STUNTGP_D3D 0x47cf50
    {"feText_DriveInfo01", 0x151},
    // STRING: STUNTGP_D3D 0x47cf64
    {"feText_DriveInfo02", 0x152},
    // STRING: STUNTGP_D3D 0x47cf78
    {"feText_DriveInfo03", 0x153},
    // STRING: STUNTGP_D3D 0x47cf8c
    {"feText_CatCarInfo01", 0x154},
    // STRING: STUNTGP_D3D 0x47cfa0
    {"feText_CatCarInfo02", 0x155},
    // STRING: STUNTGP_D3D 0x47cfb4
    {"feText_CatCarInfo03", 0x156},
    // STRING: STUNTGP_D3D 0x47cfc8
    {"feText_CatCarInfo04", 0x157},
    // STRING: STUNTGP_D3D 0x47cfdc
    {"feText_CatCarInfo05", 0x158},
    // STRING: STUNTGP_D3D 0x47cff0
    {"feText_CatCarInfo06", 0x159},
    // STRING: STUNTGP_D3D 0x47d004
    {"feText_CatCarInfo07", 0x15a},
    // STRING: STUNTGP_D3D 0x47d018
    {"feText_CatCarInfo08", 0x15b},
    // STRING: STUNTGP_D3D 0x47d02c
    {"feText_CatCarInfo09", 0x15c},
    // STRING: STUNTGP_D3D 0x47d040
    {"feText_CatCarInfo10", 0x15d},
    // STRING: STUNTGP_D3D 0x47d054
    {"feText_CatCarInfo11", 0x15e},
    // STRING: STUNTGP_D3D 0x47d068
    {"feText_CatCarInfo12", 0x15f},
    // STRING: STUNTGP_D3D 0x47d07c
    {"feText_CatCarInfo13", 0x160},
    // STRING: STUNTGP_D3D 0x47d090
    {"feText_CatCarInfo14", 0x161},
    // STRING: STUNTGP_D3D 0x47d0a4
    {"feText_CatCarInfo15", 0x162},
    // STRING: STUNTGP_D3D 0x47d0b8
    {"feText_CatCarInfo16", 0x163},
    // STRING: STUNTGP_D3D 0x47d0cc
    {"feText_CatCarInfo17", 0x164},
    // STRING: STUNTGP_D3D 0x47d0e0
    {"feText_CatCarInfo18", 0x165},
    // STRING: STUNTGP_D3D 0x47d0f4
    {"feText_CatCarInfo19", 0x166},
    // STRING: STUNTGP_D3D 0x47d108
    {"feText_CatCarInfo20", 0x167},
    // STRING: STUNTGP_D3D 0x47d11c
    {"feText_CatCarInfoStunt", 0x168},
    // STRING: STUNTGP_D3D 0x47d134
    {"feText_CatTrackInfo01", 0x169},
    // STRING: STUNTGP_D3D 0x47d14c
    {"feText_CatTrackInfo02", 0x16a},
    // STRING: STUNTGP_D3D 0x47d164
    {"feText_CatTrackInfo03", 0x16b},
    // STRING: STUNTGP_D3D 0x47d17c
    {"feText_CatTrackInfo04", 0x16c},
    // STRING: STUNTGP_D3D 0x47d194
    {"feText_CatTrackInfo05", 0x16d},
    // STRING: STUNTGP_D3D 0x47d1ac
    {"feText_CatTrackInfo06", 0x16e},
    // STRING: STUNTGP_D3D 0x47d1c4
    {"feText_CatTrackInfo07", 0x16f},
    // STRING: STUNTGP_D3D 0x47d1dc
    {"feText_CatTrackInfo08", 0x170},
    // STRING: STUNTGP_D3D 0x47d1f4
    {"feText_CatTrackInfo09", 0x171},
    // STRING: STUNTGP_D3D 0x47d20c
    {"feText_CatTrackInfo10", 0x172},
    // STRING: STUNTGP_D3D 0x47d224
    {"feText_CatTrackInfo11", 0x173},
    // STRING: STUNTGP_D3D 0x47d23c
    {"feText_CatTrackInfo12", 0x174},
    // STRING: STUNTGP_D3D 0x47d254
    {"feText_CatTrackInfo13", 0x175},
    // STRING: STUNTGP_D3D 0x47d26c
    {"feText_CatTrackInfo14", 0x176},
    // STRING: STUNTGP_D3D 0x47d284
    {"feText_CatTrackInfo15", 0x177},
    // STRING: STUNTGP_D3D 0x47d29c
    {"feText_CatTrackInfo16", 0x178},
    // STRING: STUNTGP_D3D 0x47d2b4
    {"feText_CatTrackInfo17", 0x179},
    // STRING: STUNTGP_D3D 0x47d2cc
    {"feText_CatTrackInfo18", 0x17a},
    // STRING: STUNTGP_D3D 0x47d2e4
    {"feText_CatTrackInfo19", 0x17b},
    // STRING: STUNTGP_D3D 0x47d2fc
    {"feText_CatTrackInfo20", 0x17c},
    // STRING: STUNTGP_D3D 0x47d314
    {"feText_CatTrackInfo21", 0x17d},
    // STRING: STUNTGP_D3D 0x47d32c
    {"feText_CatTrackInfo22", 0x17e},
    // STRING: STUNTGP_D3D 0x47d344
    {"feText_CatTrackInfo23", 0x17f},
    // STRING: STUNTGP_D3D 0x47d35c
    {"feText_CatTrackInfo24", 0x180},
    // STRING: STUNTGP_D3D 0x47d374
    {"feText_CatTrackInfoStunt", 0x181},
    // STRING: STUNTGP_D3D 0x47d390
    {"feText_ComponentInfoMAX", 0x182},
    // STRING: STUNTGP_D3D 0x47d3a8
    {"feText_EnterNameTitle", 0x183},
    // STRING: STUNTGP_D3D 0x47d3c0
    {"feText_SelectCarTitle", 0x184},
    // STRING: STUNTGP_D3D 0x47d3d8
    {"feText_SelectCarFunds", 0x185},
    // STRING: STUNTGP_D3D 0x47d3f0
    {"feText_SelectCarPrice", 0x186},
    // STRING: STUNTGP_D3D 0x47d408
    {"feText_SelectCarWildWheelsStr", 0x187},
    // STRING: STUNTGP_D3D 0x47d428
    {"feText_SelectCarSpeedDemonsStr", 0x188},
    // STRING: STUNTGP_D3D 0x47d448
    {"feText_SelectCarAeroBlastersStr", 0x189},
    // STRING: STUNTGP_D3D 0x47d468
    {"feText_SelectCarTeamSpecialsStr", 0x18a},
    // STRING: STUNTGP_D3D 0x47d488
    {"feText_CarName01", 0x18b},
    // STRING: STUNTGP_D3D 0x47d49c
    {"feText_CarName02", 0x18c},
    // STRING: STUNTGP_D3D 0x47d4b0
    {"feText_CarName03", 0x18d},
    // STRING: STUNTGP_D3D 0x47d4c4
    {"feText_CarName04", 0x18e},
    // STRING: STUNTGP_D3D 0x47d4d8
    {"feText_CarName05", 0x18f},
    // STRING: STUNTGP_D3D 0x47d4ec
    {"feText_CarName06", 0x190},
    // STRING: STUNTGP_D3D 0x47d500
    {"feText_CarName07", 0x191},
    // STRING: STUNTGP_D3D 0x47d514
    {"feText_CarName08", 0x192},
    // STRING: STUNTGP_D3D 0x47d528
    {"feText_CarName09", 0x193},
    // STRING: STUNTGP_D3D 0x47d53c
    {"feText_CarName10", 0x194},
    // STRING: STUNTGP_D3D 0x47d550
    {"feText_CarName11", 0x195},
    // STRING: STUNTGP_D3D 0x47d564
    {"feText_CarName12", 0x196},
    // STRING: STUNTGP_D3D 0x47d578
    {"feText_CarName13", 0x197},
    // STRING: STUNTGP_D3D 0x47d58c
    {"feText_CarName14", 0x198},
    // STRING: STUNTGP_D3D 0x47d5a0
    {"feText_CarName15", 0x199},
    // STRING: STUNTGP_D3D 0x47d5b4
    {"feText_CarName16", 0x19a},
    // STRING: STUNTGP_D3D 0x47d5c8
    {"feText_CarName17", 0x19b},
    // STRING: STUNTGP_D3D 0x47d5dc
    {"feText_CarName18", 0x19c},
    // STRING: STUNTGP_D3D 0x47d5f0
    {"feText_CarName19", 0x19d},
    // STRING: STUNTGP_D3D 0x47d604
    {"feText_CarName20", 0x19e},
    // STRING: STUNTGP_D3D 0x47d618
    {"feText_CarNameStunt", 0x19f},
    // STRING: STUNTGP_D3D 0x47d62c
    {"feText_CarInfo01", 0x1a0},
    // STRING: STUNTGP_D3D 0x47d640
    {"feText_CarInfo02", 0x1a1},
    // STRING: STUNTGP_D3D 0x47d654
    {"feText_CarInfo03", 0x1a2},
    // STRING: STUNTGP_D3D 0x47d668
    {"feText_CarInfo04", 0x1a3},
    // STRING: STUNTGP_D3D 0x47d67c
    {"feText_CarInfo05", 0x1a4},
    // STRING: STUNTGP_D3D 0x47d690
    {"feText_CarInfo06", 0x1a5},
    // STRING: STUNTGP_D3D 0x47d6a4
    {"feText_CarInfo07", 0x1a6},
    // STRING: STUNTGP_D3D 0x47d6b8
    {"feText_CarInfo08", 0x1a7},
    // STRING: STUNTGP_D3D 0x47d6cc
    {"feText_CarInfo09", 0x1a8},
    // STRING: STUNTGP_D3D 0x47d6e0
    {"feText_CarInfo10", 0x1a9},
    // STRING: STUNTGP_D3D 0x47d6f4
    {"feText_CarInfo11", 0x1aa},
    // STRING: STUNTGP_D3D 0x47d708
    {"feText_CarInfo12", 0x1ab},
    // STRING: STUNTGP_D3D 0x47d71c
    {"feText_CarInfo13", 0x1ac},
    // STRING: STUNTGP_D3D 0x47d730
    {"feText_CarInfo14", 0x1ad},
    // STRING: STUNTGP_D3D 0x47d744
    {"feText_CarInfo15", 0x1ae},
    // STRING: STUNTGP_D3D 0x47d758
    {"feText_CarInfo16", 0x1af},
    // STRING: STUNTGP_D3D 0x47d76c
    {"feText_CarInfo17", 0x1b0},
    // STRING: STUNTGP_D3D 0x47d780
    {"feText_CarInfo18", 0x1b1},
    // STRING: STUNTGP_D3D 0x47d794
    {"feText_CarInfo19", 0x1b2},
    // STRING: STUNTGP_D3D 0x47d7a8
    {"feText_CarInfo20", 0x1b3},
    // STRING: STUNTGP_D3D 0x47d7bc
    {"feText_CarInfoStunt", 0x1b4},
    // STRING: STUNTGP_D3D 0x47d7d0
    {"feText_CarInfoMAX", 0x1b5},
    // STRING: STUNTGP_D3D 0x47d7e4
    {"feText_SelectTrackTitle", 0x1b6},
    // STRING: STUNTGP_D3D 0x47d7fc
    {"feText_SelectTrackTitleSingle", 0x1b7},
    // STRING: STUNTGP_D3D 0x47d81c
    {"feText_TrackName01", 0x1b8},
    // STRING: STUNTGP_D3D 0x47d830
    {"feText_TrackName02", 0x1b9},
    // STRING: STUNTGP_D3D 0x47d844
    {"feText_TrackName03", 0x1ba},
    // STRING: STUNTGP_D3D 0x47d858
    {"feText_TrackName04", 0x1bb},
    // STRING: STUNTGP_D3D 0x47d86c
    {"feText_TrackName05", 0x1bc},
    // STRING: STUNTGP_D3D 0x47d880
    {"feText_TrackName06", 0x1bd},
    // STRING: STUNTGP_D3D 0x47d894
    {"feText_TrackName07", 0x1be},
    // STRING: STUNTGP_D3D 0x47d8a8
    {"feText_TrackName08", 0x1bf},
    // STRING: STUNTGP_D3D 0x47d8bc
    {"feText_TrackName09", 0x1c0},
    // STRING: STUNTGP_D3D 0x47d8d0
    {"feText_TrackName10", 0x1c1},
    // STRING: STUNTGP_D3D 0x47d8e4
    {"feText_TrackName11", 0x1c2},
    // STRING: STUNTGP_D3D 0x47d8f8
    {"feText_TrackName12", 0x1c3},
    // STRING: STUNTGP_D3D 0x47d90c
    {"feText_TrackName13", 0x1c4},
    // STRING: STUNTGP_D3D 0x47d920
    {"feText_TrackName14", 0x1c5},
    // STRING: STUNTGP_D3D 0x47d934
    {"feText_TrackName15", 0x1c6},
    // STRING: STUNTGP_D3D 0x47d948
    {"feText_TrackName16", 0x1c7},
    // STRING: STUNTGP_D3D 0x47d95c
    {"feText_TrackName17", 0x1c8},
    // STRING: STUNTGP_D3D 0x47d970
    {"feText_TrackName18", 0x1c9},
    // STRING: STUNTGP_D3D 0x47d984
    {"feText_TrackName19", 0x1ca},
    // STRING: STUNTGP_D3D 0x47d998
    {"feText_TrackName20", 0x1cb},
    // STRING: STUNTGP_D3D 0x47d9ac
    {"feText_TrackName21", 0x1cc},
    // STRING: STUNTGP_D3D 0x47d9c0
    {"feText_TrackName22", 0x1cd},
    // STRING: STUNTGP_D3D 0x47d9d4
    {"feText_TrackName23", 0x1ce},
    // STRING: STUNTGP_D3D 0x47d9e8
    {"feText_TrackName24", 0x1cf},
    // STRING: STUNTGP_D3D 0x47d9fc
    {"feText_TrackNameStunt", 0x1d0},
    // STRING: STUNTGP_D3D 0x47da14
    {"feText_TrackInfo01", 0x1d1},
    // STRING: STUNTGP_D3D 0x47da28
    {"feText_TrackInfo02", 0x1d2},
    // STRING: STUNTGP_D3D 0x47da3c
    {"feText_TrackInfo03", 0x1d3},
    // STRING: STUNTGP_D3D 0x47da50
    {"feText_TrackInfo04", 0x1d4},
    // STRING: STUNTGP_D3D 0x47da64
    {"feText_TrackInfo05", 0x1d5},
    // STRING: STUNTGP_D3D 0x47da78
    {"feText_TrackInfo06", 0x1d6},
    // STRING: STUNTGP_D3D 0x47da8c
    {"feText_TrackInfo07", 0x1d7},
    // STRING: STUNTGP_D3D 0x47daa0
    {"feText_TrackInfo08", 0x1d8},
    // STRING: STUNTGP_D3D 0x47dab4
    {"feText_TrackInfo09", 0x1d9},
    // STRING: STUNTGP_D3D 0x47dac8
    {"feText_TrackInfo10", 0x1da},
    // STRING: STUNTGP_D3D 0x47dadc
    {"feText_TrackInfo11", 0x1db},
    // STRING: STUNTGP_D3D 0x47daf0
    {"feText_TrackInfo12", 0x1dc},
    // STRING: STUNTGP_D3D 0x47db04
    {"feText_TrackInfo13", 0x1dd},
    // STRING: STUNTGP_D3D 0x47db18
    {"feText_TrackInfo14", 0x1de},
    // STRING: STUNTGP_D3D 0x47db2c
    {"feText_TrackInfo15", 0x1df},
    // STRING: STUNTGP_D3D 0x47db40
    {"feText_TrackInfo16", 0x1e0},
    // STRING: STUNTGP_D3D 0x47db54
    {"feText_TrackInfo17", 0x1e1},
    // STRING: STUNTGP_D3D 0x47db68
    {"feText_TrackInfo18", 0x1e2},
    // STRING: STUNTGP_D3D 0x47db7c
    {"feText_TrackInfo19", 0x1e3},
    // STRING: STUNTGP_D3D 0x47db90
    {"feText_TrackInfo20", 0x1e4},
    // STRING: STUNTGP_D3D 0x47dba4
    {"feText_TrackInfo21", 0x1e5},
    // STRING: STUNTGP_D3D 0x47dbb8
    {"feText_TrackInfo22", 0x1e6},
    // STRING: STUNTGP_D3D 0x47dbcc
    {"feText_TrackInfo23", 0x1e7},
    // STRING: STUNTGP_D3D 0x47dbe0
    {"feText_TrackInfo24", 0x1e8},
    // STRING: STUNTGP_D3D 0x47dbf4
    {"feText_TrackInfoStunt", 0x1e9},
    // STRING: STUNTGP_D3D 0x47dc0c
    {"feText_TrackInfoMAX", 0x1ea},
    // STRING: STUNTGP_D3D 0x47dc20
    {"feText_SponsorName01", 0x1eb},
    // STRING: STUNTGP_D3D 0x47dc38
    {"feText_SponsorName02", 0x1ec},
    // STRING: STUNTGP_D3D 0x47dc50
    {"feText_SponsorName03", 0x1ed},
    // STRING: STUNTGP_D3D 0x47dc68
    {"feText_SponsorName04", 0x1ee},
    // STRING: STUNTGP_D3D 0x47dc80
    {"feText_SponsorName05", 0x1ef},
    // STRING: STUNTGP_D3D 0x47dc98
    {"feText_SponsorName06", 0x1f0},
    // STRING: STUNTGP_D3D 0x47dcb0
    {"feText_SponsorInfoMIN", 0x1f1},
    // STRING: STUNTGP_D3D 0x47dcc8
    {"feText_SponsorInfo01", 0x1f2},
    // STRING: STUNTGP_D3D 0x47dce0
    {"feText_SponsorInfo02", 0x1f3},
    // STRING: STUNTGP_D3D 0x47dcf8
    {"feText_SponsorInfo03", 0x1f4},
    // STRING: STUNTGP_D3D 0x47dd10
    {"feText_SponsorInfo04", 0x1f5},
    // STRING: STUNTGP_D3D 0x47dd28
    {"feText_SponsorInfo05", 0x1f6},
    // STRING: STUNTGP_D3D 0x47dd40
    {"feText_SponsorInfo06", 0x1f7},
    // STRING: STUNTGP_D3D 0x47dd58
    {"feText_SponsorInfoMAX", 0x1f8},
    // STRING: STUNTGP_D3D 0x47dd70
    {"feText_SelectTreeTitle", 0x1f9},
    // STRING: STUNTGP_D3D 0x47dd88
    {"feText_ArcadeResults", 0x1fa},
    // STRING: STUNTGP_D3D 0x47dda0
    {"feText_ArcadeRecords", 0x1fb},
    // STRING: STUNTGP_D3D 0x47ddb8
    {"feText_TimeTrialRecords", 0x1fc},
    // STRING: STUNTGP_D3D 0x47ddd0
    {"feText_StuntTrialRecords", 0x1fd},
    // STRING: STUNTGP_D3D 0x47ddec
    {"feText_UnlockTitle", 0x1fe},
    // STRING: STUNTGP_D3D 0x47de00
    {"feText_LapsShort", 0x1ff},
    // STRING: STUNTGP_D3D 0x47de14
    {"feText_LapsMedium", 0x200},
    // STRING: STUNTGP_D3D 0x47de28
    {"feText_LapsLong", 0x201},
    // STRING: STUNTGP_D3D 0x47de38
    {"feText_DifficultyEasy", 0x202},
    // STRING: STUNTGP_D3D 0x47de50
    {"feText_DifficultyMedium", 0x203},
    // STRING: STUNTGP_D3D 0x47de68
    {"feText_DifficultyHard", 0x204},
    // STRING: STUNTGP_D3D 0x47de80
    {"feText_Opponent0", 0x205},
    // STRING: STUNTGP_D3D 0x47de94
    {"feText_Opponent1", 0x206},
    // STRING: STUNTGP_D3D 0x47dea8
    {"feText_Opponent2", 0x207},
    // STRING: STUNTGP_D3D 0x47debc
    {"feText_Opponent3", 0x208},
    // STRING: STUNTGP_D3D 0x47ded0
    {"feText_Opponent4", 0x209},
    // STRING: STUNTGP_D3D 0x47dee4
    {"feText_Opponent5", 0x20a},
    // STRING: STUNTGP_D3D 0x47def8
    {"feText_LoadSaveMIN", 0x20b},
    // STRING: STUNTGP_D3D 0x47df0c
    {"feText_InitCFG_Title", 0x20c},
    // STRING: STUNTGP_D3D 0x47df24
    {"feText_InitCFG_Quit", 0x237},
    // STRING: STUNTGP_D3D 0x47df38
    {"feText_InitCFG_NoDevice", 0x20d},
    // STRING: STUNTGP_D3D 0x47df50
    {"feText_InitCFG_NotConnected", 0x20e},
    // STRING: STUNTGP_D3D 0x47df6c
    {"feText_InitCFG_NotFormatted", 0x20f},
    // STRING: STUNTGP_D3D 0x47df88
    {"feText_InitCFG_NoSpace", 0x210},
    // STRING: STUNTGP_D3D 0x47dfa0
    {"feText_InitCFG_NoSave", 0x211},
    // STRING: STUNTGP_D3D 0x47dfb8
    {"feText_InitCFG_OK", 0x212},
    // STRING: STUNTGP_D3D 0x47dfcc
    {"feText_LoadCFG_Title", 0x213},
    // STRING: STUNTGP_D3D 0x47dfe4
    {"feText_LoadCFG_Quit", 0x238},
    // STRING: STUNTGP_D3D 0x47dff8
    {"feText_LoadCFG_NoDevice", 0x214},
    // STRING: STUNTGP_D3D 0x47e010
    {"feText_LoadCFG_NotConnected", 0x215},
    // STRING: STUNTGP_D3D 0x47e02c
    {"feText_LoadCFG_NotFormatted", 0x216},
    // STRING: STUNTGP_D3D 0x47e048
    {"feText_LoadCFG_NoSpace", 0x217},
    // STRING: STUNTGP_D3D 0x47e060
    {"feText_LoadCFG_NoSave", 0x218},
    // STRING: STUNTGP_D3D 0x47e078
    {"feText_LoadCFG_OK", 0x219},
    // STRING: STUNTGP_D3D 0x47e08c
    {"feText_SaveCFG_Title", 0x21a},
    // STRING: STUNTGP_D3D 0x47e0a4
    {"feText_SaveCFG_Quit", 0x239},
    // STRING: STUNTGP_D3D 0x47e0b8
    {"feText_SaveCFG_NoDevice", 0x21b},
    // STRING: STUNTGP_D3D 0x47e0d0
    {"feText_SaveCFG_NotConnected", 0x21c},
    // STRING: STUNTGP_D3D 0x47e0ec
    {"feText_SaveCFG_NotFormatted", 0x21d},
    // STRING: STUNTGP_D3D 0x47e108
    {"feText_SaveCFG_NoSpace", 0x21e},
    // STRING: STUNTGP_D3D 0x47e120
    {"feText_SaveCFG_NoSave", 0x21f},
    // STRING: STUNTGP_D3D 0x47e138
    {"feText_SaveCFG_OK", 0x220},
    // STRING: STUNTGP_D3D 0x47e14c
    {"feText_LoadGST_Title", 0x221},
    // STRING: STUNTGP_D3D 0x47e164
    {"feText_LoadGST_Quit", 0x23a},
    // STRING: STUNTGP_D3D 0x47e178
    {"feText_LoadGST_NoDevice", 0x222},
    // STRING: STUNTGP_D3D 0x47e190
    {"feText_LoadGST_NotConnected", 0x223},
    // STRING: STUNTGP_D3D 0x47e1ac
    {"feText_LoadGST_NotFormatted", 0x224},
    // STRING: STUNTGP_D3D 0x47e1c8
    {"feText_LoadGST_NoSpace", 0x225},
    // STRING: STUNTGP_D3D 0x47e1e0
    {"feText_LoadGST_NoSave", 0x226},
    // STRING: STUNTGP_D3D 0x47e1f8
    {"feText_LoadGST_OK", 0x227},
    // STRING: STUNTGP_D3D 0x47e20c
    {"feText_SaveGST_Title", 0x228},
    // STRING: STUNTGP_D3D 0x47e224
    {"feText_SaveGST_Quit", 0x23b},
    // STRING: STUNTGP_D3D 0x47e238
    {"feText_SaveGST_NoDevice", 0x229},
    // STRING: STUNTGP_D3D 0x47e250
    {"feText_SaveGST_NotConnected", 0x22a},
    // STRING: STUNTGP_D3D 0x47e26c
    {"feText_SaveGST_NotFormatted", 0x22b},
    // STRING: STUNTGP_D3D 0x47e288
    {"feText_SaveGST_NoSpace", 0x22c},
    // STRING: STUNTGP_D3D 0x47e2a0
    {"feText_SaveGST_NoSave", 0x22d},
    // STRING: STUNTGP_D3D 0x47e2b8
    {"feText_SaveGST_OK", 0x22e},
    // STRING: STUNTGP_D3D 0x47e2cc
    {"feText_LoadSaveMAX", 0x22f},
    // STRING: STUNTGP_D3D 0x47e2e0
    {"feText_ConfirmMIN", 0x230},
    // STRING: STUNTGP_D3D 0x47e2f4
    {"feText_ConfirmFormat", 0x231},
    // STRING: STUNTGP_D3D 0x47e30c
    {"feText_ConfirmSaveConfig", 0x232},
    // STRING: STUNTGP_D3D 0x47e328
    {"feText_ConfirmLoadConfig", 0x233},
    // STRING: STUNTGP_D3D 0x47e344
    {"feText_ConfirmSaveGhost", 0x234},
    // STRING: STUNTGP_D3D 0x47e35c
    {"feText_ConfirmLoadGhost", 0x235},
    // STRING: STUNTGP_D3D 0x47e374
    {"feText_ConfirmQuit", 0x236},
    // STRING: STUNTGP_D3D 0x47e388
    {"feText_RetryFormat", 0x23c},
    // STRING: STUNTGP_D3D 0x47e39c
    {"feText_RetrySaveConfig", 0x23d},
    // STRING: STUNTGP_D3D 0x47e3b4
    {"feText_RetryLoadConfig", 0x23e},
    // STRING: STUNTGP_D3D 0x47e3cc
    {"feText_RetrySaveGhost", 0x23f},
    // STRING: STUNTGP_D3D 0x47e3e4
    {"feText_RetryLoadGhost", 0x240},
    // STRING: STUNTGP_D3D 0x47e3fc
    {"feText_RetryQuit", 0x241},
    // STRING: STUNTGP_D3D 0x47e410
    {"feText_WarnQuit", 0x242},
    // STRING: STUNTGP_D3D 0x47e420
    {"feText_WarnLoad", 0x243},
    // STRING: STUNTGP_D3D 0x47e430
    {"feText_WarnSave", 0x244},
    // STRING: STUNTGP_D3D 0x47e440
    {"feText_WarnFormat", 0x245},
    // STRING: STUNTGP_D3D 0x47e454
    {"feText_ConfirmMAX", 0x246},
    // STRING: STUNTGP_D3D 0x47e468
    {"feText_ConfigState_NoDevice", 0x247},
    // STRING: STUNTGP_D3D 0x47e484
    {"feText_ConfigState_NotConnected", 0x248},
    // STRING: STUNTGP_D3D 0x47e4a4
    {"feText_ConfigState_NotFormatted", 0x249},
    // STRING: STUNTGP_D3D 0x47e4c4
    {"feText_ConfigState_NoSpace", 0x24a},
    // STRING: STUNTGP_D3D 0x47e4e0
    {"feText_ConfigState_NoSave", 0x24b},
    // STRING: STUNTGP_D3D 0x47e4fc
    {"feText_ConfigState_Saved", 0x24c},
    // STRING: STUNTGP_D3D 0x47e518
    {"feText_GhostState_NoDevice", 0x24d},
    // STRING: STUNTGP_D3D 0x47e534
    {"feText_GhostState_NotConnected", 0x24e},
    // STRING: STUNTGP_D3D 0x47e554
    {"feText_GhostState_NotFormatted", 0x24f},
    // STRING: STUNTGP_D3D 0x47e574
    {"feText_GhostState_NoSpace", 0x250},
    // STRING: STUNTGP_D3D 0x47e590
    {"feText_GhostState_NoSave", 0x251},
    // STRING: STUNTGP_D3D 0x47e5ac
    {"feText_GhostState_Saved", 0x252},
    // STRING: STUNTGP_D3D 0x47e5c4
    {"feText_BlocksFree", 0x253},
    // STRING: STUNTGP_D3D 0x47e5d8
    {"feText_BlocksRequiredFree", 0x254},
    // STRING: STUNTGP_D3D 0x47e5f4
    {"feText_SaveName1", 0x255},
    // STRING: STUNTGP_D3D 0x47e608
    {"feText_SaveName2", 0x256},
    // STRING: STUNTGP_D3D 0x47e61c
    {"feText_SaveName3", 0x257},
    // STRING: STUNTGP_D3D 0x47e630
    {"feText_SaveName4", 0x258},
    // STRING: STUNTGP_D3D 0x47e644
    {"feText_SaveName5", 0x259},
    // STRING: STUNTGP_D3D 0x47e658
    {"feText_SaveName6", 0x25a},
    // STRING: STUNTGP_D3D 0x47e66c
    {"feText_SaveName7", 0x25b},
    // STRING: STUNTGP_D3D 0x47e680
    {"feText_SaveName8", 0x25c},
    // STRING: STUNTGP_D3D 0x47e694
    {"feText_NoControllers", 0x25d},
    // STRING: STUNTGP_D3D 0x47e6ac
    {"feText_ControllerFailed", 0x25e},
    // STRING: STUNTGP_D3D 0x47e6c4
    {"feText_TextSplashMIN", 0x25f},
    // STRING: STUNTGP_D3D 0x47e6dc
    {"feText_TextSplashMAX", 0x26d},
    // STRING: STUNTGP_D3D 0x47e6f4
    {"feText_UnlockSplashMIN", 0x275},
    // STRING: STUNTGP_D3D 0x47e70c
    {"feText_UnlockSplashMAX", 0x27c},
    // STRING: STUNTGP_D3D 0x47e724
    {"feText_stuntteamcashaward", 0x267},
    // STRING: STUNTGP_D3D 0x47e740
    {"feText_stuntprescreen", 0x260},
    // STRING: STUNTGP_D3D 0x47e758
    {"feText_currenthigh", 0x261},
    // STRING: STUNTGP_D3D 0x47e76c
    {"feText_stuntstart", 0x262},
    // STRING: STUNTGP_D3D 0x47e780
    {"feText_carunlockarcade", 0x276},
    // STRING: STUNTGP_D3D 0x47e798
    {"feText_carunlocktimetrial", 0x277},
    // STRING: STUNTGP_D3D 0x47e7b4
    {"feText_carunlockgeneral", 0x278},
    // STRING: STUNTGP_D3D 0x47e7cc
    {"feText_carunlockspecial", 0x279},
    // STRING: STUNTGP_D3D 0x47e7e4
    {"feText_trackunlockarcade", 0x27a},
    // STRING: STUNTGP_D3D 0x47e800
    {"feText_trackunlockarcadetime", 0x27b},
    // STRING: STUNTGP_D3D 0x47e820
    {"feText_Championshippostrace1", 0x27d},
    // STRING: STUNTGP_D3D 0x47e840
    {"feText_Championshippostrace2", 0x27e},
    // STRING: STUNTGP_D3D 0x47e860
    {"feText_Championshippostrace3", 0x27f},
    // STRING: STUNTGP_D3D 0x47e880
    {"feText_Championshippostrace4", 0x280},
    // STRING: STUNTGP_D3D 0x47e8a0
    {"feText_Championshippostrace5", 0x281},
    // STRING: STUNTGP_D3D 0x47e8c0
    {"feText_Championshippostrace6", 0x282},
    // STRING: STUNTGP_D3D 0x47e8e0
    {"feText_championshippointsaward", 0x283},
    // STRING: STUNTGP_D3D 0x47e900
    {"feText_championshipcashaward", 0x284},
    // STRING: STUNTGP_D3D 0x47e920
    {"feText_stuntbonustitle", 0x263},
    // STRING: STUNTGP_D3D 0x47e938
    {"feText_stuntbonusprescreen", 0x264},
    // STRING: STUNTGP_D3D 0x47e954
    {"feText_stuntbonusaward", 0x265},
    // STRING: STUNTGP_D3D 0x47e96c
    {"feText_stuntbonusstart", 0x266},
    // STRING: STUNTGP_D3D 0x47e984
    {"feText_stuntbonuscomplete", 0x268},
    // STRING: STUNTGP_D3D 0x47e9a0
    {"feText_stuntbonuscontinue", 0x269},
    // STRING: STUNTGP_D3D 0x47e9bc
    {"feText_championshipfinalrace", 0x26a},
    // STRING: STUNTGP_D3D 0x47e9dc
    {"feText_championshipfinalaward", 0x26b},
    // STRING: STUNTGP_D3D 0x47e9fc
    {"feText_championshipfinalcontinue", 0x26c},
    // STRING: STUNTGP_D3D 0x47ea20
    {"feText_arcadetop10", 0x285},
    // STRING: STUNTGP_D3D 0x47ea34
    {"feText_recordsexit", 0x286},
    // STRING: STUNTGP_D3D 0x47ea48
    {"feText_timetrialtop10", 0x287},
    // STRING: STUNTGP_D3D 0x47ea60
    {"feText_championshipaltpage", 0x288},
    // STRING: STUNTGP_D3D 0x47ea7c
    {"feText_stuntbowltop10", 0x289},
    // STRING: STUNTGP_D3D 0x47ea94
    {"feText_championshiptop10scores", 0x28a},
    // STRING: STUNTGP_D3D 0x47eab4
    {"feText_championshiptop10cash", 0x28b},
    // STRING: STUNTGP_D3D 0x47ead4
    {"feText_quickracepost", 0x28c},
    // STRING: STUNTGP_D3D 0x47eaec
    {"feText_quickracepostp1", 0x28d},
    // STRING: STUNTGP_D3D 0x47eb04
    {"feText_quickracepostp2", 0x28e},
    // STRING: STUNTGP_D3D 0x47eb1c
    {"feText_quickracepostp3", 0x28f},
    // STRING: STUNTGP_D3D 0x47eb34
    {"feText_quickracepostp4", 0x290},
    // STRING: STUNTGP_D3D 0x47eb4c
    {"feText_quickraceoptions", 0x291},
    // STRING: STUNTGP_D3D 0x47eb64
    {"feText_tournamenttitle", 0x292},
    // STRING: STUNTGP_D3D 0x47eb7c
    {"feText_tournamentcaroption1", 0x293},
    // STRING: STUNTGP_D3D 0x47eb98
    {"feText_tournamentcaroption2", 0x294},
    // STRING: STUNTGP_D3D 0x47ebb4
    {"feText_tournamenttrackoption1", 0x295},
    // STRING: STUNTGP_D3D 0x47ebd4
    {"feText_tournamenttrackoption2", 0x296},
    // STRING: STUNTGP_D3D 0x47ebf4
    {"feText_tournamentlaps1", 0x297},
    // STRING: STUNTGP_D3D 0x47ec0c
    {"feText_tournamentlaps2", 0x298},
    // STRING: STUNTGP_D3D 0x47ec24
    {"feText_tournamentlaps3", 0x299},
    // STRING: STUNTGP_D3D 0x47ec3c
    {"feText_tournamentscoring1", 0x29a},
    // STRING: STUNTGP_D3D 0x47ec58
    {"feText_tournamentscoring2", 0x29b},
    // STRING: STUNTGP_D3D 0x47ec74
    {"feText_tournamentscoring3", 0x29c},
    // STRING: STUNTGP_D3D 0x47ec90
    {"feText_tournamentcpuai1", 0x29d},
    // STRING: STUNTGP_D3D 0x47eca8
    {"feText_tournamentcpuai2", 0x29e},
    // STRING: STUNTGP_D3D 0x47ecc0
    {"feText_tournamentcpuai3", 0x29f},
    // STRING: STUNTGP_D3D 0x47ecd8
    {"feText_tournamentcpuai4", 0x2a0},
    // STRING: STUNTGP_D3D 0x47ecf0
    {"feText_tournamentrace1", 0x2a1},
    // STRING: STUNTGP_D3D 0x47ed08
    {"feText_tournamentrace2", 0x2a2},
    // STRING: STUNTGP_D3D 0x47ed20
    {"feText_tournamentrace3", 0x2a3},
    // STRING: STUNTGP_D3D 0x47ed38
    {"feText_tournamentrace4", 0x2a4},
    // STRING: STUNTGP_D3D 0x47ed50
    {"feText_tournamenttitle1", 0x2a5},
    // STRING: STUNTGP_D3D 0x47ed68
    {"feText_tournamenttitle2", 0x2a6},
    // STRING: STUNTGP_D3D 0x47ed80
    {"feText_tournamenttitle3", 0x2a7},
    // STRING: STUNTGP_D3D 0x47ed98
    {"feText_tournamenttable1", 0x2a8},
    // STRING: STUNTGP_D3D 0x47edb0
    {"feText_tournamenttable2", 0x2a9},
    // STRING: STUNTGP_D3D 0x47edc8
    {"feText_tournamenttablehead", 0x2aa},
    // STRING: STUNTGP_D3D 0x47ede4
    {"feText_tournamenttablehead1", 0x2ab},
    // STRING: STUNTGP_D3D 0x47ee00
    {"feText_tournamenttablehead2", 0x2ac},
    // STRING: STUNTGP_D3D 0x47ee1c
    {"feText_tournamenttablehead3", 0x2ad},
    // STRING: STUNTGP_D3D 0x47ee38
    {"feText_tournamentcontinue", 0x2ae},
    // STRING: STUNTGP_D3D 0x47ee54
    {"feText_tournamentfinal", 0x2af},
    // STRING: STUNTGP_D3D 0x47ee6c
    {"feText_tournamentaward1", 0x2b0},
    // STRING: STUNTGP_D3D 0x47ee84
    {"feText_tournamentaward2", 0x2b1},
    // STRING: STUNTGP_D3D 0x47ee9c
    {"feText_tournamentaward3", 0x2b2},
    // STRING: STUNTGP_D3D 0x47eeb4
    {"feText_tournamentaward4", 0x2b3},
    // STRING: STUNTGP_D3D 0x47eecc
    {"feText_creditstitle", 0x2b4},
    // STRING: STUNTGP_D3D 0x47eee0
    {"feText_creditslist1", 0x2b6},
    // STRING: STUNTGP_D3D 0x47eef4
    {"feText_creditslist2", 0x2b7},
    // STRING: STUNTGP_D3D 0x47ef08
    {"feText_creditslist3", 0x2b8},
    // STRING: STUNTGP_D3D 0x47ef1c
    {"feText_creditslist4", 0x2b9},
    // STRING: STUNTGP_D3D 0x47ef30
    {"feText_creditslist5", 0x2ba},
    // STRING: STUNTGP_D3D 0x47ef44
    {"feText_creditslist6", 0x2bb},
    // STRING: STUNTGP_D3D 0x47ef58
    {"feText_creditslist7", 0x2bc},
    // STRING: STUNTGP_D3D 0x47ef6c
    {"feText_creditslist8", 0x2bd},
    // STRING: STUNTGP_D3D 0x47ef80
    {"feText_creditslist9", 0x2be},
    // STRING: STUNTGP_D3D 0x47ef94
    {"feText_creditslist10", 0x2bf},
    // STRING: STUNTGP_D3D 0x47efac
    {"feText_creditslist11", 0x2c0},
    // STRING: STUNTGP_D3D 0x47efc4
    {"feText_creditslist12", 0x2c1},
    // STRING: STUNTGP_D3D 0x47efdc
    {"feText_creditslist13", 0x2c2},
    // STRING: STUNTGP_D3D 0x47eff4
    {"feText_creditslist14", 0x2c3},
    // STRING: STUNTGP_D3D 0x47f00c
    {"feText_creditslist15", 0x2c4},
    // STRING: STUNTGP_D3D 0x47f024
    {"feText_creditslist16", 0x2c5},
    // STRING: STUNTGP_D3D 0x47f03c
    {"feText_TournamentOptHelp", 0x2c7},
    // STRING: STUNTGP_D3D 0x47f058
    {"feText_ControllerVibrationOFF", 0x2c8},
    // STRING: STUNTGP_D3D 0x47f078
    {"feText_ControllerVibrationON", 0x2c9},
    // STRING: STUNTGP_D3D 0x47f098
    {"feText_RecordsTitle", 0x2ca},
    // STRING: STUNTGP_D3D 0x47f0ac
    {"feText_RecordsHlp", 0x2cb},
    // STRING: STUNTGP_D3D 0x47f0c0
    {"feText_TTRecordsTitle", 0x2cc},
    // STRING: STUNTGP_D3D 0x47f0d8
    {"feText_TTRecordsHlp", 0x2cd},
    // STRING: STUNTGP_D3D 0x47f0ec
    {"feText_CampaignRecordsTitle", 0x2ce},
    // STRING: STUNTGP_D3D 0x47f108
    {"feText_CampaignRecordsHlp", 0x2cf},
    // STRING: STUNTGP_D3D 0x47f124
    {"feText_CampaignScoresStr", 0x2d0},
    // STRING: STUNTGP_D3D 0x47f140
    {"feText_CampaignMoneyStr", 0x2d1},
    // STRING: STUNTGP_D3D 0x47f158
    {"feText_Pads2PressToJoin", 0x2d2},
    // STRING: STUNTGP_D3D 0x47f170
    {"feText_Pads2PleaseWait", 0x2d3},
    // STRING: STUNTGP_D3D 0x47f188
    {"feText_Pads2Player1", 0x2d4},
    // STRING: STUNTGP_D3D 0x47f19c
    {"feText_Pads2Player2", 0x2d5},
    // STRING: STUNTGP_D3D 0x47f1b0
    {"feText_Pads2Player3", 0x2d6},
    // STRING: STUNTGP_D3D 0x47f1c4
    {"feText_Pads2Player4", 0x2d7},
    // STRING: STUNTGP_D3D 0x47f1d8
    {"feText_MainQuitHlp", 0x2d8},
    // STRING: STUNTGP_D3D 0x47f1ec
    {"feText_TournamentEndHlp", 0x2d9},
    // STRING: STUNTGP_D3D 0x47f204
    {"feText_CtrlOptMIN", 0x26e},
    // STRING: STUNTGP_D3D 0x47f218
    {"feText_Controllernote1", 0x26f},
    // STRING: STUNTGP_D3D 0x47f230
    {"feText_Controllernote2", 0x270},
    // STRING: STUNTGP_D3D 0x47f248
    {"feText_Controllernote3", 0x271},
    // STRING: STUNTGP_D3D 0x47f260
    {"feText_Controllernote4", 0x272},
    // STRING: STUNTGP_D3D 0x47f278
    {"feText_Controllernote3PC", 0x273},
    // STRING: STUNTGP_D3D 0x47f294
    {"feText_CtrlOptMAX", 0x274},
    // STRING: STUNTGP_D3D 0x47f2a8
    {"feText_CreditsStr", 0x2da},
    // STRING: STUNTGP_D3D 0x47f2bc
    {"feText_CreditsHlp", 0x2db},
    // STRING: STUNTGP_D3D 0x47f2d0
    {"feText_CreditsMIN", 0x2b5},
    // STRING: STUNTGP_D3D 0x47f2e4
    {"feText_CreditsMAX", 0x2c6},
    {NULL, 0},
};

// Bytes left in g_5ffcc8; strings are carved from its end.
// GLOBAL: STUNTGP_D3D 0x47b1a0
int g_47b1a0 = 0x6000;

// Scratch line for FUN_4409c0.
// GLOBAL: STUNTGP_D3D 0x5ff8c4
char g_5ff8c4[0x400];

// GLOBAL: STUNTGP_D3D 0x5ffcc8
char g_5ffcc8[0x6000];

// Language names for the options menu; entry 0 stays empty.
// GLOBAL: STUNTGP_D3D 0x606838
char *g_606838[9];

// Keys still waiting for a string in the current load.
// GLOBAL: STUNTGP_D3D 0x606860
TextKey g_606860[1000];

// GLOBAL: STUNTGP_D3D 0x6087a4
char g_6087a4[4];

// FUNCTION: STUNTGP_D3D 0x43c520
int FeCsv_SkipBlankLines(char *text, int *pos)
{
    int newline = 0;
    for (;;)
    {
        char c = text[*pos];
        if (!FeCsv_IsBlank(c) && !FeCsv_IsNewline(c))
        {
            return newline;
        }
        if (FeCsv_IsNewline(c))
        {
            newline = 1;
        }
        (*pos)++;
    }
}

// FUNCTION: STUNTGP_D3D 0x43c580
int FeCsv_IsBlank(char c)
{
    if (c == ' ' || c == '\t')
    {
        return 1;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x43c5a0
int FeCsv_IsNewline(char c)
{
    if (c == '\r' || c == '\n')
    {
        return 1;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x43c5c0
int FeCsv_SkipLine(char *text, int *pos)
{
    while (text[*pos] != 0 && !FeCsv_IsNewline(text[*pos]))
    {
        (*pos)++;
    }
    return FeCsv_SkipBlankLines(text, pos);
}

// FUNCTION: STUNTGP_D3D 0x43c680
int FeCsv_ReadField(char *out, char *text, int *pos)
{
    int len = 0;
    out[0] = 0;
    while (FeCsv_IsBlank(text[*pos]))
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
        while (text[*pos] != ',' && !FeCsv_IsNewline(text[*pos]) && text[*pos] != 0)
        {
            out[len++] = text[*pos];
            (*pos)++;
        }
    }
    out[len] = 0;
    while (len > 0 && out[len - 1] == ' ')
    {
        out[--len] = 0;
    }
    if (text[*pos] == ',')
    {
        (*pos)++;
    }
    return len;
}

// FUNCTION: STUNTGP_D3D 0x43c7f0
char *FeCsv_Load(char *name)
{
    char path[256];

    // STRING: STUNTGP_D3D 0x4794e0
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

// Word-wraps text in place by turning spaces into 0xff; returns the line count, or 0 if it does not fit.
// FUNCTION: STUNTGP_D3D 0x4409c0
int FUN_4409c0(char *text, int width, float size, int maxLines)
{
    int lines = 1;
    for (char *p = text; *p; p++)
    {
        if (*p == (char)0xff)
        {
            *p = ' ';
        }
    }
    int start = 0;
    int end = 0;
    for (;;)
    {
        char c = text[end];
        if (c != ' ' && c != '|' && c != 0)
        {
            end++;
            continue;
        }
        memcpy(g_5ff8c4, text + start, end - start);
        g_5ff8c4[end - start] = 0;
        if ((int)(FUN_438910(g_5ff8c4, size) + 0.999999f) >= width)
        {
            int i = end - 1;
            while (i > start && text[i] != ' ')
            {
                i--;
            }
            if (i <= start)
            {
                return 0;
            }
            text[i] = (char)0xff;
            start = i + 1;
            lines++;
            end = start;
        }
        else if (c == '|')
        {
            lines++;
            start = end + 1;
            end++;
        }
        else if (c == 0)
        {
            break;
        }
        else
        {
            end++;
        }
    }
    return lines > maxLines ? 0 : lines;
}

// FUNCTION: STUNTGP_D3D 0x440ae0
void FUN_440ae0()
{
    char token[256];
    int value;
    int i;
    int pos;

    memset(g_feText, 0, sizeof(g_feText));
    pos = 0;
    // STRING: STUNTGP_D3D 0x47f2f8
    g_6087a0 = FeCsv_Load("Setup\\languagePC.csv");
    for (i = 0; i < 9; i++)
    {
        g_606838[i] = g_6087a4;
    }
    g_menuState.languageCount = 0;
    FeCsv_ReadField(token, g_6087a0, &pos);
    for (i = 0; i < 8; i++)
    {
        if (!FeCsv_ReadField(token, g_6087a0, &pos))
        {
            break;
        }
        g_606838[i + 1] = g_menuState.languages[i].name;
        strcpy(g_menuState.languages[i].name, token);
    }
    FeCsv_SkipLine(g_6087a0, &pos);
    g_menuState.languageCount = i;
    FeCsv_ReadField(token, g_6087a0, &pos);
    for (i = 0; i < g_menuState.languageCount; i++)
    {
        FeCsv_ReadField(token, g_6087a0, &pos);
        // STRING: STUNTGP_D3D 0x47f310
        sscanf(token, "%d", &value);
        g_menuState.languages[i].id = value;
    }
}

// Loads the strings of one language; returns its column, or -1 if the id is unknown.
// FUNCTION: STUNTGP_D3D 0x440c40
int FUN_440c40(int id)
{
    char value[320];
    char key[64];
    int language;
    int count;
    int pos;
    int failures;
    int i;

    pos = 0;
    count = 0;
    failures = 0;
    language = -1;
    for (i = 0; i < g_menuState.languageCount; i++)
    {
        if (g_menuState.languages[i].id == id)
        {
            language = i;
            break;
        }
    }
    if (language < 0)
    {
        return -1;
    }
    i = 0;
    while (g_feTextKeys[i].name)
    {
        g_606860[i] = g_feTextKeys[i];
        i++;
    }
    g_47b1a0 = 0x6000;
    memset(g_feText, 0, sizeof(g_feText));
    while (g_606860[count].name)
    {
        count++;
    }
    FeCsv_SkipLine(g_6087a0, &pos);
    FeCsv_SkipLine(g_6087a0, &pos);
    while (FeCsv_ReadField(key, g_6087a0, &pos))
    {
        for (int column = -1; column != language; column++)
        {
            if (!FeCsv_ReadField(value, g_6087a0, &pos))
            {
                break;
            }
        }
        FeCsv_SkipLine(g_6087a0, &pos);
        // STRING: STUNTGP_D3D 0x47f314
        if (memcmp(value, "<>", 3) == 0)
        {
            value[0] = 0;
        }
        count = FeText_Assign(key, value, count);
    }
    for (i = 0x1a0; i < 0x1b5; i++)
    {
        failures += !FUN_4409c0(FUN_441170(i), 0x94, 1.25f, 14);
    }
    for (i = 0x1d1; i < 0x1ea; i++)
    {
        failures += !FUN_4409c0(FUN_441170(i), 0x94, 1.25f, 14);
    }
    for (i = 0x20c; i < 0x22f; i++)
    {
        failures += !FUN_4409c0(FUN_441170(i), 0x21c, 1.5f, 4);
    }
    for (i = 0x231; i < 0x246; i++)
    {
        failures += !FUN_4409c0(FUN_441170(i), 0x15c, 1.5f, 4);
    }
    for (i = 0x11f; i < 0x182; i++)
    {
        failures += !FUN_4409c0(FUN_441170(i), 0x184, 1.5f, 10);
    }
    for (i = 0x1f2; i < 0x1f8; i++)
    {
        failures += !FUN_4409c0(FUN_441170(i), 0x15c, 1.5f, 10);
    }
    for (i = 0x96; i < 0x9a; i++)
    {
        failures += !FUN_4409c0(FUN_441170(i), 0x118, 1.25f, 10);
    }
    for (i = 0x260; i < 0x26d; i++)
    {
        failures += !FUN_4409c0(FUN_441170(i), 0x17c, 1.25f, 10);
    }
    for (i = 0x276; i < 0x27c; i++)
    {
        failures += !FUN_4409c0(FUN_441170(i), 0x1ae, 1.25f, 10);
    }
    for (i = 0x26f; i < 0x274; i++)
    {
        failures += !FUN_4409c0(FUN_441170(i), 0x208, 1.25f, 10);
    }
    FUN_4409c0(FUN_441170(0xce), 0x17c, 1.5f, 6);
    FUN_4409c0(FUN_441170(0xcf), 0x17c, 1.5f, 6);
    FUN_4409c0(FUN_441170(0x3a), 0x15c, 1.5f, 5);
    FUN_4409c0(FUN_441170(0x3b), 0x15c, 1.5f, 5);
    FUN_4409c0(FUN_441170(0x3c), 0x230, 1.5f, 5);
    FUN_4409c0(FUN_441170(0x3d), 0x230, 1.5f, 5);
    FUN_4409c0(FUN_441170(2), 0x258, 1.25f, 5);
    g_menuState.language = id;
    return language;
}

// FUNCTION: STUNTGP_D3D 0x441060
int FeText_Assign(char *key, char *value, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(g_606860[i].name, key) == 0)
        {
            g_feText[g_606860[i].id] = FeText_AddString(value);
            for (; i < count - 1; i++)
            {
                g_606860[i] = g_606860[i + 1];
            }
            return count - 1;
        }
    }
    return count;
}

// FUNCTION: STUNTGP_D3D 0x441110
char *FeText_AddString(char *str)
{
    g_47b1a0 -= strlen(str) + 1;
    if (g_47b1a0 < 0)
    {
        return NULL;
    }
    char *dest = &g_5ffcc8[g_47b1a0];
    strcpy(dest, str);
    return dest;
}
