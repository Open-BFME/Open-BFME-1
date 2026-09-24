// ?rva006C96B0@BaseHeightMapRenderObjClass@@IAEXXZ
// partial score=0.306868 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2
// stlport
#include "Lib/BaseType.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
#include "dx8fvf.h"

struct Rva00733E30Coord3 { Real x, y, z; };
struct Rva00733E30Coord2 { Real x, y; };
class Rva00733E30Owner
{
public:
    bool query(Int index, Rva00733E30Coord3 *position, Real *radius,
        Rva00733E30Coord2 *primary, Rva00733E30Coord2 *secondary);
};

class Rva006C96B0Map
{
public:
    char m_beforeWidth[8];
    Int m_width;
    Int m_height;
    Int m_borderSize;
};

class Gen_0074B410
{
public:
    bool bfmeBitA(Int x, Int y) const;
};

class GlobalData
{
public:
    char m_beforeTreeFlag[0x65];
    Bool m_useShadowDecals;
};
#define TheWritableGlobalData (*(GlobalData **)0x012ED5C8)
extern Real g_bfmeScaleBK;
extern Real g_bfmeDirectionWeight1285;
extern Real g_bfmeDefaultBU;
extern const Real g_bfmeK1253;
extern const Real BfmeZeroRange;
extern "C" __declspec(dllimport) double __cdecl BfmeFloorER(double value);
extern "C" __declspec(dllimport) double __cdecl bfmeMathVE(double value);
struct Coord3D;

