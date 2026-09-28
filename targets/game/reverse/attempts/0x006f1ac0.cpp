// ?d_006f1ac0@@YAXXZ
// partial score=0.99858757 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Unlanded complete reconstruction of retail RVA 0x006F1AC0, 1416 bytes.
// The radial textured fan is proven by the five Add_Tri calls and UV arithmetic.
// Owner/method identity remains unproved; all new ABI views retain the address.
// Texture helper RVA 0x006F18F0 returns a nontrivial four-byte handle by value.
// Its hidden output pointer is caller-cleaned; ECX holds the image.
extern "C" double __cdecl atan2(double,double);
extern "C" double __cdecl tan(double);
#pragma intrinsic(atan2,tan)
#include "ascii_string.h"
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
struct Pair006F1AC0 { float x,y; Pair006F1AC0 &operator=(const Pair006F1AC0 &v) { x=v.x; y=v.y; return *this; } };
struct Rect006F1AC0 { float left,top,right,bottom; };
class RefTarget006F1AC0 { public: int unknown00; unsigned short refs04; void release006F1AC0(); };
struct Handle006F1AC0 {
 RefTarget006F1AC0 *p;
 Handle006F1AC0(const Handle006F1AC0 &v):p(v.p) { if(p) ++p->refs04; }
 ~Handle006F1AC0() { if(p) p->release006F1AC0(); }
};
struct Image006F1AC0 {
 char unknown00[0x14]; Rect006F1AC0 m_UVCoords;
 char unknown24[8]; Handle006F1AC0 *raw2c; unsigned int status30;
 AsciiString name00520640();
 unsigned getStatus006F18F0() const {return status30;}
};

struct Filter006F18F0 { char unknown00[12]; int field0c,field10; };
struct HandleAccess006F18F0 { Filter006F18F0 *filter0090DD50(); void flag0090E810(unsigned char); };
struct Assets006F18F0 {
 char storage[20];
 Assets006F18F0(); ~Assets006F18F0();
 Assets006F18F0 &insert00141D00(const AsciiString &);
};
extern int tracking0134FAA0;
void track009EBAC0(Assets006F18F0 *);
Handle006F1AC0 load0090E910(const char *,int,int);
static __declspec(noinline) Handle006F1AC0 texture006F18F0(Image006F1AC0 *image)
{
 if(image->getStatus006F18F0()&2) {
  Handle006F1AC0 h=*image->raw2c;
  ((HandleAccess006F18F0 *)&h)->filter0090DD50()->field10=1;
  ((HandleAccess006F18F0 *)&h)->filter0090DD50()->field0c=1;
  return h;
 }
 if(tracking0134FAA0) {
  Assets006F18F0 assets;
  assets.insert00141D00(image->name00520640());
  track009EBAC0(&assets);
 }
 Handle006F1AC0 h=load0090E910(image->name00520640().str(),1,0);
 ((HandleAccess006F18F0 *)&h)->filter0090DD50()->field10=1;
 ((HandleAccess006F18F0 *)&h)->filter0090DD50()->field0c=1;
 ((HandleAccess006F18F0 *)&h)->flag0090E810(1);
 return h;
}

struct Render006F1AC0 {
 int field00; char unknown04[0x50]; bool field54;
 void setTexture006EB000(const Handle006F1AC0 &);
 void tri006EB070(const Pair006F1AC0 &,const Pair006F1AC0 &,const Pair006F1AC0 &,const Pair006F1AC0 &,const Pair006F1AC0 &,const Pair006F1AC0 &,unsigned long);
};
struct RadialImage006F1AC0 {
 char unknown00[0x164]; Render006F1AC0 *field164;
 void draw(Image006F1AC0 *,float,float,float,float,float,unsigned long);
};
extern const float zero01075350;
extern const float epsilon0109BF40;
inline float pi006F1AC0() { return 3.14159265358979323846f; }
void RadialImage006F1AC0::draw(Image006F1AC0 *image,float left,float top,float right,float bottom,float percent,unsigned long color)
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
 field164->field00=2;
 field164->field54=true;
 field164->setTexture006EB000(texture006F18F0(image));
 float width=right-left;
 float halfWidth=width*0.5f;
 float height=bottom-top;
 float halfHeight=height*0.5f;
 Pair006F1AC0 center={left+halfWidth,top+halfHeight};
 float widthHeight=width/height;
 float heightWidth=height/width;
 float halfU=(uv->right-uv->left)*0.5f;
 float halfV=(uv->bottom-uv->top)*0.5f;
 Pair006F1AC0 centerUV={uv->left+halfU,uv->top+halfV};
 float corner=(float)atan2(width,height);
 Pair006F1AC0 end={left,top};
 Pair006F1AC0 endUV={uv->left,uv->top};
 Pair006F1AC0 start={center.x,top};
 Pair006F1AC0 startUV={centerUV.x,uv->top};
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
 end.y=bottom; endUV.y=uv->bottom;
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
 end.x=right; endUV.x=uv->right;
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
 end.y=top; endUV.y=uv->top;
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
