// cl: /DNDEBUG /MD
#include <string.h>
// Retail 0x007D7040, highlight filter vtable 0x01128B88 slot 3.
// Arg1 is the mode; arg3 is a bool reference; arg4 is the UV pointer.
// Arg2 is unused in retail and its original type is unknown.
struct IDirect3DSurface8;struct Texture;
struct Device;
struct DeviceVtable {
 char p0[0xe4];long (__stdcall *SetRenderState)(Device*,unsigned long,unsigned);
 char p1[0x104-0xe8];long (__stdcall *SetTexture)(Device*,unsigned,Texture*);
 char p2[4];long (__stdcall *SetTextureStageState)(Device*,unsigned,unsigned,unsigned);
 char p3[4];long (__stdcall *SetSamplerState)(Device*,unsigned,unsigned,unsigned);
 char p4[0x15c-0x118];long (__stdcall *SetFVF)(Device*,unsigned);
 char p5[0x170-0x160];long (__stdcall *SetVertexShader)(Device*,unsigned);
 char p6[0x1ac-0x174];long (__stdcall *SetPixelShader)(Device*,unsigned);
 char p7[4];long (__stdcall *SetPixelShaderConstantF)(Device*,unsigned,const float*,unsigned);
};
struct Device{DeviceVtable*v;};
struct Coord2D{float x,y;};class Vector3{public:float X,Y,Z;};
class DX8Wrapper{public:static void Set_Render_Target(IDirect3DSurface8*,bool);static void Clear(bool,bool,bool,const Vector3&,float,float,unsigned);static void Set_DX8_Render_State(unsigned long,unsigned);static void Apply_Render_State_Changes();};
extern Device *HighlightDevice;
extern bool HighlightRendering;
struct Settings{char p[0xdbd];bool active;};extern Settings *HighlightSettings;
extern unsigned HighlightFVF,ScreenTotalChanges,HighlightColorIndex;
struct Color{float x,y,z,w;};extern Color HighlightColors[];
extern Color HighlightPixelConstants[];
unsigned bfmeCurrentCU();struct Cu{unsigned f[8];};
void bfmeHighlightDrawQuad(unsigned);
void bfmeHighlightApply(unsigned,void*,unsigned,Texture*,IDirect3DSurface8*,Texture*,IDirect3DSurface8*);
void bfmeDrawFilterUV(int,int,Coord2D*);
class ScreenHilightFilter{
public:
 virtual int init();virtual int shutdown();virtual bool preRender(bool&,int&);virtual bool postRender(int,unsigned,bool&,Coord2D*);virtual bool setup(int);virtual int set(int);virtual void reset();
 unsigned pixelShader,vertexShader,size,index;bool valid;char pad[3];unsigned snap[3];Texture*texture[2];IDirect3DSurface8*surface[2];
};
bool ScreenHilightFilter::postRender(int mode,unsigned unused,bool&extra,Coord2D*uv){
 HighlightRendering=false;
 if(valid){DX8Wrapper::Set_Render_Target(0,true);reset();extra=true;valid=false;return true;}
 if(!set(mode))return false;
 Device *dev=HighlightDevice;
 if(HighlightSettings&&HighlightSettings->active){
  DX8Wrapper::Set_Render_Target(surface[0],false);
  union {Vector3 black;Color color;};black.X=0;black.Y=0;black.Z=0;DX8Wrapper::Clear(true,false,false,black,0,1,0);
  dev->v->SetSamplerState(dev,0,1,3);dev->v->SetSamplerState(dev,0,2,3);dev->v->SetSamplerState(dev,0,5,2);dev->v->SetSamplerState(dev,0,6,2);dev->v->SetSamplerState(dev,0,7,2);
  dev->v->SetRenderState(dev,22,1);dev->v->SetRenderState(dev,14,0);dev->v->SetRenderState(dev,7,0);
  dev->v->SetTextureStageState(dev,0,24,0);dev->v->SetTextureStageState(dev,1,24,0);
  dev->v->SetTexture(dev,0,texture[index+1]);dev->v->SetPixelShader(dev,pixelShader);
  HighlightDevice->v->SetFVF(HighlightDevice,HighlightFVF);++ScreenTotalChanges;
  dev->v->SetVertexShader(dev,vertexShader);
  color.x=HighlightColors[HighlightColorIndex].x-1.0f;color.y=HighlightColors[HighlightColorIndex].y-1.0f;color.z=HighlightColors[HighlightColorIndex].z-1.0f;color.w=0;
  if(memcmp(&color,HighlightPixelConstants,16)!=0){HighlightPixelConstants[0]=color;HighlightDevice->v->SetPixelShaderConstantF(HighlightDevice,0,&color.x,1);++ScreenTotalChanges;}
  dev->v->SetRenderState(dev,27,0);dev->v->SetRenderState(dev,19,2);dev->v->SetRenderState(dev,20,1);
  bfmeHighlightDrawQuad(size);DX8Wrapper::Set_Render_Target(0,true);
 }
 bfmeHighlightApply(((Cu*)bfmeCurrentCU())->f[2],snap,size,texture[0],surface[index+1],texture[index+1],surface[0]);
 HighlightDevice->v->SetTexture(HighlightDevice,0,texture[0]);
 DX8Wrapper::Set_DX8_Render_State(19,2);DX8Wrapper::Set_DX8_Render_State(20,4);DX8Wrapper::Set_DX8_Render_State(27,1);DX8Wrapper::Apply_Render_State_Changes();
 dev->v->SetTextureStageState(dev,0,5,1);dev->v->SetTextureStageState(dev,0,6,2);dev->v->SetTextureStageState(dev,0,4,2);dev->v->SetTextureStageState(dev,0,24,0);dev->v->SetTextureStageState(dev,1,24,0);
 dev->v->SetVertexShader(dev,0);
 bfmeDrawFilterUV(-1,1,uv);reset();return true;
}


