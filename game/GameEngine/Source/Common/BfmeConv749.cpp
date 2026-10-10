#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

extern "C" void __identifier("??0?$StringBase@D@@AAE@ABV0@@Z")();

class BfmeOtherDPB
{
public:
	unsigned char m_bfmeHead[4];
	char m_bfmeVal;
};

BfmeOtherDPB *bfmeGoDPB(BfmeOtherDPB *other, void *value, char *src)
{
	volatile int tmp = 0;
	union
	{
		void (*raw)();
		void (StringBase<char>::*member)(const StringBase<char> &);
	} copy;
	copy.raw = __identifier("??0?$StringBase@D@@AAE@ABV0@@Z");
	(((StringBase<char> *)other)->*copy.member)(*(const StringBase<char> *)value);
	other->m_bfmeVal = *src;
	return other;
}
