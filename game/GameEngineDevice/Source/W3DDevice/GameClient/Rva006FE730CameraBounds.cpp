// RVA 0x006FE730, 644 bytes. Camera-bounds update; public owner unproved.
// Retail field +0x84 uses RenderObjClass slots +0x104 Get_Bounding_Box and
// +0x54 Set_Transform. Native WWMath/WW3D declarations supply those contracts.
// The global at VA 0x012F706C exposes the configuration view at +0x0c;
// opaque fields retain offsets relative to that view, not guessed identities.
// ILT 0x000460A1 -> 0x006FDCB0: thiscall, no stack args, void.
// ILT 0x00042843 -> 0x006FD990: thiscall, one Vector3[4] out pointer, ret 4.
// Member-pointer adapters preserve those observed ECX/stack contracts.
// Float-valued tangent/reciprocal and reference-parameter multiplication
// preserve retail rounding lifetimes and scheduling without compiler switches.
// cl: /DNDEBUG /MD /EHsc /O2 /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Include
#include "camera.h"
#include "aabox.h"
#include <math.h>
class BfmeGameCW;
extern BfmeGameCW *g_bfmeGameCW;
extern void j_000460a1();
extern void j_00042843();
struct Rva006FE730Config {
 char pad000[4]; float field04,field08,field0c,field10;
 char pad014[0x130]; float field144,field148;
};
class Rva006FE730CameraBounds {
public:
 void update();
 char pad000[0x84]; RenderObjClass* object84;
 float field88,field8c; char pad090[0x18];
 Vector3 fielda8,fieldb4,fieldc0;
 float fieldcc,fieldd0,fieldd4,fieldd8,fielddc,fielde0,fielde4;
 char pad0e8[8]; Vector3 fieldf0[4]; AABoxClass box120;
};
static __forceinline void projection006FE730(void* self) {
 struct Thunk { void call(); }; typedef void (Thunk::*Function)();
 union {void (*raw)(); Function member;} f; f.raw=j_000460a1;
 (reinterpret_cast<Thunk*>(self)->*f.member)();
}
static __forceinline void corners006FE730(void* self,Vector3* points) {
 struct Thunk { void call(Vector3*); }; typedef void (Thunk::*Function)(Vector3*);
 union {void (*raw)(); Function member;} f; f.raw=j_00042843;
 (reinterpret_cast<Thunk*>(self)->*f.member)(points);
}
static __forceinline float tan006FE730(float angle) { return tan(angle); }
static __forceinline float recip006FE730(float x) { return 1.0f/x; }
static __forceinline float mul006FE730(const float& a,const float& b) { return a*b; }
void Rva006FE730CameraBounds::update() {
 box120=object84->Get_Bounding_Box();
 Rva006FE730Config* config=reinterpret_cast<Rva006FE730Config*>(reinterpret_cast<char*>(g_bfmeGameCW)+0xc);
 box120.Extent.X=config->field0c;
 box120.Extent.Y=config->field10;
 box120.Center.X=config->field04;
 box120.Center.Y=config->field08;
 fieldb4=box120.Center;
 fieldb4.Z=0.0f;
 fielda8=fieldb4;
 float tangent=tan006FE730(0.4363323152065277f); float factor=recip006FE730(tangent);
 float width=(box120.Extent.X-fieldd0)*factor;
 float height=mul006FE730((box120.Extent.Y-fieldd0)*1.333f,factor);
 Matrix3D transform(true);
 transform.Set_Translation(Vector3(0.0f,0.0f,-(box120.Center.Z-box120.Extent.Z)));
 box120.Center.Z=box120.Extent.Z;
 object84->Set_Transform(transform);
 if(width<height) width=height;
 field8c=width;
 fielde4=0.0f;
 projection006FE730(this);
 Vector3 points[4]; corners006FE730(this,points);
 float dx=fielda8.X-points[0].X;
 fieldd4=(box120.Center.X-box120.Extent.X*config->field144)+fieldd0+dx;
 fielddc=(box120.Extent.X*config->field144+box120.Center.X)-(dx+fieldd0);
 fieldd8=(fielda8.Y-points[2].Y)+(box120.Center.Y-config->field148*box120.Extent.Y)+fieldd0;
 fielde0=(config->field148*box120.Extent.Y+box120.Center.Y)-((points[0].Y-fielda8.Y)+fieldd0);
 fielde4=1.0f;
 projection006FE730(this);
 corners006FE730(this,fieldf0);
}
