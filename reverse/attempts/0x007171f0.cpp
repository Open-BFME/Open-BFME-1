// ?startRenderToTexture@W3DShaderManager@@SAXXZ
// partial score=0.99 date=2026-09-04
// ?startRenderToTexture@W3DShaderManager@@SAXXZ
// Solo refinement: shared scratch lifetimes recover the complete retail stack frame.
// W3DShaderManager::startRenderToTexture, retail RVA0x007171F0, 445 bytes.
// Bank: 445/445B, four remaining ECX/EDX register bytes at +11D,+123,+129,+132.
// Frame20 and all local offsets now match retail using the shared Scratch union.
// Hardware test uses device slot3; Set_Render_Target9052B0; Clear904250.
// Soft-edge flag GlobalData+0x8C; opacity data+0x301C; filters2/3 use alpha-only blit,4 clears.
// Inline decrement and float getter restore retail material and clear instruction shapes.
// cl: /DNDEBUG /MD
struct IDirect3DSurface8;
struct Device;
struct DeviceVtable { void *unused[3]; long (__stdcall *TestCooperativeLevel)(Device *); };
struct Device { DeviceVtable *v; };
extern Device *ScreenDevice;
class Vector3 { public: float x,y,z; Vector3(float a,float b,float c):x(a),y(b),z(c){} };
struct Coord2D {float x,y;};
class ShaderClass {public:unsigned bits;};
static inline int decrementRef(int *p) { return --*p; }
class VertexMaterialClass {
public: virtual void Delete_This(); int refs;
 enum PresetType {PRELIT_DIFFUSE};
 static VertexMaterialClass *Get_Preset(PresetType);
 void Release_Ref(){if(!--refs) Delete_This();}
 void ReleaseGlobalRef(){decrementRef(&refs);if(refs==0)Delete_This();}
};

extern VertexMaterialClass *ScreenMaterial;
extern unsigned TheBoxTextureDirtyMask, ScreenOpaqueShader;
struct GlobalDataView {char pad[0x8c];bool showSoftWaterEdge;};extern GlobalDataView *ShaderGlobalData;
struct WaterView {char pad[0x301c];float minOpacity;float getOpacity()const{return minOpacity;}};extern WaterView *ShaderWaterData;
class DX8Wrapper {
public:
 static void Set_Render_Target(IDirect3DSurface8*,bool);
 static void Set_DX8_Render_State(unsigned long,unsigned int);
 static void Set_Shader(const ShaderClass&);
 static void Clear(bool,bool,bool,const Vector3&,float,float,unsigned);
 static __forceinline void Set_Material(VertexMaterialClass *p) {
  if(p)++p->refs;
  if(ScreenMaterial){ScreenMaterial->ReleaseGlobalRef();}
  ScreenMaterial=p; TheBoxTextureDirtyMask|=0x4000;
 }
};
void bfmeDrawFilterUV(int,int,Coord2D*);
class W3DShaderManager {public:static void startRenderToTexture();
 static bool m_renderingToTexture;
 static IDirect3DSurface8 *m_newRenderSurface,*m_oldDepthSurface;
 static int m_currentFilter;
};
union Scratch {Coord2D dims;float opacity;ShaderClass shader;};

void W3DShaderManager::startRenderToTexture() {
 Scratch slot;
 if(m_renderingToTexture || !m_newRenderSurface || !m_oldDepthSurface)return;
 if(ScreenDevice && ScreenDevice->v->TestCooperativeLevel(ScreenDevice)!=0)return;
 DX8Wrapper::Set_Render_Target(m_newRenderSurface,true);
 m_renderingToTexture=true;
 if(ShaderGlobalData->showSoftWaterEdge){
  if(m_currentFilter==2 || m_currentFilter==3){
   DX8Wrapper::Set_DX8_Render_State(168,8);
   slot.shader.bits=(ScreenOpaqueShader&~8)|7;
   DX8Wrapper::Set_Shader(slot.shader);
   VertexMaterialClass *p=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
   DX8Wrapper::Set_Material(p);
   if(p)p->Release_Ref();
   int alpha=(int)(ShaderWaterData->getOpacity()*255.0f);slot.dims.x=1;slot.dims.y=1;bfmeDrawFilterUV(0xffffff|(alpha<<24),0,&slot.dims);
   DX8Wrapper::Set_DX8_Render_State(168,7);
  }else {slot.opacity=ShaderWaterData->getOpacity();DX8Wrapper::Clear(true,false,false,Vector3(0,0,0),slot.opacity,1,0);}
 }else if(m_currentFilter==4){slot.opacity=ShaderWaterData->getOpacity();DX8Wrapper::Clear(true,false,false,Vector3(0,0,0),slot.opacity,1,0);}
}
