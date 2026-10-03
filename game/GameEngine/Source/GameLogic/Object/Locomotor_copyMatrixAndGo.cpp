// cl: /DNDEBUG /MD
//
// Retail 0x001B9C50: copy twelve dwords from arg+8 into this+0x64 then two
// follow-up calls.

// The ILT at 0x00024EA6 (the call this body makes first) is a thunk to
// 0x001B5860, which the ledger owns as Locomotor::getMaxTurnRate
// (game/GameEngine/Source/GameLogic/Object/LocomotorGetMaxTurnRateObject.cpp,
// 133 B, matched): that TU's header comment names 0x001B9C50 -- this body --
// as the rotate-toward caller that hands it its Object pointer.
#include "object.h"

class Locomotor
{
public:
	float getMaxTurnRate(Object *object) const;
};

struct Mat12
{
	char m_pad[8];
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
};

class BfmeSub1CC_EC3
{
public:
	void finish(Mat12 *m, int a, int t, int b);
	void copyMatrixAndGo(Mat12 *m, int a, int b);

private:
	char m_pad[0x64];
	int m_64;
	int m_68;
	int m_6C;
	int m_70;
	int m_74;
	int m_78;
	int m_7C;
	int m_80;
	int m_84;
	int m_88;
	int m_8C;
	int m_90;
};

void BfmeSub1CC_EC3::copyMatrixAndGo(Mat12 *m, int a, int b)
{
	m_64 = m->m_08;
	m_68 = m->m_0C;
	m_6C = m->m_10;
	m_70 = m->m_14;
	m_74 = m->m_18;
	m_78 = m->m_1C;
	m_7C = m->m_20;
	m_80 = m->m_24;
	m_84 = m->m_28;
	m_88 = m->m_2C;
	m_8C = m->m_30;
	m_90 = m->m_34;
	float t = ((Locomotor *)this)->getMaxTurnRate((Object *)m);
	finish(m, a, *(int *)&t, b);
}