class BaseHeightMapRenderObjClass
{
public:
    virtual void rvaSlot000(void) = 0;
    virtual void rvaSlot001(void) = 0;
    virtual void rvaSlot002(void) = 0;
    virtual void rvaSlot003(void) = 0;
    virtual void rvaSlot004(void) = 0;
    virtual void rvaSlot005(void) = 0;
    virtual void rvaSlot006(void) = 0;
    virtual void rvaSlot007(void) = 0;
    virtual void rvaSlot008(void) = 0;
    virtual void rvaSlot009(void) = 0;
    virtual void rvaSlot010(void) = 0;
    virtual void rvaSlot011(void) = 0;
    virtual void rvaSlot012(void) = 0;
    virtual void rvaSlot013(void) = 0;
    virtual void rvaSlot014(void) = 0;
    virtual void rvaSlot015(void) = 0;
    virtual void rvaSlot016(void) = 0;
    virtual void rvaSlot017(void) = 0;
    virtual void rvaSlot018(void) = 0;
    virtual void rvaSlot019(void) = 0;
    virtual void rvaSlot020(void) = 0;
    virtual void rvaSlot021(void) = 0;
    virtual void rvaSlot022(void) = 0;
    virtual void rvaSlot023(void) = 0;
    virtual void rvaSlot024(void) = 0;
    virtual void rvaSlot025(void) = 0;
    virtual void rvaSlot026(void) = 0;
    virtual void rvaSlot027(void) = 0;
    virtual void rvaSlot028(void) = 0;
    virtual void rvaSlot029(void) = 0;
    virtual void rvaSlot030(void) = 0;
    virtual void rvaSlot031(void) = 0;
    virtual void rvaSlot032(void) = 0;
    virtual void rvaSlot033(void) = 0;
    virtual void rvaSlot034(void) = 0;
    virtual void rvaSlot035(void) = 0;
    virtual void rvaSlot036(void) = 0;
    virtual void rvaSlot037(void) = 0;
    virtual void rvaSlot038(void) = 0;
    virtual void rvaSlot039(void) = 0;
    virtual void rvaSlot040(void) = 0;
    virtual void rvaSlot041(void) = 0;
    virtual void rvaSlot042(void) = 0;
    virtual void rvaSlot043(void) = 0;
    virtual void rvaSlot044(void) = 0;
    virtual void rvaSlot045(void) = 0;
    virtual void rvaSlot046(void) = 0;
    virtual void rvaSlot047(void) = 0;
    virtual void rvaSlot048(void) = 0;
    virtual void rvaSlot049(void) = 0;
    virtual void rvaSlot050(void) = 0;
    virtual void rvaSlot051(void) = 0;
    virtual void rvaSlot052(void) = 0;
    virtual void rvaSlot053(void) = 0;
    virtual void rvaSlot054(void) = 0;
    virtual void rvaSlot055(void) = 0;
    virtual void rvaSlot056(void) = 0;
    virtual void rvaSlot057(void) = 0;
    virtual void rvaSlot058(void) = 0;
    virtual void rvaSlot059(void) = 0;
    virtual void rvaSlot060(void) = 0;
    virtual void rvaSlot061(void) = 0;
    virtual void rvaSlot062(void) = 0;
    virtual void rvaSlot063(void) = 0;
    virtual void rvaSlot064(void) = 0;
    virtual void rvaSlot065(void) = 0;
    virtual void rvaSlot066(void) = 0;
    virtual void rvaSlot067(void) = 0;
    virtual void rvaSlot068(void) = 0;
    virtual void rvaSlot069(void) = 0;
    virtual void rvaSlot070(void) = 0;
    virtual void rvaSlot071(void) = 0;
    virtual void rvaSlot072(void) = 0;
    virtual void rvaSlot073(void) = 0;
    virtual void rvaSlot074(void) = 0;
    virtual void rvaSlot075(void) = 0;
    virtual void rvaSlot076(void) = 0;
    virtual void rvaSlot077(void) = 0;
    virtual void rvaSlot078(void) = 0;
    virtual void rvaSlot079(void) = 0;
    virtual void rvaSlot080(void) = 0;
    virtual void rvaSlot081(void) = 0;
    virtual void rvaSlot082(void) = 0;
    virtual void rvaSlot083(void) = 0;
    virtual void rvaSlot084(void) = 0;
    virtual void rvaSlot085(void) = 0;
    virtual void rvaSlot086(void) = 0;
    virtual void rvaSlot087(void) = 0;
    virtual void rvaSlot088(void) = 0;
    virtual void rvaSlot089(void) = 0;
    virtual void rvaSlot090(void) = 0;
    virtual void rvaSlot091(void) = 0;
    virtual void rvaSlot092(void) = 0;
    virtual void rvaSlot093(void) = 0;
    virtual void rvaSlot094(void) = 0;
    virtual void rvaSlot095(void) = 0;
    virtual void rvaSlot096(void) = 0;
    virtual void rvaSlot097(void) = 0;
    virtual void rvaSlot098(void) = 0;
    virtual void rvaSlot099(void) = 0;
    virtual void rvaSlot100(void) = 0;
    virtual void rvaSlot101(void) = 0;
    virtual void rvaSlot102(void) = 0;
    virtual void rvaSlot103(void) = 0;
    virtual void rvaSlot104(void) = 0;
    virtual void rvaSlot105(void) = 0;
    virtual void rvaSlot106(void) = 0;
    virtual void rvaSlot107(void) = 0;
    virtual void rvaSlot108(void) = 0;
    virtual void rvaSlot109(void) = 0;
    virtual void rvaSlot110(void) = 0;
    virtual void rvaSlot111(void) = 0;
    virtual void rvaSlot112(void) = 0;
    virtual void rvaSlot113(void) = 0;
    virtual void rvaSlot114(void) = 0;
    virtual void rvaSlot115(void) = 0;
    virtual void rvaSlot116(void) = 0;
    virtual void rvaSlot117(void) = 0;
    virtual void rvaSlot118(void) = 0;
    virtual void rvaSlot119(void) = 0;
    virtual void rvaSlot120(void) = 0;
    virtual void rvaSlot121(void) = 0;
    virtual void rvaSlot122(void) = 0;
    virtual void rvaSlot123(void) = 0;
    virtual void rvaSlot124(void) = 0;
    virtual void rvaSlot125(void) = 0;
    virtual void rvaSlot126(void) = 0;
    virtual void rvaSlot127(void) = 0;
    virtual void rvaSlot128(void) = 0;
    virtual void rvaSlot129(void) = 0;
    virtual void rvaSlot130(void) = 0;
    virtual void rvaSlot131(void) = 0;
    virtual void rvaSlot132(void) = 0;
    virtual void rvaSlot133(void) = 0;
    virtual void rvaSlot134(void) = 0;
    virtual void rvaSlot135(void) = 0;
    virtual void rvaSlot136(void) = 0;
    virtual void rvaSlot137(void) = 0;
    virtual void rvaSlot138(void) = 0;
    virtual void rvaSlot139(void) = 0;
    virtual void rvaSlot140(void) = 0;
    virtual void rvaSlot141(void) = 0;
    virtual void rvaSlot142(void) = 0;
    virtual void rvaSlot143(void) = 0;
    virtual void rvaSlot144(void) = 0;
    virtual void rvaSlot145(void) = 0;
    virtual Real getHeightMapHeight(Real x, Real y, Coord3D *normal) const = 0;
    unsigned short getClipHeight(Int x, Int y) const;
protected:
    char m_beforeBuffers[0x2fd8 - sizeof(void *)];
    VertexBufferClass *m_vertexBuffer;
    IndexBufferClass *m_indexBuffer;
    Int m_at2FE0;
    Int m_curNumScorchVertices;
    Int m_curNumScorchIndices;
    Int m_maxScorchVertices;
    Int m_maxScorchIndices;
    Rva006C96B0Map *m_map;
    char m_beforeTreeBuffer[0x3094 - 0x2ff8];
    Rva00733E30Owner *m_treeBuffer;
    void rva006C96B0(void);
};

