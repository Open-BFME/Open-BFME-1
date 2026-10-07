class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
enum UpdateSleepTime;

class BfmeThingCOA;

// Declaration only: retail calls ILT 0x000157DA -> 0x002B2040, UpdateModule.cpp's
// matched protected setWakeFrame; friendship satisfies the access check.
class UpdateModule
{
	friend class BfmeThingCOA;

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
};

class BfmeSubCOA
{
public:
	virtual void bfmeSpareCOA0();
	virtual void bfmeSpareCOA1();
	virtual void bfmeSpareCOA2();
	virtual void bfmeSpareCOA3();
	virtual void bfmeSpareCOA4();
	virtual void bfmeSpareCOA5();
	virtual void bfmeSpareCOA6();
	virtual void bfmeSpareCOA7();
	virtual void bfmeV8COA(int flag);
	virtual void bfmeV9COA();
	virtual void bfmeSpareCOA10();
	virtual void bfmeV11COA();
	virtual void bfmeSpareCOA12();
	virtual void bfmeV13COA();
};

class BfmeThingCOA
{
public:
	void bfmeGoCOA();
	unsigned char m_bfmeHead[8];
	void *m_bfmeVal;
	unsigned char m_bfmeGap[0x14];
	BfmeSubCOA m_bfmeSub;
	unsigned char m_bfmeGap2[0xc];
	bool m_bfmeFlag;
};

void BfmeThingCOA::bfmeGoCOA()
{
	BfmeSubCOA *sub = &m_bfmeSub;
	m_bfmeFlag = false;
	sub->bfmeV11COA();
	sub->bfmeV13COA();
	sub->bfmeV9COA();
	sub->bfmeV8COA(1);
	reinterpret_cast<UpdateModule *>(this)->setWakeFrame(
		static_cast<Object *>(m_bfmeVal), static_cast<UpdateSleepTime>(1));
}
