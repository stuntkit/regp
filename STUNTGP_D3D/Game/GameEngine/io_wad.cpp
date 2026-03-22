#include "io_wad.h"

// TODO: should it be here?
// FUNCTION: STUNTGP_D3D 0x44b170
int FUN_0044b170(char *in)
{
    // start in from the end of GameDirectory and return position of first non '\\' char
    int len = strlen(g_GameDirectory);
    char tmp = in[len];
    int a = len;
    while (tmp == '\\')
    {
        a = len + 1;
        tmp = in[a];
        len++;
    }
    return len;
}

// TODO: should it be here?
// FUNCTION: STUNTGP_D3D 0x44b140
void FUN_0044b140(char *out, char *in)
{
    // get buffer and return filename without doubled '\\\\'
    char tmp = *in;
    while (tmp != '\0')
    {
        if ((tmp == '\\') && (in[1] == '\\'))
        {
            in++;
        }
        tmp = *in;
        in++;
        *out = tmp;
        out++;
        tmp = *in;
    }
    *out = '\0';
    return;
}

// inline int findLast(char *buffer, int len)
// {
//     char tmp = buffer[len];
//     while ((tmp != '\\') && (len > 0))
//     {
//         len--;
//         tmp = buffer[len];
//     }
//     return len;
// }

// inline void skipDoubled(char *buffer, int last)
// {
//     char tmp = buffer[last];
//     int len2 = last;
//     // skip doubled '\\'
//     while (tmp == '\\')
//     {
//         len2++;
//         tmp = buffer[len2];
//     }
//     // return len2;
// }

// TODO: shitty 38%
// FUNCTION: STUNTGP_D3D 0x44b050
void WAD_SplitFileName(char *in, char *a, char *filename)
{
    char buffer[128];
    // char *dwojeczka = a;

    strcpy(buffer, in);
    int len = strlen(buffer) - 1; //-1/-2?

    char tmp = buffer[len];

    // find last '\\'
    while ((tmp != '\\') && (0 < len))
    {
        len--;
        tmp = buffer[len];
    }

    tmp = buffer[len];
    int len2 = len;

    // skip doubled '\\'
    while (tmp == '\\')
    {
        len2++;
        tmp = buffer[len2];
    }

    // tmp = buffer[len2]; // ???? whyy, useless?

    int afterGameDir = FUN_0044b170(buffer);
    FUN_0044b140(filename, buffer + afterGameDir);

    char *orig = a;
    if (len < 0)
    {
        *a = '\0';
    }
    else
    {
        buffer[len] = '\0';
        FUN_0044b140(orig, buffer + afterGameDir);
    }
    orig = a;

    tolower(filename, filename);
    tolower(orig, orig);
    return;
}

// // FUNCTION: STUNTGP_D3D 0x44b260
// int bload(char *param_1, char *param_2, int param_3)
// {
// }

// FUNCTION: STUNTGP_D3D 0x44b3b0
int size_of_file(char *path)
{

    char root[64];
    char filename[64];
    WAD_SplitFileName(path, root, filename);
    // strcmpi(root, point);
    //  array of pointers to strings
    //  pairs of pointers and {NULL, NULL} at the end?
    /*
"sound\\sfx"
"sfx.wad"
"graphics24\\overlays"
"overlay.wad"
"graphics24\\misc"
"misc.wad"
"graphics24\\trackset00"
"tset00.wad"
"graphics24\\trackset01"
"tset01.wad"
"graphics24\\trackset02"
"tset02.wad"
"graphics24\\trackset03"
"tset03.wad"
"graphics24\\trackset04"
"tset04.wad"
"graphics24\\trackset05"
"tset05.wad"
"graphics24\\trackset06"
"tset06.wad"
"graphics24\\cars\\misc"
"carmisc.wad"
"graphics24\\cars\\car1"
"car01.wad"
"graphics24\\cars\\car2"
"car02.wad"
"graphics24\\cars\\car3"
"car03.wad"
"graphics24\\cars\\car4"
"car04.wad"
"graphics24\\cars\\car5"
"car05.wad"
"graphics24\\cars\\car6"
"car06.wad"
"graphics24\\cars\\car7"
"car07.wad"
"graphics24\\cars\\car8"
"car08.wad"
"graphics24\\cars\\car9"
"car09.wad"
"graphics24\\cars\\car10"
"car10.wad"
"graphics24\\cars\\car11"
"car11.wad"
"graphics24\\cars\\car12"
"car12.wad"
"graphics24\\cars\\car13"
"car13.wad"
"graphics24\\cars\\car14"
"car14.wad"
"graphics24\\cars\\car15"
"car15.wad"
"graphics24\\cars\\car16"
"car16.wad"
"graphics24\\cars\\car17"
"car17.wad"
"graphics24\\cars\\car18"
"car18.wad"
"graphics24\\cars\\car19"
"car19.wad"
"graphics24\\cars\\car20"
"car20.wad"
"graphics24\\level1"
"level1.wad"
"graphics24\\level2"
"level2.wad"
"graphics24\\level3"
"level3.wad"
"graphics24\\level4"
"level4.wad"
"graphics24\\level5"
"level5.wad"
"graphics24\\level6"
"level6.wad"
"graphics24\\level7"
"level7.wad"
"graphics24\\level8"
"level8.wad"
"graphics24\\challenge3"
"chall3.wad"
"graphics24\\frontend\\dialog"
"dialog.wad"
"graphics24\\frontend\\tiles"
"tiles.wad"
"graphics24\\frontend\\logos"
"logos.wad"
"graphics24\\frontend\\icons"
"icons.wad"
"graphics24\\frontend\\pads\\pc"
"pads_pc.wad"
"graphics24\\frontend\\pads\\dc"
"pads_dc.wad"
"graphics24\\frontend\\pads\\ps"
"pads_ps.wad"
"graphics24\\frontend\\pages\\
"p_carsa.wad"
"graphics24\\frontend\\pages\\
"p_carsb.wad"
"graphics24\\frontend\\pages\\
"p_catal.wad"
"graphics24\\frontend\\pages\\
"p_spons.wad"
"graphics24\\frontend\\pages\\
"p_title.wad"
"graphics24\\frontend\\pages\\
"p_tracka.wad"
"graphics24\\frontend\\pages\\
"p_trackb.wad"
"graphics24\\frontend\\pages\\
"p_lang.wad"
"graphics24\\frontend\\pages\\
"p_single.wad"
"graphics24\\fonts"
"fonts.wad"
"graphics24\\boot"
"boot.wad"
"graphics24\\loading"
"loading.wad"
"setup"
"setup.wad"
"replays"
"replays.wad"
"config"
"config.wad"
"config\\cams"
"config.wad"
"config\\levels"
"config.wad"
"config\\vehicles"
"config.wad"
*/
    // auto uh = PTR_;

    return 0;
}

// FUNCTION: STUNTGP_D3D 0x44b470
void tolower(char *out, char *in)
{
    char tmp;

    tmp = *in;
    while (tmp != '\0')
    {
        in++;
        if ((tmp >= 'A') && (tmp <= 'Z'))
        {
            tmp += ' ';
        }
        *out = tmp;
        out++;
        tmp = *in;
    }
    *out = '\0';

    return;
}
