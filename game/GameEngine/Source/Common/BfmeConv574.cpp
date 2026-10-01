// The receiver of bfmeNotifyCCC is an Object: the cleared word is
// Object::m_modelConditionFlags[1] at +0x114, and the call is the ILT
// 0x0002191D thunk to Object::notifyModelConditionChanged.

#define OBJECT_TU_MEMBERS void notifyModelConditionChanged();
#include "../GameLogic/Object/object.h"

struct BfmeOwnerCCC
{
	unsigned char m_bfmeHead[0x10];
	Object *m_bfmeMid;
};

class BfmeThingCCC
{
public:
	void bfmeGoCCC(void *spare);
	unsigned char m_bfmeHead[0x1c];
	BfmeOwnerCCC *m_bfmeOwner;
};

void BfmeThingCCC::bfmeGoCCC(void *spare)
{
	Object *sub = m_bfmeOwner->m_bfmeMid;
	if (sub->m_modelConditionFlags[1] & 0x20000000u)
	{
		sub->m_modelConditionFlags[1] &= ~0x20000000u;
		sub->notifyModelConditionChanged();
	}
}