// cl: /O2 /Ob0 /G6

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

extern "C" void __identifier("??0?$StringBase@D@@AAE@ABV0@@Z")();

struct BfmeTailF5
{
};

struct BfmeElemF5
{
	int m_00;
	int m_04;
	int m_08;
	BfmeTailF5 m_0C;
};

BfmeElemF5 *bfmeFillF5(BfmeElemF5 *dest, unsigned n, const BfmeElemF5 *src)
{
	unsigned k = n;
	BfmeElemF5 *d = dest;
	if (k > 0)
	{
		unsigned m = k;
		do
		{
			if (d)
			{
				d->m_00 = src->m_00;
				d->m_04 = src->m_04;
				d->m_08 = src->m_08;
				union
				{
					void (*raw)();
					void (StringBase<char>::*member)(const StringBase<char> &);
				} copy;
				copy.raw = __identifier("??0?$StringBase@D@@AAE@ABV0@@Z");
				(((StringBase<char> *)&d->m_0C)->*copy.member)(*(const StringBase<char> *)&src->m_0C);
			}
			++d;
		} while (--m);
	}
	return d;
}
