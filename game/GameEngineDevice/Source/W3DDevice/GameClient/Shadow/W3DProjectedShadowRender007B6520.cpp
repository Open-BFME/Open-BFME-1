// ?render007B6520@W3DProjectedShadowManager@@QAEHAAVRenderInfoClass@@@Z
// cl: /DNDEBUG /MD /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /DWIN32 /D_WINDOWS /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
#include "vector3.h"
#include "aabox.h"
#include "sphere.h"
#include "../../../../../Libraries/Source/WWVegas/WW3D2/ww3d.h"
#define BFME_FASTCRITICALSECTION_DEFINED
#include "../../../../../Libraries/Source/WWVegas/WWLib/wwstring.h"
class FrustumClass;
class CameraClass;
#include "../../../../../Libraries/Source/WWVegas/WW3D2/rinfo.h"
#include "../../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"

struct ShadowTexture007B6D30;
struct Shadow007B6D30 { char pad00[4]; bool enabled04; bool invisible05; char pad06[0x2e]; unsigned type34; char pad38[0x30]; ShadowTexture007B6D30 *texture68,*texture6c; RenderObjClass *object70; char pad74[0x60]; Shadow007B6D30 *nextd4; };
struct ShadowPair007B6D30;
struct Rect007B6D30 { int x0,y0,x1,y1; };
struct TerrainDispatch007B6D30 {
 virtual void slot000();
 virtual void slot001();
 virtual void slot002();
 virtual void slot003();
 virtual void slot004();
 virtual void slot005();
 virtual void slot006();
 virtual void slot007();
 virtual void slot008();
 virtual void slot009();
 virtual void slot010();
 virtual void slot011();
 virtual void slot012();
 virtual void slot013();
 virtual void slot014();
 virtual void slot015();
 virtual void slot016();
 virtual void slot017();
 virtual void slot018();
 virtual void slot019();
 virtual void slot020();
 virtual void slot021();
 virtual void slot022();
 virtual void slot023();
 virtual void slot024();
 virtual void slot025();
 virtual void slot026();
 virtual void slot027();
 virtual void slot028();
 virtual void slot029();
 virtual void slot030();
 virtual void slot031();
 virtual void slot032();
 virtual void slot033();
 virtual void slot034();
 virtual void slot035();
 virtual void slot036();
 virtual void slot037();
 virtual void slot038();
 virtual void slot039();
 virtual void slot040();
 virtual void slot041();
 virtual void slot042();
 virtual void slot043();
 virtual void slot044();
 virtual void slot045();
 virtual void slot046();
 virtual void slot047();
 virtual void slot048();
 virtual void slot049();
 virtual void slot050();
 virtual void slot051();
 virtual void slot052();
 virtual void slot053();
 virtual void slot054();
 virtual void slot055();
 virtual void slot056();
 virtual void slot057();
 virtual void slot058();
 virtual void slot059();
 virtual void slot060();
 virtual void slot061();
 virtual void slot062();
 virtual void slot063();
 virtual void slot064();
 virtual void slot065();
 virtual void slot066();
 virtual void slot067();
 virtual void slot068();
 virtual void slot069();
 virtual void slot070();
 virtual void slot071();
 virtual void slot072();
 virtual void slot073();
 virtual void slot074();
 virtual void slot075();
 virtual void slot076();
 virtual void slot077();
 virtual void slot078();
 virtual void slot079();
 virtual void slot080();
 virtual void slot081();
 virtual void slot082();
 virtual void slot083();
 virtual void slot084();
 virtual void slot085();
 virtual void slot086();
 virtual void slot087();
 virtual void slot088();
 virtual void slot089();
 virtual void slot090();
 virtual void slot091();
 virtual void slot092();
 virtual void slot093();
 virtual void slot094();
 virtual void slot095();
 virtual void slot096();
 virtual void slot097();
 virtual void slot098();
 virtual void slot099();
 virtual void slot100();
 virtual void slot101();
 virtual void slot102();
 virtual void slot103();
 virtual void slot104();
 virtual void slot105();
 virtual void slot106();
 virtual void slot107();
 virtual void slot108();
 virtual void slot109();
 virtual void slot110();
 virtual void slot111();
 virtual void slot112();
 virtual void slot113();
 virtual void slot114();
 virtual void slot115();
 virtual void slot116();
 virtual void slot117();
 virtual void slot118();
 virtual void slot119();
 virtual void slot120();
 virtual void slot121();
 virtual void slot122();
 virtual void slot123();
 virtual void slot124();
 virtual void slot125();
 virtual void slot126();
 virtual void slot127();
 virtual void slot128();
 virtual void slot129();
 virtual void slot130();
 virtual void slot131();
 virtual void slot132();
 virtual void slot133();
 virtual void slot134();
 virtual void slot135();
 virtual void slot136();
 virtual void slot137();
 virtual void slot138();
 virtual void slot139();
 virtual void slot140();
 virtual void slot141();
 virtual void bounds238(Rect007B6D30 *);
};
extern TerrainDispatch007B6D30 *terrain012F7FE0;
static int drawStartX, drawStartY, drawEdgeX, drawEdgeY;
class W3DProjectedShadowManager { public:
 void *vptr;
 Shadow007B6D30 *m_shadowList,*m_decalList,*m_simpleDecalList;
 void *m_10;
 ShadowPair007B6D30 *m_14;
 void *m_18; Shadow007B6D30 *m_1c;
 void flush007B14A0(unsigned,ShadowTexture007B6D30 *,ShadowTexture007B6D30 *,int);
 void queue007B4FE0(Shadow007B6D30 *,int,int);
 void project007B23F0(ShadowPair007B6D30 *);
 int render007B6520(RenderInfoClass&);
 int renderShadows(RenderInfoClass&);
};
#include <d3d8.h>
extern unsigned number_of_DX8_calls;
class DX8Wrapper {
public:
 static unsigned RenderStates[256];
 static unsigned render_state_changes;
 static IDirect3DDevice8 *D3DDevice;
 static bool Has_Stencil();
 static void Set_DX8_Render_State007B6520(unsigned long,unsigned);
 static void Get_DX8_Render_State_Value_Name(StringClass &,unsigned long,unsigned);
 static void Clear(bool,bool,bool,const Vector3 &,float,float,unsigned);
 static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
};

