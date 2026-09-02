// cl: /ICode/Libraries/Source/WWVegas/WWLib /DNDEBUG /MD /EHsc

#include "ascii_string.h"

// Open-BFME5: RecorderClass's constructor, retail 0x000993E0, 103 bytes. The
// body carried only a machine byte-dump row; the symbols.csv pin names it, and
// the member constructor and the init it ends with are pinned with this row.
//
// SubsystemInterface is the base -- the same constructor at 0x009A1A30
// W3DTerrainVisualBase calls -- and the class puts its own vtable over it.
// Then two pointers at +0x10 and +0x1C are nulled, the member at +0x20 is
// constructed through its own constructor, the word at +0x2B0 is cleared and
// init runs on this.
//
// The unwind slot goes 0, 2, 3 rather than counting every step, because the two
// nulled members cannot throw: the compiler only writes the state where a call
// follows, and by then those two are already accounted for.

class BfmeRecorderStore
{
public:
	BfmeRecorderStore();					// ILT 0x00016D47
	~BfmeRecorderStore();

private:
	// ReplayGameInfo is 0x278 bytes in this image: a 0x58-byte GameInfo
	// base followed by eight 0x44-byte slots.  The Recorder-owned state starts
	// immediately after it at RecorderClass+0x298.
	char m_bfmeBody[0x278];
};

// The BFME ReplayGameInfo vtable has two leading virtuals before reset.  The
// methods below are declared-only views so their calls resolve to the already
// pinned GameInfo bodies/thunks without changing the constructor's member type.
class GameInfo
{
public:
	virtual void bfmeGameInfoSlot0(void);
	virtual void bfmeGameInfoSlot1(void);
	virtual void reset(void);
	void clearSlotList(void);
	void setMap(AsciiString mapName);
};

// The ten-byte setter reached by RecorderClass::bfmeInit is an ICF-folded
// body shared with W3DVolumetricShadow::setOptimalExtrusionPadding.  Its retail
// call-site thunk is pinned at 0x0001F4A6; using the folded owner keeps the
// clean C++ call's ABI and target address without inventing a new pin.
class RecorderClass;

class W3DVolumetricShadow
{
	friend class RecorderClass;

	protected:
	void setOptimalExtrusionPadding(float padding);
};

extern int Rva00096A50Get(void);

// GlobalData's pending/map strings are the adjacent BFME fields at +0xB84 and
// +0xB88.  The pointer itself is the established 0x012ED5C8 singleton.  The
// pending-file test is deliberately local: the retail body inlines the
// StringBase header check instead of calling StringBase::isEmpty.
struct BfmeAsciiStringState
{
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
	};

	Header *m_data;

	bool isEmpty(void) const
	{
		return m_data == 0 || m_data->length == 0;
	}
};

class BfmeGlobalData
{
private:
	char m_bfmeHead[0x08];

public:
	BfmeAsciiStringState m_mapName;

private:
	char m_bfmeGap[0xB84 - 0x0C];

public:
	BfmeAsciiStringState m_pendingFile;
};

extern BfmeGlobalData *TheGlobalData;
extern int OpenBFME5_netCRCInterval;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();					// retail 0x009A1A30
	~SubsystemInterface();
	virtual void bfmeSlot0(void);

private:
	int m_bfmeState;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass : public SubsystemInterface
{
public:
	RecorderClass();

private:
	void bfmeInit(void);					// ILT 0x0000B721

	char m_bfmeHeadA[0x0C - 0x08];
	void *m_bfmeFile;						// +0x0C
	AsciiString m_bfmeFileName;				// +0x10
	int m_bfmeCurrentFilePosition;				// +0x14
	int m_bfmeMode;						// +0x18
	AsciiString m_bfmeCurrentReplayFilename;			// +0x1C
	BfmeRecorderStore m_bfmeGameInfo;				// +0x20
	int m_bfmeNetworkCrcInterval;				// +0x298
	int m_bfmeOriginalGameMode;				// +0x29C
	int m_bfmeNextFrame;					// +0x2A0
	int m_bfmeSeedOrDesync;					// +0x2A4
	unsigned char m_bfmeDoingAnalysis;				// +0x2A8
	char m_bfmeModePadding[0x2AC - 0x2A9];
	int m_bfmeGameMode;					// +0x2AC
	int m_bfme2B0;						// +0x2B0
};

// ??0RecorderClass@@QAE@XZ
RecorderClass::RecorderClass()
{
	m_bfme2B0 = 0;

	bfmeInit();
}

// ?bfmeInit@RecorderClass@@AAEXXZ
void RecorderClass::bfmeInit(void)
{
	// The BFME recorder starts in NONE mode, clears its file state, and resets
	// the embedded ReplayGameInfo before selecting the pending map (or the
	// current map when no pending map is present).
	m_bfmeGameMode = 8;
	m_bfmeMode = 2;
	m_bfmeFile = 0;
	m_bfmeFileName.clear();

	GameInfo *gameInfo = reinterpret_cast<GameInfo *>(&m_bfmeGameInfo);
	m_bfmeCurrentFilePosition = 0;
	gameInfo->clearSlotList();
	gameInfo->reset();

	if (TheGlobalData->m_pendingFile.isEmpty())
		gameInfo->setMap(reinterpret_cast<const AsciiString &>(TheGlobalData->m_mapName));
	else
		gameInfo->setMap(reinterpret_cast<const AsciiString &>(TheGlobalData->m_pendingFile));

	W3DVolumetricShadow *seedView = reinterpret_cast<W3DVolumetricShadow *>(gameInfo);
	union BfmeSeedBits
	{
		int integer;
		float real;
	} seed;
	seed.integer = Rva00096A50Get();
	seedView->setOptimalExtrusionPadding(seed.real);

	m_bfmeOriginalGameMode = -1;
	m_bfmeNetworkCrcInterval = OpenBFME5_netCRCInterval;
	m_bfmeNextFrame = 0;
	m_bfmeDoingAnalysis = 0;
	m_bfmeSeedOrDesync = -1;
}
