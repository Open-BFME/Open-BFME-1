// Retail RVA 0x00717C90; shutdown at 0x00717DA2 calls ILT RVA 0x1BB30.
// Global 0x012F9D1C is a vertex buffer: allocation path 0x00716770 calls
// DX8VertexBuffer ctor 0x0091F2F0. Other addresses remain explicit.
// The eight texture-handle resets retain a temporary lifetime around release.
// cl: /DNDEBUG /MD /EHsc
static inline int decrement(int *p) { return --*p; }
class ShaderVertexBufferRef { public: virtual void Delete_This(); int NumRefs; void Release_Ref() { decrement(&NumRefs); if(NumRefs==0) Delete_This(); } };
struct ShaderSurfaceRef { void **VTable; };
typedef unsigned long (__stdcall *ReleaseSurface)(ShaderSurfaceRef*);
class TextureBaseClass { public: void Release_Ref(); void Add_Ref(); };
class ShaderTextureHandle { public:
 TextureBaseClass *ptr;
 ShaderTextureHandle(TextureBaseClass *p):ptr(p) { if(ptr) ptr->Add_Ref(); }
 ~ShaderTextureHandle() { if(ptr) ptr->Release_Ref(); }
 ShaderTextureHandle &operator=(const ShaderTextureHandle &o) { if(o.ptr) o.ptr->Add_Ref(); if(ptr) ptr->Release_Ref(); ptr=o.ptr; return *this; }
};
extern ShaderVertexBufferRef *rva012F9D1C;
extern unsigned rva012F9D20;
extern ShaderSurfaceRef *rva012F9D0C, *rva012F9D04, *rva012F9D08, *rva012F9D10;
extern ShaderTextureHandle rva012F9D28[8];
class BfmeShaderShutdown { public: static void releaseDependentResources(); };
void BfmeShaderShutdown::releaseDependentResources() {
 if(rva012F9D1C) { rva012F9D1C->Release_Ref(); rva012F9D1C=0; }
 rva012F9D20=0;
 if(rva012F9D0C) { ((ReleaseSurface)rva012F9D0C->VTable[2])(rva012F9D0C); rva012F9D0C=0; }
 if(rva012F9D04) { ((ReleaseSurface)rva012F9D04->VTable[2])(rva012F9D04); rva012F9D04=0; }
 if(rva012F9D08) { ((ReleaseSurface)rva012F9D08->VTable[2])(rva012F9D08); rva012F9D08=0; }
 if(rva012F9D10) { ((ReleaseSurface)rva012F9D10->VTable[2])(rva012F9D10); rva012F9D10=0; }
 for(unsigned i=0;i<8;++i) rva012F9D28[i]=0;
}