// ?Set_DX8_Render_State007B6520@DX8Wrapper@@SAXKI@Z absent-from-retail
__forceinline void DX8Wrapper::Set_DX8_Render_State007B6520(unsigned long state,unsigned value) {
 if (RenderStates[state]==value) return;
 if (WW3D::Is_Snapshot_Activated()) {
  StringClass value_name(0,true);
  Get_DX8_Render_State_Value_Name(value_name,state,value);
 }
 RenderStates[state]=value;
 _Get_D3D_Device8()->SetRenderState(state,value);
 ++number_of_DX8_calls;
 ++render_state_changes;
}

struct GlobalData007B6520 { char pad00[0xa77]; bool byteA77; };
// Retail 0x012ED5C8 is ?TheWritableGlobalData@@3PAVGlobalData@@A (data_rows.csv,
// Common/GlobalData.cpp); TheGlobalData was only a pin.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
#define TheGlobalData ( *(void **)&TheWritableGlobalData )
// Each head read observes the manager's current list after batching calls.
#define head m_1c
// ?render007B6520@W3DProjectedShadowManager@@QAEHAAVRenderInfoClass@@@Z
int W3DProjectedShadowManager::render007B6520(RenderInfoClass &)
{
 static AABoxClass aaBox;
 static SphereClass sphere;
 int projectionCount=0;
 if (!m_1c || !DX8Wrapper::D3DDevice || !terrain012F7FE0) return 0;
  Rect007B6D30 rect;
  terrain012F7FE0->bounds238(&rect);
  drawStartX=rect.x0-4;
  drawStartY=rect.y0-4;
  drawEdgeY=rect.x1+4;
  drawEdgeX=rect.y1+4;
  if (m_1c) {
   int passCount;
   if (DX8Wrapper::Has_Stencil()) {
    passCount=(!((GlobalData007B6520 *)TheGlobalData)->byteA77)+1;
   } else {
    passCount=1;
   }
   if (DX8Wrapper::Has_Stencil()) {
    DX8Wrapper::Set_DX8_Render_State007B6520(0x34,1);
    DX8Wrapper::Set_DX8_Render_State007B6520(0x39,0xff);
    DX8Wrapper::Set_DX8_Render_State007B6520(0x3a,0xffffffffu);
    DX8Wrapper::Set_DX8_Render_State007B6520(0x3b,0xffffffffu);
    DX8Wrapper::Set_DX8_Render_State007B6520(0x36,1);
    DX8Wrapper::Set_DX8_Render_State007B6520(0x35,1);
   }
   for (int passIndex=0;passIndex<passCount;++passIndex) {
    Shadow007B6D30 *shadow=head;
    ShadowTexture007B6D30 *lastTexture=0;
    ShadowTexture007B6D30 *lastTexture2=0;
    unsigned lastType=0;
    for (;shadow;shadow=shadow->nextd4) {
     if (shadow->enabled04 && !shadow->invisible05) {
      if (!lastTexture) lastTexture=head->texture68;
      if (!lastTexture2) lastTexture2=head->texture6c;
      if (!lastType) lastType=head->type34;
      ShadowTexture007B6D30 *texture=shadow->texture68;
      ShadowTexture007B6D30 *texture2=shadow->texture6c;
      unsigned type=head->type34;
      if (texture!=lastTexture || texture2!=lastTexture2 || type!=lastType) {
       flush007B14A0(lastType,lastTexture,lastTexture2,passIndex);
       lastTexture=texture;
       lastTexture2=texture2;
       lastType=type;
      }
      if (!shadow->object70 || shadow->object70->Is_Really_Visible()) {
       queue007B4FE0(shadow,passCount,passIndex);
       if (passIndex==0) ++projectionCount;
      }
     }
    }
    flush007B14A0(lastType,lastTexture,lastTexture2,passIndex);
   }
   if (DX8Wrapper::Has_Stencil() && DX8Wrapper::RenderStates[0x34]!=0) {
    DX8Wrapper::Set_DX8_Render_State007B6520(0x34,0);
   }
  }
  if (DX8Wrapper::Has_Stencil()) {
   Vector3 clearColor(0,0,0);
   DX8Wrapper::Clear(false,false,true,clearColor,0.0f,1.0f,0);
  }
 return projectionCount;
}
#undef head
