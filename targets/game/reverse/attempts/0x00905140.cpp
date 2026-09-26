// ?Create_Render_Target@DX8Wrapper@@SA?AV?$RefCountPtr@VTextureClass@@@@HHW4WW3DFormat@@@Z
// partial score=0.86 date=2026-09-22
// ?Create_Render_Target@DX8Wrapper@@SA?AV?$RefCountPtr@VTextureClass@@@@HHW4WW3DFormat@@@Z
// Partial reconstruction retained after the 2026-09-22 retry.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// DX8Wrapper::Create_Render_Target(int,int,WW3DFormat), retail 0x00905140
// The BFME ABI is RefCountPtr<TextureClass> by hidden sret. The support table
// is at CurrentCaps+0x1a7 and the caps subobject at CurrentCaps+8. The
// retaining copy helper is required by the complete landed RefCountPtr model.
// Probe result: 366 B versus 358 B, with the first non-relocation mismatch at
// +0x58. Retail keeps the unsupported-format null return inline after the
// three checks; MSVC hoists it to the common tail. Direct format assignment,
// corrected vtable arity, corrected member offsets, goto/else guards, and
// default and named null-result spellings did not remove this wall.

extern "C" int __cdecl Find_POT(int size);

typedef enum { WW3D_FORMAT_UNKNOWN = 0 } WW3DFormat;

struct D3DDISPLAYMODE { unsigned Width, Height, RefreshRate, Format; };
struct IDirect3DDevice8Vtbl
{
	void *reserved[8];
	long (__stdcall *GetDisplayMode)(void *self, unsigned swapChain, D3DDISPLAYMODE *mode);
};
struct IDirect3DDevice8 { IDirect3DDevice8Vtbl *lpVtbl; };

extern unsigned number_of_DX8_calls;

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

private:
	int MaxDisplayWidth;
	int MaxDisplayHeight;
	D3DCapsPrefix Caps;
	unsigned char m_layoutGap[0x13f];

public:
	unsigned char m_supportedRenderTargetFormat[100];
};

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
	RefCountPtr(RefCountPtr const &other) : Referent(other.Referent)
	{
		if (Referent != 0)
			++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(Referent) + 4);
	}
	~RefCountPtr();

private:
	T *Referent;
};

class DX8Wrapper
{
	protected:
	static IDirect3DDevice8 *D3DDevice;
	static DX8Caps *CurrentCaps;

public:
	static RefCountPtr<TextureClass> Create_Render_Target(int width, int height, WW3DFormat format);
};

RefCountPtr<TextureClass> DX8Wrapper::Create_Render_Target(int width, int height, WW3DFormat format)
{
	++number_of_DX8_calls;

	if (format == WW3D_FORMAT_UNKNOWN)
	{
		D3DDISPLAYMODE mode;
		DX8Wrapper::D3DDevice->lpVtbl->GetDisplayMode(DX8Wrapper::D3DDevice, format, &mode);
		++number_of_DX8_calls;
		format = (WW3DFormat)mode.Format;
	}

	if (format < 0 || format >= 100 || !DX8Wrapper::CurrentCaps->m_supportedRenderTargetFormat[format])
		return 0;

	const D3DCapsPrefix &caps = DX8Wrapper::CurrentCaps->Get_DX8_Caps();
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
