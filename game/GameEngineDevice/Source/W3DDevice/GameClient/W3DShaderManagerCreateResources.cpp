// Retail RVA 0x00716770, 399 bytes; shader dependent-resource creation.
// Matched W3DShaderManager::init at 0x00718E90 calls this via ILT 0xCF8B
// at 0x00718E9B; keep the method address-qualified pending its exact name.
// Address-qualified method: releases/recreates the same vertex buffer and COM
// resources cleared by verified releaseDependentResources at 0x00717C90.
// DX8VertexBuffer constructor 0x0091F2F0 takes FVF 0x144, 200 vertices,
// USAGE_DYNAMIC (1), and vertex_size 0; the retail allocation is 0x20 bytes.
// cl: /DNDEBUG /MD /EHsc
static inline int decrement(int *p) { return --*p; }
class BfmeDX8VertexBuffer {
public:
 enum UsageType { USAGE_DYNAMIC=1 };
 virtual void Delete_This();
 int NumRefs;
 unsigned char remaining[24];
 BfmeDX8VertexBuffer(unsigned, unsigned short, UsageType, unsigned);
 void Release_Ref() { decrement(&NumRefs); if(NumRefs==0) Delete_This(); }
};
void *__cdecl operator new(unsigned);
void __cdecl operator delete(void *);
struct SurfaceDesc { unsigned format,type,usage,pool,multisample,quality,width,height; };
struct Resource { void **vt; };
extern BfmeDX8VertexBuffer *rva012F9D1C;
extern unsigned rva012F9D20;
extern Resource *rva012F9D04, *rva012F9D08, *rva012F9D0C, *rva012F9D10, *rva01340534;
typedef long (__stdcall *GetTarget)(Resource*,unsigned,Resource**);
typedef long (__stdcall *GetDesc)(Resource*,SurfaceDesc*);
typedef long (__stdcall *CreateTexture)(Resource*,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,Resource**,void*);
typedef long (__stdcall *GetLevel)(Resource*,unsigned,Resource**);
typedef long (__stdcall *GetDepth)(Resource*,Resource**);
typedef unsigned long (__stdcall *Release)(Resource*);
static inline void release(Resource *p) { if(p) ((Release)p->vt[2])(p); }
class BfmeShaderShutdown { public: static void rva00716770(); };
void BfmeShaderShutdown::rva00716770() {
 if(rva012F9D1C) { rva012F9D1C->Release_Ref(); rva012F9D1C=0; }
 rva012F9D1C=new BfmeDX8VertexBuffer(0x144,200,BfmeDX8VertexBuffer::USAGE_DYNAMIC,0);
 rva012F9D20=0;
 if(rva012F9D04 || rva012F9D08 || rva012F9D0C || rva012F9D10) return;
 ((GetTarget)rva01340534->vt[38])(rva01340534,0,&rva012F9D04);
 SurfaceDesc desc;
 ((GetDesc)rva012F9D04->vt[12])(rva012F9D04,&desc);
 if(((CreateTexture)rva01340534->vt[23])(rva01340534,desc.width,desc.height,1,1,desc.format,0,&rva012F9D08,0)!=0) {
  release(rva012F9D04); rva012F9D04=0; rva012F9D08=0;
 } else if(((GetLevel)rva012F9D08->vt[18])(rva012F9D08,0,&rva012F9D0C)!=0) {
  release(rva012F9D08); rva012F9D0C=0; rva012F9D08=0;
 } else if(((GetDepth)rva01340534->vt[40])(rva01340534,&rva012F9D10)!=0) {
  release(rva012F9D0C); release(rva012F9D08);
  rva012F9D10=0; rva012F9D0C=0; rva012F9D08=0;
 }
}
