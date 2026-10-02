// Open-BFME5 conversions.

template <int NUMBITS>
class BitFlags;

#define OBJECT_TU_MEMBERS void setStatus(const BitFlags<86> &objectStatus, bool set);
#include "../GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

class BfmeSetterSLA;

class BfmeThingSLA
{
public:
	void bfmeOneSLA();
	void bfmeTwoSLA();
};

void BfmeThingSLA::bfmeOneSLA()
{
	BfmeSetterSLA *s = *(BfmeSetterSLA **)((char *)this - 8);
	((Object *)s)->setStatus(
		*(BitFlags<86> *)(*(char **)((char *)this - 0xc) + 0x70), true);
	((Object *)s)->setStatus(
		*(BitFlags<86> *)(*(char **)((char *)this - 0xc) + 0x7c), false);
}

void BfmeThingSLA::bfmeTwoSLA()
{
	BfmeSetterSLA *s = *(BfmeSetterSLA **)((char *)this - 8);
	((Object *)s)->setStatus(
		*(BitFlags<86> *)(*(char **)((char *)this - 0xc) + 0x70), false);
	((Object *)s)->setStatus(
		*(BitFlags<86> *)(*(char **)((char *)this - 0xc) + 0x7c), true);
}
