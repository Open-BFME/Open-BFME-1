// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#define _STLP_USE_STATIC_LIB 1
#include <list>

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void loadPostProcess() = 0;
	virtual const char *getSnapshotName() = 0;
	virtual void xfer(Xfer *xfer) = 0;
};

struct SnapshotBlock
{
	void *snapshot;
	int blockName;
};

class GameState
{
	typedef _STL::list<Snapshot *> SnapshotList;
	typedef SnapshotList::iterator SnapshotListIterator;
	typedef _STL::list<SnapshotBlock> SnapshotBlockList;

	private:
	void gameStatePostProcessLoad();

private:
	char m_pad[0x48];
	SnapshotList m_snapshotPostProcessList;
	SnapshotBlockList m_snapshotBlockList;
};

class GameLogicFp
{
public:
	char m_pad[0x1A0];
	int m_fp;
};

extern GameLogicFp *TheBfmeGameLogic;
extern void setFPMode();

void GameState::gameStatePostProcessLoad( void )
{
	GameState *state = this;
	GameLogicFp *logic = TheBfmeGameLogic;
	int *fp = &logic->m_fp;
	if( *fp == 0 )
		setFPMode();
	++*fp;

	SnapshotListIterator it;
	Snapshot *snapshot;
	for( it = state->m_snapshotPostProcessList.begin(); it != state->m_snapshotPostProcessList.end(); /* empty */ )
	{
		snapshot = *it;
		++it;
		snapshot->loadPostProcess();
	}

	state->m_snapshotPostProcessList.clear();
	state->m_snapshotBlockList.clear();
	--TheBfmeGameLogic->m_fp;
}
