// ?d_007d3d40@@YAXXZ
// partial score=0.26 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc
// Retail 0x007D3D40, 1817 B.  The constructor at 0x007D3740 installs
// vtable 0x01128A50; this is slot 5.  The readable W3DShaderManager donor
// supplies the filter operation.  BFME's wrapper routes ADDRESSU/V through
// sampler state (device slot 0x114), while the circle-mask states remain the
// cached texture-stage operation at slot 0x10c.
class StringClass {
	char *m_Buffer;
	static char *m_EmptyString; static char m_NullChar;
	void Get_String(int,bool); void Free_String();
public:
	__forceinline StringClass(int n=0,bool temp=false):m_Buffer(m_EmptyString) { Get_String(n,temp); m_Buffer[0]=m_NullChar; }
	~StringClass(){Free_String();}
};
class VertexMaterialClass {
public:
	virtual void Delete_This(); int refs;
	enum PresetType {PRELIT_DIFFUSE};
	static VertexMaterialClass *Get_Preset(PresetType);
	void Release_Ref(){if (!--refs) Delete_This();}
};
class TextureClass { public: void Release_Ref(); };
class TextureBaseClass;
class TextureHandle { public: TextureClass *p; TextureHandle():p(0){} ~TextureHandle(){if(p)p->Release_Ref();} };
void BoxSetTexture(unsigned int,TextureBaseClass*&);
struct Device;
struct DeviceVtable {
	char pad0[0xe4];
	int (__stdcall *SetRenderState)(Device*,unsigned long,unsigned);
	char pad1[0x24];
	int (__stdcall *SetTextureStageState)(Device*,unsigned,unsigned long,unsigned);
	char pad2[4];
	int (__stdcall *SetSamplerState)(Device*,unsigned,unsigned long,unsigned);
};
struct Device{DeviceVtable *v;};
extern VertexMaterialClass *ScreenMaterial;
extern unsigned TheBoxTextureDirtyMask;
extern bool ScreenShaderDirty;
extern unsigned ScreenOpaqueShader, ScreenCurrentShader;
extern bool ScreenSnapshot;
extern Device *ScreenDevice;
extern unsigned number_of_DX8_calls;
class DX8Wrapper {
public:
	static unsigned RenderStates[256];
	static unsigned TextureStageStates[8][32];
	static unsigned render_state_changes;
	static unsigned texture_stage_state_changes;
	static void Apply_Render_State_Changes();
	static void Get_DX8_Render_State_Value_Name(StringClass&,unsigned long,unsigned int) throw();
	static void Get_DX8_Texture_Stage_State_Value_Name(StringClass&,unsigned long,unsigned int);
	static __forceinline void Set_DX8_Render_State(unsigned long state,unsigned value) {
		if(RenderStates[state]==value)return;
		if(ScreenSnapshot){StringClass s(0,true);Get_DX8_Render_State_Value_Name(s,state,value);}
		RenderStates[state]=value;
		ScreenDevice->v->SetRenderState(ScreenDevice,state,value);
		++number_of_DX8_calls; ++render_state_changes;
	}
	static __forceinline void Set_DX8_Texture_Stage_State(unsigned stage,unsigned long state,unsigned value) {
		if(state==13) {
			ScreenDevice->v->SetSamplerState(ScreenDevice,stage,1,value);
			++number_of_DX8_calls; ++texture_stage_state_changes;
			return;
		}
		if(state==14) {
			ScreenDevice->v->SetSamplerState(ScreenDevice,stage,2,value);
			++number_of_DX8_calls; ++texture_stage_state_changes;
			return;
		}
		if(TextureStageStates[stage][state]==value)return;
		if(ScreenSnapshot){StringClass s(0,true);Get_DX8_Texture_Stage_State_Value_Name(s,state,value);}
		TextureStageStates[stage][state]=value;
		ScreenDevice->v->SetTextureStageState(ScreenDevice,stage,state,value);
		++number_of_DX8_calls; ++texture_stage_state_changes;
	}
};

enum { BFME_SET_TSS_SLOT = 67, BFME_SET_RS_SLOT = 57, BFME_SET_SAMP_SLOT = 69 };
typedef int (__stdcall *BFMESetTSSFn)(Device *, unsigned, unsigned, unsigned);
typedef int (__stdcall *BFMESetRSFn)(Device *, unsigned, unsigned);

