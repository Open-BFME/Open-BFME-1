// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#include "PreRTS.h"
#include "Common/Errors.h"
#include "Rva000A1310StateLookup.h"

// Native scalar key, State* result, and ErrorCode enum throw; the old
// iterator-by-value / returning-diagnostic declarations were false contracts.
State *Rva000A1310StateMachine::lookup(unsigned int stateID)
{
	std::map<unsigned int, State *>::iterator i = m_stateMap.find(stateID);
	if (i == m_stateMap.end())
		throw ERROR_BAD_ARG;
	return i->second;
}
