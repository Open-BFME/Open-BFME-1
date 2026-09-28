// ?bfmeSetXC@BfmeXformXC@@QAEXM@Z
// partial score=0.9732142857 date=2026-09-28
struct Row001B4A50 {float X,Y,Z,W; void Set(float x,float y,float z,float w){X=x;Y=y;Z=z;W=w;} };
struct Matrix001B4A50 { Row001B4A50 row[3];
 void Set(float a,float b,float c,float d,float e,float f,float g,float h,float i,float j,float k,float l) {
 row[0].Set(a,b,c,d); row[1].Set(e,f,g,h); row[2].Set(i,j,k,l);
 }
};
float Cos(float); float Sin(float);
class BfmeXformXC { public: void bfmeSetXC(float a); unsigned char pad[0x64]; Matrix001B4A50 m; };
struct Vector001B4A50 {
 float x,y,z;
 static __forceinline void cross(const Vector001B4A50 *a,const Vector001B4A50 *b,Vector001B4A50 *r) {
 r->x=a->y*b->z-a->z*b->y;
 r->y=a->z*b->x-a->x*b->z;
 r->z=a->x*b->y-a->y*b->x;
 }
};
void BfmeXformXC::bfmeSetXC(float a) {
 Vector001B4A50 u,x,y,z,pos;
 pos.x=m.row[0].W; pos.y=m.row[1].W; pos.z=m.row[2].W;
 z.x=0.0f; z.y=0.0f; z.z=1.0f;
 u.x=Cos(a); u.y=Sin(a); u.z=0.0f;
 Vector001B4A50::cross(&z,&u,&y);
 Vector001B4A50::cross(&y,&z,&x);
 m.Set(x.x,y.x,z.x,pos.x,x.y,y.y,z.y,pos.y,x.z,y.z,z.z,pos.z);
}
