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

// Retail 0x0017BA40+0x2B calls 0x00029311, the matched
// onExit@AIInternalMoveToState@@UAEXW4StateExitType@@@Z (a direct base call).
enum StateExitType { EXIT_NORMAL };

class AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

class BfmeThingCLC
{
public:
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
	((AIInternalMoveToState *)this)->AIInternalMoveToState::onExit((StateExitType)(int)what);
}