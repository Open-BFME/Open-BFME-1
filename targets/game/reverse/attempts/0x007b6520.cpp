// ?render007B6520@W3DProjectedShadowManager@@QAEHAAVRenderInfoClass@@@Z
// partial score=0.934 date=2026-09-27
// cl: /DNDEBUG /MD /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// BFME W3DProjectedShadowManager::renderShadows, RVA 0x007B6D30.
// Identity: ZH W3DProjectedShadow.cpp and the DoShadows retail caller.
// Lists +4/+8/+C agree with the landed manager constructor/removeAllShadows.
// Retail additionally walks paired shadows at +0x14 and tests +0x1C on entry.
// The opaque views below preserve witnessed offsets and callee argument order;
// no unproved ZH helper signature is reused. Geometry uses native WWMath headers.
// Keeping the terrain rectangle in its own scope permits retail stack reuse.
#include "vector3.h"
#include "aabox.h"
#include "sphere.h"
#include "../../../../../Libraries/Source/WWVegas/WW3D2/ww3d.h"
#define BFME_FASTCRITICALSECTION_DEFINED
#include "../../../../../Libraries/Source/WWVegas/WWLib/wwstring.h"
class FrustumClass;
class CameraClass;
class RenderInfoClass { public: CameraClass &Camera; };
class RenderObjClass {
public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void slot77();
 virtual void slot78();
 virtual void slot79();
 virtual void slot80();
 virtual void slot81();
 virtual void slot82();
 virtual void slot83();
 virtual void slot84();
 virtual void slot85();
 virtual void slot86();
 virtual void slot87();
 virtual void slot88();
 virtual void slot89();
 virtual void slot90();
 virtual void slot91();
 virtual void slot92();
 virtual void slot93();
 virtual void slot94();
 virtual int Is_Really_Visible() const;
 Vector3 Get_Position() const;
};
struct ShadowTexture007B6D30 { char pad00[0x64]; AABoxClass box64; SphereClass sphere7c; };
struct Shadow007B6D30 { char pad00[4]; bool enabled04; bool invisible05; char pad06[0x2e]; unsigned type34; char pad38[0x30]; ShadowTexture007B6D30 *texture68,*texture6c; RenderObjClass *object70; char pad74[0x60]; Shadow007B6D30 *nextd4; };
struct ShadowPair007B6D30 { char pad00[4]; bool enabled04; bool invisible05; char pad06[0x2e]; unsigned type34; char pad38[0x20]; Shadow007B6D30 *shadow58,*shadow5c; RenderObjClass *object60; ShadowPair007B6D30 *next64; };
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
class DX8MeshRendererClass { public: void *vptr; CameraClass *camera04; void Flush(); };
extern DX8MeshRendererClass *TheDX8MeshRenderer;
extern TerrainDispatch007B6D30 *terrain012F7FE0;
extern void *device01340534;
extern const FrustumClass *shadowCameraFrustum;
static int drawStartX, drawStartY, drawEdgeX, drawEdgeY;
static int nShadowDecalVertsInBuf,nShadowDecalIndicesInBuf;
class W3DProjectedShadowManager { public:
 void *vptr;
 Shadow007B6D30 *m_shadowList,*m_decalList,*m_simpleDecalList;
 void *m_10;
 ShadowPair007B6D30 *m_14;
 void *m_18,*m_1c;
 void flush007B14A0(unsigned,ShadowTexture007B6D30 *,ShadowTexture007B6D30 *,int);
 void queue007B4FE0(Shadow007B6D30 *,int,int);
 void project007B23F0(ShadowPair007B6D30 *);
 int render007B6520(RenderInfoClass&);
 int renderShadows(RenderInfoClass&);
};
int W3DProjectedShadowManager::renderShadows(RenderInfoClass &rinfo)
{
 Shadow007B6D30 *shadow;
 static AABoxClass aaBox;
 static SphereClass sphere;
 int projectionCount=0;
 if (!m_shadowList && !m_decalList && !m_simpleDecalList && !m_1c) return projectionCount;
 if (!device01340534 || !terrain012F7FE0) return projectionCount;
 {
 Rect007B6D30 rect;
 terrain012F7FE0->bounds238(&rect);
 drawStartX=rect.x0-4; drawStartY=rect.y0-4;
 drawEdgeX=rect.x1+4; drawEdgeY=rect.y1+4;
 }
 nShadowDecalVertsInBuf=0x8000; nShadowDecalIndicesInBuf=0x10000;
 if (m_simpleDecalList) {
 ShadowTexture007B6D30 *lastTexture=0;
 unsigned lastType=0;
 for(shadow=m_simpleDecalList; shadow; shadow=shadow->nextd4) {
  if(shadow->enabled04 && !shadow->invisible05) {
   if(!lastTexture) lastTexture=shadow->texture68;
   if(!lastType) lastType=shadow->type34;
   if(shadow->texture68!=lastTexture || shadow->type34!=lastType) {
    flush007B14A0(lastType,lastTexture,0,0);
    lastTexture=shadow->texture68; lastType=shadow->type34;
   }
   if(!shadow->object70 || shadow->object70->Is_Really_Visible()) {
    queue007B4FE0(shadow,1,0); ++projectionCount;
   }
  }
 }
 flush007B14A0(lastType,lastTexture,0,0);
 }
 if(m_shadowList) {
 TheDX8MeshRenderer->camera04=&rinfo.Camera;
 ShadowTexture007B6D30 *lastTexture=0;
 unsigned lastType=0;
 for(shadow=m_shadowList;shadow;shadow=shadow->nextd4) {
  if(shadow->enabled04 && !shadow->invisible05) {
   if(shadow->type34 & 0xc61) {
    if(!lastTexture) lastTexture=shadow->texture68;
    if(!lastType) lastType=shadow->type34;
    if(shadow->texture68!=lastTexture || shadow->type34!=lastType) {
     flush007B14A0(lastType,lastTexture,0,0);
     lastTexture=shadow->texture68; lastType=shadow->type34;
    }
    if(!shadow->object70 || shadow->object70->Is_Really_Visible() || (shadow->type34 & 0xc00)) {
     queue007B4FE0(shadow,1,0); ++projectionCount;
    }
    continue;
   }
   sphere=shadow->texture68->sphere7c;
   sphere.Center+=shadow->object70->Get_Position();
   CollisionMath::OverlapType result=CollisionMath::Overlap_Test(*shadowCameraFrustum,sphere);
   if(result==CollisionMath::OVERLAPPED) {
    aaBox=shadow->texture68->box64;
    aaBox.Translate(shadow->object70->Get_Position());
    if(CollisionMath::Overlap_Test(*shadowCameraFrustum,aaBox)==CollisionMath::OUTSIDE) continue;
   } else if(result==CollisionMath::OUTSIDE) continue;
   if(result==CollisionMath::INSIDE) {
    aaBox=shadow->texture68->box64;
    aaBox.Translate(shadow->object70->Get_Position());
   }
  }
 }
 flush007B14A0(lastType,lastTexture,0,0);
 TheDX8MeshRenderer->Flush();
 }
 if (m_decalList) {
 ShadowTexture007B6D30 *lastTexture=0;
 unsigned lastType=0;
 for(shadow=m_decalList; shadow; shadow=shadow->nextd4) {
  if(shadow->enabled04 && !shadow->invisible05) {
   if(!lastTexture) lastTexture=shadow->texture68;
   if(!lastType) lastType=shadow->type34;
   if(shadow->texture68!=lastTexture || shadow->type34!=lastType) {
    flush007B14A0(lastType,lastTexture,0,0);
    lastTexture=shadow->texture68; lastType=shadow->type34;
   }
   if(!shadow->object70 || shadow->object70->Is_Really_Visible()) {
    queue007B4FE0(shadow,1,0); ++projectionCount;
   }
  }
 }
 flush007B14A0(lastType,lastTexture,0,0);
 }
 if(m_14) {
 ShadowTexture007B6D30 *lastTexture=0,*lastTexture2=0;
 unsigned lastType=0;
 for(ShadowPair007B6D30 *pair=m_14;pair;pair=pair->next64) {
  if(pair->enabled04 && !pair->invisible05) {
   if(!lastTexture) lastTexture=pair->shadow58 ? pair->shadow58->texture68 : 0;
   if(!lastTexture2) lastTexture2=pair->shadow5c ? pair->shadow5c->texture68 : 0;
   if(!lastType) lastType=pair->type34;
   ShadowTexture007B6D30 *texture=pair->shadow58 ? pair->shadow58->texture68 : 0;
   ShadowTexture007B6D30 *texture2=pair->shadow5c ? pair->shadow5c->texture68 : 0;
   unsigned type=m_14->type34;
   if(texture!=lastTexture || texture2!=lastTexture2 || type!=lastType) {
    flush007B14A0(lastType,lastTexture,lastTexture2,0);
    lastTexture=texture; lastTexture2=texture2; lastType=type;
   }
   if(!pair->object60 || pair->object60->Is_Really_Visible()) {
    project007B23F0(pair); ++projectionCount;
   }
  }
 }
 flush007B14A0(lastType,lastTexture,lastTexture2,0);
 }
 return projectionCount+render007B6520(rinfo);
}

