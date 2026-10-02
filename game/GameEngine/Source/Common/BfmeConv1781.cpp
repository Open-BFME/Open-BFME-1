// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "PreRTS.h"
#include "Common/StateMachine.h"

class BfmeItemHM;

class BfmeSourceHM
{
public:
	virtual void bfmeV0HM(void);
	virtual void bfmeV1HM(void);
	virtual void bfmeV2HM(void);
	virtual void bfmeV3HM(void);
	virtual void bfmeV4HM(void);
	virtual void bfmeV5HM(void);
	virtual void bfmeV6HM(void);
	virtual void bfmeV7HM(void);
	virtual void bfmeV8HM(void);
	virtual void bfmeV9HM(void);
	virtual void bfmeV10HM(void);
	virtual void bfmeV11HM(void);
	virtual void bfmeV12HM(void);
	virtual void bfmeSendHM(BfmeItemHM *item, int flag);
	virtual void bfmeV14HM(void);
	virtual void bfmeV15HM(void);
	virtual void bfmeV16HM(void);
	virtual void bfmeV17HM(void);
	virtual void bfmeV18HM(void);
	virtual void bfmeV19HM(void);
	virtual void bfmeV20HM(void);
	virtual void bfmeV21HM(void);
	virtual void bfmeV22HM(void);
	virtual void bfmeV23HM(void);
	virtual void bfmeV24HM(void);
	virtual void bfmeV25HM(void);
	virtual void *bfmePickHM(void);
};

class BfmeItemHM
{
public:
	unsigned char m_bfmeHeadHM[0x1fc];
	BfmeSourceHM *m_bfmeSourceHM;
};

class BfmeHolderHM
{
public:
	unsigned char m_bfmeHeadHM[0x10];
	BfmeItemHM *m_bfmeFirstHM;
};

class BfmeOwnerHM
{
public:
	int bfmeCheckHM(void);

	unsigned char m_bfmeHeadHM[0x1c];
	BfmeHolderHM *m_bfmeHolderHM;
};

int BfmeOwnerHM::bfmeCheckHM(void)
{
	BfmeItemHM *first = m_bfmeHolderHM->m_bfmeFirstHM;
	BfmeItemHM *second = (BfmeItemHM *)((StateMachine *)m_bfmeHolderHM)->getGoalObject();

	if (!first || !second)
		return -2;

	BfmeSourceHM *source = first->m_bfmeSourceHM;

	if (!source)
		return -2;

	if (!source->bfmePickHM())
		return -2;

	BfmeSourceHM *other = second->m_bfmeSourceHM;

	if (other)
		other->bfmeSendHM(first, 1);

	return 0;
}
