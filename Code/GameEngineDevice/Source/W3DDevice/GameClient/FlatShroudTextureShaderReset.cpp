// cl: /DNDEBUG /MD /EHsc
// Retail 0x007C5240, 635 B. Neighbours already landed in W3DShaderManager.cpp:
// 0x007C5560 (Rva007C5560Get) and 0x007C55B0 (FlatTerrainShader2Stage::init).
// W3DShaderManager.cpp (same directory) documents this exact source under
// "FlatShroudTextureShader::reset" (present-unmatched) with the BFME_SET_RS/
// BFME_SET_TSS macro shapes this body's disassembly matches field-for-field:
// the D3DRS_ZFUNC/D3DCMP_LESSEQUAL global slot, the runtime-stage
// D3DTSS_TEXCOORDINDEX/D3DTSS_TEXTURETRANSFORMFLAGS pair, and the
// StageTextureRef-guarded BoxSetTexture(m_stageOfSet<MAX_TEXTURE_STAGES) call.
// This TU is a self-contained shim (own StringClass/Device/DX8Wrapper stand-ins)
// so it does not depend on the still-unmatched narrative file compiling.
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

enum { D3DRS_ZFUNC = 23, D3DCMP_LESSEQUAL = 4 };
enum { D3DTSS_TEXCOORDINDEX = 11, D3DTSS_TEXTURETRANSFORMFLAGS = 24, D3DTTFF_DISABLE = 0 };
enum { MAX_TEXTURE_STAGES = 8 };

class DX8Wrapper
{
public:
	static void Get_DX8_Render_State_Value_Name(StringClass&, unsigned long, unsigned int);
	static void Get_DX8_Texture_Stage_State_Value_Name(StringClass&, unsigned long, unsigned int);

	static __forceinline void Set_DX8_Render_State(unsigned long state, unsigned value)
	{
		if (ScreenRenderStates[state]==value) return;
		if (ScreenSnapshot) { StringClass s(0,true); Get_DX8_Render_State_Value_Name(s,state,value); }
		ScreenRenderStates[state]=value;
		ScreenDevice->v->SetRenderState(ScreenDevice,state,value);
		++ScreenNumberOfCalls; ++ScreenRenderStateChanges;
	}

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

#define BFME_SET_RS(state_, value_) DX8Wrapper::Set_DX8_Render_State(state_, value_)
#define BFME_SET_TSS(stage_, state_, value_) DX8Wrapper::Set_DX8_Texture_Stage_State(stage_, state_, value_)

class FlatShroudTextureShader
{
	virtual int set(int pass);
	virtual int init(void);
	virtual void reset(void);
	int m_numPasses;
	int m_stageOfSet;
};

// ?reset@FlatShroudTextureShader@@EAEXXZ
void FlatShroudTextureShader::reset(void)
{
	if ((unsigned)m_stageOfSet < MAX_TEXTURE_STAGES)
	{
		StageTextureRef texture;
		BoxSetTexture(m_stageOfSet,texture);
	}
	BFME_SET_RS(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
	BFME_SET_TSS(m_stageOfSet,  D3DTSS_TEXCOORDINDEX, m_stageOfSet);
	BFME_SET_TSS(m_stageOfSet,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
}
