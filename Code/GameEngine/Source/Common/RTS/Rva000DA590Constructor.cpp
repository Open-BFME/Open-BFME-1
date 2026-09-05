// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Byte-twin of ??0TeamRelationMap@@QAE@XZ at 0x000F76E0
// (Code/GameEngine/Source/Common/RTS/TeamRelationMapConstructor.cpp):
// identical 92 bytes once relocations are masked. The installed vtable
// constant (0x01083E94, tools/vtable_lookup.py) differs from TeamRelationMap's
// own, so this is a sibling class with the same TeamRelationHashTable-shaped
// member, not TeamRelationMap itself; no name is provable, so it is claimed
// address-derived. Destructor twin: Rva000DA590Destructor.cpp (0x000D3FA0),
// which unwinds through the same base vtable (0x01073744, the shared
// Snapshot-family base) as the ZH-twinned DisplayString destructor.

#include <vector>

class Xfer;

class Rva000DA590PoolObject
{
public:
	Rva000DA590PoolObject() {}
	virtual ~Rva000DA590PoolObject();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
};

class Rva000DA590HashTable
{
public:
	__forceinline Rva000DA590HashTable()
		: m_size(0)
	{
		initializeBuckets(100);
	}
	~Rva000DA590HashTable();

private:
	void initializeBuckets(unsigned int count);

	unsigned int m_hashState;
	_STL::vector<void *> m_buckets;
	unsigned int m_size;
};

class Rva000DA590Map : public Rva000DA590PoolObject
{
public:
	Rva000DA590Map();
	virtual ~Rva000DA590Map();

private:
	Rva000DA590HashTable m_map;
};

Rva000DA590Map::Rva000DA590Map()
{
}
