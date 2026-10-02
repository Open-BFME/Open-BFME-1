// cl: /O2 /Ob0 /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// 66-byte filterMode setter with W3DShaderManager::filterSetup call

#include "Lib/BaseType.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShaderManager.h

class Rva0073B650
{
public:
	bool setMode( FilterModes mode );

	char        m_pad00[ 0x10C ];
	FilterTypes m_filterType;
	FilterModes m_filterMode;
};

bool Rva0073B650::setMode( FilterModes mode )
{
	FilterModes oldMode = m_filterMode;
	m_filterMode = mode;
	if ( m_filterType && mode )
	{
		if ( !W3DShaderManager::filterSetup(
			static_cast<FilterTypes>(mode), static_cast<FilterModes>(m_filterType) ) )
		{
			m_filterMode = oldMode;
			return false;
		}
	}
	return true;
}
