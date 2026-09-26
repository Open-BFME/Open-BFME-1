// Open-BFME: Rva003C8340::notifyHilight at retail 0x003C7420.
// The shared thunk at 0x0003F413 is called with the Rva003C8340 receiver
// still in ECX. Its owner pointer sits at +0x04, and the target dispatches
// the HilightBordersEffect key through the owner at +0x40.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef bool Bool;

class Rva003C8340Item
{
public:
	char m_unmodelled_000[0x28];
	int m_payload;
};

class Rva003BAD00Owner
{
public:
	void notify0C(const AsciiString &key, int payload, int mode);
	void notify04(const AsciiString &key, int mode);
	void notify08(const AsciiString &key, int mode);
};

class Rva003C8340
{
public:
	void notifyHilight(Rva003C8340Item *item, Bool enabled);

private:
	char m_unmodelled_000[4];
	Rva003BAD00Owner *m_owner;
};

// ?notifyHilight@Rva003C8340@@QAEXPAVRva003C8340Item@@_N@Z
void Rva003C8340::notifyHilight(Rva003C8340Item *item, Bool enabled)
{
	Rva003BAD00Owner *owner =
		(Rva003BAD00Owner *)((char *)m_owner + 0x40);
	if (enabled)
	{
		owner->notify0C(AsciiString("HilightBordersEffect"),
			(int)&item->m_payload, 1);
		owner->notify04(AsciiString("HilightBordersEffect"), 0);
	}
	else
	{
		owner->notify0C(AsciiString("HilightBordersEffect"),
			(int)&item->m_payload, 0);
		owner->notify08(AsciiString("HilightBordersEffect"), 1);
	}
}
