// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/gamewindowlist /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// Open-BFME: GameWindowTransitionsHandler destructor at retail 0x0048B410.
// The named GameWindowManager::init/delete path, constructor vptr 0x010F9610,
// and the four handler fields establish the owner.  These declarations keep
// the BFME map/list layout local to this destructor TU.  Retail's call below
// is KERNEL32.dll!DeleteCriticalSection at IAT VA 0x01358D0C; bfmeInitDXB is
// retained only as the ABI alias that already reproduces that import.

// stlport
#define _STLP_USE_STATIC_LIB 1
#include <list>

typedef int Int;

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface( void );
	virtual void init( void ) = 0;
	virtual void postProcessLoad( void ) { }
	virtual void reset( void ) = 0;
	virtual void update( void ) = 0;
	virtual void draw( void ) { }

	char m_name[4];
};

class TransitionGroup
{
public:
	void reset( void );
	~TransitionGroup( void );
};

// The retail transition map's first member starts at this+0x08 and occupies
// 0x14 bytes.  Its destructor is the existing ICF body reached by ILT 0x99C6.
class Rva0048B1A0TransitionMap
{
public:
	~Rva0048B1A0TransitionMap( void );

private:
	unsigned char m_storage[0x14];
};

extern "C" __declspec(dllimport) void __stdcall bfmeInitDXB( void *criticalSection );

class GameWindowTransitionsHandler : public SubsystemInterface
{
public:
	virtual ~GameWindowTransitionsHandler( void );

private:
	typedef std::list<TransitionGroup *> TransitionGroupList;

	Rva0048B1A0TransitionMap m_transitionMap;
	TransitionGroupList m_transitionGroupList;
	TransitionGroup *m_currentGroup;
	TransitionGroup *m_pendingGroup;
	TransitionGroup *m_drawGroup;
	TransitionGroup *m_secondaryDrawGroup;
	Int m_unknown30;
	Int m_unknown34[6];
	bool m_unknown4C;
	bool m_unknown4D;
	Int m_unknown50;
	bool m_unknown54;
	bool m_unknown55;
};

// ??1GameWindowTransitionsHandler@@UAE@XZ
GameWindowTransitionsHandler::~GameWindowTransitionsHandler( void )
{
	if (m_currentGroup)
	{
		m_currentGroup->reset();
		m_currentGroup = NULL;
	}
	if (m_pendingGroup)
	{
		m_pendingGroup->reset();
		m_pendingGroup = NULL;
	}
	if (m_drawGroup)
	{
		m_drawGroup->reset();
		m_drawGroup = NULL;
	}
	if (m_secondaryDrawGroup)
	{
		m_secondaryDrawGroup->reset();
		m_secondaryDrawGroup = NULL;
	}

	if (m_unknown4C)
	{
		bfmeInitDXB( &m_unknown34[0] );
		m_unknown4C = 0;
	}

	TransitionGroupList::iterator it = m_transitionGroupList.begin();
	while (it != m_transitionGroupList.end())
	{
		TransitionGroup *g = *it;
		delete g;
		it = m_transitionGroupList.erase(it);
	}
}
