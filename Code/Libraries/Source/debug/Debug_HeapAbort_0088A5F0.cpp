// cl: /DNDEBUG /MD /EHs-c- /Oy-

// _heap_abort at 0x0088A5F0 (78 B): the CRT fatal-heap hook from the Zero Hour
// debug library (debug_debug.cpp: DCRASH_RELEASE("Fatal heap error.")). Retail
// pushes that exact literal (0x01133150) and runs BFME's release crash chain on
// the debug manager global 0x01336E5C: record the caller (slot 0x5C with the
// return address and kind 1, the same call _bfme_debugRecordCallsite at
// 0x008896A0 makes), slot 0x60, slot 0x6C(0,0), then slot 0x38 with the
// message and slot 0x4C(true) on the returned report object.
//
// The caller is captured through a stack slot the way the frame-pointer
// idiom of 0x008896A0 does. The barrier keeps the store ahead of the global
// load (docs/shape_levers.md, _ReadWriteBarrier store-order row, landed at
// 0x009A45A0). The __assume states that a return address is never null
// (docs/shape_levers.md, codepushbool 0x0099EF70 __assume precedent); it emits
// no bytes and keeps the call temporaries in retail's EAX/EDX order.
//
// Slot and report-class names are offsets only; no identity is claimed.

extern "C" void *_ReturnAddress(void);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReturnAddress)
#pragma intrinsic(_ReadWriteBarrier)

class Rva0088A5F0Report
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual Rva0088A5F0Report *slot38(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual bool slot4C(bool fatal);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58();
	virtual void slot5C(void *returnAddress, int kind);
	virtual void slot60();
	virtual void slot64(); virtual void slot68();
	virtual Rva0088A5F0Report *slot6C(const char *file, int line);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;

// ?_heap_abort@@YAXXZ
void __cdecl _heap_abort(void)
{
	void *returnAddress = _ReturnAddress();
	void * volatile caller = returnAddress;
	_ReadWriteBarrier();
	TheBfmeAwakenDebug->slot5C(caller, 1);
	__assume(returnAddress != 0);
	TheBfmeAwakenDebug->slot60();
	TheBfmeAwakenDebug->slot6C(0, 0)->slot38("Fatal heap error.")->slot4C(true);
}
