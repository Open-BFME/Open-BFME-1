// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <string.h>

struct BFMELockedRect008FC660
{
	int pitch;
	void *bits;
};

class BFMESurfaceResource008FC660
{
public:
	virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30();
	virtual unsigned long __stdcall LockRect(BFMELockedRect008FC660 *locked,
		const void *rectangle, unsigned flags);
};

class BFMEDebugStream008FC660
{
public:
	virtual BFMEDebugStream008FC660 *Put_Unsigned(unsigned value);
	virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34();
	virtual BFMEDebugStream008FC660 *Put_String(const char *text);
	virtual void Slot3C(); virtual void Slot40(); virtual void Slot44(); virtual void Slot48();
	virtual BFMEDebugStream008FC660 *Finish(int report);
};

class BFMEDebugClass008FC660
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
	virtual BFMEDebugStream008FC660 *Get_Stream(void *owner, void *context);
};

extern BFMEDebugClass008FC660 *g_BFMEIndexBufferDebug;
extern void _bfme_debugRecordCallsite(int kind);

static __forceinline void BFME_Surface_ErrorCode008FC660(unsigned result)
{
	if (result != 0) {
		_bfme_debugRecordCallsite(1);
		g_BFMEIndexBufferDebug->Begin_Report();
		BFMEDebugStream008FC660 *stream =
			g_BFMEIndexBufferDebug->Get_Stream(0, 0);
		stream->Put_String("DX8 error ")->Put_Unsigned(result)->Finish(1);
	}
}

class SurfaceClass
{
public:
	void *Lock(int *pitch, bool discard);
};

void *SurfaceClass::Lock(int *pitch, bool discard)
{
	BFMELockedRect008FC660 locked;
	memset(&locked, 0, sizeof(locked));
	BFMESurfaceResource008FC660 *surface =
		*reinterpret_cast<BFMESurfaceResource008FC660 **>(this);
	unsigned flags = 0x800 | (discard ? 0x2000 : 0);
	BFME_Surface_ErrorCode008FC660(surface->LockRect(&locked, 0, flags));
	*pitch = locked.pitch;
	return locked.bits;
}
