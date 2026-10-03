// cl: /DNDEBUG /MD /EHsc
// Rva0090C2F0Inner::rva0090CD00LoadFromMemory, retail 0x0090CD00 (649 bytes).
//
// The 0x48-byte texture holder Rva0090C2F0Go.cpp and Rva006D51B0Ctor.cpp
// already lay out: +0x08 the D3D texture, +0x10/+0x14 an image file held in
// memory and its size, +0x1C a second buffer, +0x24..+0x30 current and
// original size, +0x34 mip levels, +0x38 reduction mode, +0x3C format.
// The body reads the image header with D3DX, shrinks the size by the
// global texture reduction (never below 32, and at most one step for names
// starting "livingmap"), builds the texture from memory, frees both
// buffers and records the format and mip count; with no image, or when D3DX
// fails, it falls back to go(1, 1, 0x15, ...) -- the 1x1 A8R8G8B8 texture
// -- and paints its one pixel 0xFFFF00FF. go() (0x0090C2F0) is inlined here.
// The only caller, BfmeThing937B::bfmeGo937B, passes its own name string.
// Nothing names the member, so it keeps the address.

// The buffers are freed through operator delete[] (0x00881EF0); without this
// declaration VC7.1 lowers delete[] of a POD array to operator delete.
void __cdecl operator delete[](void *p);

extern "C" __declspec(dllimport) int __cdecl _strnicmp(const char *a, const char *b, unsigned int n);

extern void W3DRadarResetLock(void);
extern char bfmeUnlock1179(void);
extern int Rva008FD440Get(void);		// the global texture reduction

extern void _bfme_debugRecordCallsite(int kind);

