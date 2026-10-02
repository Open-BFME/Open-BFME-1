class DockUpdateInterface;
#define OBJECT_TU_MEMBERS DockUpdateInterface *getDockUpdateInterface();
#include "../GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

class StateMachine
{
public:
	Object *getGoalObject();
};

enum StateReturnType {};

class AIInternalMoveToState
{
public:
	virtual StateReturnType update();
};

class BfmeTwoCKE
{
public:
	virtual void bfmeSpareCKE0();
	virtual void bfmeSpareCKE1();
	virtual void bfmeSpareCKE2();
	virtual void bfmeSpareCKE3();
	virtual void bfmeSpareCKE4();
	virtual void bfmeRunCKE(void *value, void *buf);
};

class BfmeSubCKE
{
public:
	unsigned char m_bfmeHead[0x10];
	void *m_bfmeVal;
};

class BfmeThingCKE
{
public:
	int bfmeGoCKE();
	unsigned char m_bfmeHead[0x1c];
	BfmeSubCKE *m_bfmeSub;
	unsigned char m_bfmeGap[4];
	unsigned char m_bfmeBuf[4];
};

int BfmeThingCKE::bfmeGoCKE()
{
	Object *one = ((StateMachine *)m_bfmeSub)->getGoalObject();
	if (one == 0)
		return -2;
	BfmeTwoCKE *two = (BfmeTwoCKE *)one->getDockUpdateInterface();
	if (two == 0)
		return -2;
	two->bfmeRunCKE(m_bfmeSub->m_bfmeVal, m_bfmeBuf);
	return ((AIInternalMoveToState *)this)->AIInternalMoveToState::update();
}
