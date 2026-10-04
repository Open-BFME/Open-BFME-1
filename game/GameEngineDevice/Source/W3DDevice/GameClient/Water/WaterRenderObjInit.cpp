// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// BFME WaterRenderObjClass::init, RVA 0x007A5200 (1383 bytes).
// Identity: ZH W3DWater.cpp init and the retail W3DTerrainVisual init caller.
// BFME puts the render-object subobject at +4 and uses RAII device/texture
// wrappers. The ZH water layout cannot represent those offsets.
// LightClass Ambient/Diffuse/Specular and VertexMaterialClass CRCDirty /
// UseLighting use name_oracle witnesses. Other BFME-only offsets retain tokens.
// The 32-entry bump arrays start at +0x144 and +0x1C4. Their end is +0x244.
// Texture references use a 16-bit count at +4; render objects use 32-bit +4.
#include "vector3.h"
#include "ascii_string.h"
#include <stdio.h>
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
void W3DRadarResetLock();
char bfmeUnlock1179();
struct WaterDeviceScope007A5200 { WaterDeviceScope007A5200(){W3DRadarResetLock();} ~WaterDeviceScope007A5200(){bfmeUnlock1179();} };
class TextureBaseClass { public: void Release_Ref(); };
class BFMEWaterTrackTextureHandle { public: TextureBaseClass *m_texture; ~BFMEWaterTrackTextureHandle(){if(m_texture)((TextureBaseClass *)m_texture)->Release_Ref();} };
BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char*,int,int);
static inline void assignTexture(TextureBaseClass *&dest,const BFMEWaterTrackTextureHandle &src) {
 if(src.m_texture) ++*(unsigned short*)((char*)src.m_texture+4);
 if(dest) dest->Release_Ref();
 dest=src.m_texture;
}
class SurfaceClass { public: void DrawPixel(unsigned,unsigned,unsigned); };
class W3DRadarResetSurface : public SurfaceClass { public: ~W3DRadarResetSurface(); void *m_surface; };
class W3DRadarResetTexture { public: W3DRadarResetSurface getSurfaceLevel(); void *m_texture; };
class Rva006D6050 { public: void init(unsigned,unsigned,unsigned,unsigned,unsigned,unsigned); };
class LightClass { public:
 enum LightType { POINT=0,DIRECTIONAL=1 };
 LightClass(LightType);
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
 virtual void Set_Position(const Vector3&);
 char m_pad04[0xd4];
 Vector3 Ambient,Diffuse,Specular;
 char m_padfc[0x1c];
 Vector3 m_spot118;
 void Set_Ambient(const Vector3 &v){Ambient=v;}
 void Set_Diffuse(const Vector3 &v){Diffuse=v;}
 void Set_Specular(const Vector3 &v){Specular=v;}
 void Set_Spot_Direction(const Vector3 &v){m_spot118=v;}
};
class VertexMaterialClass { public:
 VertexMaterialClass();
 void Set_Shininess(float); void Set_Ambient(float,float,float); void Set_Diffuse(float,float,float); void Set_Specular(float,float,float); void Set_Opacity(float);
 enum PresetType { PRELIT_DIFFUSE=0 };
 static VertexMaterialClass *Get_Preset(PresetType);
 char m_pad00[0x68]; bool CRCDirty,UseLighting; char m_pad6a[2];
 void Set_Lighting(bool v){CRCDirty=true;UseLighting=v;}
};
class RenderObjClass { public:
 virtual void Delete_This(); virtual void slot01(); virtual void slot02(); virtual int Class_ID() const;
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
 virtual int Get_Num_Sub_Objects() const; virtual void slot28(); virtual RenderObjClass *Get_Sub_Object(int) const;
 int m_refCount;
};
RenderObjClass *Create_Render_Obj(const char*);
class WaterRenderDispatch007A5200 { public:
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
 virtual void Set_Sort_Level(int);
 virtual void slot095();
 virtual void slot096();
 virtual void slot097();
 virtual void slot098();
 virtual void slot099();
 virtual void slot100();
 virtual void slot101();
 virtual void slot102();
 virtual void slot103();
 virtual void Set_Force_Visible(int);
 char m_pad04[0xc8];
};
enum ChipsetType { CHIPSET_0,CHIPSET_1,CHIPSET_2,CHIPSET_3 };
class W3DShaderManager { public: static ChipsetType getChipset(); };
class WaterTracksRenderSystem { public: WaterTracksRenderSystem(); char m_data[0x28]; };
class WaterTracksRenderSystemInitShim { public: void init(); };
class SceneClass;
enum WaterType { WATER_TYPE_0,WATER_TYPE_1,WATER_TYPE_2 };
enum TimeOfDay { TOD_0,TOD_1,TOD_2,TOD_3,TOD_4 };
struct SkySettings007A5200 { int m_00; AsciiString m_04,m_08,m_0c,m_10,m_14; };
struct SkyNode007A5200 { void *m_00; AsciiString m_04; SkySettings007A5200 *m_08; };
class SkyMap007A5200 { public: SkyNode007A5200 *find000B8A10(const AsciiString&); };
extern SkyMap007A5200 skyMap012F1404;
struct Shader007A5200 { unsigned bits; void disableCull(){bits &= ~0x100000;} };
extern Shader007A5200 shader012BBBA8;
class WaterRenderObjClass { public:
 struct Setting { char data[0x30]; };
 void *m_vptr;
 WaterRenderDispatch007A5200 m_render04;
 SceneClass *m_d0;
 Shader007A5200 m_d4;
 VertexMaterialClass *m_d8,*m_dc;
 LightClass *m_e0;
 TextureBaseClass *m_e4;
 float m_e8,m_ec;
 Vector3 m_f0;
 float m_fc,m_100,m_104,m_108,m_10c,m_110;
 unsigned long m_114;
 int m_118;
 WaterType m_11c;
 int m_pad120[9];
 void *m_144[32],*m_1c4[32];
 int m_244; float m_248; int m_24c;
 RenderObjClass *m_250;
 WaterTracksRenderSystem *m_254;
 char m_pad258[0x50];
 W3DRadarResetTexture m_2a8;
 char m_pad2ac[0x1c];
 AsciiString m_2c8,m_2cc,m_2d0,m_2d4,m_2d8,m_2dc;
 char m_pad2e0[0x30]; Setting m_310,m_340,m_370,m_3a0;
 int init(float,float,float,SceneClass*,WaterType);
protected:
 void loadSetting(Setting*,TimeOfDay);
public:
 void resources007A0500();
 void initBump0079E700(void **,const BFMEWaterTrackTextureHandle&);
 void clamp007A0960(RenderObjClass*);
};
int WaterRenderObjClass::init(float waterLevel,float dx,float dy,SceneClass *parentScene,WaterType type) {
 WaterDeviceScope007A5200 lock;
 m_244=0; m_248=0.06f;
 m_e8=dx; m_ec=dy; m_100=waterLevel;
 m_114=timeGetTime();
 m_10c=0.001f; m_110=0.001f; m_104=0; m_108=0;
 m_d0=parentScene; m_11c=type;
 m_f0=Vector3(0,0,1); m_fc=m_100;
 m_e0=new LightClass(LightClass::DIRECTIONAL);
 m_e0->Set_Ambient(Vector3(0.1f,0.1f,0.1f));
 m_e0->Set_Diffuse(Vector3(1,1,1));
 m_e0->Set_Specular(Vector3(1,1,1));
 m_e0->Set_Position(Vector3(1000,1000,1000));
 m_e0->Set_Spot_Direction(Vector3(-0.57f,-0.57f,-0.57f));
 m_dc=new VertexMaterialClass;
 m_dc->Set_Shininess(20);
 m_dc->Set_Ambient(1,1,1); m_dc->Set_Diffuse(1,1,1); m_dc->Set_Specular(0.5f,0.5f,0.5f); m_dc->Set_Opacity(0.5f);
 m_dc->Set_Lighting(true);
 loadSetting(&m_310,TOD_1);loadSetting(&m_340,TOD_2);loadSetting(&m_370,TOD_3);loadSetting(&m_3a0,TOD_4);
 m_render04.Set_Sort_Level(2);m_render04.Set_Force_Visible(1);
 resources007A0500();
 if(type==WATER_TYPE_2 || W3DShaderManager::getChipset()>=CHIPSET_3) {
  int i=32;
  while(i--) {
   char name[128];
   sprintf(name,"caust%.2d.tga",i);
   initBump0079E700(m_144+i,BFMEGetWaterTrackTexture(name,0,0));
   sprintf(name,"caustS%.2d.tga",i);
   initBump0079E700(m_1c4+i,BFMEGetWaterTrackTexture(name,0,0));
  }
 }
 m_d8=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
 m_d4=shader012BBBA8;m_d4.disableCull();
 assignTexture(m_e4,BFMEGetWaterTrackTexture("TSMoonLarg.tga",0,0));
 m_250=Create_Render_Obj("new_skybox");
 SkyNode007A5200 *node=skyMap012F1404.find000B8A10(m_2c8);
 m_2cc=node->m_08->m_04; m_2d0=node->m_08->m_08;m_2d4=node->m_08->m_0c;m_2d8=node->m_08->m_10;m_2dc=node->m_08->m_14;
 if(m_250) {
  if(m_250->Class_ID()==25) {
   for(int i=0;i<m_250->Get_Num_Sub_Objects();++i) {
    RenderObjClass *obj=m_250->Get_Sub_Object(i);
    if(obj) {
     if(obj->Class_ID()==0)clamp007A0960(obj);
     if(--obj->m_refCount==0)obj->Delete_This();
    }
   }
  } else if(m_250->Class_ID()==0)clamp007A0960(m_250);
 }
 ((Rva006D6050*)&m_2a8)->init(1,1,0x1a,1,1,0);
 m_2a8.getSurfaceLevel().DrawPixel(0,0,0xffffffff);
 m_254=new WaterTracksRenderSystem;
 ((WaterTracksRenderSystemInitShim*)m_254)->init();
 return 0;
}
