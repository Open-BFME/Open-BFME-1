// ?set@Rva007D3D40CrossFadeFilter@@MAEHW4FilterModes@@@Z
// Address-derived stand-in: the vtable-slot-5 identity is the Zero Hour
// ScreenCrossFadeFilter::set, but retail's ILT window contradicts that
// decoration, so this row keeps an Rva-qualified owner.
// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /MD /EHsc
// Rva007D3D40CrossFadeFilter vtable slot 5; BFME device slots and local lifetimes.
// Evidence: targets/game/reverse/identity_evidence/007d3d40-set.md
#include "shader.h"
// Keep the native string constructor visible at each snapshot call site.
#define inline __forceinline
#include "wwstring.h"
#undef inline
#include "vertmaterial.h"
#include "texture.h"
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
#define ScreenOpaqueShader (ShaderClass::_PresetAlphaShader.Get_Bits())
extern unsigned ScreenCurrentShader;
extern bool ScreenSnapshot;
extern Device *ScreenDevice;
extern unsigned number_of_DX8_calls;
#include "dx8wrapper.h"
class DX8WrapperState007D3D40 : public DX8Wrapper {
public:
    using DX8Wrapper::RenderStates;
    using DX8Wrapper::TextureStageStates;
    using DX8Wrapper::render_state_changes;
    using DX8Wrapper::texture_stage_state_changes;
};

enum { BFME_SET_TSS_SLOT = 67, BFME_SET_RS_SLOT = 57, BFME_SET_SAMP_SLOT = 69 };
typedef int (__stdcall *BFMESetTSSFn)(Device *, unsigned, unsigned, unsigned);
typedef int (__stdcall *BFMESetRSFn)(Device *, unsigned, unsigned);

#define BFME_SET_TSS(stage_, state_, value_) \
	if (DX8WrapperState007D3D40::TextureStageStates[(stage_)][(state_)] != value_) { \
		if (ScreenSnapshot) { \
			StringClass value_name(0, true); \
			DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(value_name, (state_), (value_)); \
		} \
		DX8WrapperState007D3D40::TextureStageStates[(stage_)][(state_)] = value_; \
		Device *tss_device_ = ScreenDevice; \
		(*(BFMESetTSSFn **)tss_device_)[BFME_SET_TSS_SLOT](tss_device_, (stage_), (state_), (value_)); \
		++number_of_DX8_calls; \
		++DX8WrapperState007D3D40::texture_stage_state_changes; \
	}

#define BFME_SET_SAMP(stage_, state_, value_) { \
		Device *samp_device_ = ScreenDevice; \
		(*(BFMESetTSSFn **)samp_device_)[BFME_SET_SAMP_SLOT](samp_device_, (stage_), (state_), (value_)); \
		++number_of_DX8_calls; \
		++DX8WrapperState007D3D40::texture_stage_state_changes; \
	}

#define BFME_SET_RS(state_, value_) \
	if (DX8WrapperState007D3D40::RenderStates[(state_)] != value_) { \
		if (ScreenSnapshot) { \
			StringClass value_name(0, true); \
			DX8Wrapper::Get_DX8_Render_State_Value_Name(value_name, (state_), (value_)); \
		} \
		DX8WrapperState007D3D40::RenderStates[(state_)] = value_; \
		Device *rs_device_ = ScreenDevice; \
		(*(BFMESetRSFn **)rs_device_)[BFME_SET_RS_SLOT](rs_device_, (state_), (value_)); \
		++number_of_DX8_calls; \
		++DX8WrapperState007D3D40::render_state_changes; \
	}

enum FilterModes {FM_NULL_MODE=0,FM_VIEW_CROSSFADE_CIRCLE=4};
enum CustomScenePassModes;
struct Coord2D;
class Rva007D3D40CrossFadeFilter {
public:
    virtual int init();
    virtual int shutdown();
    virtual bool preRender(bool &, CustomScenePassModes &);
    virtual bool postRender(FilterModes, Coord2D &, bool &, Coord2D *);
    virtual bool setup(FilterModes);
protected:
    virtual int set(FilterModes);
    virtual void reset();
};

// ?set@Rva007D3D40CrossFadeFilter@@MAEHW4FilterModes@@@Z
int Rva007D3D40CrossFadeFilter::set(FilterModes mode)
{
	if(mode>FM_NULL_MODE) {
		VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		if(vmat)vmat->Add_Ref();
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
