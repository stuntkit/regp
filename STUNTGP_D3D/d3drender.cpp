#include "d3drender.h"
#include "common.h"
#include "globals.h"
#include "windowInit.h"

// GLOBAL: STUNTGP_D3D 0x5da1c4
LPDIRECT3DDEVICE3 g_d3dDevice = NULL;

// GLOBAL: STUNTGP_D3D 0x5da1c8
BOOL g_d3dInScene = FALSE;

// GLOBAL: STUNTGP_D3D 0x576bc4
int g_576bc4 = 0;

// GLOBAL: STUNTGP_D3D 0x576bc8
int g_576bc8 = 0;

// GLOBAL: STUNTGP_D3D 0x576bd8
int g_576bd8 = 0;

// GLOBAL: STUNTGP_D3D 0x576be0
int g_576be0 = 0;

// GLOBAL: STUNTGP_D3D 0x5d91b4
int *g_5d91b4 = NULL;

// GLOBAL: STUNTGP_D3D 0x592054
int g_592054 = 0;

// GLOBAL: STUNTGP_D3D 0x592058
int g_592058 = 0;

// GLOBAL: STUNTGP_D3D 0x59205c
int g_59205c = 0;

// GLOBAL: STUNTGP_D3D 0x592060
int g_592060 = 0;

// GLOBAL: STUNTGP_D3D 0x592064
int g_592064 = 0;

// GLOBAL: STUNTGP_D3D 0x477ccc
float g_477ccc = 128.0f;

// GLOBAL: STUNTGP_D3D 0x61c5f0
OverlayPoly *g_61c5f0 = NULL;

// GLOBAL: STUNTGP_D3D 0x61c604
DWORD g_61c604 = 0;

// GLOBAL: STUNTGP_D3D 0x61c5e4
int g_61c5e4 = 0;

// GLOBAL: STUNTGP_D3D 0x6227d4
TextureSlot g_6227d4[1];

// FUNCTION: STUNTGP_D3D 0x431a80
void FUN_431a80()
{
    FUN_423430();
}

// FUNCTION: STUNTGP_D3D 0x432190
void FUN_432190(int mode)
{
    switch (mode)
    {
    case 0x58:
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
        break;
    case 0x70:
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_DESTCOLOR);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
        break;
    case 0x60:
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
        break;
    case 0x48:
    case 0x50:
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
        break;
    case 0x20:
    case 0x28:
    default:
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
        break;
    }
    g_d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
}

// FUNCTION: STUNTGP_D3D 0x4328c0
void FUN_4328c0(int color)
{
    D3DTLVERTEX2 v[8];
    BOOL inScene = g_d3dInScene;
    FUN_433ee0();

    float width = (float)g_576bc4;
    float height = (float)g_576bc8;
    D3DCOLOR c = RGBA_MAKE(GetRValue(color), GetGValue(color), GetBValue(color), 0xff);

    v[0].sx = 0.0f;
    v[0].sy = 0.0f;
    v[0].sz = 0.0f;
    v[0].rhw = 0.999f;
    v[0].color = c;
    v[0].specular = 0xff000000;

    v[1].sx = width;
    v[1].sy = 0.0f;
    v[1].sz = 0.0f;
    v[1].rhw = 0.999f;
    v[1].color = c;
    v[1].specular = 0xff000000;

    v[2].sx = width;
    v[2].sy = height;
    v[2].sz = 0.0f;
    v[2].rhw = 0.999f;
    v[2].color = c;
    v[2].specular = 0xff000000;

    v[3].sx = 0.0f;
    v[3].sy = height;
    v[3].sz = 0.0f;
    v[3].rhw = 0.999f;
    v[3].color = c;
    v[3].specular = 0xff000000;

    FUN_432190(0x28);
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_ALWAYS);
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, FALSE);
    g_d3dDevice->SetTexture(0, NULL);
    g_d3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, FVF_TLVERTEX2, v, 4, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTLIGHT);
    FUN_432a90();
    if (g_592054 == 1 || g_592058 == 1)
    {
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, TRUE);
    }
    if (!inScene)
    {
        FUN_433f20();
    }
}

// FUNCTION: STUNTGP_D3D 0x432a60
void FUN_432a60()
{
    int res = g_surface->Flip(NULL, DDFLIP_WAIT);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
}

// FUNCTION: STUNTGP_D3D 0x432a90
void FUN_432a90()
{
    if (g_5d91b4[25])
    {
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_GREATEREQUAL);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
        g_477ccc = 128.0f;
        g_59205c = 1;
        g_592060 = 1;
        g_592064 = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x432f60
void FUN_432f60()
{
    D3DTLVERTEX2 v[8];
    DWORD mode;
    DWORD i;
    OverlayPoly *poly;

    g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 1);
    poly = g_61c5f0;
    mode = 0xffffffff;
    for (i = 0; i < g_61c604; i++)
    {
        DWORD alpha = poly->alpha << 24;
        OverlayVertex *src = poly->verts;
        D3DTLVERTEX2 *dst = v;
        for (DWORD j = 0; j < poly->numVerts; j++)
        {
            dst->sx = src->x;
            dst->sy = src->y;
            dst->sz = dst->rhw = src->z;
            dst->tu1 = src->u;
            dst->tv1 = src->v;
            dst->color = src->color | alpha;
            dst->specular = 0xff000000;
            src++;
            dst++;
        }
        if (mode != (poly->flags & 0x78))
        {
            mode = poly->flags & 0x78;
            FUN_432190(mode);
        }
        int tex = poly->texture;
        if (g_61c5e4 != tex)
        {
            g_d3dDevice->SetTexture(0, g_6227d4[tex].texture);
            g_61c5e4 = tex;
        }
        g_d3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, FVF_TLVERTEX2, v, poly->numVerts,
                                   D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTLIGHT);
        poly++;
    }
    if (poly->flags & 0x40)
    {
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
    }
    FUN_425870();
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 0xa0);
}

// FUNCTION: STUNTGP_D3D 0x433ee0
void FUN_433ee0()
{
    if (g_d3dInScene != TRUE)
    {
        g_d3dInScene = TRUE;
        int res = g_d3dDevice->BeginScene();
        if (res != DD_OK)
        {
            exitError(ddGetErrMessage(res));
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x433f20
void FUN_433f20()
{
    if (g_d3dInScene)
    {
        g_d3dInScene = FALSE;
        g_d3dDevice->EndScene();
    }
}

// STUB: STUNTGP_D3D 0x43d250
void FUN_43d250()
{
}

// GLOBAL: STUNTGP_D3D 0x61c7cc
BYTE g_61c7cc[0x6000];

// GLOBAL: STUNTGP_D3D 0x6227cc
BYTE *g_6227cc = NULL;

// GLOBAL: STUNTGP_D3D 0x6227d0
int g_6227d0 = 0;

// FUNCTION: STUNTGP_D3D 0x44fd60
void FUN_44fd60()
{
    g_6227cc = g_61c7cc;
    g_6227d0 = 0;
}

// FUNCTION: STUNTGP_D3D 0x425870
void FUN_425870()
{
    g_61c604 = 0;
}

// FUNCTION: STUNTGP_D3D 0x42e420
void FUN_42e420()
{
    g_61c5e4 = -1;
}
