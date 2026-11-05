// cl: /DNDEBUG /MD /EHs-c- /Ob2


enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID = 0,
	OBJECTSHROUD_CLEAR = 1,
	OBJECTSHROUD_PARTIAL_CLEAR = 2,
	OBJECTSHROUD_FOGGED = 3,
	OBJECTSHROUD_SHROUDED = 4
};

struct Rva008F8110ShroudEntry
{
	unsigned short status;
	unsigned char pad[4];
};

enum CellShroudStatus
{
	CELLSHROUD_CLEAR = 0,
	CELLSHROUD_FOGGED = 1,
	CELLSHROUD_SHROUDED = 2
};

class Rva008F8110CellView
{
public:
	CellShroudStatus getShroudStatusForPlayer(int playerIndex) const
	{
		unsigned short s = m_shroud[playerIndex].status;
		if (s == 0xFFFF)
			return CELLSHROUD_SHROUDED;
		return (CellShroudStatus)(s == 0);
	}
	void *m_first;
	Rva008F8110ShroudEntry m_shroud[16];
};

struct CellAndObjectIntersection
{
	Rva008F8110CellView *m_cell;
	void *m_module;
	void *m_prev;
	void *m_next;
};

class Rva008F8110Visibility
{
public:
	virtual ~Rva008F8110Visibility();
	virtual void d1();
	virtual void d2();
	virtual void d3();
	virtual void d4();
	virtual bool rva008F8110Slot14(int playerIndex);
};

class Rva008F8110Ghost
{
public:
	virtual ~Rva008F8110Ghost();
	virtual void d1();
	virtual void rva008F8110Slot08(int playerIndex);
	virtual void rva008F8110Slot0C(int playerIndex);
};

class PartitionData
{
public:
	ObjectShroudStatus getShroudedStatus(int playerIndex);

private:
	void *m_owner;
	Rva008F8110Visibility *m_object;
	Rva008F8110Ghost *m_ghost;
	void *m_next;
	void *m_prev;
	void *m_prevDirty;
	void *m_nextDirty;
	CellAndObjectIntersection *m_coiArray;
	int m_coiInUseCount;
	int m_shroudedness[16];
	int m_shroudednessPrevious[16];
	unsigned char m_everSeen[16];
};

// ?getShroudedStatus@PartitionData@@QAE?AW4ObjectShroudStatus@@H@Z
// Open BFME 2: Code/GameEngine/Source/Common/PartitionDataShroudStatus.cpp
ObjectShroudStatus PartitionData::getShroudedStatus(int playerIndex)
{
	if (playerIndex < 0 || playerIndex >= 16)
		return OBJECTSHROUD_SHROUDED;
	if (m_shroudedness[playerIndex] == OBJECTSHROUD_INVALID)
	{
		int shroudedCells = 0;
		int foggedCells = 0;
		int total = 0;
		CellAndObjectIntersection *end = m_coiArray + m_coiInUseCount;
		for (CellAndObjectIntersection *coi = m_coiArray; coi != end; ++coi)
		{
			Rva008F8110CellView *cell = coi->m_cell;
			if (cell)
			{
				++total;
				switch (cell->getShroudStatusForPlayer(playerIndex))
				{
				case CELLSHROUD_FOGGED:
					++foggedCells;
					break;
				case CELLSHROUD_SHROUDED:
					++shroudedCells;
					break;
				}
			}
		}

		if (total == 0 || shroudedCells == total)
		{
			m_shroudedness[playerIndex] = OBJECTSHROUD_SHROUDED;
			m_everSeen[playerIndex] = 0;
			if (m_ghost && m_shroudednessPrevious[playerIndex] == OBJECTSHROUD_FOGGED)
				m_ghost->rva008F8110Slot0C(playerIndex);
		}
		else if (shroudedCells + foggedCells == total)
		{
			m_shroudedness[playerIndex] = OBJECTSHROUD_FOGGED;
			if (m_object && m_ghost)
			{
				if (m_object->rva008F8110Slot14(playerIndex))
					m_shroudedness[playerIndex] = OBJECTSHROUD_SHROUDED;
				else if (m_shroudednessPrevious[playerIndex] < OBJECTSHROUD_FOGGED)
					m_ghost->rva008F8110Slot08(playerIndex);
			}
		}
		else if (shroudedCells == 0 && foggedCells == 0)
		{
			m_everSeen[playerIndex] = 1;
			m_shroudedness[playerIndex] = OBJECTSHROUD_CLEAR;
			if (m_ghost && m_shroudednessPrevious[playerIndex] != OBJECTSHROUD_CLEAR)
				m_ghost->rva008F8110Slot0C(playerIndex);
		}
		else
		{
			m_everSeen[playerIndex] = 1;
			m_shroudedness[playerIndex] = OBJECTSHROUD_PARTIAL_CLEAR;
			if (m_ghost && m_shroudednessPrevious[playerIndex] != OBJECTSHROUD_PARTIAL_CLEAR)
				m_ghost->rva008F8110Slot0C(playerIndex);
		}

		if (total)
			m_shroudednessPrevious[playerIndex] = m_shroudedness[playerIndex];
	}

	return (ObjectShroudStatus)m_shroudedness[playerIndex];
}
