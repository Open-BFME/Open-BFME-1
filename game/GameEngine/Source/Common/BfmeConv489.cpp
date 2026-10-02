// The conditional call target (0x008FC4C0) is setFPMode, the free function
// GameLogic.cpp defines; the previous placeholder spelled it as an invented
// member of BfmeThingBMB, which nothing defines.  Same cdecl void() shape, so
// the call and the register save around it are unchanged.

extern void setFPMode();

class BfmeThingBMB
{
public:
	void bfmeGoBMB();
	unsigned char m_bfmeHead[0x1a0];
	int m_bfmeCount;
};

void BfmeThingBMB::bfmeGoBMB()
{
	if (m_bfmeCount == 0)
		setFPMode();
	++m_bfmeCount;
}