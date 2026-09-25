// ?_heap_abort@@YAXXZ
// partial score=0.9744 date=2026-09-25
// ?_heap_abort@@YAXXZ
// cl: /DNDEBUG /MD /EHsc /Oy-

extern "C" void *_ReturnAddress(void);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReturnAddress)
#pragma intrinsic(_ReadWriteBarrier)

class BfmeDebugMessage
{
public:
	virtual BfmeDebugMessage *slot00(const void *value);
	virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18();
	virtual void slot1C(); virtual void slot20(); virtual void slot24();
	virtual void slot28(); virtual void slot2C(); virtual void slot30();
	virtual void slot34();
	virtual BfmeDebugMessage *slot38(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44();
	virtual void slot48();
	virtual bool slot4C(bool fatal);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3C(); virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C(); virtual void slot50();
	virtual void slot54(); virtual void slot58();
	virtual void recordCallsite(const void *address, int kind);
	virtual void beginReport();
	virtual void slot64(); virtual void slot68();
	virtual BfmeDebugMessage *crashBegin(const char *file, int line);
};

// The first slot takes the caller and diagnostic kind on the stack. The EDX
// duplicate is a caller-side adapter for the witnessed retail register shape.
typedef void (__fastcall *BfmeRecordCallsiteSlot)(
	BfmeAwakenDebug *manager, unsigned int edxCaller,
	unsigned int address, int kind);

typedef void (__fastcall *BfmeBeginReportSlot)(BfmeAwakenDebug *manager);
struct BfmeAwakenDebugVtable;
// The crash-begin adapter passes the table in EDX; the real thiscall slot
// still receives only file and line on the stack.
typedef BfmeDebugMessage *(__fastcall *BfmeCrashBeginSlot)(
	BfmeAwakenDebug *manager, BfmeAwakenDebugVtable *edxVtable,
	const char *file, int line);

struct BfmeAwakenDebugVtable
{
	void *slots[0x5c / sizeof(void *)];
	BfmeRecordCallsiteSlot recordCallsite;
	BfmeBeginReportSlot beginReport;
	void *slot64;
	void *slot68;
	BfmeCrashBeginSlot crashBegin;
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;

void __cdecl _heap_abort(void)
{
	const void * volatile caller = _ReturnAddress();
	_ReadWriteBarrier();
	{
		BfmeAwakenDebug *manager = TheBfmeAwakenDebug;
		unsigned int address = (unsigned int)caller;
		BfmeAwakenDebugVtable *vtable =
			*reinterpret_cast<BfmeAwakenDebugVtable **>(manager);
		vtable->recordCallsite(manager, address, address, 1);
	}
	{
		BfmeAwakenDebug *manager = TheBfmeAwakenDebug;
		BfmeAwakenDebugVtable *vtable =
			*reinterpret_cast<BfmeAwakenDebugVtable **>(manager);
		vtable->beginReport(manager);
	}
	{
		BfmeAwakenDebug *manager = TheBfmeAwakenDebug;
		BfmeAwakenDebugVtable *vtable =
			*reinterpret_cast<BfmeAwakenDebugVtable **>(manager);
		vtable->crashBegin(manager, vtable, 0, 0)
			->slot38("Fatal heap error.")->slot4C(true);
	}
}
