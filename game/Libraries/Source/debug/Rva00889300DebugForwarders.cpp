// Two forwarders into the debug singleton, carved from one 57-byte dump at
// 0x00889300 (the int3 run at +0x1E splits it): 0x00889300 passes three
// arguments to vftable slot 0x80 and 0x00889320 passes two to slot 0x84.
// They sit between Debug::RepeatChar and the Debug constructor, and load the
// same opaque singleton pointer cell (0x01336E5C) that Debug::PreStaticInit sets.
// The arguments are pushed again rather than tail-jumped, as a cdecl caller
// forwarding to a thiscall slot must. No direct callers, so the names keep the
// address; the slot numbers are all the bytes say about the callees.

class BfmeAwakenDebug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80(int first, int second, int third);
	virtual void slot84(int first, int second);
};

// Existing owned pointer cell; the original singleton class type is unproven.
extern void *g_Rva00F36E5C;

// ?Rva00889300DebugForward3@@YAXHHH@Z
void Rva00889300DebugForward3(int first, int second, int third)
{
	reinterpret_cast<BfmeAwakenDebug *>(g_Rva00F36E5C)->slot80(first, second, third);
}

// ?Rva00889320DebugForward2@@YAXHH@Z
void Rva00889320DebugForward2(int first, int second)
{
	reinterpret_cast<BfmeAwakenDebug *>(g_Rva00F36E5C)->slot84(first, second);
}
