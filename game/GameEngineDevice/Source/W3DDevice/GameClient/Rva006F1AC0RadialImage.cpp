// Retail private texture helper 0x006F18F0 and its radial-image caller 0x006F1AC0.
// See targets/game/reverse/identity_evidence/006f1ac0-native-setters.md.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug

// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include "ascii_string.h"
#include <stdlib.h>
typedef int Int;
typedef unsigned long UnsignedInt;
typedef float Real;

#include "rect.h"
#include "texture.h"

class ShroudFilter { public: unsigned char pad[0x0c]; int field0c; int field10; };
class ShroudTexture { public: ShroudFilter *getFilter(); };
class Gen_0090E810 { public: void bfmeSetFlag(unsigned char); };
class BFMEWaterTrackTextureHandle
{
public:
 TextureClass *texture;
 BFMEWaterTrackTextureHandle(const BFMEWaterTrackTextureHandle &o):texture(o.texture){if(texture)texture->Add_Ref();}
 ~BFMEWaterTrackTextureHandle(){if(texture)texture->Release_Ref();}
 ShroudFilter *getFilter(){return ((ShroudTexture*)this)->getFilter();}
 void setFlag(unsigned char value){((Gen_0090E810*)this)->bfmeSetFlag(value);}
};
extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char*,int,int);
struct Rva001408C0Target;
class AssetList { public: AssetList &operator<<(const AsciiString &); };
class BfmeList950B
{
 _STL::set<Rva001408C0Target*> prototypes;
 unsigned int field0c;
 bool changed;
public:
 BfmeList950B();
 BfmeList950B &insert006F18F0(const AsciiString &s) { ((AssetList *)this)->operator<<(s); return *this; }
};
// Keep the existing BfmeList950B constructor provider at 0x00143B20.
// Its 20-byte layout agrees with AssetList operator<< and native set cleanup.
// The inline insert adapter uses the already matched AssetList operation.
extern void Rva009EBAC0(int);
struct Rect006F1AC0 { struct Coord { float x,y; }; Coord lo,hi; };
class Image
{
 unsigned char pad00[0x14];
public:
 Rect006F1AC0 m_UVCoords;
 const Rect006F1AC0 *getUV()const{return &m_UVCoords;}
 unsigned char pad24[8];
 BFMEWaterTrackTextureHandle *m_rawTextureData;
 UnsignedInt m_status;
 UnsignedInt getStatus() const {return m_status;}
 AsciiString getFilename()const;
};
class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;
static BFMEWaterTrackTextureHandle texture006F18F0(const Image *image)
{
 if(image->getStatus() & 2)
 {
  BFMEWaterTrackTextureHandle texture(*image->m_rawTextureData);
  texture.getFilter()->field10=1;
  texture.getFilter()->field0c=1;
  return texture;
 }
 else
 {
  if(Rva0134FAA0)
  {
   BfmeList950B assets;
   assets.insert006F18F0(image->getFilename());
   Rva009EBAC0((int)&assets);
  }
  BFMEWaterTrackTextureHandle texture(BFMEGetWaterTrackTexture((char*)image->getFilename().str(),1,0));
  texture.getFilter()->field10=1;
  texture.getFilter()->field0c=1;
  texture.setFlag(1);
  return texture;
 }
}


