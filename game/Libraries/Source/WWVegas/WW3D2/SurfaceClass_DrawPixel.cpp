// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep

#include <windows.h>

typedef unsigned long BfmeResult;

struct BfmeLockedRect
{
	long Pitch;
	void *pBits;
};

typedef BfmeLockedRect D3DLOCKED_RECT;

class BFMEIndexBufferDebugStream
{
public:
	virtual BFMEIndexBufferDebugStream *Put_Unsigned(unsigned value);
	virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34();
	virtual BFMEIndexBufferDebugStream *Put_String(const char *text);
	virtual void Slot3C(); virtual void Slot40(); virtual void Slot44(); virtual void Slot48();
	virtual BFMEIndexBufferDebugStream *Finish(int report);
};

class BFMEIndexBufferDebugClass
{
public:
	virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3C();
	virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4C();
	virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5C();
	virtual void Begin_Report();
	virtual void Slot64(); virtual void Slot68();
	virtual BFMEIndexBufferDebugStream *Get_Stream(void *owner, void *context);
};

class BfmeSurfaceResource
{
public:
	virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30();
	virtual BfmeResult __stdcall LockRect(void *, RECT *, unsigned);
	virtual BfmeResult __stdcall UnlockRect();
};

extern BFMEIndexBufferDebugClass *g_BFMEIndexBufferDebug;
extern void _bfme_debugRecordCallsite(int kind);

static __forceinline void BFME_Surface_ErrorCode(unsigned result)
{
	if (result != 0) {
		_bfme_debugRecordCallsite(1);
		g_BFMEIndexBufferDebug->Begin_Report();
		BFMEIndexBufferDebugStream *stream =
			g_BFMEIndexBufferDebug->Get_Stream(0, 0);
		stream->Put_String("DX8 error ")->Put_Unsigned(result)->Finish(1);
	}
}

class SurfaceClass
{
public:
	struct SurfaceDescription
	{
		unsigned Format;
		unsigned Width;
		unsigned Height;
	};

	void Get_Description(SurfaceDescription &surface_desc);
	void DrawPixel(const unsigned int x, const unsigned int y, unsigned int color);
	unsigned int Rva008FCA30_Surface_Byte_Size() const;

private:
	BfmeSurfaceResource *D3DSurface;
};

extern void d_008fc4f0(void);

// Keep the format table beside the SurfaceClass methods that consume it.  The
// address-qualified helper name is retained because its historical verb is
// unavailable, while its caller and exact switch body are established.
static __declspec(noinline) unsigned int Rva008FC4F0_PixelSize(
	const SurfaceClass::SurfaceDescription &description)
{
	unsigned int size = 0;
	switch (description.Format)
	{
	case 21: case 22:
		size = 4;
		break;
	case 20:
		size = 3;
		break;
	case 23: case 24: case 25: case 26: case 29: case 30: case 40: case 51:
		size = 2;
		break;
	case 27: case 28: case 41: case 50: case 52:
		size = 1;
		break;
	}
	return size;
}

// ?DrawPixel@SurfaceClass@@QAEXIII@Z
void SurfaceClass::DrawPixel(const unsigned int x, const unsigned int y, unsigned int color)
{
	if (D3DSurface == 0)
		return;

	SurfaceDescription sd;
	Get_Description(sd);

	typedef unsigned (SurfaceClass::SurfaceDescription::*PixelSizeOperation)(void);
	union { void *asVoid; PixelSizeOperation asMember; } pixelSizeCast;
	pixelSizeCast.asVoid = reinterpret_cast<void *>(d_008fc4f0);
	unsigned int size =
		(reinterpret_cast<SurfaceClass::SurfaceDescription *>(&sd)->*pixelSizeCast.asMember)();

	D3DLOCKED_RECT lock_rect;
	::ZeroMemory(&lock_rect, sizeof(D3DLOCKED_RECT));
	RECT rect;
	::ZeroMemory(&rect, sizeof(RECT));

	rect.bottom = y + 1;
	rect.top = y;
	rect.left = x;
	rect.right = x + 1;

	BFME_Surface_ErrorCode(D3DSurface->LockRect(&lock_rect, &rect, 0));
	unsigned char *cptr = (unsigned char *)lock_rect.pBits;
	unsigned short *sptr = (unsigned short *)lock_rect.pBits;
	unsigned int *lptr = (unsigned int *)lock_rect.pBits;

	switch (size)
	{
	case 1:
		*cptr = (unsigned char)(color & 0xFF);
		break;
	case 2:
		*sptr = (unsigned short)(color & 0xFFFF);
		break;
	case 4:
		*lptr = color;
		break;
	}

	BFME_Surface_ErrorCode(D3DSurface->UnlockRect());
}

unsigned int SurfaceClass::Rva008FCA30_Surface_Byte_Size() const
{
	if (!D3DSurface)
		return 0;
	SurfaceDescription description;
	const_cast<SurfaceClass *>(this)->Get_Description(description);
	unsigned int pixelSize = Rva008FC4F0_PixelSize(description);
	if (pixelSize)
		return description.Width * description.Height * pixelSize;
	if (description.Format != 0x31545844 && description.Format != 0x32545844 &&
		description.Format != 0x33545844 && description.Format != 0x34545844 &&
		description.Format != 0x35545844)
		return 0;
	unsigned int size = description.Width * description.Height;
	if (description.Format == 0x31545844)
		size /= 2;
	return size;
}
