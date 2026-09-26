#include <string.h>
// cl: /DNDEBUG /MD
// Retail 0x007D6E40: highlight filter vtable 0x01128B88 slot 2.
struct IDirect3DSurface8;
struct Desc {unsigned Format,Type,Usage,Pool,MultiSampleType,MultiSampleQuality,Width,Height;};
struct SurfaceVtable {char pad[0x30]; long (__stdcall *GetDesc)(IDirect3DSurface8*,Desc*);};
struct IDirect3DSurface8{SurfaceVtable *v;};
struct Rect{long left,top,right,bottom;};
struct Device;
struct DeviceVtable{char pad[0x88];long (__stdcall *StretchRect)(Device*,IDirect3DSurface8*,const Rect*,IDirect3DSurface8*,const Rect*,unsigned);};
struct Device{DeviceVtable*v;};
class W3DRadarResetSurface{public:IDirect3DSurface8*p;~W3DRadarResetSurface();};
W3DRadarResetSurface getBackBufferSurface006e(int);
class Vector3{public:float X,Y,Z;};
class DX8Wrapper{public:static void Set_Render_Target(IDirect3DSurface8*,bool);static void Clear(bool,bool,bool,const Vector3&,float,float,unsigned);};
extern Device *HighlightDevice;
extern bool HighlightRefresh;
struct Settings{char p[0xdbd];bool active;};
extern Settings *HighlightSettings;
unsigned bfmeCurrentCU();void bfmeCopyCuSnap(void*,void*);
struct Cu {unsigned f[8];};
class ScreenHilightFilter {
public:
 virtual bool preRender(bool&,int&);
 unsigned pixelShader,vertexShader,size,index;
 bool valid;char pad14[3];unsigned pad18[5];
 IDirect3DSurface8 *surface[2];
};
bool ScreenHilightFilter::preRender(bool &skip,int &mode){
 skip=false;
 if(HighlightRefresh){
  unsigned snap[6];snap[0]=2;
  snap[1]=((Cu*)bfmeCurrentCU())->f[1];snap[3]=((Cu*)bfmeCurrentCU())->f[5];snap[5]=((Cu*)bfmeCurrentCU())->f[7];snap[2]=((Cu*)bfmeCurrentCU())->f[4];snap[4]=((Cu*)bfmeCurrentCU())->f[6];
  bfmeCopyCuSnap((char*)this+0x18,snap);HighlightRefresh=false;
 }
 if(HighlightSettings&&HighlightSettings->active){
  IDirect3DSurface8 *dest=surface[index+1];
  IDirect3DSurface8 *src=getBackBufferSurface006e(0).p;
  Device *dev=HighlightDevice;
  Desc d;memset(&d,0,sizeof(d));
  if(src)src->v->GetDesc(src,&d);
  Rect source;source.bottom=d.Height;source.right=d.Width;source.top=0;source.left=0;
  Rect target;target.bottom=size;target.right=size;target.top=0;target.left=0;
  dev->v->StretchRect(dev,src,&source,dest,&target,2);

  ++index;
  if(index==1)index=0;
 }else{
  DX8Wrapper::Set_Render_Target(surface[0],true);
  Vector3 black;black.X=0;black.Y=0;black.Z=0;
  DX8Wrapper::Clear(true,false,false,black,0,1,0);

 }
 valid=true; return true;
}



