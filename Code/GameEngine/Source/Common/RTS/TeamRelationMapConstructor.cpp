// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ??0TeamRelationMap@@QAE@XZ: Code/GameEngine/Source/Common/RTS/Team.cpp

#include <vector>

class Xfer;

class TeamRelationPoolObject
{
public:
	TeamRelationPoolObject() {}
	virtual ~TeamRelationPoolObject();
};

class TeamRelationHashTable
{
public:
	__forceinline TeamRelationHashTable()
		: m_size(0)
	{
		initializeBuckets(100);
	}
	~TeamRelationHashTable();

private:
	void initializeBuckets(unsigned int count);

	unsigned int m_hashState;
	_STL::vector<void *> m_buckets;
	unsigned int m_size;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamRelationMap : public TeamRelationPoolObject
{
public:
	TeamRelationMap();
	virtual ~TeamRelationMap();

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	TeamRelationHashTable m_map;
};

// BFME uses one polymorphic base here, unlike the later Zero Hour layout.
TeamRelationMap::TeamRelationMap()
{
}
