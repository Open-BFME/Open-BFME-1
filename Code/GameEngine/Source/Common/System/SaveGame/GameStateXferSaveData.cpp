// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ivendor/stlport /Ivendor/stlport/src
// Real-C++ reconstruction of ?xferSaveData@GameState@@AAEXPAVXfer@@W4SnapshotType@@@Z.
//
// The named friend_xferSaveDataForCRC caller at 0x00110CF0 proves this
// GameState body and its SaveGameInfo offsets.  The local views below keep the
// BFME ABI needed by this function without changing shared headers.
// The former address-derived row at 0x0010FDD4 was the compiler's EH rethrow
// block inside this contiguous body, so it is retired rather than split out.

#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <string.h>

#pragma intrinsic(strlen)

extern "C" __declspec(dllimport) int __cdecl _memicmp(
	const void *left, const void *right, unsigned int count);

typedef unsigned short UnsignedShort;
typedef bool Bool;

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
	friend class AsciiString;

protected:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }


	private:
	StringBase(const T *text);
	void set(const StringBase<T> &other);
	BfmeStringData<T> *m_data;

private:
	void releaseBuffer();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void set(const AsciiString &other)
	{
		StringBase<char>::set(other);
	}

	int compareNoCase(const char *text) const;
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
	virtual void crc(Xfer *xfer) = 0;
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
	unsigned char m_pad[0x28];
	SaveFileType saveFileType;
	unsigned char m_tail[0x04];
};

// BFME places these operations at the slots observed in the retail body:
// IsStoring +0x08, block operations +0x14/+0x18/+0x1c, snapshot +0x30, and
// AsciiString transfer +0x68.
class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool IsStoring();
	virtual void slot03();
	virtual void slot04();
	virtual int beginBlock(const char *name);
	virtual void endBlock();
	virtual void skipBlock(const char *name);
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void xferSnapshot(Snapshot *snapshot);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void xferAsciiString(AsciiString *value);
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

private:
	SnapshotBlock *findBlockInfoByToken(AsciiString token, SnapshotType which);
	void xferSaveData(Xfer *xfer, SnapshotType which);

	SnapshotBlockList m_snapshotBlockList[SNAPSHOT_MAX];
	SaveGameInfo m_gameInfo;
};

static const char *SAVE_FILE_EOF = "EOF";

static __forceinline int compareEofToken(const AsciiString &value,
	const char *text)
{
	BfmeStringData<char> *data =
		*(BfmeStringData<char> * const *)(const void *)&value;
	int otherLength = text ? (int)strlen(text) : 0;
	const char *otherText = text;
	int thisLength = data ? data->m_length : 0;
	const char *thisText = data ? data->m_text : "";
	int length = thisLength < otherLength ? thisLength : otherLength;
	int result = _memicmp(thisText, otherText, length);
	if (result != 0)
		return result;
	return thisLength - otherLength;
}

// ?xferSaveData@GameState@@AAEXPAVXfer@@W4SnapshotType@@@Z
void GameState::xferSaveData(Xfer *xfer, SnapshotType which)
{
	if (xfer->IsStoring())
	{
		AsciiString blockName;
		SnapshotBlock *blockInfo;
		SnapshotBlockListIterator it;
		for (it = m_snapshotBlockList[which].begin();
			it != m_snapshotBlockList[which].end(); ++it)
		{
			blockInfo = &(*it);
			blockName.set(blockInfo->blockName);
			if (m_gameInfo.saveFileType != SAVE_FILE_TYPE_MISSION ||
				blockName.compareNoCase("CHUNK_GameState") == 0 ||
				blockName.compareNoCase("CHUNK_Campaign") == 0 ||
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
		AsciiString eofToken = SAVE_FILE_EOF;
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
			if (compareEofToken(token, SAVE_FILE_EOF) == 0)
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
