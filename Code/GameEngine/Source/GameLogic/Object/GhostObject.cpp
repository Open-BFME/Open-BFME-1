// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GhostObject.h
class GhostObjectManager
{
	virtual void virtualAnchor( void ) = 0;
	unsigned int m_value;
	unsigned char m_active;
	unsigned char m_reserved;

public:
	GhostObjectManager( void );
};

GhostObjectManager::GhostObjectManager( void )
{
	m_active = 0;
	m_reserved = 0;
	m_value = 0;
}
