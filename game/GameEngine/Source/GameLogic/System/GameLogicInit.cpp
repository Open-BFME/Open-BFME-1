// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// GameLogic::init, retail 0x0038A1F0 (1017 B, ret at 0x0038A5E8).
// Identity: slot 1 (+0x04) of both GameLogic vtables (0x010EB574 and the
// concrete 0x0111CA5C) reaches this body through ILT 0x00030D3C, and the body
// is Zero Hour's GameLogic::init with BFME's subsystem set.  The setName
// literals name every global it creates: ThePartitionManager,
// TheShroudManager, TheCollisionManager, TheTerrainLogic,
// TheLargeGroupAudio and TheBuffLogic.  The trailing loop is the inlined
// GameLogic::resetPlayerLeaveStatus (matched out of line at its own RVA),
// reached through TheGameLogic rather than this.

#include <list>
#include "ascii_string.h"

typedef float Real;
typedef bool Bool;
typedef int Int;

struct Coord3D
{
	Real x, y, z;
	void zero(void) { x = 0.0f; y = 0.0f; z = 0.0f; }
};

struct Region3D
{
	Coord3D lo, hi;
	void zero(void) { lo.zero(); hi.zero(); }
};

extern void __cdecl setFPMode(void);                                     // 0x008FC4C0

// Zero Hour SubsystemInterface: slot 1 is init, the name follows the vptr.
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface(void);
	virtual void init(void) = 0;

public:
	AsciiString m_name;
};

// Retail inlines this store at every call site except GameLogic::init's
// TheLargeGroupAudio, which reaches the out-of-line body (owned by
// SubsystemInterfaceName.cpp) through ILT 0x0001CE9A. A TU-local forced-inline
// helper keeps this file from emitting its own ?setName@SubsystemInterface COMDAT.
template <class T>
static __forceinline void bfmeSetSubsystemName(T *subsystem, AsciiString name)
{
	subsystem->m_name = name;
}

class PartitionManager : public SubsystemInterface
{
public:
	void rva009F2650(Int value);                                          // 0x009F2650

protected:
	int m_impl[2];
};

// The concrete ThePartitionManager object is known only by its constructor.
class Rva009F2730Owner : public PartitionManager
{
public:
	Rva009F2730Owner(void);                                               // 0x009F2730
	virtual void init(void);
};

class ShroudManager : public SubsystemInterface
{
public:
	void rva008F7390(const Region3D *extent, Real cellSize);              // 0x008F7390
	void rva008F7370(Int duration);                                       // 0x008F7370

protected:
	int m_impl[2];
};

class Rva008F7510ShroudManager : public ShroudManager
{
public:
	Rva008F7510ShroudManager(void);                                       // 0x008F7510
	virtual void init(void);
};

class CollisionManager : public SubsystemInterface
{
public:
	CollisionManager(void);                                               // 0x009A25B0
	virtual void init(void);
	void rva009A2570(void);                                               // 0x009A2570

protected:
	int m_impl[2];
};

class BfmeTaintManager
{
public:
	void rva00880E20(const Region3D *extent, Real cellSize);              // 0x00880E20
};

class Snapshot
{
public:
	virtual void crc(void *xfer) = 0;
};

class TerrainLogic : public Snapshot, public SubsystemInterface
{
};

// The object vtable slot 11 returns; the literal names its global TheBuffLogic.
class Manager012EF4F0 : public Snapshot, public SubsystemInterface
{
};

class GhostObjectManager;

extern void j_0001ce9a(void);

class LargeGroupAudio : public SubsystemInterface
{
public:
	LargeGroupAudio(void);                                                // 0x003CEF00
	virtual void init(void);

private:
	int m_body[12];
};

class BfmeTableERJ
{
public:
	void rva0019B030(void);                                               // 0x0019B030
	void rva0019F500(void);                                               // 0x0019F500
};

class GlobalData
{
public:
	char m_pad000[0x1bc];
	Real m_partitionCellSize;                                             // +0x1BC
	char m_pad1C0[0xc6c - 0x1c0];
	Int m_unlookPersistDuration;                                          // +0xC6C
};

struct PlayerLeaveStatus
{
	int status;                                                           // +0x00
	int quitFrame;                                                        // +0x04
	int defeatFrame;                                                      // +0x08
	int victoryFrame;                                                     // +0x0C
	bool notPresent;                                                      // +0x10
	char padding[3];
	int isHuman;                                                          // +0x14
	char playerName[4];                                                   // +0x18
};

class GameLogic : public SubsystemInterface
{
public:
	virtual void init(void);
	virtual void vslot08(void);
	virtual void vslot0C(void);
	virtual void vslot10(void);
	virtual void vslot14(void);
	virtual void vslot18(void);
	virtual void vslot1C(void);
	virtual void vslot20(void);
	virtual TerrainLogic *createTerrainLogic(void) = 0;                   // +0x24
	virtual GhostObjectManager *createGhostObjectManager(void) = 0;       // +0x28
	virtual Manager012EF4F0 *vslot2C(void) = 0;                           // +0x2C

	void setDefaults(Bool loadingSaveGame);

