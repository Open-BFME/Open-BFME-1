// cl: /O2 /Ob0
// The hand-off at 0x0013E470 calls StringBase<wchar_t>::set (0x00888530, the
// ?$StringBase@G row) with the taken string in ECX and this string as the
// argument, so the local view casts onto the real StringBase instead of
// assigning.
#include <stdlib.h>
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class Rva00630D00UStr
{
public:
	struct Data
	{
		short a;
		short b;
		unsigned short first;
	};

	Data *m_item;
};

class Rva0013E470
{
	char m_pad[0x14];
	Rva00630D00UStr m_14;

public:
	bool take(Rva00630D00UStr &dest);
};

bool Rva0013E470::take(Rva00630D00UStr &dest)
{
	if (m_14.m_item && m_14.m_item->first)
	{
		reinterpret_cast<StringBase<wchar_t> *>(&dest)->set(
			*reinterpret_cast<const StringBase<wchar_t> *>(&m_14));
		return true;
	}
	return false;
}