struct IDirect3DDevice8 {
#define RENDER_STATE_SLOT(n) virtual void __stdcall slot##n()=0;
 RENDER_STATE_SLOT(00) RENDER_STATE_SLOT(01) RENDER_STATE_SLOT(02) RENDER_STATE_SLOT(03)
 RENDER_STATE_SLOT(04) RENDER_STATE_SLOT(05) RENDER_STATE_SLOT(06) RENDER_STATE_SLOT(07)
 RENDER_STATE_SLOT(08) RENDER_STATE_SLOT(09) RENDER_STATE_SLOT(10) RENDER_STATE_SLOT(11)
 RENDER_STATE_SLOT(12) RENDER_STATE_SLOT(13) RENDER_STATE_SLOT(14) RENDER_STATE_SLOT(15)
 RENDER_STATE_SLOT(16) RENDER_STATE_SLOT(17) RENDER_STATE_SLOT(18) RENDER_STATE_SLOT(19)
 RENDER_STATE_SLOT(20) RENDER_STATE_SLOT(21) RENDER_STATE_SLOT(22) RENDER_STATE_SLOT(23)
 RENDER_STATE_SLOT(24) RENDER_STATE_SLOT(25) RENDER_STATE_SLOT(26) RENDER_STATE_SLOT(27)
 RENDER_STATE_SLOT(28) RENDER_STATE_SLOT(29) RENDER_STATE_SLOT(30) RENDER_STATE_SLOT(31)
 RENDER_STATE_SLOT(32) RENDER_STATE_SLOT(33) RENDER_STATE_SLOT(34) RENDER_STATE_SLOT(35)
 RENDER_STATE_SLOT(36) RENDER_STATE_SLOT(37) RENDER_STATE_SLOT(38) RENDER_STATE_SLOT(39)
 RENDER_STATE_SLOT(40) RENDER_STATE_SLOT(41) RENDER_STATE_SLOT(42) RENDER_STATE_SLOT(43)
 RENDER_STATE_SLOT(44) RENDER_STATE_SLOT(45) RENDER_STATE_SLOT(46) RENDER_STATE_SLOT(47)
 RENDER_STATE_SLOT(48) RENDER_STATE_SLOT(49) RENDER_STATE_SLOT(50) RENDER_STATE_SLOT(51)
 RENDER_STATE_SLOT(52) RENDER_STATE_SLOT(53) RENDER_STATE_SLOT(54) RENDER_STATE_SLOT(55)
 RENDER_STATE_SLOT(56)
#undef RENDER_STATE_SLOT
 virtual long __stdcall SetRenderState(unsigned long,unsigned long)=0;
};
extern unsigned number_of_DX8_calls;
class DX8Wrapper {
public:
 static unsigned RenderStates[256];
 static unsigned render_state_changes;
 static IDirect3DDevice8 *D3DDevice;
 static bool Has_Stencil();
 static void Get_DX8_Render_State_Value_Name(StringClass &,unsigned,unsigned);
 static void Clear(bool,bool,bool,const Vector3 &,float,float,unsigned);
 static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
};

