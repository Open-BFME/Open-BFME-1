// ?getStringSlot@Rva00387D90StringSlots@@QBEABVAsciiString@@H@Z
// partial score=0.55 date=2026-09-02
// cl: /O2 /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// BFME string-slot lookup with the retail local-static invalid sentinel.

#include "StringInline.h"

class Rva00387D90StringSlots
{
public:
	const AsciiString &getStringSlot(int index) const;

private:
	char m_pad00[0x54];
	AsciiString *m_begin;
	AsciiString *m_end;
};

const AsciiString &Rva00387D90StringSlots::getStringSlot(int index) const
{
	if (index >= 0)
	{
		AsciiString *end = m_end;
		AsciiString *begin = m_begin;
		unsigned int count = (unsigned int)(end - begin);
		if ((unsigned int)index < count)
			return begin[index];
	}

	static AsciiString invalidSlot("Invalid Slot");
	return invalidSlot;
}
