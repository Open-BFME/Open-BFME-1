// ?init@Rva007DB820@@UAEHXZ
// partial score=0.99 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Bank: all1035 bytes agree modulo relocations except SIB bytes+0x2F8/+0x2FC.
// Retail uses[EBX+ECX+8], compiler[ECX+EBX+8]; both compute identical addresses.
// Reuse one Snap to retain32-byte frame. Two Snap locals cost24 frame bytes.
// Retail 0x007DB1F0: vtable0x01128C0C slot0; matched constructor Rva007DB820.
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
extern Device *HighlightDevice;
extern unsigned HighlightVertexSupport,HighlightPixelSupport;
int bfmeCheck986B();
void bfmeCopyCuSnap(void*,void*);

class TextureClass{public:void Release_Ref();};
class BFMEWaterTrackTexture{public:void Release_Ref();};
class BFMEWaterTrackTextureHandle{public:TextureClass*m_texture;~BFMEWaterTrackTextureHandle(){if(m_texture)((BFMEWaterTrackTexture*)m_texture)->Release_Ref();}};
BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char*,int,int);
class ShroudTexture{public:TextureClass*p;__forceinline void bind(const BFMEWaterTrackTextureHandle&t){if(t.m_texture)++*(unsigned short*)((char*)t.m_texture+4);if(p)((BFMEWaterTrackTexture*)p)->Release_Ref();p=t.m_texture;}};

class BfmeShaderLoader16{public:static int LoadAndCreateD3DShader(const char*,unsigned*);};
struct GridGlobals{char pad[0x54];float scale;int count;};GridGlobals*GridScaleRva007D95B0();
struct Sample{float x,y,weight;};
struct Samples{Sample*begin,*end,*capacity;unsigned size(){return end-begin;}Sample&operator[](unsigned n){return begin[n];}};
struct Snap{int mode,count;float a,b,c,d;};
extern int FadeCurrentFrame;extern void*RingFilterSlot;extern char RingFilterObject;
class Rva007DB820{public:virtual int init();virtual int shutdown();unsigned shader[3];ShroudTexture vapor[2];Texture*texture0;Surface*surface0;char pad[0x2c-0x20];Samples samples0,samples1;Texture*texture1,*texture2;Surface*surface1,*surface2;};
int Rva007DB820::init(){
 shader[0]=0;FadeCurrentFrame=0;
 if(!HighlightVertexSupport||!HighlightPixelSupport)return 0;
 int chip=bfmeCheck986B();if(chip==0)return 0;if(chip<8)return 0;
 vapor[0].bind(BFMEGetWaterTrackTexture("EXVapor01.tga",0,0));
 vapor[1].bind(BFMEGetWaterTrackTexture("EXVapor02.tga",0,0));
 bool failed=false;
 if(HighlightDevice->v->CreateTexture(HighlightDevice,512,512,1,1,21,0,&texture0,0)>=0){if(texture0->v->GetSurfaceLevel(texture0,0,&surface0)<0)failed=true;}
 if(HighlightDevice->v->CreateTexture(HighlightDevice,512,512,1,1,21,0,&texture1,0)>=0){if(texture1->v->GetSurfaceLevel(texture1,0,&surface1)<0)failed=true;}
 if(HighlightDevice->v->CreateTexture(HighlightDevice,512,512,1,1,21,0,&texture2,0)>=0){if(texture2->v->GetSurfaceLevel(texture2,0,&surface2)<0)failed=true;}
 if(failed||!surface2||!surface1||!surface0){shutdown();return 0;}
 BfmeShaderLoader16::LoadAndCreateD3DShader("shaders\\ring.nvp",&shader[0]);
 BfmeShaderLoader16::LoadAndCreateD3DShader("shaders\\ring1.nvp",&shader[1]);
 BfmeShaderLoader16::LoadAndCreateD3DShader("shaders\\ring2.nvp",&shader[2]);
 RingFilterSlot=&RingFilterObject;
 Snap s;s.mode=1;s.count=GridScaleRva007D95B0()->count;s.b=.06f;s.d=.11f;s.a=.18f;s.c=4.5f;bfmeCopyCuSnap(&samples0,&s);
 s.mode=2;s.count=GridScaleRva007D95B0()->count;s.b=.06f;s.d=.11f;s.a=.18f;s.c=4.5f;bfmeCopyCuSnap(&samples1,&s);
 float total=0;for(unsigned i=0;i<samples0.size();++i)total+=samples0[i].weight;
 float inv=1.0f/total;for(unsigned j=0;j<samples0.size();++j)samples0[j].weight*=inv;
 total=0;for(unsigned k=0;k<samples1.size();++k)total+=samples1[k].weight;
 inv=1.0f/total;for(unsigned l=0;l<samples1.size();++l)samples1[l].weight*=inv;
 return 1;
}
