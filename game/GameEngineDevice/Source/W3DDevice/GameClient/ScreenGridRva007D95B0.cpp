// cl: /DNDEBUG /MD
#include <math.h>
// Retail 0x007D95B0: dynamic index/vertex grid update; original method name unknown.
// Integer indices precede a 52-byte mapped-vertex update with two animated sine waves.
// File-static wave factors retain retail loop invariance. The volatile u1 read keeps
// the mapped-buffer reload before the object spread load, matching retail exactly.
struct Coord2D{float x,y;};
class DynamicIBAccessClass{public:class WriteLockClass{DynamicIBAccessClass*access;public:unsigned short*indices;WriteLockClass(DynamicIBAccessClass*);~WriteLockClass();};};
struct Vertex{float x,y,z,rhw;unsigned color;float u0,v0,u1,v1,u2,v2,u3,v3;};
class BoxDynamicVBAccessClass{public:class WriteLockClass{BoxDynamicVBAccessClass*access;public:Vertex*vertices;WriteLockClass(BoxDynamicVBAccessClass*);~WriteLockClass();};};
struct GridGlobals{char pad[0x54];float scale;};GridGlobals*GridScaleRva007D95B0();
extern float GridFrameScale;static float Grid95Phase0,Grid95Phase1;
static float Grid95Wave0Amplitude=0.2f,Grid95Wave0Frequency=12.566370964f,Grid95Wave0Phase=2.0f;
static float Grid95Wave1Amplitude=0.5f,Grid95Wave1Frequency=12.566370964f,Grid95Wave1Phase=2.0f;
class ScreenGridRva007D95B0{char pad[0x20];float scrollX,scrollY,spread;public:void update(DynamicIBAccessClass*,int,BoxDynamicVBAccessClass*,int,int,int,float,float,float,float,Coord2D*);};
void ScreenGridRva007D95B0::update(DynamicIBAccessClass*ib,int a,BoxDynamicVBAccessClass*vb,int b,int columns,int rows,float left,float top,float width,float height,Coord2D*dims){
 ++columns;++rows;float scale=GridFrameScale*0.0125f;
 if(scale>6.0f)scale=6.0f;else if(scale<0.6f)scale=0.6f;
 float amplitude=scale*GridScaleRva007D95B0()->scale;
 {
  DynamicIBAccessClass::WriteLockClass lock(ib);unsigned short*p=lock.indices;
  for(int y=0;y<rows-1;++y){for(int x=0;x<columns-1;++x){
   p[0]=y*columns+x;p[1]=(y+1)*columns+x+1;p[2]=(y+1)*columns+x;
   p[3]=y*columns+x;p[4]=y*columns+x+1;p[5]=(y+1)*columns+x+1;p+=6;
  }}
 }
 Grid95Phase0+=0.05f;Grid95Phase1+=0.05f;
 {
  BoxDynamicVBAccessClass::WriteLockClass lock(vb);Vertex*p=lock.vertices;
  float invRows=1.0f/(rows-1);float invColumns=1.0f/(columns-1);
  for(int y=0;y<rows;++y){
   float fy=y*invRows;float py=fy*height+top;float screenY=py-0.5f;
   for(int x=0;x<columns;++x){
    float fx=x*invColumns;float px=fx*width+left;
    p->x=px-0.5f;p->y=screenY;p->z=0;p->rhw=1;p->color=0x64ffffff;
    p->u0=px/dims->x;p->v0=py/dims->y;
    p->u1=fx*amplitude*2+scrollX;p->v1=fy*amplitude+scrollY;
    p->v2=p->v1+spread;p->u2=p->u1-spread;{const volatile float*u=&p->u1;p->u1=*u+spread;}
    p->v3=0;
    p->u3=(0.5f-0.5f*(float)sin((fx+fy)*Grid95Wave0Frequency+Grid95Phase0*Grid95Wave0Phase))*Grid95Wave0Amplitude;
    float wave=(0.5f-0.5f*(float)sin((fx+fy)*Grid95Wave1Frequency+Grid95Phase1*Grid95Wave1Phase))*Grid95Wave1Amplitude;
    p->u1+=wave;p->u2+=wave;++p;
   }
  }
 }
}




