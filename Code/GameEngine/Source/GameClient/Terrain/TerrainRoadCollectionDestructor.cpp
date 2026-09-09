// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: TerrainRoadCollection::~TerrainRoadCollection, retail 0x00601490.
// The constructor at 0x00601430 installs the same 0x01114FD4 vtable and
// initializes the road and bridge heads at +0x08 and +0x0C.  This is the
// retained upstream destructor: drain each intrusive list, deleting its old
// head before storing the saved next link.

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	char m_bfmePad04[4];
};

class TerrainRoadType
{
public:
	virtual ~TerrainRoadType();
	TerrainRoadType *friend_getNext(void) { return m_next; }

private:
	char m_bfmePad04[0x0C];
	TerrainRoadType *m_next;
};

class TerrainRoadCollection : public SubsystemInterface
{
public:
	virtual ~TerrainRoadCollection();

private:
	TerrainRoadType *m_roadList;
	TerrainRoadType *m_bridgeList;
};

// ??1TerrainRoadCollection@@UAE@XZ
TerrainRoadCollection::~TerrainRoadCollection(void)
{
	TerrainRoadType *temp;

	while (m_roadList)
	{
		temp = m_roadList->friend_getNext();
		delete m_roadList;
		m_roadList = temp;
	}

	while (m_bridgeList)
	{
		temp = m_bridgeList->friend_getNext();
		delete m_bridgeList;
		m_bridgeList = temp;
	}
}
