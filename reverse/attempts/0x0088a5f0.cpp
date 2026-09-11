// ?_heap_abort@@YAXXZ
// partial score=0.95 date=2026-09-11
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

class BfmeDebugManager
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
	virtual BfmeDebugManager *recordCallsite(unsigned int address, int kind);
	virtual void beginReport();
	virtual void slot64(); virtual void slot68();
	virtual BfmeDebugMessage *crashBegin(const char *file, int line);
};

extern BfmeDebugManager *TheBfmeDebugManager;

void __cdecl _heap_abort(void)
{
	const void * volatile caller = _ReturnAddress();
	_ReadWriteBarrier();
	{
		BfmeDebugManager *manager = TheBfmeDebugManager;
		unsigned int address = (unsigned int)caller;
		manager->recordCallsite(address, 1);
	}
	TheBfmeDebugManager->beginReport();
	TheBfmeDebugManager->crashBegin(0, 0)->slot38("Fatal heap error.")->slot4C(true);
}
