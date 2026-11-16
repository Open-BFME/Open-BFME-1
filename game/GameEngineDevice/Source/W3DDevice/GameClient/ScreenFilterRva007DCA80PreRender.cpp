// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWLib
// Retail0x007DB890: vtable0x01128C5C slot2; matched Rva007DCA80 constructor.
struct IDirect3DSurface8;
#include "../../../../Libraries/Source/WWVegas/WWMath/vector3.h"
class DX8Wrapper{public:static void Set_Render_Target(IDirect3DSurface8*,bool);static void Clear(bool,bool,bool,const Vector3&,float,float,unsigned);};
// The one global at 0x012ED5C8 is EA's GlobalData *TheWritableGlobalData
// (defined in Common/GlobalData.cpp). This TU reads/writes its +0xDBD flag
// through a view struct, so the extern carries the canonical type.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct Settings{char pad[0xdbd];bool active;};
// The snapshot copy is reached through ILT 0x0002D664, the ledger's 5-byte row
// ?j_0002d664@@YAXXZ (symbols.csv pins ?bfmeCopyCuSnap@@YAXPAX0@Z there and
// nothing defines it); the cdecl call casts the row's symbol to its shape.
void j_0002d664();
typedef void (*BfmeCopyCuSnapFn)(void*,void*);
struct Snap{int mode,count;float a,b,c,d;};
class Rva007DCA80{public:virtual bool preRender(bool&,int&);char pad0[0x14-4];float amount;int count;bool saved;char pad1[0x30-0x1d];bool valid;char pad2[3];char snap[0x18];IDirect3DSurface8*surface;};
bool Rva007DCA80::preRender(bool&skip,int&mode){
 skip=false;if(mode!=0)return false;mode=6;
 float scale=18.0f/count;
 Snap s;s.mode=2;s.count=count*2;s.a=0.18f;s.b=0.06f*scale;s.c=4.5f;s.d=0.11f*scale;
 amount=0.8f;
 ((BfmeCopyCuSnapFn)j_0002d664)(snap,&s);
 saved=((Settings*)TheWritableGlobalData)->active;((Settings*)TheWritableGlobalData)->active=false;
 DX8Wrapper::Set_Render_Target(surface,true);
 Vector3 black;black.X=0;black.Y=0;black.Z=0;
 DX8Wrapper::Clear(true,false,false,black,0,1,0);
 valid=true;return true;
}
