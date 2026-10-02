// StatusBitsUpgrade, UpgradeMux table 0x010CDC00 (stored at +0x10 by the registered constructor
// 0x002D7DD0):
//   slot 9 -> 0x002D7F00 StatusBitsUpgrade::upgradeImplementation (ILT 0x000034D6, sole image ref)
//   slot 7 -> 0x002D7F40 StatusBitsUpgrade::rva002D7F40 (ILT 0x0003BFF2, sole image ref); slot 7 is a
//            BFME-only virtual that undoes slot 9; its name is unproven.
// Slot 9 is the upgradeImplementation call in UpgradeMux::attemptUpgrade
// (0x002D9AD0). Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md
// Open-BFME5 conversions.

template <int NUMBITS>
class BitFlags;

#define OBJECT_TU_MEMBERS void setStatus(const BitFlags<86> &objectStatus, bool set);
#include "../object.h"
#undef OBJECT_TU_MEMBERS

class BfmeSetterSLA;

class StatusBitsUpgrade
{
protected:
	virtual void upgradeImplementation();
	virtual void rva002D7F40();
};

void StatusBitsUpgrade::upgradeImplementation()
{
	BfmeSetterSLA *s = *(BfmeSetterSLA **)((char *)this - 8);
	((Object *)s)->setStatus(
		*(BitFlags<86> *)(*(char **)((char *)this - 0xc) + 0x70), true);
	((Object *)s)->setStatus(
		*(BitFlags<86> *)(*(char **)((char *)this - 0xc) + 0x7c), false);
}

void StatusBitsUpgrade::rva002D7F40()
{
	BfmeSetterSLA *s = *(BfmeSetterSLA **)((char *)this - 8);
	((Object *)s)->setStatus(
		*(BitFlags<86> *)(*(char **)((char *)this - 0xc) + 0x70), false);
	((Object *)s)->setStatus(
		*(BitFlags<86> *)(*(char **)((char *)this - 0xc) + 0x7c), true);
}