void BaseHeightMapRenderObjClass::rva006C96B0(void)
{
    if (!m_treeBuffer)
        return;

    m_at2FE0 = 0;
    m_curNumScorchVertices = 0;
    m_curNumScorchIndices = 0;
    if (!TheWritableGlobalData->m_useShadowDecals)
        return;

    Rva00733E30Coord3 position;
    Real radius;
    Rva00733E30Coord2 primary, secondary;
    IndexBufferClass::WriteLockClass indexLock(m_indexBuffer, 0);
    unsigned short *indices = indexLock.Get_Index_Array();
    VertexBufferClass::WriteLockClass vertexLock(m_vertexBuffer, 0);
    VertexFormatXYZDUV1 *vertices =
        (VertexFormatXYZDUV1 *)vertexLock.Get_Vertex_Array();
    Int border = m_map->m_borderSize;
    Int treeCount = *(Int *)((char *)m_treeBuffer + 0x2a7cb0);

    for (Int treeIndex = 0; treeIndex < treeCount; ++treeIndex) {
        if (!m_treeBuffer->query(treeIndex, &position, &radius,
            &primary, &secondary))
            continue;

        Int minX = (Int)fast_float2long_round((Real)BfmeFloorER(
            (double)((position.x - radius) * g_bfmeScaleBK)));
        Int minY = (Int)fast_float2long_round((Real)BfmeFloorER(
            (double)((position.y - radius) * g_bfmeScaleBK)));
        Int maxX = (Int)fast_float2long_round((Real)bfmeMathVE(
            (double)((position.x + radius) * g_bfmeScaleBK))) + 1;
        Int maxY = (Int)fast_float2long_round((Real)bfmeMathVE(
            (double)((position.y + radius) * g_bfmeScaleBK))) + 1;

        if (minX < -border)
            minX = -border;
        if (minY < -border)
            minY = -border;
        Int widthLimit = m_map->m_width - border;
        Int heightLimit = m_map->m_height - border;
        if (maxX > widthLimit)
            maxX = widthLimit;
        if (maxY > heightLimit)
            maxY = heightLimit;

        Int startVertex = m_curNumScorchVertices;
        Int gridWidth = maxX - minX;
        for (Int j = minY; j < maxY; ++j) {
            for (Int i = minX; i < maxX; ++i) {
                if (m_curNumScorchVertices >= m_maxScorchVertices)
                    return;

                Real worldX = (Real)i * g_bfmeDirectionWeight1285;
                Real worldY = (Real)j * g_bfmeDirectionWeight1285;
                Real u = g_bfmeDefaultBU +
                    (worldX - position.x) / (radius + radius);
                Real v = g_bfmeDefaultBU +
                    (worldY - position.y) / (radius + radius);
                Real u1;
                Real v1;
                Real z;
                if (!(u >= BfmeZeroRange && u <= g_bfmeDefaultBU &&
                    v >= BfmeZeroRange && v <= g_bfmeDefaultBU)) {
                    if (u < BfmeZeroRange) {
                        worldX -= u * (radius + radius);
                        u = BfmeZeroRange;
                    } else if (u > g_bfmeDefaultBU) {
                        worldX -= (u - g_bfmeDefaultBU) * (radius + radius);
                        u = g_bfmeDefaultBU;
                    }
                    if (v < BfmeZeroRange) {
                        worldY -= v * (radius + radius);
                        v = BfmeZeroRange;
                    } else if (v > g_bfmeDefaultBU) {
                        worldY -= (v - g_bfmeDefaultBU) * (radius + radius);
                        v = g_bfmeDefaultBU;
                    }
                    u1 = primary.x * u + secondary.x;
                    v1 = primary.y * v + secondary.y;
                    z = getHeightMapHeight(worldX, worldY, 0);
                } else {
                    u1 = primary.x * u + secondary.x;
                    v1 = primary.y * v + secondary.y;
                    z = (Real)getClipHeight(i + border, j + border) *
                        *(const Real *)0x010F653C;
                }
                vertices->x = worldX;
                vertices->y = worldY;
                vertices->z = z + g_bfmeK1253;
                vertices->diffuse = 0xffffffff;
                vertices->v1 = v1;
                vertices->u1 = u1;
                ++vertices;
                ++m_curNumScorchVertices;
            }
        }

        Int gridHeight = maxY - minY;
        for (Int j = 0; j < gridHeight - 1; ++j) {
            for (Int i = 0; i < gridWidth - 1; ++i) {
                if (m_curNumScorchIndices + 6 > m_maxScorchIndices)
                    return;
                Int x = i + minX;
                Int y = j + minY;
                Int cellX = x + border;
                Int cellY = y + border;
                Int c = startVertex + j * gridWidth + i;
                if (((Gen_0074B410 *)m_map)->bfmeBitA(cellX, cellY)) {
                    *indices++ = (unsigned short)(c + 1);
                    *indices++ = (unsigned short)(c + gridWidth);
                    *indices++ = (unsigned short)c;
                    *indices++ = (unsigned short)(c + 1);
                    *indices++ = (unsigned short)(c + gridWidth + 1);
                    *indices++ = (unsigned short)(c + gridWidth);
                } else {
                    *indices++ = (unsigned short)c;
                    *indices++ = (unsigned short)(c + gridWidth + 1);
                    *indices++ = (unsigned short)(c + gridWidth);
                    *indices++ = (unsigned short)c;
                    *indices++ = (unsigned short)(c + 1);
                    *indices++ = (unsigned short)(c + gridWidth + 1);
                }
                m_curNumScorchIndices += 6;
            }
        }
        ++m_at2FE0;
    }
}
