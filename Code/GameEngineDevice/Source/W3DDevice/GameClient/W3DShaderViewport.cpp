// Retail RVA 0x00716AD0, 913 bytes: shader viewport quad rendering.
// The matched highlight postRender at 0x007D7040 calls this through ILT
// 0x000196A0; its last argument supplies optional texture-coordinate dimensions.
// Keep an address-qualified name until the exact original BFME signature is known.
// Vertex-buffer creation at 0x00716770 proves the 32-byte DX8 buffer layout;
// AppendLock constructor/destructor at 0x0091DE90/0x0091DF50 are matched C++.
// Separate dimension scalars are significant: a Coord2D local changes MSVC 7.1
// stack allocation despite otherwise identical instructions. No forced padding.
// cl: /DNDEBUG /MD
struct Coord2D {float x,y;};
struct Vec4Base {float x,y,z,w;};
struct Vec4 : Vec4Base {Vec4(float a,float b,float c,float d){x=a;y=b;z=c;w=d;}};
struct Vertex {Vec4Base pos;unsigned color;float u,v;};
struct Resource {void **vt;};
struct FVFInfo {unsigned fvf,vertexSize;};
class VertexBufferClass {public:
 char pad[0x14]; FVFInfo *info;unsigned unknown;Resource *buffer;
 class AppendLockClass {VertexBufferClass *Buffer;void *Vertices;public:
 AppendLockClass(VertexBufferClass*,unsigned,unsigned,int);
 ~AppendLockClass();void *Get_Vertex_Array(){return Vertices;}
 };
};
extern VertexBufferClass *ShaderQuadBuffer;
extern int ShaderQuadIndex;
class View {public:
 virtual void unused0();
 virtual void unused1();
 virtual void unused2();
 virtual void unused3();
 virtual void unused4();
 virtual void unused5();
 virtual void unused6();
 virtual void unused7();
 virtual void unused8();
 virtual void unused9();
 virtual void unused10();
 virtual void unused11();
 virtual void unused12();
 virtual void unused13();
 virtual void unused14();
 virtual int GetWidth();
 virtual void unused16();
 virtual int GetHeight();
 virtual void unused18();
 virtual void GetOrigin(int*,int*);
};
extern View *ShaderTacticalView;
class Display {public:
 virtual void unused0();
 virtual void unused1();
 virtual void unused2();
 virtual void unused3();
 virtual void unused4();
 virtual void unused5();
 virtual void unused6();
 virtual void unused7();
 virtual void unused8();
 virtual void unused9();
 virtual void unused10();
 virtual unsigned GetWidth();
 virtual unsigned GetHeight();
};
extern Display *ShaderDisplay;
extern Resource *ShaderQuadDevice;
typedef long(__stdcall *SetFVF)(Resource*,unsigned);
typedef long(__stdcall *GetStream)(Resource*,unsigned,Resource**,unsigned*,unsigned*);
typedef long(__stdcall *SetStream)(Resource*,unsigned,Resource*,unsigned,unsigned);
typedef long(__stdcall *DrawPrimitive)(Resource*,unsigned,unsigned,unsigned);
typedef unsigned long(__stdcall *ReleaseResource)(Resource*);
void ShaderViewportRva00716AD0(int color,bool useSize,const Coord2D *givenSize) {
 if(!ShaderQuadBuffer)return;
 int x,y;
 ShaderTacticalView->GetOrigin(&x,&y);
 int width=ShaderTacticalView->GetWidth();
 int height=ShaderTacticalView->GetHeight();
 float displayWidth, displayHeight;
 if (useSize) {
  displayWidth = givenSize->x;
  displayHeight = givenSize->y;
 }
 else if (ShaderDisplay) {
  displayWidth = (float)ShaderDisplay->GetWidth();
  displayHeight = (float)ShaderDisplay->GetHeight();
 }
 else {
  displayWidth = 1;
  displayHeight = 1;
 }
 {
  VertexBufferClass::AppendLockClass lock(ShaderQuadBuffer,ShaderQuadIndex*4,4,ShaderQuadIndex?0x1000:0x2000);
  Vertex *v=(Vertex*)lock.Get_Vertex_Array();
  v[0].pos=Vec4(x+width-0.5f,y+height-0.5f,0,1);
  v[0].color=color;
  v[0].u=(float)(x+width)/displayWidth;
  v[0].v=(float)(y+height)/displayHeight;
  v[1].pos=Vec4(x+width-0.5f,y-0.5f,0,1);
  v[1].color=color;
  v[1].u=(float)(x+width)/displayWidth;
  v[1].v=(float)y/displayHeight;
  v[2].pos=Vec4(x-0.5f,y+height-0.5f,0,1);
  v[2].color=color;
  v[2].u=(float)x/displayWidth;
  v[2].v=(float)(y+height)/displayHeight;
  v[3].pos=Vec4(x-0.5f,y-0.5f,0,1);
  v[3].color=color;
  v[3].u=(float)x/displayWidth;
  v[3].v=(float)y/displayHeight;
 }
 Resource *dev=ShaderQuadDevice;
 ((SetFVF)dev->vt[89])(dev,0x144);
 Resource *old = 0;
 unsigned offset = 0, stride = 0;
 ((GetStream)dev->vt[101])(dev,0,&old,&offset,&stride);
 ((SetStream)dev->vt[100])(dev,0,ShaderQuadBuffer->buffer,0,ShaderQuadBuffer->info->vertexSize);
 ((DrawPrimitive)dev->vt[81])(dev,5,ShaderQuadIndex*4,2);
 ((SetStream)dev->vt[100])(dev,0,old,offset,stride);
 if (old) ((ReleaseResource)old->vt[2])(old);
 if (++ShaderQuadIndex >= 50) ShaderQuadIndex = 0;
}

