// ?d_0079d530@@YAXXZ
// partial score=0.7825 date=2026-09-28
// ?rva0079D530@AptPalantir@@QAEXXZ
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath
//
// AptPalantir 0x0079D530: rebuilds the inner and outer radar view-box quads
// from the four view-box corners at +0x4DC, insetting by the RadarViewBoxEdge
// image width scaled by TheDisplay->getWidth() / 1024.
//
// Identity: the only caller, 0x0079DEE0, is slot 10 (+0x28) of vtable
// 0x01127A48, which the matched AptPalantir constructor (0x0079D9F0) installs,
// and slot 10 is renderRadarViewBox (matched aptPalantirRenderRadarViewBox).
// The fields read and written (+0x51C RadarViewBoxEdge image, Coord2D[4] at
// +0x524/+0x544/+0x564) are the constructor/destructor's witnessed layout.
// The method name is not proven, so it keeps the address token.
// Image+0x24 is m_imageSize (name_oracle, layout witness).
//
// The subtraction callee (0x0079CFF0, reached through ILT 0x00402DBF) returns
// a Coord2D-like pair by hidden pointer, taking the left operand by value and
// the right by reference; the ledger row names it bfmeSubtract with a
// (float,float,const*) signature that has the same stack layout.
struct FloatPairBase0079D530 {float x,y;};
class BfmeVec2CY : public FloatPairBase0079D530 { public:
 BfmeVec2CY();BfmeVec2CY(const BfmeVec2CY &);BfmeVec2CY(float,float);~BfmeVec2CY();
 BfmeVec2CY &operator+=(const BfmeVec2CY &); BfmeVec2CY &operator-=(const BfmeVec2CY &);
 float length()const;float toAngle()const;bool IsExactlyEqualTo(const BfmeVec2CY &)const;
};
#include <math.h>
#include <float.h>
inline BfmeVec2CY::BfmeVec2CY(){}
inline BfmeVec2CY::BfmeVec2CY(const BfmeVec2CY &v){x=v.x;y=v.y;}
inline BfmeVec2CY::BfmeVec2CY(float a,float b){x=a;y=b;}
inline BfmeVec2CY::~BfmeVec2CY(){}

inline BfmeVec2CY &BfmeVec2CY::operator+=(const BfmeVec2CY &v){x+=v.x;y+=v.y;return *this;}
inline BfmeVec2CY &BfmeVec2CY::operator-=(const BfmeVec2CY &v){x-=v.x;y-=v.y;return *this;}
inline float BfmeVec2CY::length()const{return (float)sqrt(x*x+y*y);}
inline float BfmeVec2CY::toAngle()const{return (float)atan2(y,x);}
inline bool BfmeVec2CY::IsExactlyEqualTo(const BfmeVec2CY &v)const{return x==v.x && y==v.y;}

BfmeVec2CY subtract0079CFF0(BfmeVec2CY,const BfmeVec2CY &);
#pragma comment(linker, "/alternatename:?subtract0079CFF0@@YA?AVBfmeVec2CY@@V1@ABV1@@Z=?j_00002dbf@@YAXXZ")

class Display {public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0c();
 virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1c();
 virtual void slot20();virtual void slot24();virtual void slot28();virtual unsigned getWidth();
};
extern Display *TheDisplay;

struct ICoord2D0079D530 {int x,y;};
class Image {public:
 char pad00[0x24]; ICoord2D0079D530 m_imageSize;
};

class AptPalantir {public:
 char pad00[0x4dc]; BfmeVec2CY m_points4dc[4]; char pad4fc[0x20]; const Image *m_image51c;
 char pad520[4]; BfmeVec2CY m_coords524[4],m_coords544[4],m_coords564[4];
 void rva0079D530();
};

static inline float wrapAngle(float a){
 if(a<0.0f)return 6.2831855f-(float)fmod(-a,6.2831855f);
 return (float)fmod(a,6.2831855f);
}
static inline float angleDifference(float a,float b){if(a<b)a+=6.2831855f;return a-b;}

void AptPalantir::rva0079D530(){
 float minimum=FLT_MAX;
 for(int i=0;i<4;i++){
  int next=i-3;if(i+1<4)next=i+1;
  BfmeVec2CY edge=subtract0079CFF0(BfmeVec2CY(m_points4dc[next]),m_points4dc[i]);
  float len=edge.length();if(len<minimum)minimum=len;
 }
 // An int local converted into a float local: fild after the call and a
 // separate fmulp, where a single cast expression folds into fimul.
 int rawWidth=m_image51c->m_imageSize.x;
 float width=(float)rawWidth;width=width*(float)TheDisplay->getWidth()/1024.0f;
 if(width>minimum)width=minimum;
 BfmeVec2CY *prev=&m_points4dc[3];
 for(int i=0;i<4;i++){
  int next=i+1;if(next>=4)next=i-3;
  BfmeVec2CY &point=m_points4dc[i];
  m_coords544[i]=point;
  m_coords564[i]=point;
  if(!point.IsExactlyEqualTo(m_points4dc[next]) && !point.IsExactlyEqualTo(*prev)){
   float first=wrapAngle(subtract0079CFF0(m_points4dc[next],point).toAngle());
   float second=wrapAngle(subtract0079CFF0(*prev,point).toAngle());
   float middle=wrapAngle(angleDifference(second,first)*0.5f+first);
   float angle=middle;
   if(angle<first)angle+=6.2831855f;
   angle-=first;
   if(fabs(angle)>0.00001f){
    float distance=width*0.5f/(float)sin(angle);
    // Retail computes cos first and keeps x on the x87 stack across fsin,
    // spilling y; every spelling tried keeps whichever is assigned last.
    BfmeVec2CY offset;offset.y=(float)sin(middle)*distance;offset.x=(float)cos(middle)*distance;
    m_coords544[i]+=offset;m_coords564[i]-=offset;
   }
  }
  prev=&point;
 }
 m_coords524[0]=m_points4dc[0];m_coords524[1]=m_points4dc[1];m_coords524[2]=m_points4dc[2];m_coords524[3]=m_points4dc[3];
}
