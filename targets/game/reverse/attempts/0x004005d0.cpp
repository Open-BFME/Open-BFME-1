// ?method@Rva004005D0@@QAEXPAXPAURva004005D0Node@@1PBURva004005D0Vector@@M@Z
// partial score=0.2235 date=2026-10-03
#include <math.h>
extern const float BfmeShadowScale, BfmeZeroRange, g_bfmeK1253;
extern float g_bfmeDefaultBU;
void j_0001e31c();
struct Rva004005D0Vector {
 float x,y,z;
 Rva004005D0Vector() {}
 Rva004005D0Vector(const Rva004005D0Vector &r) {x=r.x;y=r.y;z=r.z;}
 Rva004005D0Vector &operator=(const Rva004005D0Vector &r) {x=r.x;y=r.y;z=r.z;return *this;}
 void scale(float s) {x*=s;y*=s;z*=s;}
 void add(const Rva004005D0Vector &r) {x+=r.x;y+=r.y;z+=r.z;}
 void sub(const Rva004005D0Vector &r) {x-=r.x;y-=r.y;z-=r.z;}
 void normalize() {float length=(float)sqrt(x*x+y*y+z*z);if(length!=0.0f){float s=1.0f/length;scale(s);}}
};
struct Rva004005D0Node {char m_00[12];Rva004005D0Vector m_0c;};
struct Rva004005D0Config {unsigned char m_00,m_01;float m_04;unsigned char m_08;};
class Rva004005D0 {
public:
 void method(void*,Rva004005D0Node*,Rva004005D0Node*,const Rva004005D0Vector*,float);
 int call(void*a,Rva004005D0Node*b,Rva004005D0Vector*c,Rva004005D0Config*d,unsigned e,float f,int g) {
  typedef int (Rva004005D0::*Member)(void*,Rva004005D0Node*,Rva004005D0Vector*,Rva004005D0Config*,unsigned,float,int);
  union {void(*p)();Member m;} bridge;
  typedef char Check[sizeof(bridge)==4?1:-1];
  bridge.p=j_0001e31c;return (this->*bridge.m)(a,b,c,d,e,f,g);
 }
};
void Rva004005D0::method(void *a,Rva004005D0Node *from,Rva004005D0Node *to,const Rva004005D0Vector *direction,float distance) {
 Rva004005D0Vector negative=*direction;
 negative.scale(-1.0f);
 Rva004005D0Vector *destination=(Rva004005D0Vector *)((unsigned)to+12);
 Rva004005D0Vector delta=*destination;
 delta.sub(from->m_0c);
 delta.normalize();
 Rva004005D0Config config;
 config.m_00=0;config.m_01=0;config.m_04=distance;config.m_08=1;
 bool flip=negative.x*delta.y-delta.x*negative.y>0.0f;
 Rva004005D0Vector point;
 Rva004005D0Vector sum=delta;
 sum.add(negative);
 sum.scale(distance*0.5f);
 Rva004005D0Vector side;
 side.x=-delta.y-negative.y;
 side.y=delta.x+negative.x;side.z=0;
 side.normalize();
 if(flip)side.scale(-1.0f);
 side.scale(distance+distance);
 Rva004005D0Vector saved=*destination;
 point=from->m_0c;
 point.add(side);point.add(sum);
 *destination=point;
 call(a,from,&negative,&config,0xffff,3.1415927410125732422f,0);
 side.scale(-1.0f);
 *destination=saved;
 call(a,from,&side,&config,0xffff,3.1415927410125732422f,0);
}