#define BFME_SET_TSS(stage_, state_, value_) \
	if (DX8Wrapper::TextureStageStates[(stage_)][(state_)] != value_) { \
		if (ScreenSnapshot) { \
			StringClass value_name(0, true); \
			DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(value_name, (state_), (value_)); \
		} \
		DX8Wrapper::TextureStageStates[(stage_)][(state_)] = value_; \
		Device *tss_device_ = ScreenDevice; \
		(*(BFMESetTSSFn **)tss_device_)[BFME_SET_TSS_SLOT](tss_device_, (stage_), (state_), (value_)); \
		++number_of_DX8_calls; \
		++DX8Wrapper::texture_stage_state_changes; \
	}

#define BFME_SET_SAMP(stage_, state_, value_) { \
		Device *samp_device_ = ScreenDevice; \
		(*(BFMESetTSSFn **)samp_device_)[BFME_SET_SAMP_SLOT](samp_device_, (stage_), (state_), (value_)); \
		++number_of_DX8_calls; \
		++DX8Wrapper::texture_stage_state_changes; \
	}

#define BFME_SET_RS(state_, value_) \
	if (DX8Wrapper::RenderStates[(state_)] != value_) { \
		if (ScreenSnapshot) { \
			StringClass value_name(0, true); \
			DX8Wrapper::Get_DX8_Render_State_Value_Name(value_name, (state_), (value_)); \
		} \
		DX8Wrapper::RenderStates[(state_)] = value_; \
		Device *rs_device_ = ScreenDevice; \
		(*(BFMESetRSFn **)rs_device_)[BFME_SET_RS_SLOT](rs_device_, (state_), (value_)); \
		++number_of_DX8_calls; \
		++DX8Wrapper::render_state_changes; \
	}

enum FilterModes {FM_NULL_MODE=0,FM_VIEW_CROSSFADE_CIRCLE=4};
enum {D3DTSS_COLOROP=1,D3DTSS_COLORARG1=2,D3DTSS_COLORARG2=3,
	D3DTSS_ALPHAOP=4,D3DTSS_ALPHAARG1=5,D3DTSS_ALPHAARG2=6,
	D3DTSS_TEXCOORDINDEX=11,D3DTSS_ADDRESSU=13,D3DTSS_ADDRESSV=14,
	D3DTSS_MIPFILTER=18};
enum {D3DTA_CURRENT=1,D3DTA_TEXTURE=2,D3DTOP_MODULATE=4,
	D3DTADDRESS_CLAMP=3,D3DTEXF_NONE=1};
enum {D3DRS_ZFUNC=23,D3DRS_ZWRITEENABLE=14,D3DCMP_ALWAYS=8};
class ScreenCrossFadeFilter { protected: virtual int set(FilterModes); };

// ?set@ScreenCrossFadeFilter@@MAEHW4FilterModes@@@Z
int ScreenCrossFadeFilter::set(FilterModes mode)
{
	if(mode>FM_NULL_MODE) {
		VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		if(vmat)++vmat->refs;
		if(ScreenMaterial)ScreenMaterial->Release_Ref();
		ScreenMaterial=vmat;
		TheBoxTextureDirtyMask|=0x4000;
		if(vmat)vmat->Release_Ref();
		if(ScreenShaderDirty || ScreenOpaqueShader!=ScreenCurrentShader){ScreenCurrentShader=ScreenOpaqueShader;TheBoxTextureDirtyMask|=0x8000;StringClass s;}
		{TextureHandle tex;BoxSetTexture(0,(TextureBaseClass*&)tex.p);}
		{TextureHandle tex;BoxSetTexture(1,(TextureBaseClass*&)tex.p);}
		DX8Wrapper::Apply_Render_State_Changes();
		BFME_SET_SAMP(0,1,D3DTADDRESS_CLAMP);
		BFME_SET_SAMP(0,2,D3DTADDRESS_CLAMP);
		if(mode==FM_VIEW_CROSSFADE_CIRCLE) {
			BFME_SET_TSS(1,D3DTSS_COLORARG1,D3DTA_TEXTURE);
			BFME_SET_TSS(1,D3DTSS_COLORARG2,D3DTA_CURRENT);
			BFME_SET_TSS(1,D3DTSS_COLOROP,D3DTOP_MODULATE);
			BFME_SET_TSS(1,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
			BFME_SET_TSS(1,D3DTSS_ALPHAARG2,D3DTA_CURRENT);
			BFME_SET_TSS(1,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
			BFME_SET_TSS(1,D3DTSS_TEXCOORDINDEX,1);
			BFME_SET_SAMP(1,1,D3DTADDRESS_CLAMP);
			BFME_SET_SAMP(1,2,D3DTADDRESS_CLAMP);
			BFME_SET_SAMP(1,7,0);
		}
		BFME_SET_RS(D3DRS_ZFUNC,D3DCMP_ALWAYS);
		BFME_SET_RS(D3DRS_ZWRITEENABLE,0);
		return true;
	}
	return false;
}
