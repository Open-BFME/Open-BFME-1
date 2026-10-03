// cl: /DNDEBUG /MD /EHsc /Ob0 /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

// Address-derived name: real identity not recovered.
//
// Retail reaches the notify callee through the ILT thunk at 0x0004326B, whose
// jump targets 0x000D59F0: Player::onPowerBrownOutChange (row 126467).  The
// sink pointer is therefore a Player*, spelled with its defining class and
// signature so the call links; no field of Player is read here, so the view
// class below stays unrelated to it.
#include "PreRTS.h"
#include "Common/Player.h"

class Rva000C7E30Owner
{
public:
	void accumulate(int amount);

	int m_head;
	int m_total;
	int m_limit;
	Player *m_sink;
};

void Rva000C7E30Owner::accumulate(int amount)
{
	m_total = m_total + amount;

	if (m_sink != 0)
		m_sink->onPowerBrownOutChange(m_total < m_limit);
}
