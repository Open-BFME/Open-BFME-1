// The receiver of bfmeNotifyCIE is an Object: the cleared word is
// Object::m_modelConditionFlags[7] at +0x12C, and the call is the ILT
// 0x0002191D thunk to Object::notifyModelConditionChanged.

#define OBJECT_TU_MEMBERS void notifyModelConditionChanged();
#include "../GameLogic/Object/object.h"

class BfmeThingCIE
{
public:
	void bfmeGoCIE(void *one, void *two);
	unsigned char m_bfmeHead[8];
	Object *m_bfmeSub;
	unsigned char m_bfmeGap[0xdc];
	bool m_bfmeFlag;
};

void BfmeThingCIE::bfmeGoCIE(void *one, void *two)
{
	Object *sub = m_bfmeSub;
	if (sub->m_modelConditionFlags[7] & 0x200)
	{
		sub->m_modelConditionFlags[7] &= ~0x200u;
		sub->notifyModelConditionChanged();
	}
	m_bfmeFlag = false;
}