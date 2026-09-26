// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/stringinline
// stlport
// Real C++ reconstruction of ??0GameState@@QAE@XZ.
//
// The initSubsystem<GameState> caller at 0x00075960 proves the class identity.
// Retail lays out three list<SnapshotBlock> headers at +0x0c, SaveGameInfo at
// +0x18, a Snapshot* list at +0x48, a second SnapshotBlock list at +0x4c,
// AvailableGameInfo* at +0x50, and the load flag at +0x54. These local views
// retain only the ABI needed by this constructor; the existing named callees
// provide the base, SaveGameInfo, and STLport implementations.

#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "StringInline.h"

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	void *m_name;
};

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}
	virtual void crc(void *xfer) = 0;
	virtual void xfer(void *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

// The thunk is the existing incremental-link route to the matched
// SaveGameInfo constructor at 0x0010D680; it preserves ECX as the destination.
extern void j_0000f218(void) throw();

class SaveGameInfo
{
public:
	SaveGameInfo() throw();
	~SaveGameInfo() throw();

private:
	unsigned char m_data[0x30];
};

class GameState : public SubsystemInterface, public Snapshot
{
public:
	GameState();
	virtual ~GameState();
	virtual void init();
	virtual void reset();
	virtual void update();

protected:
	virtual void crc(void *xfer);
	virtual void xfer(void *xfer);
	virtual void loadPostProcess();

private:
	struct SnapshotBlock
	{
		Snapshot *snapshot;
		AsciiString blockName;
	};

	std::list<SnapshotBlock> m_snapshotBlockList[3];
	SaveGameInfo m_gameInfo;
	std::list<Snapshot *> m_snapshotPostProcessList;
	std::list<SnapshotBlock> m_bfmeSnapshotBlockList;
	void *m_availableGames;
	unsigned char m_isInLoadGame;
};

// ??0GameState@@QAE@XZ
GameState::GameState()
	: m_gameInfo(),
	  m_snapshotPostProcessList(),
	  m_bfmeSnapshotBlockList()
{
	m_availableGames = 0;
	m_isInLoadGame = 0;
}
