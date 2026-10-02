// cl: /DNDEBUG /MD /EHsc /Ob0 /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "PreRTS.h"
#include "Common/Player.h"

class BfmeSubEVI;

class BfmeThingEVI
{
public:
	int m_bfmeHeadAEVI;
	BfmeSubEVI *m_bfmeSubEVI;
	unsigned char m_bfmePadEVI[0x414];
	int m_bfmeDeltaEVI;
};

class BfmeArgEVI
{
public:
	int m_bfmeHeadEVI;
	BfmeThingEVI *m_bfmeThingEVI;
};

class BfmeSinkEVI
{
public:
	void bfmeNotifyEVI(bool flag);
};

// retail resolves the sub-object's final override through the ILT thunk at
// 0x000022BB, which targets Overridable::getFinalOverride (matching row
// 0x00087A80).  Spelled with its defining class and signature so the call
// links; the view classes below stay unrelated to it, the pointer crosses as
// void so no code is emitted.
class BfmeHostEVI
{
public:
	void bfmeAdvanceEVI(BfmeArgEVI *arg);

	int m_bfmeHeadEVI;
	int m_bfmeValueEVI;
	int m_bfmeLimitEVI;
	BfmeSinkEVI *m_bfmeSinkEVI;
};

void BfmeHostEVI::bfmeAdvanceEVI(BfmeArgEVI *arg)
{
	if (arg == 0)
		return;

	BfmeThingEVI *thing = arg->m_bfmeThingEVI;

	if (thing != 0 && thing->m_bfmeSubEVI != 0)
		thing = (BfmeThingEVI *)(const void *)((const Overridable *)thing->m_bfmeSubEVI)->getFinalOverride();

	m_bfmeValueEVI = m_bfmeValueEVI - thing->m_bfmeDeltaEVI;

	if (m_bfmeSinkEVI != 0)
		((Player *)m_bfmeSinkEVI)->onPowerBrownOutChange(m_bfmeValueEVI < m_bfmeLimitEVI);
}
