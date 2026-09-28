// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <vector>
#include <math.h>
#include "ascii_string.h"

// BaseHeightMapRenderObjClass constructor, retail RVA 0x006CFAE0, 1307 bytes.
// Identity: the landed HeightMapRenderObjClass constructor calls this base
// constructor; the four installed vtables agree with the landed destructor
// at 0x006CEE90. The original ZH constructor supplies the initialization order.
// BFME adds a second bit vector, eight strings, texture handles and buffers.
// This TU uses the destructor's verified BFME base layout. BaseHeightMap.cpp's
// imported header still has the partial ZH member layout; changing that shared
// header would affect unrelated landed methods.
// RenderObjBaseA/B preserve the existing destructor's vtable symbol spellings.
// The base occupies 0xC8 bytes; cleanup and snapshot bases are at 0xC8/0xCC.
// Allocated object extents below are the retail new-expression sizes; their
// named constructor identities come from callees.py and the landed siblings.
class RenderObjBaseA { public: virtual ~RenderObjBaseA(); int field04; };
class RenderObjBaseB { public: virtual ~RenderObjBaseB(); };
class RenderObjClass : public RenderObjBaseA, public RenderObjBaseB {
public: RenderObjClass(); virtual ~RenderObjClass(); char bytes0C[0xBC];
};
class DX8_CleanupHook { public: virtual void ReleaseResources()=0; virtual void ReAcquireResources()=0; };
class Snapshot { public: ~Snapshot(); virtual void crc(void*)=0; virtual void xfer(void*)=0; virtual void loadPostProcess()=0; };
class TextureBaseClass { public: void Release_Ref(); };
class TextureRef006CFAE0 {
public:
 TextureRef006CFAE0():ptr(0) {}
 ~TextureRef006CFAE0() { if(ptr) ptr->Release_Ref(); }
 TextureBaseClass* ptr;
};
struct Shader006CFAE0 { Shader006CFAE0():bits(0x10441b) {} unsigned bits; };
class W3DTreeBuffer { public: W3DTreeBuffer(bool); char bytes[0x2a9910]; };
class W3DShrubBuffer { public: W3DShrubBuffer(unsigned char); char bytes[0x1e3928]; };
class W3DPropBuffer { public: W3DPropBuffer(); char bytes[0x2f71c]; };
class W3DBibBuffer { public: W3DBibBuffer(); char bytes[0x109d0]; };
class W3DBridgeBuffer { public: W3DBridgeBuffer(); char bytes[0xd7c0]; };
class W3DFloorBuffer { public: W3DFloorBuffer(); char bytes[0x2c]; };
class W3DWaypointBuffer { public: W3DWaypointBuffer(); char bytes[0xc]; };
class W3DRoadBuffer { public: W3DRoadBuffer(); char bytes[0x58]; };
class Rva006DED60RoadBuffer { public: Rva006DED60RoadBuffer(); char bytes[0x110]; };
class W3DShroud { public: W3DShroud(); char bytes[0x50]; };
class TaintBuffer { public: TaintBuffer(); char bytes[0x50]; };