class BfmeAwakenLog
{
public:
	virtual BfmeAwakenLog *slot00(int value);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual BfmeAwakenLog *slot38(const char *value);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual BfmeAwakenLog *slot4c(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(void);
	virtual void slot50(void);
	virtual void slot54(void);
	virtual void slot58(void);
	virtual void slot5c(void);
	virtual void slot60(void);
	virtual void slot64(void);
	virtual void slot68(void);
	virtual BfmeAwakenLog *slot6c(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;

// Native D3D9 interfaces, only the slots this body calls.
struct D3DSURFACE_DESC
{
	unsigned Format, Type, Usage, Pool, MultiSampleType, MultiSampleQuality, Width, Height;
};

struct D3DXIMAGE_INFO
{
	unsigned Width, Height, Depth, MipLevels, Format, ResourceType, ImageFileFormat;
};

struct IDirect3DSurface9
{
	virtual long __stdcall QueryInterface(const void *iid, void **object);
	virtual unsigned long __stdcall AddRef(void);
	virtual unsigned long __stdcall Release(void);
};

struct IDirect3DTexture9
{
	virtual long __stdcall QueryInterface(const void *iid, void **object);
	virtual unsigned long __stdcall AddRef(void);
	virtual unsigned long __stdcall Release(void);
	virtual void __stdcall s0c(void); virtual void __stdcall s10(void);
	virtual void __stdcall s14(void); virtual void __stdcall s18(void);
	virtual void __stdcall s1c(void); virtual void __stdcall s20(void);
	virtual void __stdcall s24(void); virtual void __stdcall s28(void);
	virtual void __stdcall s2c(void); virtual void __stdcall s30(void);
	virtual unsigned long __stdcall GetLevelCount(void);				// +0x34
	virtual void __stdcall s38(void); virtual void __stdcall s3c(void);
	virtual void __stdcall s40(void);
	virtual long __stdcall GetLevelDesc(unsigned level, D3DSURFACE_DESC *desc);	// +0x44
	virtual long __stdcall GetSurfaceLevel(unsigned level, IDirect3DSurface9 **surface);	// +0x48
};

struct IDirect3DDevice8;

extern "C" long __stdcall D3DXGetImageInfoFromFileInMemory(const void *data, unsigned size,
	D3DXIMAGE_INFO *info);
extern "C" long __stdcall D3DXCreateTextureFromFileInMemoryEx(IDirect3DDevice8 *device,
	const void *data, unsigned size, unsigned width, unsigned height, unsigned mipLevels,
	unsigned usage, unsigned format, unsigned pool, unsigned filter, unsigned mipFilter,
	unsigned colorKey, D3DXIMAGE_INFO *srcInfo, void *palette, IDirect3DTexture9 **texture);

class Rva0090C2F0Inner;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
	friend class Rva0090C2F0Inner;

protected:
	static IDirect3DDevice8 *D3DDevice;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.h
class SurfaceClass
{
public:
	SurfaceClass(IDirect3DSurface9 *d3d_surface);
	~SurfaceClass();
	void DrawPixel(const unsigned int x, const unsigned int y, unsigned int color);

private:
	IDirect3DSurface9 *D3DSurface;
};

// Unwind state 0 releases this scope lock; both halves inline, as in
// W3DRadar_taintCell_rva006C2710.cpp.
class Rva0090CD00Lock
{
public:
	Rva0090CD00Lock() { W3DRadarResetLock(); }
	~Rva0090CD00Lock() { bfmeUnlock1179(); }
};

// Rva00904BE0TextureCreate.cpp: DX8Wrapper::_Create_DX8_Texture's BFME body.
struct Rva00904BE0Texture;
Rva00904BE0Texture *Rva00904BE0CreateTexture(unsigned width, unsigned height, unsigned format,
	unsigned mipLevels, unsigned pool, unsigned usage);

class Rva0090C2F0Inner
{
	void *m_vptr;
	char m_04;
	IDirect3DTexture9 *m_08;
	int m_0C;
	unsigned char *m_10;
	unsigned m_14;
	int m_18;
	unsigned char *m_1C;
	int m_20;
	unsigned m_24;
	unsigned m_28;
	unsigned m_2C;
	unsigned m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;

	friend void rva0090C2F0Go(Rva0090C2F0Inner *self, int arg1, int arg2, int arg3, int arg4, int arg5,
		int arg6, int arg7);

public:
	void go(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7);
	bool rva0090CAD0();
	void rva0090CD00LoadFromMemory(const char *name);
};

// The body of 0x0090C2F0, visible here so it inlines as it does in retail.
// It is a TU-local function, not the member of Rva0090C2F0Inner: that member
// is defined out of line (and owned by the ledger) in Rva0090C2F0Go.cpp, and a
// second definition of it here would collide at link (LNK2005).
static __forceinline void rva0090C2F0Go(Rva0090C2F0Inner *self, int arg1, int arg2, int arg3,
	int arg4, int arg5, int arg6, int arg7)
{
	if (self->m_08 != 0)
		return;

	self->m_34 = arg4;
	self->m_3C = arg3;
	self->m_40 = arg5;
	self->m_44 = arg6;
	self->m_38 = arg7;

	int mode;
	switch (arg5) {
	case 0:
		mode = 0;
		break;
	case 1:
		mode = 1;
		break;
	case 2:
		mode = 2;
		break;
	default:
		mode = 0;
		break;
	}

	int flags;
	switch (arg6) {
	case 0:
		flags = 0;
		break;
	case 1:
		flags = 1;
		break;
	case 2:
		flags = 0x200;
		break;
	default:
		flags = 0;
		break;
	}

	W3DRadarResetLock();
	self->m_08 = (IDirect3DTexture9 *)Rva00904BE0CreateTexture(arg1, arg2, arg3, arg4, mode, flags);
	bfmeUnlock1179();
	self->m_24 = arg1;
	self->m_28 = arg2;
	self->m_2C = arg1;
	self->m_30 = arg2;
}

// ?rva0090CD00LoadFromMemory@Rva0090C2F0Inner@@QAEXPBD@Z
void Rva0090C2F0Inner::rva0090CD00LoadFromMemory(const char *name)
{
	unsigned char *data = m_10;
	if (data != 0)
	{
		unsigned size = m_14;
		m_08 = 0;

		D3DXIMAGE_INFO info;
		if (D3DXGetImageInfoFromFileInMemory(data, size, &info) >= 0)
		{
			m_24 = info.Width;
			m_2C = info.Width;
			m_28 = info.Height;
			m_30 = info.Height;

			int reduction = Rva008FD440Get();
			if (m_38 < 2)
			{
				if (m_38 >= 1)
				{
					if (m_24 > 0x200 || m_28 > 0x200)
						reduction--;
					else
						goto create;
				}

				if (reduction > 1 && _strnicmp(name, "livingmap", 9) == 0)
					reduction = 1;

				while (reduction > 0)
				{
					reduction--;
					if (m_24 <= 32 || m_28 <= 32)
						break;
					m_24 >>= 1;
					m_28 >>= 1;
				}
			}
create:
			W3DRadarResetLock();
			if (m_1C)
				rva0090CAD0();
			else if (D3DXCreateTextureFromFileInMemoryEx(DX8Wrapper::D3DDevice, data, size,
					m_24, m_28, m_34, 0, m_3C, 1, 0xffffffff, 0xffffffff, 0, 0, 0, &m_08) < 0)
				m_08 = 0;
			bfmeUnlock1179();
		}

		m_40 = 1;
		m_44 = 0;
		delete[] m_10;
		m_10 = 0;
		if (m_1C)
		{
			delete[] m_1C;
			m_1C = 0;
		}

		if (m_08)
		{
			Rva0090CD00Lock lock;
			D3DSURFACE_DESC desc;
			m_08->GetLevelDesc(0, &desc);
			m_3C = desc.Format;
			m_34 = m_08->GetLevelCount();
			return;
		}
	}

	W3DRadarResetLock();
	rva0090C2F0Go(this, 1, 1, 0x15, 1, 1, 0, 0);

	if (m_08)
	{
		IDirect3DSurface9 *surface = 0;
		long result = m_08->GetSurfaceLevel(0, &surface);
		if (result)
		{
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->slot60();
			TheBfmeAwakenDebug->slot6c(0, 0)->slot38("DX8 error ")->slot00(result)->slot4c(1);
		}
		SurfaceClass(surface).DrawPixel(0, 0, 0xffff00ff);
		surface->Release();
	}
	bfmeUnlock1179();
}
