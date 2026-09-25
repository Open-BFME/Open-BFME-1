// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

// Retail 0x003C8030, 64 bytes, ret 0x10. The only call reaches 0x003C7F40
// through ILT 0x00029B31 with three stack arguments and no ECX setup: retail
// keeps ECX untouched from entry to the call (arguments are staged through
// EAX/EDX only), so both functions are __thiscall members of one owner and the
// incoming this is passed straight through. Neither the owner nor either
// method has a caller, vtable slot or string naming it, so all names stay
// address-qualified.
class Rva003C7F40Receiver;

// The looked-up object: vslot +0x190 takes one int, the dword at +4 is a
// reference count, and vslot 0 is called when it drops to zero.
class Rva003C8030Result
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0A();
	virtual void slot0B();
	virtual void slot0C();
	virtual void slot0D();
	virtual void slot0E();
	virtual void slot0F();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot1A();
	virtual void slot1B();
	virtual void slot1C();
	virtual void slot1D();
	virtual void slot1E();
	virtual void slot1F();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot2A();
	virtual void slot2B();
	virtual void slot2C();
	virtual void slot2D();
	virtual void slot2E();
	virtual void slot2F();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot3A();
	virtual void slot3B();
	virtual void slot3C();
	virtual void slot3D();
	virtual void slot3E();
	virtual void slot3F();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot4A();
	virtual void slot4B();
	virtual void slot4C();
	virtual void slot4D();
	virtual void slot4E();
	virtual void slot4F();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot5A();
	virtual void slot5B();
	virtual void slot5C();
	virtual void slot5D();
	virtual void slot5E();
	virtual void slot5F();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64Int(int on);

	int m_refCount;
};

class Rva003C7F40Owner
{
public:
	void *rva003C7F40(Rva003C7F40Receiver *receiver, const AsciiString &left, const AsciiString &right);
	void rva003C8030(Rva003C7F40Receiver *receiver, const AsciiString &left, const AsciiString &right, bool flag);
};

void Rva003C7F40Owner::rva003C8030(Rva003C7F40Receiver *receiver, const AsciiString &left, const AsciiString &right, bool flag)
{
	Rva003C8030Result *thing = (Rva003C8030Result *)rva003C7F40(receiver, left, right);

	if (thing == 0)
		return;

	thing->slot64Int(!flag);

	if (--thing->m_refCount == 0)
		thing->slot00();
}
