// ?_bfme_debugRecordCallsite@@YAXH@Z
// partial score=0.98 date=2026-08-28
// cl: /DNDEBUG /MD /EHs-c- /Oy-
// Forward the caller address and diagnostic kind to the shared BFME debug
// manager.  _ReturnAddress is the compiler intrinsic used by the retail
// crash-report macro expansion.

extern "C" void * _ReturnAddress(void);
#pragma intrinsic(_ReturnAddress)
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Gen001336E5C
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58();
	virtual void slot5C(void *returnAddress, int kind);
};

extern Gen001336E5C *TheGen001336E5C;

// ?_bfme_debugRecordCallsite@@YAXH@Z
void _bfme_debugRecordCallsite(int kind)
{
	void * volatile returnAddress = _ReturnAddress();
	_ReadWriteBarrier();
	TheGen001336E5C->slot5C(returnAddress, kind);
}
