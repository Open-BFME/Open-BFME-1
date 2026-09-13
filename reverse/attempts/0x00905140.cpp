// ?Create_Render_Target@DX8Wrapper@@SA?AV?$RefCountPtr@VTextureClass@@@@HHW4WW3DFormat@@@Z
// partial score=0.85 date=2026-09-13
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// DX8Wrapper::Create_Render_Target(int,int,WW3DFormat), retail 0x00905140
// (358 B).  Prior banks assumed a raw TextureClass* return (matching ZH's
// declaration) and could not close the gap; the real BFME ABI returns
// RefCountPtr<TextureClass> by hidden sret, the SAME wrapper already
// verified in TextureHandleApply.cpp (Referent at offset 0).  Confirmed via
// full retail disassembly against ZH's dx8wrapper.cpp Create_Render_Target:
// default-format lookup via GetDisplayMode+D3DFormat_To_WW3DFormat, a
// direct byte-table format-support check at BfmeCurrentCaps+0x1a7 (replacing
// ZH's Support_Render_To_Texture_Format call), the power-of-two sizing via
// Find_POT and the unsigned-caps-to-float fixups (MaxTextureWidth/Height at
// caps+0x58/+0x5c), and the actual texture construction going through the
// already-landed Rva006D6050::init (0x0090DBC0) on a local temporary handle,
// whose Referent is then transplanted into the caller's sret slot with a
// manual AddRef (retail: `inc word ptr [ecx+4]`) mirroring the temp's own
// destructor Release (0x9EB7A0) when it goes out of scope.
// Compiles 365/358 (7 B over), every instruction present and in the right
// relative order; the one systematic difference is block PLACEMENT: retail
// keeps the merged "format unsupported -> return null handle" tail INLINE
// right after the three OR'd checks (a `jne` skips it, falls through
// otherwise), while this compiler always hoists that tail to the function's
// end regardless of phrasing, shifting every later offset and forcing
// larger e.g. `jl/jge` displacements. Ruled out: splitting the `||` into
// separate sequential `if(...) return` statements (duplicates the tail,
// 387 B, worse); a `goto` past the fail case to a `supported:` label placed
// where retail's inline block sits (identical 365 B, no change); returning
// via an implicit `T*`-converting constructor (`return 0;`) instead of the
// default constructor (identical 365 B, no change) -- so the tail hoist is
// not sensitive to any of the return-statement phrasings tried. Globals are
// unpinned in this probe (D3DDevice 0x1340534, DX8Calls 0x1340594,
// BfmeCurrentCaps 0x1340578, g_bfmeUint32Scale 0x1075358), so most of the
// probe's raw relocation-layout-drift noise clears once real pins are
// added; the 7-byte block-placement gap is the only real remaining defect.
// t=35min model=claude-sonnet-5

extern "C" int __cdecl Find_POT(int size);

typedef enum { WW3D_FORMAT_UNKNOWN = 0 } WW3DFormat;

struct D3DDISPLAYMODE { unsigned Width, Height, RefreshRate, Format; };
struct IDirect3DDevice8Vtbl
{
	void *reserved[8];
	long (__stdcall *GetDisplayMode)(void *self, D3DDISPLAYMODE *mode);
};
struct IDirect3DDevice8 { IDirect3DDevice8Vtbl *lpVtbl; };

extern "C" WW3DFormat __cdecl D3DFormat_To_WW3DFormat(unsigned fmt);

extern IDirect3DDevice8 *g_D3DDevice;
extern unsigned int g_D3DCallCount;

struct D3DCapsPrefix
{
	unsigned char reserved[0x58];
	unsigned int MaxTextureWidth;
	unsigned int MaxTextureHeight;
};

class DX8Caps
{
public:
	const D3DCapsPrefix &Get_DX8_Caps() const { return Caps; }

	unsigned char m_supportedRenderTargetFormat[100];
private:
	int MaxDisplayWidth;
	int MaxDisplayHeight;
	D3DCapsPrefix Caps;
};

extern DX8Caps *g_CurrentCaps;

class Rva006D6050TextureBase;

class Rva006D6050
{
public:
	Rva006D6050() : m_texture(0) {}
	~Rva006D6050();
	void init(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);

private:
	Rva006D6050TextureBase *m_texture;
};

class TextureClass;

template<class T>
class RefCountPtr
{
public:
	RefCountPtr(T *ptr = 0) : Referent(ptr) {}
	~RefCountPtr();

private:
	T *Referent;
};

class DX8Wrapper
{
public:
	static RefCountPtr<TextureClass> Create_Render_Target(int width, int height, WW3DFormat format);
};

RefCountPtr<TextureClass> DX8Wrapper::Create_Render_Target(int width, int height, WW3DFormat format)
{
	++g_D3DCallCount;

	if (format == WW3D_FORMAT_UNKNOWN)
	{
		D3DDISPLAYMODE mode;
		g_D3DDevice->lpVtbl->GetDisplayMode(g_D3DDevice, &mode);
		++g_D3DCallCount;
		format = D3DFormat_To_WW3DFormat(mode.Format);
	}

	if (format < 0 || format >= 100 || !g_CurrentCaps->m_supportedRenderTargetFormat[format])
		return 0;

	const D3DCapsPrefix &caps = g_CurrentCaps->Get_DX8_Caps();
	float poweroftwosize = (float)width;
	if (height > 0 && height < width)
		poweroftwosize = (float)height;
	int potInt = Find_POT((int)poweroftwosize);
	float potFloat = (float)potInt;
	if (potFloat > (float)caps.MaxTextureWidth)
		potFloat = (float)caps.MaxTextureWidth;
	if (potFloat > (float)caps.MaxTextureHeight)
		potFloat = (float)caps.MaxTextureHeight;
	width = height = (int)potFloat;

	Rva006D6050 tempHandle;
	tempHandle.init((unsigned)width, (unsigned)height, (unsigned)format, 1, 0, 1);
	return *reinterpret_cast<RefCountPtr<TextureClass> *>(&tempHandle);
}