extern "C" double __cdecl atan2(double,double);
extern "C" double __cdecl tan(double);
#pragma intrinsic(atan2,tan)
struct Pair006F1AC0 { float x,y; Pair006F1AC0 &operator=(const Pair006F1AC0 &v) { x=v.x; y=v.y; return *this; } };
class Render2DClass { public: void Add_Tri(const Vector2 &,const Vector2 &,const Vector2 &,const Vector2 &,const Vector2 &,const Vector2 &,unsigned long); };
struct Render006F1AC0 {
 int field00; char unknown04[0x50]; bool field54;
 void set00_006F1AC0(int v) { field00=v; }
 void set54_006F1AC0(bool v) { field54=v; }
 void setTexture006EB000(const BFMEWaterTrackTextureHandle &);
 void tri006EB070(const Pair006F1AC0 &a,const Pair006F1AC0 &b,const Pair006F1AC0 &c,const Pair006F1AC0 &u,const Pair006F1AC0 &v,const Pair006F1AC0 &w,unsigned long color) { ((Render2DClass *)this)->Add_Tri((const Vector2 &)a,(const Vector2 &)b,(const Vector2 &)c,(const Vector2 &)u,(const Vector2 &)v,(const Vector2 &)w,color); }
};
struct RadialImage006F1AC0 {
 char unknown00[0x164]; Render006F1AC0 *field164;
 void draw(Image *,float,float,float,float,float,unsigned long);
};
extern const float zero01075350;
extern const float epsilon0109BF40;
inline float pi006F1AC0() { return 3.14159265358979323846f; }
// ?draw@RadialImage006F1AC0@@QAEXPAVImage@@MMMMMK@Z present-unmatched
void RadialImage006F1AC0::draw(Image *image,float left,float top,float right,float bottom,float percent,unsigned long color)
{
 if(!image) return;
 const Rect006F1AC0 *uv=&image->m_UVCoords;
 if(!uv) return;
 static float angle012F81F8=pi006F1AC0()/2.0f;
 static float angle012F81F4=pi006F1AC0()*1.5f;
 static float angle012F81F0=pi006F1AC0()*2.0f;
 float angle=angle012F81F0-(angle012F81F0*percent)*0.01f;
 if(angle<=zero01075350) return;
 if(angle>angle012F81F0) angle=angle012F81F0;
 field164->set00_006F1AC0(2);
 field164->set54_006F1AC0(true);
 field164->setTexture006EB000(texture006F18F0(image));
 float width=right-left;
 float halfWidth=width*0.5f;
 float height=bottom-top;
 float halfHeight=height*0.5f;
 Pair006F1AC0 center={left+halfWidth,top+halfHeight};
 float widthHeight=width/height;
 float heightWidth=height/width;
 float halfU=(uv->hi.x-uv->lo.x)*0.5f;
 float halfV=(uv->hi.y-uv->lo.y)*0.5f;
 Pair006F1AC0 centerUV={uv->lo.x+halfU,uv->lo.y+halfV};
 float corner=(float)atan2(width,height);
 Pair006F1AC0 end={left,top};
 Pair006F1AC0 endUV={uv->lo.x,uv->lo.y};
 Pair006F1AC0 start={center.x,top};
 Pair006F1AC0 startUV={centerUV.x,uv->lo.y};
 bool done=false;
 if(angle<=corner) {
  float t=(float)tan(angle);
  end.x=(float)(center.x-halfHeight*t);
  endUV.x=(float)(centerUV.x-t*halfU*heightWidth);
  done=true;
 }
 field164->tri006EB070(center,end,start,centerUV,endUV,startUV,color);
 if(done) return;
 float boundary2=3.14159265358979323846f-corner;
 start.x=end.x; start.y=top; startUV=endUV;
 end.y=bottom; endUV.y=uv->hi.y;
 if(angle<=boundary2) {
  if(angle>angle012F81F8) {
   float t=(float)tan(angle-angle012F81F8);
   end.y=(float)(center.y+halfWidth*t);
   endUV.y=(float)(centerUV.y+t*halfV*widthHeight);
  } else {
   float t=(float)tan(angle012F81F8-angle);
   end.y=(float)(center.y-halfWidth*t);
   endUV.y=(float)(centerUV.y-t*halfV*widthHeight);
  }
  done=true;
 }
 field164->tri006EB070(center,end,start,centerUV,endUV,startUV,color);
 if(done) return;
 float boundary3=corner+3.14159265358979323846f;
 start=end; startUV=endUV;
 end.x=right; endUV.x=uv->hi.x;
 if(angle<=boundary3) {
  if(angle>3.14159265358979323846f) {
   float t=(float)tan(angle-3.14159265358979323846f);
   end.x=(float)(center.x+halfHeight*t);
   endUV.x=(float)(centerUV.x+t*halfU*heightWidth);
  } else {
   float t=(float)tan(3.14159265358979323846f-angle);
   end.x=(float)(center.x-halfHeight*t);
   endUV.x=(float)(centerUV.x-t*halfU*heightWidth);
  }
  done=true;
 }
 field164->tri006EB070(center,end,start,centerUV,endUV,startUV,color);
 if(done) return;
 float boundary4=angle012F81F0-corner;
 start=end; startUV=endUV;
 end.y=top; endUV.y=uv->lo.y;
 if(angle<=boundary4) {
  if(angle>angle012F81F4) {
   float t=(float)tan(angle-angle012F81F4);
   end.y=(float)(center.y-halfWidth*t);
   endUV.y=(float)(centerUV.y-t*halfV*widthHeight);
  } else {
   float t=(float)tan(angle012F81F4-angle);
   end.y=(float)(center.y+halfWidth*t);
   endUV.y=(float)(centerUV.y+t*halfV*widthHeight);
  }
  done=true;
 }
 field164->tri006EB070(center,end,start,centerUV,endUV,startUV,color);
 if(done) return;
 start=end; startUV=endUV;
 end.x=center.x; endUV.x=centerUV.x;
 float remaining=angle012F81F0-angle;
 if(remaining>epsilon0109BF40) {
  float t=(float)tan(remaining);
  end.x=(float)(center.x+halfHeight*t);
  endUV.x=(float)(centerUV.x+t*halfU*heightWidth);
 }
 field164->tri006EB070(center,end,start,centerUV,endUV,startUV,color);
}
