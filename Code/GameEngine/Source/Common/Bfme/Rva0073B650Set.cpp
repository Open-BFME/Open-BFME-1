// 66-byte filterMode setter with W3DShaderManager::filterSetup call

enum FilterTypes {};
enum FilterModes {};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShaderManager.h
class W3DShaderManager
{
public:
	static bool filterSetup( FilterModes mode, FilterTypes filter );
};

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
		if ( !W3DShaderManager::filterSetup( mode, m_filterType ) )
		{
			m_filterMode = oldMode;
			return false;
		}
	}
	return true;
}
