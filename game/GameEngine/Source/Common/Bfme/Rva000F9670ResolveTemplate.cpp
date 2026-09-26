// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib

// Retail 0x000F9670 (32 bytes).  The receiver is the same 0x60-byte record
// vector whose checked element accessor is matched at 0x000F94B0.  Each
// record begins with the AsciiString passed to the global ThingFactory.
// Retail callers at 0x000FE476, 0x0029D980, and 0x004A6021 consume EAX as a
// pointer, proving the return ABI; the first pushes it directly into the next
// call and the latter two store/use it.  A relocation-wildcard scan finds this
// complete instruction shape only at 0x000F9670, followed by INT3 padding.

#include "ascii_string.h"

class ThingTemplate;

// Existing matched BFME ABI view of the retail ThingFactory body at
// 0x00137E80.
class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern BfmeThingFactory *TheThingFactory;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct BfmeElemVLH
{
	AsciiString m_name;
	unsigned char m_opaque04[0x5c];
};

class BfmeVecVLH
{
public:
	BfmeElemVLH *bfmeAtVLH(int index);
	const ThingTemplate *rva000F9670(int index);

private:
	int m_opaque00;
	BfmeElemVLH *m_begin;
	BfmeElemVLH *m_end;
};

// ?rva000F9670@BfmeVecVLH@@QAEPBVThingTemplate@@H@Z
const ThingTemplate *BfmeVecVLH::rva000F9670(int index)
{
	BfmeElemVLH *record = bfmeAtVLH(index);
	if (record == 0)
	{
		// This intrinsic emits no instruction.  It preserves retail's null
		// fallthrough block ahead of the non-null tail call under MSVC 7.1.
		_ReadWriteBarrier();
		return 0;
	}

	return TheThingFactory->findTemplate(record->m_name);
}
