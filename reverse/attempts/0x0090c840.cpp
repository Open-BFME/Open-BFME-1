// ?Apply@TextureClass@@UAEXI@Z
// partial score=0.9 date=2026-09-13
// cl: /DNDEBUG /MD /EHsc
// TextureClass::Apply(unsigned int stage), retail 0x0090C840 (264 B).  ZH
// twin: WWVegas/WW3D2/texture.cpp TextureClass::Apply, inlining
// DX8Wrapper::Set_DX8_Texture(stage, texture) once with the real texture
// pointer and once with NULL for the "texturing disabled or no texture"
// path (dx8wrapper.h WWINLINE), which is why the body duplicates the whole
// cache-check block.  No caller/pin cited for this address; identity rests
// on the ZH source matching essentially every instruction and every global
// (D3DDevice 0x1340534, the 8-entry Textures[] cache at 0x133F478, the DX8
// call counter 0x1340594, texture_changes at 0x1340560) once the two are
// laid side by side -- verify against docs/naming_evidence.md before
// landing under the real name.
// Compiles 260/264 with all four globals unpinned (relocations read 0,
// hence the reported relocation-layout drift; a real pin pass would clear
// most reported diffs).  The one real gap: retail re-tests the stored
// pointer (`test esi,esi`) before the conditional AddRef even though the
// same pointer was already proven non-null a few instructions earlier
// (entering the block requires texture!=0); this compiler proves the
// check redundant and elides it, landing 4 bytes short with every
// subsequent branch offset by 4.  Ruled out: re-reading through the
// just-stored global array element instead of the local (compiler still
// proves it equals the known-nonzero value, no change); a volatile
// qualifier on the Textures[] array (changes register allocation for the
// whole body, far worse); `_ReadWriteBarrier()` between the store and the
// check (moves other, unrelated code and grows the diff instead of
// shrinking it). Next lever to try: a source shape where the "texture"
// value used for the AddRef check is NOT provably the same SSA value the
// compiler already tested (e.g. two distinct getter calls through the
// TU-local class instead of one cached local).
// t=32min model=claude-sonnet-5

struct ID3D8UnknownVtbl
{
	void *QueryInterface;
	unsigned long (__stdcall *AddRef)(void *self);
	unsigned long (__stdcall *Release)(void *self);
};

struct ID3D8Unknown
{
	ID3D8UnknownVtbl *lpVtbl;
};

struct IDirect3DDevice8Vtbl
{
	void *reserved[65];
	long (__stdcall *SetTexture)(void *self, unsigned int stage, ID3D8Unknown *texture);
};

struct IDirect3DDevice8
{
	IDirect3DDevice8Vtbl *lpVtbl;
};

extern "C" bool g_bfmeTexturingEnabled;
extern IDirect3DDevice8 *g_D3DDevice;
extern unsigned int g_D3DCallCount;
extern unsigned int g_TextureChanges;
extern ID3D8Unknown *g_Textures[8];

#define MAX_TEXTURE_STAGES 8

class TextureClass
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void Init();

	bool Initialized;
	ID3D8Unknown *m_d3dBaseTexture;

	virtual void Apply(unsigned int stage);
};

void TextureClass::Apply(unsigned int stage)
{
	if (!Initialized)
		Init();

	ID3D8Unknown *texture;
	if (g_bfmeTexturingEnabled && (texture = m_d3dBaseTexture) != 0)
	{
		if (stage >= MAX_TEXTURE_STAGES)
		{
			g_D3DDevice->lpVtbl->SetTexture(g_D3DDevice, stage, texture);
			++g_D3DCallCount;
			return;
		}
		if (g_Textures[stage] != texture)
		{
			if (g_Textures[stage])
				g_Textures[stage]->lpVtbl->Release(g_Textures[stage]);
			g_Textures[stage] = texture;
			if (g_Textures[stage])
				g_Textures[stage]->lpVtbl->AddRef(g_Textures[stage]);
			g_D3DDevice->lpVtbl->SetTexture(g_D3DDevice, stage, texture);
			++g_D3DCallCount;
			++g_TextureChanges;
		}
	}
	else
	{
		if (stage >= MAX_TEXTURE_STAGES)
		{
			g_D3DDevice->lpVtbl->SetTexture(g_D3DDevice, stage, 0);
			++g_D3DCallCount;
			return;
		}
		if (g_Textures[stage] != 0)
		{
			g_Textures[stage]->lpVtbl->Release(g_Textures[stage]);
			g_Textures[stage] = 0;
			g_D3DDevice->lpVtbl->SetTexture(g_D3DDevice, stage, 0);
			++g_D3DCallCount;
			++g_TextureChanges;
		}
	}
}
