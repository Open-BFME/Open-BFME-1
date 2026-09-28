// ?d_0079d530@@YAXXZ
// partial score=0.971 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath
// 0079D530: four-point inside/outside miter construction, owner name unproved.
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
class Display {public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0c();
 virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1c();
 virtual void slot20();virtual void slot24();virtual void slot28();virtual unsigned slot2c();
};
extern Display *TheDisplay;
struct Width0079D530 {char pad00[0x24];int value24;};
class QuadrilateralInset0079D530 {public:
 char pad00[0x4dc]; BfmeVec2CY points4dc[4]; char pad4fc[0x20]; Width0079D530 *settings51c;
 char pad520[4]; BfmeVec2CY copy524[4],inner544[4],outer564[4];
 void update();
};
static inline float wrapAngle(float a){
 if(a<0.0f)return 6.2831855f-(float)fmod(-a,6.2831855f);
 return (float)fmod(a,6.2831855f);
}
static inline int nextIndex(int next){if(next>=4)next-=4;return next;}
static inline float widthScale(float w){return w*(float)TheDisplay->slot2c()/1024.0f;}
static inline float angleDifference(float a,float b){if(a<b)a+=6.2831855f;return a-b;}
void QuadrilateralInset0079D530::update(){
 float minimum=FLT_MAX;
 for(int i=0;i<4;i++){
  int next=i-3;if(i+1<4)next=i+1;
  BfmeVec2CY edge=subtract0079CFF0(BfmeVec2CY(points4dc[next]),points4dc[i]);
  float len=edge.length();if(len<minimum)minimum=len;
 }
 int rawWidth=settings51c->value24;
 float width=(float)rawWidth*(float)TheDisplay->slot2c()/1024.0f;
 if(width>minimum)width=minimum;
 BfmeVec2CY *prev=&points4dc[3];
 for(int i=0;i<4;i++){
  int next=i+1;if(next>=4)next=i-3;
  BfmeVec2CY &point=points4dc[i];
  inner544[i]=point;
  outer564[i]=point;
  if(!point.IsExactlyEqualTo(points4dc[next]) && !point.IsExactlyEqualTo(*prev)){
   float first=wrapAngle(subtract0079CFF0(points4dc[next],point).toAngle());
   float second=wrapAngle(subtract0079CFF0(*prev,point).toAngle());
   float middle=wrapAngle(angleDifference(second,first)*0.5f+first);
   float angle=middle;
   if(angle<first)angle+=6.2831855f;
   angle-=first;
   if(fabs(angle)>0.00001f){
    float distance=width*0.5f/(float)sin(angle);
    BfmeVec2CY offset;offset.y=(float)sin(middle)*distance;offset.x=(float)cos(middle)*distance;
    inner544[i]+=offset;outer564[i]-=offset;
   }
  }
  prev=&point;
 }
 copy524[0]=points4dc[0];copy524[1]=points4dc[1];copy524[2]=points4dc[2];copy524[3]=points4dc[3];
}

