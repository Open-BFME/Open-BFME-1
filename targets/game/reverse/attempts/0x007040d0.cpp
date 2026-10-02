// ?updateSegLighting@RoadSegment@@QAEXXZ
// partial score=0.3913 date=2026-10-02
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/w3droadbuffer /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4
#include "W3DDevice/GameClient/W3DRoadBuffer.h"
#include "W3DDevice/GameClient/HeightMap.h"
// Retail map owner +0x2ff4 -> border at +0x10. The ZH accessor uses +0x14.
// Keep the final destination as m_vb[i]: the diffuse query can change the base.
class BfmeA1087 {public: int getStaticDiffuse(int,int);};
extern BfmeA1087 *g_bfmeA1087;
static const char *rva007040D0Map()
{
    return *(const char **)((const char *)g_bfmeA1087 + 0x2ff4);
}
void RoadSegment::updateSegLighting(void)
{
    int x,y,border;
    for(int i=0;i<m_numVertex;++i) {
        border=*(const int*)((const char*)rva007040D0Map()+0x10);
        x=m_vb[i].x/MAP_XY_FACTOR+0.5;
        const VertexFormatXYZDUV1 &vertex=m_vb[i];
        y=vertex.y/MAP_XY_FACTOR+0.5;
        x+=border;
        y+=border;
        m_vb[i].diffuse=(255<<24)|g_bfmeA1087->getStaticDiffuse(x,y);
    }
}

