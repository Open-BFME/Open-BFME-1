// ?xferSaveData@GameState@@AAEXPAVXfer@@W4SnapshotType@@@Z
// partial score=0.72 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/stringinline
// stlport
// Open-BFME5: GameState::xferSaveData, retail 0x0010FBD0 size 550.
// GameState/SnapshotBlock/AsciiString layout reused verbatim from the matched
// sibling Code/GameEngine/Source/Common/System/SaveGame/GameStateFindBlockInfoByToken.cpp
// (proven std::list<SnapshotBlock> m_snapshotBlockList[SNAPSHOT_MAX] at this+0xc).
// Xfer slot layout reused from the matched Xfer/XferBeginBlock/XferEndBlock/
// XferSkipBlock/Xfer.cpp family: IsStoring is slot 2, beginBlock/endBlock/
// skipBlock are ReservedVirtual1-3 (slots 5-7) repurposed by BFME, xferSnapshot
// wraps operator==(Snapshot&) at slot 12, xferAsciiString wraps
// operator==(AsciiString&) at slot 26 (0x68 -- matches the observed retail
// vtable call offset).
//
// State: compiles clean to 478B vs retail 550 (72 short); the save-branch
// entry skeleton (sub esp; mov this-param; call [+8]=IsStoring; test/je;
// list-begin/end walk indexed [ebx+ecx*4+0xc]) matches retail almost
// instruction-for-instruction through the loop entry -- confirms the Xfer
// slot numbers and the reused GameState/list layout are right.
// Root cause of the remaining gap: AsciiString::compareNoCase(const char*)
// is NOT the same body as the already-landed
// StringBase<char>::compareNoCase(const StringBase<char>&) in
// Code/Libraries/Source/WWVegas/WWLib/RvaTreeInsertUniqueNoCase.cpp (which
// calls __imp___memicmp against another StringBase's m_data->length/data,
// no strlen needed). Retail's block-name-literal comparisons instead: read a
// global slot (observed 0x0012ABFB0-ish -- likely the literal's own storage,
// re-derive the exact address from a fresh compile before reusing it), do a
// manual byte-count loop (lea/inc/test cl,cl/jne -- an inlined strlen over
// the C-string literal) to get its length into ebx, THEN call an import at
// an address close to (but not identical to -- re-resolve, do not reuse
// blind) reverse/symbols.csv's __imp___stricmp (0x0135933C); the length is
// almost certainly the case-sensitive compare()'s min-length/tiebreak
// pattern reapplied around a full _stricmp rather than a bounded call.
// Next step: write compareNoCase(const char *str) with an inline strlen loop
// + __declspec(dllimport) _stricmp(thisText, str) + (thisLen - strlen(str))
// tiebreak, matching compare()'s shape but swapping memcmp for _stricmp, and
// iterate against explain_mismatch from there -- the save-branch entry
// almost certainly does not need any further changes.
// t=40min model=sonnet-5

#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1
#include <list>

extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef int Int;
#define TRUE true
#define FALSE false

template <typename T> struct BfmeStringData
{
	int m_refs;
	UnsignedShort m_length;
	UnsignedShort m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
protected:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }
	BfmeStringData<T> *m_data;

private:
	void releaseBuffer();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString(const char *str);
	~AsciiString() {}

	bool isEmpty() const
	{
		return m_data == 0 || m_data->m_length == 0;
	}

	int compare(const AsciiString &other) const
	{
		int otherLength = other.m_data ? other.m_data->m_length : 0;
		const char *otherText = other.m_data ? other.m_data->m_text : "";
		int thisLength = m_data ? m_data->m_length : 0;
		const char *thisText = m_data ? m_data->m_text : "";
		int length = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp(thisText, otherText, length);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}

	int compareNoCase(const char *str) const;

	bool operator==(const AsciiString &rhs) const
	{
		return compare(rhs) == 0;
	}

	const char *str() const { return m_data ? m_data->m_text : ""; }
};

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

