// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /D_STLP_USE_STATIC_LIB
// stlport
// Real C++ reconstruction of ?addSnapshotBlock@GameState@@AAEXVAsciiString@@PAVSnapshot@@W4SnapshotType@@@Z.
// The GameState::init body at 0x001112D0 is the named caller of this 216-byte
// helper. The landed GameState constructor proves three STLport list headers
// at this+0x0c, so this TU keeps the reference SnapshotBlock layout and the
// list insertion in the vendor container rather than inventing a new owner.

#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;

template <typename T> struct BfmeStringData
{
	int m_refs;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

protected:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }
	BfmeStringData<T> *m_data;

private:
	void releaseBuffer();
	void set(const StringBase<T> &other);
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

	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}
};

class Snapshot;

enum SnapshotType
{
	SNAPSHOT_SAVELOAD,
	SNAPSHOT_DEEPCRC_LOGICONLY,
	SNAPSHOT_DEEPCRC,
	SNAPSHOT_MAX
};

class GameState
{
private:
	struct SnapshotBlock
	{
		Snapshot *snapshot;
		AsciiString blockName;
	};

	char m_unmodelled_000[0x0c];
	_STL::list<SnapshotBlock> m_snapshotBlockList[SNAPSHOT_MAX];

	void addSnapshotBlock(AsciiString blockName, Snapshot *snapshot,
		SnapshotType which);
};

// ?addSnapshotBlock@GameState@@AAEXVAsciiString@@PAVSnapshot@@W4SnapshotType@@@Z
void GameState::addSnapshotBlock(AsciiString blockName, Snapshot *snapshot,
	SnapshotType which)
{
	if (blockName.isEmpty() || snapshot == 0)
		return;

	SnapshotBlock blockInfo;
	blockInfo.snapshot = snapshot;
	blockInfo.blockName = blockName;
	m_snapshotBlockList[which].push_back(blockInfo);
}