	void resetPlayerLeaveStatusForInit(void)
	{
		for (int index = 0; index < 8; ++index)
		{
			m_playerLeaveStatus[index].notPresent = true;
			m_playerLeaveStatus[index].quitFrame = 0;
			m_playerLeaveStatus[index].defeatFrame = 0;
			m_playerLeaveStatus[index].victoryFrame = 0;
			m_playerLeaveStatus[index].status = 0;
			m_playerLeaveStatus[index].isHuman = 0xFF;
		}
	}

private:
	char m_pad008[0x44 - 0x08];
	int m_field44;                                                        // +0x44
	char m_pad048[0x4c - 0x48];
	_STL::list<int> m_list4C;                                             // +0x4C
	char m_pad050[0x6b - 0x50];
	Bool m_field6B;                                                       // +0x6B
	char m_pad06C[0x8c - 0x6c];
	int m_field8C;                                                        // +0x8C
	Bool m_isScoringEnabled;                                              // +0x90
	Bool m_showBehindBuildingMarkers;                                     // +0x91
	Bool m_drawIconUI;                                                    // +0x92
	Bool m_showDynamicLOD;                                                // +0x93
	char m_pad094[0x98 - 0x94];
	Int m_scriptHulkMaxLifetimeOverride;                                  // +0x98
	Int m_field9C;                                                        // +0x9C
	char m_pad0A0[0x11c - 0xa0];
	Bool m_gamePaused;                                                    // +0x11C
	Bool m_field11D;                                                      // +0x11D
	Bool m_inputEnabledMemory;                                            // +0x11E
	Bool m_mouseVisibleMemory;                                            // +0x11F
	Bool m_progressComplete[8];                                           // +0x120
	Int m_progressCompleteTimeout[8];                                     // +0x128
	Bool m_forceGameStartByTimeOut;                                       // +0x148
	char m_pad149[0x1b0 - 0x149];
	PlayerLeaveStatus m_playerLeaveStatus[8];                             // +0x1B0
	Int m_field290;                                                       // +0x290
};

extern PartitionManager *ThePartitionManager;                             // 0x012ED5B8
extern ShroudManager *TheShroudManager;                                   // 0x012ED5BC
extern BfmeTaintManager *TheTaintManager;                                 // 0x012ED5C0
extern CollisionManager *TheCollisionManager;                             // 0x012ED5C4
extern GlobalData *TheWritableGlobalData;                                 // 0x012ED5C8
class SidesList;
extern SidesList *TheSidesList;                                      // 0x012EF428
extern TerrainLogic *TheTerrainLogic;                                     // 0x012EF4CC
extern Manager012EF4F0 *g_012EF4F0;                                       // 0x012EF4F0 TheBuffLogic
extern GhostObjectManager *TheGhostObjectManager;                         // 0x012EF4FC
extern GameLogic *TheGameLogic;                                           // 0x012F0898
LargeGroupAudio *TheLargeGroupAudio = 0;                               // 0x012F1044

// ?init@GameLogic@@UAEXXZ
void GameLogic::init(void)
{
	setFPMode();

	setDefaults(false);

	ThePartitionManager = new Rva009F2730Owner;
	ThePartitionManager->init();
	bfmeSetSubsystemName(ThePartitionManager, "ThePartitionManager");

	TheShroudManager = new Rva008F7510ShroudManager;
	TheShroudManager->init();
	bfmeSetSubsystemName(TheShroudManager, "TheShroudManager");

	TheCollisionManager = new CollisionManager;
	TheCollisionManager->init();
	bfmeSetSubsystemName(TheCollisionManager, "TheCollisionManager");
	TheCollisionManager->rva009A2570();

	Region3D extent;
	extent.zero();
	TheShroudManager->rva008F7390(&extent, TheWritableGlobalData->m_partitionCellSize);
	TheShroudManager->rva008F7370(TheWritableGlobalData->m_unlookPersistDuration);
	ThePartitionManager->rva009F2650(7);
	TheTaintManager->rva00880E20(&extent, TheWritableGlobalData->m_partitionCellSize);

	TheGhostObjectManager = createGhostObjectManager();

	TheTerrainLogic = createTerrainLogic();
	TheTerrainLogic->init();
	bfmeSetSubsystemName(TheTerrainLogic, "TheTerrainLogic");

	TheLargeGroupAudio = new LargeGroupAudio;
	if (TheLargeGroupAudio)
	{
		TheLargeGroupAudio->init();
		typedef void (LargeGroupAudio::*SetNameThunk)(AsciiString);
		union
		{
			void (*function)(void);
			SetNameThunk member;
		} setNameThunk;
		setNameThunk.function = j_0001ce9a;
		(TheLargeGroupAudio->*setNameThunk.member)("TheLargeGroupAudio");
	}

	g_012EF4F0 = vslot2C();
	g_012EF4F0->init();
	bfmeSetSubsystemName(g_012EF4F0, "TheBuffLogic");

	((BfmeTableERJ *)TheSidesList)->rva0019B030();
	((BfmeTableERJ *)TheSidesList)->rva0019F500();

	m_gamePaused = false;
	m_field11D = false;
	m_inputEnabledMemory = true;
	m_mouseVisibleMemory = true;
	for (Int i = 0; i < 8; ++i)
	{
		m_progressComplete[i] = false;
		m_progressCompleteTimeout[i] = 0;
	}
	m_forceGameStartByTimeOut = false;

	m_isScoringEnabled = true;
	m_showBehindBuildingMarkers = true;
	m_drawIconUI = true;
	m_showDynamicLOD = true;
	m_scriptHulkMaxLifetimeOverride = -1;
	m_field9C = 1;

	m_field6B = false;
	m_field8C = 0;
	m_field44 = 0;
	m_list4C.clear();

	TheGameLogic->resetPlayerLeaveStatusForInit();
	m_field290 = 2;
}
