// Retail RVA 0x00717C90; shutdown at 0x00717DA2 calls ILT RVA 0x1BB30.
// Global 0x012F9D1C is a vertex buffer: allocation path 0x00716770 calls
// DX8VertexBuffer ctor 0x0091F2F0. Other addresses remain explicit.
// The eight texture-handle resets retain a temporary lifetime around release.
// cl: /DNDEBUG /MD /EHsc
static inline int decrement(int *p) { return --*p; }
class ShaderVertexBufferRef { public: virtual void Delete_This(); int NumRefs; void Release_Ref() { decrement(&NumRefs); if(NumRefs==0) Delete_This(); } };
struct ShaderComResourceRef { void **VTable; };
typedef unsigned long (__stdcall *ReleaseResource)(ShaderComResourceRef*);
class TextureBaseClass { public: void Release_Ref(); void Add_Ref(); };
class ShaderTextureHandle { public:
 TextureBaseClass *ptr;
 ShaderTextureHandle(TextureBaseClass *p):ptr(p) { if(ptr) ptr->Add_Ref(); }
 ~ShaderTextureHandle() { if(ptr) ptr->Release_Ref(); }
 ShaderTextureHandle &operator=(const ShaderTextureHandle &o) { if(o.ptr) o.ptr->Add_Ref(); if(ptr) ptr->Release_Ref(); ptr=o.ptr; return *this; }
};
extern ShaderVertexBufferRef *rva012F9D1C;
extern int ShaderQuadIndex;
extern ShaderComResourceRef *rva012F9D0C, *rva012F9D04, *rva012F9D08, *rva012F9D10;
// 0x012F9D28 is the shader texture-handle table (BfmeHandleCX *[8]), defined by
// Rva00C6C520StaticInit.cpp. Declared by its defining name; the table's 4-byte
// slots are cleared through the ShaderTextureHandle view this TU models.
class BfmeHandleCX;
extern BfmeHandleCX *g_bfmeTableDU;
class BfmeShaderShutdown { public: static void releaseDependentResources(); };
void BfmeShaderShutdown::releaseDependentResources() {
 if(rva012F9D1C) { rva012F9D1C->Release_Ref(); rva012F9D1C=0; }
 ShaderQuadIndex=0;
 if(rva012F9D0C) { ((ReleaseResource)rva012F9D0C->VTable[2])(rva012F9D0C); rva012F9D0C=0; }
 if(rva012F9D04) { ((ReleaseResource)rva012F9D04->VTable[2])(rva012F9D04); rva012F9D04=0; }
 if(rva012F9D08) { ((ReleaseResource)rva012F9D08->VTable[2])(rva012F9D08); rva012F9D08=0; }
 if(rva012F9D10) { ((ReleaseResource)rva012F9D10->VTable[2])(rva012F9D10); rva012F9D10=0; }
 for(unsigned i=0;i<8;++i) ((ShaderTextureHandle *)&g_bfmeTableDU)[i]=0;
}
