// cl: /DNDEBUG /MD /EHsc
// Retail 0x007DBA00: vtable0x01128C5C slot0; matched constructor Rva007DCA80.
struct Surface;
struct Texture;
struct Device;
struct TextureVtable {
 char p0[8]; unsigned long (__stdcall *Release)(Texture*);
 char p1[0x48-12]; long (__stdcall *GetSurfaceLevel)(Texture*,unsigned,Surface**);
};
struct Texture {TextureVtable *v;};
struct DeviceVtable {
 char p[0x5c]; long (__stdcall *CreateTexture)(Device*,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,Texture**,void*);
};
struct Device {DeviceVtable *v;};
struct Rect {long left,top,right,bottom;};
extern "C" long __stdcall D3DXLoadSurfaceFromMemory(Surface*,const void*,const Rect*,const void*,unsigned,unsigned,const void*,const Rect*,unsigned,unsigned);
extern Device *HighlightDevice;
extern unsigned HighlightVertexSupport,HighlightPixelSupport;
extern void *HighlightActive;
int bfmeCheck986B();
unsigned bfmeCurrentCU();
void bfmeCopyCuSnap(void*,void*);
class BfmeVertexShaderLoader {public: static long LoadAndCreateD3DShader(const char*,unsigned long*);};
class BfmeShaderLoader {public: static long LoadAndCreateD3DShader(const char*,unsigned long*);};
struct Cu {unsigned f[8];};

class TextureClass{public:void Release_Ref();};
class BFMEWaterTrackTexture{public:void Release_Ref();};
class BFMEWaterTrackTextureHandle{public:TextureClass*m_texture;~BFMEWaterTrackTextureHandle(){if(m_texture)((BFMEWaterTrackTexture*)m_texture)->Release_Ref();}};
BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char*,int,int);
class ShroudFilter{public:char pad[12];int u,v;};
class ShroudTexture{public:TextureClass*p;ShroudFilter*getFilter();__forceinline void bind(const BFMEWaterTrackTextureHandle&t){if(t.m_texture)++*(unsigned short*)((char*)t.m_texture+4);if(p)((BFMEWaterTrackTexture*)p)->Release_Ref();p=t.m_texture;}};
class Rva007DCA80 {
public:
 virtual int init(); virtual int shutdown();
 unsigned long pixelShader,vertexShader;
 unsigned pad0[8];unsigned size;unsigned pad1[4];Texture *texture[3];Surface *surface[3];ShroudTexture vapor[2];
};
int Rva007DCA80::init(){
 if(bfmeCheck986B()<3)return 0;
 if(!HighlightVertexSupport)return 0;
 if(!HighlightPixelSupport)return 0;
 vapor[0].bind(BFMEGetWaterTrackTexture("ExVapor01.tga",0,0));
 vapor[1].bind(BFMEGetWaterTrackTexture("ExVapor02.tga",0,0));
 vapor[0].getFilter()->u=0;vapor[0].getFilter()->v=0;vapor[1].getFilter()->u=0;vapor[1].getFilter()->v=0;
 if(BfmeVertexShaderLoader::LoadAndCreateD3DShader("shaders\\hilightfilter.vso",&vertexShader)<0){shutdown();return 0;}
 if(BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\hilightfilter.pso",&pixelShader)<0){shutdown();return 0;}
 size=((Cu*)bfmeCurrentCU())->f[3];
 if(HighlightDevice->v->CreateTexture(HighlightDevice,size,size,1,1,21,0,&texture[0],0)<0){shutdown();return 0;}
 if(texture[0]->v->GetSurfaceLevel(texture[0],0,&surface[0])!=0){
  if(texture[0])texture[0]->v->Release(texture[0]);
  texture[0]=0;surface[0]=0;
 }
 Device*dev=HighlightDevice;
 if(dev->v->CreateTexture(dev,size,size,1,1,21,0,&texture[1],0)<0){shutdown();return 0;}
 if(texture[1]->v->GetSurfaceLevel(texture[1],0,&surface[1])!=0){
  if(texture[1])texture[1]->v->Release(texture[1]);texture[1]=0;surface[1]=0;
 }
 unsigned snap[6];snap[0]=2;
 snap[1]=((Cu*)bfmeCurrentCU())->f[1];
 snap[3]=((Cu*)bfmeCurrentCU())->f[5];
 snap[5]=((Cu*)bfmeCurrentCU())->f[7];
 snap[2]=((Cu*)bfmeCurrentCU())->f[4];
 snap[4]=((Cu*)bfmeCurrentCU())->f[6];
 bfmeCopyCuSnap((char*)this+0x34,snap);
 HighlightActive=this;
 return 1;
}