class Xfer;

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}
	virtual void crc(void *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

enum SnapshotType
{
	SNAPSHOT_SAVELOAD,
	SNAPSHOT_DEEPCRC_LOGICONLY,
	SNAPSHOT_DEEPCRC,
	SNAPSHOT_MAX
};

enum SaveFileType
{
	SAVE_FILE_TYPE_NORMAL,
	SAVE_FILE_TYPE_MISSION
};

struct SaveGameInfo
{
	SaveFileType saveFileType;
	char m_pad[0x40];
};

// Minimal Xfer stub reproducing only the retail vtable slots this body calls.
class Xfer
{
public:
	virtual void slot00();               // dtor
	virtual void slot01();                // IsLoading
	virtual bool IsStoring();             // slot 2
	virtual void slot03();
	virtual void slot04();
	virtual int beginBlock(const char *name);   // slot 5 (ReservedVirtual1)
	virtual void endBlock();                    // slot 6 (ReservedVirtual2)
	virtual void skipBlock(const char *name);   // slot 7 (ReservedVirtual3)
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void xferSnapshotSlot(Snapshot *snapshot);  // slot 12
	virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18();
	virtual void slot19(); virtual void slot20(); virtual void slot21();
	virtual void slot22(); virtual void slot23(); virtual void slot24();
	virtual void slot25();
	virtual void xferAsciiStringSlot(AsciiString *value);  // slot 26

	void xferAsciiString(AsciiString *value) { xferAsciiStringSlot(value); }
	void xferSnapshot(Snapshot *snapshot) { xferSnapshotSlot(snapshot); }
};

class GameState : public SubsystemInterface, public Snapshot
{
public:
	struct SnapshotBlock
	{
		Snapshot *snapshot;
		AsciiString blockName;
	};

	typedef std::list<SnapshotBlock> SnapshotBlockList;
	typedef SnapshotBlockList::iterator SnapshotBlockListIterator;

	SaveGameInfo *getSaveGameInfo() { return &m_gameInfo; }

	private:
	void xferSaveData(Xfer *xfer, SnapshotType which);
	SnapshotBlock *findBlockInfoByToken(AsciiString token, SnapshotType which);

	SnapshotBlockList m_snapshotBlockList[SNAPSHOT_MAX];
	SaveGameInfo m_gameInfo;
};

// ?xferSaveData@GameState@@AAEXPAVXfer@@W4SnapshotType@@@Z
void GameState::xferSaveData(Xfer *xfer, SnapshotType which)
{
	if (xfer->IsStoring())
	{
		AsciiString blockName;
		SnapshotBlock *blockInfo;
		SnapshotBlockListIterator it;
		for (it = m_snapshotBlockList[which].begin(); it != m_snapshotBlockList[which].end(); ++it)
		{
			blockInfo = &(*it);
			blockName = blockInfo->blockName;

			if (getSaveGameInfo()->saveFileType != SAVE_FILE_TYPE_MISSION ||
				blockName.compareNoCase("GameState") == 0 ||
				blockName.compareNoCase("Campaign") == 0 ||
				blockName.compareNoCase("CHUNK_LivingWorldLogic") == 0 ||
				blockName.compareNoCase("CHUNK_Palantir") == 0 ||
				blockName.compareNoCase("CHUNK_Audio") == 0)
			{
				xfer->xferAsciiString(&blockName);
				try
				{
					xfer->beginBlock("Snapshot");
					xfer->xferSnapshot(blockInfo->snapshot);
					xfer->endBlock();
				}
				catch (...)
				{
					throw;
				}
			}
		}
		AsciiString eofToken("EOF");
		xfer->xferAsciiString(&eofToken);
	}
	else
	{
		AsciiString token;
		Bool done = FALSE;
		SnapshotBlock *blockInfo;
		while (done == FALSE)
		{
			xfer->xferAsciiString(&token);
			if (token.compareNoCase("EOF") == 0)
				done = TRUE;
			else
			{
				blockInfo = findBlockInfoByToken(token, which);
				if (blockInfo == 0)
				{
					xfer->skipBlock("Snapshot");
					continue;
				}
				try
				{
					xfer->beginBlock("Snapshot");
					xfer->xferSnapshot(blockInfo->snapshot);
					xfer->endBlock();
				}
				catch (...)
				{
					throw;
				}
			}
		}
	}
}

// ?findBlockInfoByToken@GameState@@AAEPAUSnapshotBlock@1@VAsciiString@@W4SnapshotType@@@Z
GameState::SnapshotBlock *GameState::findBlockInfoByToken(
	AsciiString token, SnapshotType which)
{
	if (token.isEmpty())
		return 0;

	SnapshotBlock *blockInfo;
	GameState::SnapshotBlockListIterator it;
	for (it = m_snapshotBlockList[which].begin();
		it != m_snapshotBlockList[which].end(); ++it)
	{
		blockInfo = &(*it);
		if (blockInfo->blockName == token)
			return blockInfo;
	}

	return 0;
}
