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

class BfmeTwoCKF
{
public:
	virtual void bfmeSpareCKF0();
	virtual void bfmeSpareCKF1();
	virtual void bfmeSpareCKF2();
	virtual void bfmeSpareCKF3();
	virtual void bfmeSpareCKF4();
	virtual void bfmeSpareCKF5();
	virtual void bfmeSpareCKF6();
	virtual void bfmeRunCKF(void *value, void *buf);
};

class BfmeSubCKF
{
public:
	unsigned char m_bfmeHead[0x10];
	void *m_bfmeVal;
};

class BfmeThingCKF
{
public:
	int bfmeGoCKF();
	unsigned char m_bfmeHead[0x1c];
	BfmeSubCKF *m_bfmeSub;
	unsigned char m_bfmeGap[4];
	unsigned char m_bfmeBuf[4];
};

int BfmeThingCKF::bfmeGoCKF()
{
	Object *one = ((StateMachine *)m_bfmeSub)->getGoalObject();
	if (one == 0)
		return -2;
	BfmeTwoCKF *two = (BfmeTwoCKF *)one->getDockUpdateInterface();
	if (two == 0)
		return -2;
	two->bfmeRunCKF(m_bfmeSub->m_bfmeVal, m_bfmeBuf);
	return ((AIInternalMoveToState *)this)->AIInternalMoveToState::update();
}
