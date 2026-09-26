// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/stringinline
// stlport
// Real C++ reconstruction of ?findBlockInfoByToken@GameState@@AAEPAUSnapshotBlock@1@VAsciiString@@W4SnapshotType@@@Z.
//
// The sole named caller is GameState::getSaveGameInfoFromFile at 0x00111980,
// whose ILT 0x0000A6A5 reaches this body.  The published GameState constructor
// proves three std::list<SnapshotBlock> headers at this+0x0c.  BFME's narrow
// string view has a WORD length at data+4 and the intrinsic comparison is the
// length/minimum-byte comparison used below; this TU keeps that ABI local.

#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1
#include <list>

extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

typedef unsigned short UnsignedShort;

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

	bool operator==(const AsciiString &rhs) const
	{
		return compare(rhs) == 0;
	}
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

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}
	virtual void crc(void *xfer) = 0;
	virtual void xfer(void *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

enum SnapshotType
{
	SNAPSHOT_SAVELOAD,
	SNAPSHOT_DEEPCRC_LOGICONLY,
	SNAPSHOT_DEEPCRC,
	SNAPSHOT_MAX
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

	SnapshotBlockList m_snapshotBlockList[SNAPSHOT_MAX];
};

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
