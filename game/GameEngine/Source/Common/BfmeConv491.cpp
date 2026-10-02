// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/asciistring8 /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "PreRTS.h"
#include "Common/Upgrade.h"

class BfmeThingBMD
{
public:
	void bfmeGoBMD();
	unsigned char m_bfmeHead[4];
	void *m_bfmeWhat;
	unsigned char m_bfmeGap[0x24];
	const UpgradeTemplate *m_bfmeGot;
};

void BfmeThingBMD::bfmeGoBMD()
{
	m_bfmeGot = TheUpgradeCenter->findUpgrade(
		*reinterpret_cast<const AsciiString *>((char *)m_bfmeWhat + 0x18));
}
