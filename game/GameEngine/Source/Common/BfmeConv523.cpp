class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
enum UpdateSleepTime;

class BfmeThingBSC;

// Declaration only: retail calls ILT 0x000157DA -> 0x002B2040, UpdateModule.cpp's
// matched protected setWakeFrame; friendship satisfies the access check.
class UpdateModule
{
	friend class BfmeThingBSC;

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
};

class BfmeThingBSC
{
public:
	void bfmeGoBSC();
	unsigned char m_bfmeHead[8];
	void *m_bfmeWhat;
	unsigned char m_bfmeGap[0x18];
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
	int m_bfmeD;
	int m_bfmeE;
	int m_bfmeF;
};

void BfmeThingBSC::bfmeGoBSC()
{
	m_bfmeA = 0;
	m_bfmeC = 0;
	m_bfmeD = 0;
	m_bfmeB = 0;
	m_bfmeE = 0;
	m_bfmeF = 0;
	reinterpret_cast<UpdateModule *>(this)->setWakeFrame(
		static_cast<Object *>(m_bfmeWhat), static_cast<UpdateSleepTime>(1));
}