class GlobalData;
extern GlobalData *TheWritableGlobalData;
class Overridable {
public:
 const Overridable *getFinalOverride() const { if(next) return next->getFinalOverride(); return this; }
 void *vfptr; const Overridable *next; // retail Overridable +0/+4
};
// WaterTransparencySetting FieldParse and ZH Water.h establish +0xC/+0x10.
struct WaterTransparency006CFAE0 : Overridable {
 unsigned field08; float m_transparentWaterDepth, m_minWaterOpacity;
};
extern WaterTransparency006CFAE0 *water012F18F0;
static const WaterTransparency006CFAE0 *waterSetting() {
 if(!water012F18F0) return 0;
 return (const WaterTransparency006CFAE0*)water012F18F0->getFinalOverride();
}
class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern DX8_CleanupHook *cleanup0134058C;
class BaseHeightMapRenderObjClass : public RenderObjClass, public DX8_CleanupHook, public Snapshot {
public:
 BaseHeightMapRenderObjClass();
 virtual ~BaseHeightMapRenderObjClass();
 virtual void ReleaseResources(); virtual void ReAcquireResources();
 virtual void crc(void*); virtual void xfer(void*); virtual void loadPostProcess();
 unsigned fieldD0; // +0xD0
 unsigned fieldD4; // +0xD4
 TextureRef006CFAE0 textureD8; // +0xD8
 char padDC[0x2ee8];
 unsigned field2FC4; // +0x2FC4
 unsigned field2FC8; // +0x2FC8
 unsigned field2FCC; // +0x2FCC
 float m_curImpassableSlope; // +0x2FD0
 float field2FD4; // +0x2FD4
 unsigned field2FD8; // +0x2FD8
 unsigned field2FDC; // +0x2FDC
 unsigned field2FE0; // +0x2FE0
 char pad2FE4[0x10];
 void* m_map; // +0x2FF4
 bool m_useDepthFade; // +0x2FF8
 bool m_updating; // +0x2FF9
 char pad2FFA[0x2];
 float m_depthFade[3]; // +0x2FFC
 bool field3008; // +0x3008
 bool m_needFullUpdate; // +0x3009
 char pad300A[0x2];
 float m_minHeight; // +0x300C
 float m_maxHeight; // +0x3010
 bool field3014; // +0x3014
 char pad3015[0x3];
 float field3018; // +0x3018
 float field301C; // +0x301C
 std::vector<bool> m_showAsVisibleCliff; // +0x3020
 std::vector<bool> bits3034; // +0x3034
 Shader006CFAE0 shader3048; // +0x3048
 void* field304C; // +0x304C
 TextureRef006CFAE0 texture3050; // +0x3050
 TextureRef006CFAE0 texture3054; // +0x3054
 TextureRef006CFAE0 texture3058; // +0x3058
 TextureRef006CFAE0 texture305C; // +0x305C
 TextureRef006CFAE0 texture3060; // +0x3060
 TextureRef006CFAE0 texture3064; // +0x3064
 TextureRef006CFAE0 texture3068; // +0x3068
 char pad306C[0x4];
 AsciiString string3070; // +0x3070
 AsciiString string3074; // +0x3074
 AsciiString string3078; // +0x3078
 AsciiString string307C; // +0x307C
 AsciiString string3080; // +0x3080
 AsciiString string3084; // +0x3084
 AsciiString string3088; // +0x3088
 AsciiString string308C; // +0x308C
 TextureRef006CFAE0 texture3090; // +0x3090
 W3DTreeBuffer* m_treeBuffer; // +0x3094
 W3DShrubBuffer* buffer3098; // +0x3098
 W3DPropBuffer* m_propBuffer; // +0x309C
 W3DBibBuffer* m_bibBuffer; // +0x30A0
 W3DFloorBuffer* buffer30A4; // +0x30A4
 W3DWaypointBuffer* buffer30A8; // +0x30A8
 W3DRoadBuffer* m_roadBuffer; // +0x30AC
 W3DBridgeBuffer* buffer30B0; // +0x30B0
 Rva006DED60RoadBuffer* buffer30B4; // +0x30B4
 W3DShroud* m_shroud; // +0x30B8
 TaintBuffer* buffer30BC; // +0x30BC
 void* field30C0; // +0x30C0
 int field30C4; // +0x30C4
 int field30C8; // +0x30C8
 float field30CC; // +0x30CC
 bool field30D0; // +0x30D0
};
typedef char BaseHeightMapSize006CFAE0[(sizeof(BaseHeightMapRenderObjClass)==0x30D4)?1:-1];
typedef char RenderObjSize006CFAE0[(sizeof(RenderObjClass)==0xC8)?1:-1];
typedef char BitVectorSize006CFAE0[(sizeof(std::vector<bool>)==20)?1:-1];

BaseHeightMapRenderObjClass::BaseHeightMapRenderObjClass() {
 m_needFullUpdate=false;
 field3014=false;
 m_updating=false;
 m_maxHeight=(pow(256.0,2)-1.0)*0.0390625;
 m_minHeight=0;
 field30C0=0;
 field30C4=0;
 field30C8=0;
 field30CC=-1.0f;
 field304C=0;
 m_map=0;
 m_depthFade[0]=0;
 m_depthFade[1]=0;
 m_depthFade[2]=0;
 m_useDepthFade=false;
 field3008=false;
 TheTerrainRenderObject=this;
 m_treeBuffer=0;
 m_treeBuffer=new W3DTreeBuffer(*(bool*)((char*)TheWritableGlobalData+0xDCD));
 buffer3098=0;
 buffer3098=new W3DShrubBuffer(*(unsigned char*)((char*)TheWritableGlobalData+0xDCD));
 m_propBuffer=0;
 m_propBuffer=new W3DPropBuffer;
 m_bibBuffer=0;
 m_bibBuffer=new W3DBibBuffer;
 m_curImpassableSlope=89.9f;
 field2FD4=70.0f;
 buffer30B0=0;
 buffer30B0=new W3DBridgeBuffer;
 buffer30A4=0;
 buffer30A4=new W3DFloorBuffer;
 buffer30A8=new W3DWaypointBuffer;
 m_roadBuffer=0;
 m_roadBuffer=new W3DRoadBuffer;
 buffer30B4=0;
 buffer30B4=new Rva006DED60RoadBuffer;
 fieldD0=0;
 fieldD4=0;
 field2FC4=0;
 field2FC8=0;
 field2FCC=0;
 field2FD8=0;
 field2FDC=0;
 field2FE0=0;
 m_shroud=new W3DShroud;
 if(*(bool*)((char*)TheWritableGlobalData+0xCF5)) buffer30BC=new TaintBuffer;
 else buffer30BC=0;
 cleanup0134058C=this;
 string3084.StringBase<char>::set("TSCloudMed.tga",14);
 string3080.StringBase<char>::set("TSNoiseUrb.tga",14);
 string3088.StringBase<char>::set("TSTaintMed.tga",14);
 string308C.StringBase<char>::set("TSElvenMed.tga",14);
 field301C=waterSetting()->m_minWaterOpacity;
 field3018=waterSetting()->m_transparentWaterDepth;
 field30D0=true;
}
