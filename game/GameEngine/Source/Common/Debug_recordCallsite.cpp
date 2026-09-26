// cl: /DNDEBUG /MD /EHs-c- /Oy-

// Forward the caller address and diagnostic kind to the shared BFME debug
// manager. WWDebug's SkipNext uses this same frame-pointer capture idiom and
// explicitly requires a valid frame pointer; the rest of the body is C++.

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
	unsigned returnAddress;
	__asm
	{
		mov eax, [ebp + 4]
		mov returnAddress, eax
	}
	TheGen001336E5C->slot5C(reinterpret_cast<void *>(returnAddress), kind);
}
