// cl: /O2 /Ob0 /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/namekeygenerator /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
#include "PreRTS.h"
#include "Common/NameKeyGenerator.h"

class BfmeThingBLC
{
public:
	void bfmeGoBLC(void *what);
	void *m_bfmeGot;
};

void BfmeThingBLC::bfmeGoBLC(void *what)
{
	// The key is stored through a void* hand-off; the retail body returns the
	// NameKeyType in eax and this file only forwards it, so the cast is free.
	m_bfmeGot = (void *)TheNameKeyGenerator->nameToKey((const char *)what);
}
