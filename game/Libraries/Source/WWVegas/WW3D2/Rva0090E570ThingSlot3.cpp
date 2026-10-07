// cl: /DNDEBUG /MD /EHsc
// Rva0090E570Thing slot 3, retail 0x0090D860 (685 bytes).
//
// The vftable at 0x0113A6B0 is pinned to Rva0090E570Thing (its constructor at
// 0x0090E570 writes it; Rva0090E570ThingCtor.cpp); slot 3 points here, which
// that TU declares as derivedSlot3. Its layout gives the fields this body
// reads: +0x14 the 0x48-byte texture holder of Rva0090C2F0InnerLoad.cpp and
// +0x40 the constructor's third argument, used here as an 0x00RRGGBB tint.
//
// The body reloads the texture from its in-memory image (slot 0 supplies the
// name), then multiplies every pixel of mip level 0 by the tint over 255: per
// nibble for A4R4G4B4 (alpha kept) and per byte for A8R8G8B8, and finally
// rebuilds the mip chain with D3DXFilterTexture. EA's file is texture.cpp
// (ea_evidence.csv); nothing names the method, so it keeps the placeholder.

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

extern void *g_Rva00F36E5C; // VA 01336E5C debug manager cell (data_rows.csv owner)
#define TheBfmeAwakenDebug (static_cast<BfmeAwakenDebug *>(g_Rva00F36E5C))

// Native D3D9 interfaces, only the slots this body calls.
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
	virtual void __stdcall s34(void); virtual void __stdcall s38(void);
	virtual void __stdcall s3c(void); virtual void __stdcall s40(void);
	virtual void __stdcall s44(void);
	virtual long __stdcall GetSurfaceLevel(unsigned level, IDirect3DSurface9 **surface);	// +0x48
};

extern "C" long __stdcall D3DXFilterTexture(IDirect3DTexture9 *texture, const void *palette,
	unsigned srcLevel, unsigned filter);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.h
// BFME's SurfaceClass holds only the D3D9 surface; Format is the raw D3DFORMAT.
struct BfmeItemDC;
class BfmeThingDC
{
public:
	BfmeThingDC(BfmeItemDC *item);

private:
	BfmeItemDC *m_bfmeItem;
};

class SurfaceClass
{
public:
	struct SurfaceDescription {
		unsigned Format;
		unsigned int Width;
		unsigned int Height;
	};

	SurfaceClass(BfmeItemDC *item) : m_surfaceOwner(item) {}
	void Get_Description(SurfaceDescription &surface_desc);
	void *Lock(int *pitch, bool discard);
	void Unlock(void);

	// Same one-pointer storage as the SurfaceClass D3D9 field.
	BfmeThingDC m_surfaceOwner;
};

// Retail destroys the surface (inline and in its unwind funclet) through
// 0x008FC5B0, the matched ??1W3DRadarResetSurface@@QAE@XZ row, the same
// wrapper W3DSmudgeManager_ReAcquireResources.cpp declares.
class W3DRadarResetSurface : public SurfaceClass
{
public:
	W3DRadarResetSurface(BfmeItemDC *item) : SurfaceClass(item) {}
	~W3DRadarResetSurface();
};

// Rva0090C2F0InnerLoad.cpp
class Rva0090C2F0Inner
{
public:
	void rva0090CD00LoadFromMemory(const char *name);

	void *m_vptr;
	char m_04;
	IDirect3DTexture9 *m_08;
};

// Rva0090E570ThingCtor.cpp
class Rva0090E570Thing
{
public:
	virtual const char *slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void derivedSlot3(void);

	unsigned int m_flags;
	unsigned int m_zero08;
	unsigned int m_zero0c;
	unsigned int m_zero10;
	Rva0090C2F0Inner *m_bfme14;
	char m_gap18[0x40 - 0x18];
	int m_field;
};

enum
{
	RVA0090D860_FORMAT_A8R8G8B8 = 0x15,
	RVA0090D860_FORMAT_A4R4G4B4 = 0x1A
};

// ?derivedSlot3@Rva0090E570Thing@@UAEXXZ
void Rva0090E570Thing::derivedSlot3(void)
{
	m_bfme14->rva0090CD00LoadFromMemory(slot00());

	if (m_bfme14->m_08)
	{
		IDirect3DSurface9 *surface = 0;
		long result = m_bfme14->m_08->GetSurfaceLevel(0, &surface);
		if (result)
		{
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->slot60();
			TheBfmeAwakenDebug->slot6c(0, 0)->slot38("DX8 error ")->slot00(result)->slot4c(1);
		}

		W3DRadarResetSurface surf((BfmeItemDC *)surface);
		if (surface)
			surface->Release();

		int pitch;
		void *bits = surf.Lock(&pitch, false);
		SurfaceClass::SurfaceDescription desc;
		surf.Get_Description(desc);

		// Retail reads red and green as single bytes of the tint and blue as
		// the masked dword, all three before the pixel loops.
		int red = ((unsigned char *)&m_field)[2];
		int green = ((unsigned char *)&m_field)[1];
		int blue = m_field & 0xff;

		switch (desc.Format)
		{
		case RVA0090D860_FORMAT_A4R4G4B4:
			{
				unsigned short *pixel = (unsigned short *)bits;
				for (unsigned int y = desc.Height; y; y--)
				{
					for (unsigned int x = desc.Width; x; x--)
					{
						unsigned short value = *pixel;
						*pixel = (unsigned short)((((value * red) / 255) & 0xf00)
							| (((value * green) / 255) & 0xf0)
							| (((value * blue) / 255) & 0xf)
							| (value & 0xf000));
						pixel++;
					}
					pixel += pitch / 2 - desc.Width;
				}
			}
			break;

		case RVA0090D860_FORMAT_A8R8G8B8:
			{
				unsigned char *pixel = (unsigned char *)bits;
				for (unsigned int y = desc.Height; y; y--)
				{
					for (unsigned int x = desc.Width; x; x--)
					{
						pixel[0] = (unsigned char)((pixel[0] * blue) / 255);
						pixel[1] = (unsigned char)((pixel[1] * green) / 255);
						pixel[2] = (unsigned char)((pixel[2] * red) / 255);
						pixel += 4;
					}
					pixel += pitch - desc.Width * 4;
				}
			}
			break;
		}

		surf.Unlock();
		D3DXFilterTexture(m_bfme14->m_08, 0, 0, 0xffffffff);
	}
}
