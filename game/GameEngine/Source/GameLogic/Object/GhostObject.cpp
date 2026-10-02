// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GhostObject.h
class GhostObjectManager
{
	virtual void virtualAnchor( void ) = 0;
	unsigned int m_localPlayer;
	unsigned char m_active;
	unsigned char m_saveLockGhostObjects;

public:
	GhostObjectManager( void );
};

GhostObjectManager::GhostObjectManager( void )
{
	m_active = 0;
	m_saveLockGhostObjects = 0;
	m_localPlayer = 0;
}

// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
// The ghost manager singleton.  Zero Hour GameLogic/Object/GhostObject.cpp:37
// defines `GhostObjectManager *TheGhostObjectManager = NULL;` next to this
// class; retail holds four loader-zero bytes at VA 0x012EF4FC, and the matched
// GameLogic::init body (RVA 0x0038A1F0) stores the createGhostObjectManager()
// result through that exact address at RVA 0x0038A3FD.
GhostObjectManager *TheGhostObjectManager = 0;
