// cl: /DNDEBUG /MD /EHsc /Ob0 /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

// Retail reaches the sink notify through the ILT thunk at 0x0004326B, whose
// jump targets 0x000D59F0: Player::onPowerBrownOutChange (row 126467, the
// same callee BfmeConv1998/BfmeConv1999 already spell).  Spelled with its
// defining class and signature so the call links; no field of Player is read
// here, so the view class below stays unrelated to it.
#include "PreRTS.h"
#include "Common/Player.h"

class BfmeHostZT
{
public:
	void bfmeAdvanceZT(int delta);

	int m_bfmeHeadZT;
	int m_bfmeLimitZT;
	int m_bfmeValueZT;
	Player *m_bfmeSinkZT;
};

void BfmeHostZT::bfmeAdvanceZT(int delta)
{
	m_bfmeValueZT = m_bfmeValueZT + delta;

	if (m_bfmeSinkZT != 0)
		m_bfmeSinkZT->onPowerBrownOutChange(m_bfmeLimitZT < m_bfmeValueZT);
}