#define APPLY_PROJECTED_SHADOW_STATE(state,value) do { \
 if (DX8Wrapper::RenderStates[state]!=(unsigned)(value)) { \
  if (WW3D::Is_Snapshot_Activated()) { \
   StringClass value_name(0,true); \
   DX8Wrapper::Get_DX8_Render_State_Value_Name(value_name,state,(unsigned)(value)); \
  } \
  DX8Wrapper::RenderStates[state]=(unsigned)(value); \
  DX8Wrapper::_Get_D3D_Device8()->SetRenderState(state,(unsigned)(value)); \
  ++number_of_DX8_calls; \
  ++DX8Wrapper::render_state_changes; \
 } \
} while (0)

int W3DProjectedShadowManager::render007B6520(RenderInfoClass &)
{
 unsigned flags;
 flags=*(unsigned *)0x01306EB0;
 if ((flags&1)==0) {
  flags|=1;
  *(unsigned *)0x01306EB0=flags;
 }
 if ((flags&2)==0) {
  flags|=2;
  *(unsigned *)0x01306EB0=flags;
 }
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
    passCount=(*(unsigned char *)(*(unsigned *)0x012ED5C8+0xA77)==0)+1;
   } else {
    passCount=1;
   }
   if (DX8Wrapper::Has_Stencil()) {
    APPLY_PROJECTED_SHADOW_STATE(0x34,1);
    APPLY_PROJECTED_SHADOW_STATE(0x39,0xff);
    APPLY_PROJECTED_SHADOW_STATE(0x3a,0xffffffffu);
    APPLY_PROJECTED_SHADOW_STATE(0x3b,0xffffffffu);
    APPLY_PROJECTED_SHADOW_STATE(0x36,1);
    APPLY_PROJECTED_SHADOW_STATE(0x35,1);
   }
   for (int passIndex=0;passIndex<passCount;++passIndex) {
    Shadow007B6D30 *head=(Shadow007B6D30 *)m_1c;
    Shadow007B6D30 *shadow=head;
    ShadowTexture007B6D30 *lastTexture=0;
    ShadowTexture007B6D30 *lastTexture2=0;
    unsigned lastType=0;
    for (;shadow;shadow=shadow->nextd4) {
     if (shadow->enabled04 && !shadow->invisible05) {
      if (!lastTexture) lastTexture=head->texture68;
      if (!lastTexture2) lastTexture2=head->texture6c;
      if (!lastType) lastType=head->type34;
      unsigned type=head->type34;
      if (shadow->texture68!=lastTexture || shadow->texture6c!=lastTexture2 || type!=lastType) {
       flush007B14A0(lastType,lastTexture,lastTexture2,passIndex);
       lastType=type;
       lastTexture=shadow->texture68;
       lastTexture2=shadow->texture6c;
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
    APPLY_PROJECTED_SHADOW_STATE(0x34,0);
   }
  }
  if (DX8Wrapper::Has_Stencil()) {
   Vector3 clearColor(0,0,0);
   DX8Wrapper::Clear(false,false,true,clearColor,0.0f,1.0f,0);
  }
 return projectionCount;
}
#undef APPLY_PROJECTED_SHADOW_STATE