// Retail RVA 0x00716F50, 532 bytes. Highlight postRender calls this through
// ILT 0x18BB0 at RVA 0x007D72A3. The dimensions are interpreted as signed by
// retail's FILD; the original method spelling is not asserted here.
// Keep reciprocal and half-texel values separate, and populate each vertex
// completely before the next. Combining 1/size*0.5 folds a retail FPU operation.
void ShaderQuadRva00716F50(int size) {
 if(!ShaderQuadBuffer)return;
 {
  VertexBufferClass::AppendLockClass lock(ShaderQuadBuffer,ShaderQuadIndex*4,4,ShaderQuadIndex?0x1000:0x2000);
  Vertex *v=(Vertex*)lock.Get_Vertex_Array();
float inverse = 1.0f / size;
  float halfTexel = inverse * 0.5f;
v[0].pos=Vec4(1,1,0,1);
v[0].color=0xffffffff;
v[0].u=1+halfTexel;
  v[0].v=halfTexel;
v[1].pos=Vec4(1,-1,0,1);
v[1].color=0xffffffff;
v[1].u=1+halfTexel;
  v[1].v=1+halfTexel;
v[2].pos=Vec4(-1,1,0,1);
v[2].color=0xffffffff;
v[2].u=halfTexel;
  v[2].v=halfTexel;
v[3].pos=Vec4(-1,-1,0,1);
v[3].color=0xffffffff;
v[3].u=halfTexel;
  v[3].v=1+halfTexel;
 }
 Resource *dev=ShaderQuadDevice;
 Resource *old = 0;
 unsigned offset = 0, stride = 0;
 ((GetStream)dev->vt[101])(dev,0,&old,&offset,&stride);
 ((SetStream)dev->vt[100])(dev,0,ShaderQuadBuffer->buffer,0,ShaderQuadBuffer->info->vertexSize);
 ((DrawPrimitive)dev->vt[81])(dev,5,ShaderQuadIndex*4,2);
 ((SetStream)dev->vt[100])(dev,0,old,offset,stride);
 if(old)((ReleaseResource)old->vt[2])(old);
 if(++ShaderQuadIndex>=50)ShaderQuadIndex=0;
}
