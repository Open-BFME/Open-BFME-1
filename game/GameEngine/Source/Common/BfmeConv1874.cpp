#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// ILT 000480F4 targets the const three-argument wide comparator at 0009ECA0.
extern "C" void __identifier("?compareNoCaseRaw@?$StringBase@G@@ABEHPBG0H@Z")();

struct BfmeSmallZG
{
	int m_bfmeSlotZG;
};

int __cdecl bfmeClampZG(void *first, int value, void *third, int limit, BfmeSmallZG obj)
{
	int n = value < limit ? value : limit;
	union
	{
		void (*raw)();
		int (StringBase<unsigned short>::*member)(const unsigned short *, const unsigned short *, int) const;
	} compare;
	compare.raw = __identifier("?compareNoCaseRaw@?$StringBase@G@@ABEHPBG0H@Z");
	int r = (((const StringBase<unsigned short> *)&obj)->*compare.member)(
		(const unsigned short *)first, (const unsigned short *)third, n);

	if (r != 0)
		return r;

	return value - limit;
}
