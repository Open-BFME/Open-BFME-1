// cl: /DNDEBUG /MD /EHs-c- /Oy-

// _heap_abort at 0x0088A5F0 (78 B): the CRT fatal-heap hook from the Zero Hour
// debug library (debug_debug.cpp: DCRASH_RELEASE("Fatal heap error.")). Retail
// pushes that exact literal (0x01133150) and runs BFME's release crash chain on
// the debug manager global 0x01336E5C: record the caller (slot 0x5C with the
// return address and kind 1, the same call _bfme_debugRecordCallsite at
// 0x008896A0 makes), slot 0x60, slot 0x6C(0,0), then slot 0x38 with the
// message and slot 0x4C(true) on the returned report object.
//
// The caller is captured with the inline `mov eax,[ebp+4]` idiom Zero Hour's
// Debug::SkipNext uses (debug_debug.cpp: "we do need a valid frame pointer
// here"), the same capture the landed _bfme_debugRecordCallsite at 0x008896A0
// compiles; the asm block also forces the stack-slot store and reload retail
// shows at +0x07 and +0x10.
//
// Slot and report-class names are offsets only; no identity is claimed.

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
	unsigned returnAddress;
	__asm
	{
		mov eax, [ebp + 4]
		mov returnAddress, eax
	}
	TheBfmeAwakenDebug->slot5C(reinterpret_cast<void *>(returnAddress), 1);
	TheBfmeAwakenDebug->slot60();
	TheBfmeAwakenDebug->slot6C(0, 0)->slot38("Fatal heap error.")->slot4C(true);
}
