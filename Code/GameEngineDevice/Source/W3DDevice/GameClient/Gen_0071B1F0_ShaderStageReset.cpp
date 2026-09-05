// cl: /DNDEBUG /MD /EHsc
// Retail 0x0071B1F0, 384 B, from dump d_006e7d70.asm (neighbours 0x0071B3D0
// W3DShroud destructor, 0x0071B4B0 Rva0071B4B0::reset, both landed nearby in
// this directory). Identity is NOT recovered -- class/field names are
// address-derived.
//
// Evidence: the body calls the TU-local `BoxSetTexture` ABI (retail
// 0x00905AC0, pinned "TU-local texture binding ABI for BoxRenderObjClass::
// render_box" in reverse/symbols.csv) with a NULL texture at a constant
// stage index 0, then inlines DX8Wrapper::Set_DX8_Texture_Stage_State twice
// with STAGE=0 and STATE constants 0xb and 0x18 -- exactly
// D3DTSS_TEXCOORDINDEX(11) and D3DTSS_TEXTURETRANSFORMFLAGS(24), both to
// VALUE=0 (D3DTTFF_DISABLE). This is the same shape as the sibling
// `FlatShroudTextureShader::reset` narrative documented in
// FlatShroudTextureShaderReset.cpp (BFME_SET_TSS / StageTextureRef /
// BoxSetTexture-guard), except our stage is a compile-time constant 0
// rather than the member `m_stageOfSet`, and the whole body is additionally
// guarded by a `this`-relative flag at +0x40, with a second `this`-relative
// byte at +0x4C cleared unconditionally once the guard passes. Neither field
// is read again in this body, so their real names and the owning class are
// open questions -- only the two-stage-state-reset behaviour is proven.
//
// This TU is a self-contained shim (own StringClass/Device/DX8Wrapper stand-ins),
// same style as FlatShroudTextureShaderReset.cpp, so it does not depend on any
// still-unmatched narrative file compiling.

class StringClass {
	char *m_Buffer;
	static char *m_EmptyString; static char m_NullChar;
	void Get_String(int,bool); void Free_String();
public:
	StringClass(int n=0,bool temp=false):m_Buffer(m_EmptyString) { Get_String(n,temp); m_Buffer[0]=m_NullChar; }
	~StringClass(){Free_String();}
};

class TextureClass { public: void Release_Ref(); };
class TextureBaseClass;
class StageTextureRef
{
	TextureClass *Texture;
public:
	StageTextureRef():Texture(0){}
	~StageTextureRef(){ if(Texture) Texture->Release_Ref(); }
	operator TextureBaseClass *&() { return *(TextureBaseClass **)&Texture; }
};
void BoxSetTexture(unsigned int, TextureBaseClass*&);

struct Device;
struct DeviceVtable {
	char pad[0xe4];
	int (__stdcall *SetRenderState)(Device*,unsigned long,unsigned);
	char pad2[0x24];
	int (__stdcall *SetTextureStageState)(Device*,unsigned,unsigned long,unsigned);
};
struct Device{ DeviceVtable *v; };

extern Device *ScreenDevice;
extern unsigned ScreenRenderStates[];
extern unsigned ScreenTextureStageStates[8][32];
extern bool ScreenSnapshot;
extern unsigned ScreenNumberOfCalls;
extern unsigned ScreenRenderStateChanges;
extern unsigned ScreenTextureStageStateChanges;

enum { D3DTSS_TEXCOORDINDEX = 11, D3DTSS_TEXTURETRANSFORMFLAGS = 24, D3DTTFF_DISABLE = 0 };
enum { MAX_TEXTURE_STAGES = 8 };

class DX8Wrapper
{
public:
	static void Get_DX8_Texture_Stage_State_Value_Name(StringClass&, unsigned long, unsigned int);

	static __forceinline void Set_DX8_Texture_Stage_State(unsigned stage, unsigned long state, unsigned value)
	{
		if (stage>=MAX_TEXTURE_STAGES)
		{
			ScreenDevice->v->SetTextureStageState(ScreenDevice,stage,state,value);
			++ScreenNumberOfCalls;
			return;
		}
		if (ScreenTextureStageStates[stage][state]==value) return;
		if (ScreenSnapshot) { StringClass s(0,true); Get_DX8_Texture_Stage_State_Value_Name(s,state,value); }
		ScreenTextureStageStates[stage][state]=value;
		ScreenDevice->v->SetTextureStageState(ScreenDevice,stage,state,value);
		++ScreenNumberOfCalls; ++ScreenTextureStageStateChanges;
	}
};

#define BFME_SET_TSS(stage_, state_, value_) DX8Wrapper::Set_DX8_Texture_Stage_State(stage_, state_, value_)

class Rva0071B1F0
{
public:
	void apply(void);
	char m_pad[0x40];
	unsigned char m_needsApply;	// +0x40
	char m_pad2[0xB];
	unsigned char m_applied;	// +0x4C
};

// @?apply@Rva0071B1F0@@QAEXXZ 0x0071B1F0
void Rva0071B1F0::apply(void)
{
	if (m_needsApply)
	{
		m_applied = 0;
		{
			StageTextureRef texture;
			BoxSetTexture(0, texture);
		}
		BFME_SET_TSS(0, D3DTSS_TEXCOORDINDEX, 0);
		BFME_SET_TSS(0, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
	}
}
