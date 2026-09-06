// cl: /DNDEBUG /MD /EHsc
// Retail 0x007D6BF0: vtable 0x01128B88 slot 0 via 0x0044831A.
// Highlight filter identity: hilightfilter.vso and hilightfilter.pso.
// ScreenHilightFilter is descriptive: the retail class name is unknown, but this
// init loads shaders\hilightfilter.vso and shaders\hilightfilter.pso and nothing
// else does, and the matched constructor at 0x007D8580 installs this vtable.
// The prior 460-byte dump truncates the error epilogue; final ret is at RVA 0x007D6DC2.
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
class ScreenHilightFilter {
public:
 virtual int init(); virtual int shutdown();
 unsigned long pixelShader,vertexShader;
 unsigned size;
 unsigned pad[5];
 Texture *texture[2];
 Surface *surface[2];
};
int ScreenHilightFilter::init(){
 if(bfmeCheck986B()<3)return 0;
 if(!HighlightVertexSupport||!HighlightPixelSupport)return 0;
 if(BfmeVertexShaderLoader::LoadAndCreateD3DShader("shaders\\hilightfilter.vso",&vertexShader)<0){shutdown();return 0;}
 if(BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\hilightfilter.pso",&pixelShader)<0){shutdown();return 0;}
 size=((Cu*)bfmeCurrentCU())->f[3];
 if(HighlightDevice->v->CreateTexture(HighlightDevice,size,size,1,1,21,0,&texture[0],0)<0){shutdown();return 0;}
 if(texture[0]->v->GetSurfaceLevel(texture[0],0,&surface[0])!=0){
  if(texture[0])texture[0]->v->Release(texture[0]);
  texture[0]=0;surface[0]=0;
 }
 for(int i=0;i<1;++i){
  Device *dev=HighlightDevice;
  if(dev->v->CreateTexture(dev,size,size,1,1,21,0,&texture[i+1],0)<0){shutdown();return 0;}
  if(texture[i+1]->v->GetSurfaceLevel(texture[i+1],0,&surface[i+1])!=0){
   texture[i+1]->v->Release(texture[i+1]);texture[i+1]=0;surface[i+1]=0;
  }else{
   unsigned color=0;Rect rect;rect.top=0;rect.left=0;rect.bottom=1;rect.right=1;
   D3DXLoadSurfaceFromMemory(surface[i+1],0,0,&color,21,4,0,&rect,2,0);
  }
 }
 unsigned snap[6];snap[0]=2;
 snap[1]=((Cu*)bfmeCurrentCU())->f[1];
 snap[3]=((Cu*)bfmeCurrentCU())->f[5];
 snap[5]=((Cu*)bfmeCurrentCU())->f[7];
 snap[2]=((Cu*)bfmeCurrentCU())->f[4];
 snap[4]=((Cu*)bfmeCurrentCU())->f[6];
 bfmeCopyCuSnap((char*)this+0x18,snap);
 HighlightActive=this;
 return 1;
}


