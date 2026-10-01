// The receiver of bfmeNotifyCLC is an Object: the cleared word is
// Object::m_modelConditionFlags[2] at +0x118, and the call is the ILT
// 0x0002191D thunk to Object::notifyModelConditionChanged.

#define OBJECT_TU_MEMBERS void notifyModelConditionChanged();
#include "../GameLogic/Object/object.h"

struct BfmeOwnerCLC
{
	unsigned char m_bfmeHead[0x10];
	Object *m_bfmeMid;
};

class BfmeThingCLC
{
public:
	void bfmeThenCLC(void *what);
	void bfmeGoCLC(void *what);
	unsigned char m_bfmeHead[0x1c];
	BfmeOwnerCLC *m_bfmeOwner;
};

void BfmeThingCLC::bfmeGoCLC(void *what)
{
	Object *mid = m_bfmeOwner->m_bfmeMid;
	if (mid->m_modelConditionFlags[2] & 0x1000)
	{
		mid->m_modelConditionFlags[2] &= ~0x1000u;
		mid->notifyModelConditionChanged();
	}
	bfmeThenCLC(what);
}