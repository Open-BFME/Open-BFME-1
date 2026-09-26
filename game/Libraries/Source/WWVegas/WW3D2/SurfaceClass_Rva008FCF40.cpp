// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <string.h>
#include <windows.h>

typedef unsigned long BfmeResult;

struct BfmeLockedRect008FCF40
{
	long Pitch;
	void *pBits;
};

class BFMEDebugStream008FCF40
{
public:
	virtual BFMEDebugStream008FCF40 *Put_Unsigned(unsigned value);
	virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34();
	virtual BFMEDebugStream008FCF40 *Put_String(const char *text);
	virtual void Slot3C(); virtual void Slot40(); virtual void Slot44(); virtual void Slot48();
	virtual BFMEDebugStream008FCF40 *Finish(int report);
};

class BFMEDebugClass008FCF40
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
	virtual BFMEDebugStream008FCF40 *Get_Stream(void *owner, void *context);
};

class BfmeSurfaceResource008FCF40
{
public:
	virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30();
	virtual BfmeResult __stdcall LockRect(BfmeLockedRect008FCF40 *, RECT *, unsigned);
	virtual BfmeResult __stdcall UnlockRect();
};

extern BFMEDebugClass008FCF40 *g_BFMEIndexBufferDebug;
extern void _bfme_debugRecordCallsite(int kind);

static __forceinline void BFME_Surface_ErrorCode008FCF40(unsigned result)
{
	if (result != 0) {
		_bfme_debugRecordCallsite(1);
		g_BFMEIndexBufferDebug->Begin_Report();
		BFMEDebugStream008FCF40 *stream =
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
	void rva008FCF40(unsigned x, unsigned y, unsigned value);

private:
	BfmeSurfaceResource008FCF40 *D3DSurface;
};

// Address-qualified name: the sole direct caller is the W3DRadar shroud path,
// but no surviving source or relocation recovers the historical method verb.
void SurfaceClass::rva008FCF40(unsigned x, unsigned y, unsigned value)
{
	if (D3DSurface == 0)
		return;

	SurfaceDescription description;
	Get_Description(description);

	BfmeLockedRect008FCF40 lock;
	memset(&lock, 0, sizeof(lock));

	RECT rect;
	memset(&rect, 0, sizeof(rect));

	rect.bottom = y + 1;
	rect.top = y;
	rect.left = x;
	rect.right = x + 1;

	BFME_Surface_ErrorCode008FCF40(
		D3DSurface->LockRect(&lock, &rect, 0));

	if (description.Format == 0x15)
		static_cast<unsigned char *>(lock.pBits)[3] = (unsigned char)value;

	BFME_Surface_ErrorCode008FCF40(D3DSurface->UnlockRect());
}
