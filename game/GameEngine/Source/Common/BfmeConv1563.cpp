// Open-BFME5 conversions.

class PartitionCell;
class PartitionManager
{
public:
	void getCellRange(PartitionCell **first, PartitionCell **last, int x1, int x2, int y);
};

// The per-cell touch target at 0x008FC3B0 is owned by the ShroudManager pimpl
// element class (see game/GameEngine/Source/Common/RTS/
// ShroudManagerImpl008FBA40.cpp, ledger row 0x008FC3B0).  No header declares
// it, so this TU forward-declares it and the call below passes the same
// objects the retail body does.  The range request uses the proven
// PartitionManager::getCellRange name at 0x008F7D10.
class ShroudManagerImpl008FBA40;

class ShroudManagerImpl008FBA40Element
{
public:
	void updatePlayerCells008FC3B0(ShroudManagerImpl008FBA40 *manager, int index);
};

class BfmeCellVRB
{
public:
	char m_bfmePad00[0x68];
};

class BfmeShroudVRB
{
public:
	char bfmeUpdateVRB(int x, int y, int radius);
	PartitionManager *m_bfme00;
	int m_bfme04;
};

char BfmeShroudVRB::bfmeUpdateVRB(int x, int y, int radius)
{
	BfmeCellVRB *volatile first;
	BfmeCellVRB *last;
	unsigned int mask;
	int index;

	m_bfme00->getCellRange((PartitionCell **)&first, (PartitionCell **)&last, x, y, radius);

	mask = m_bfme04;
	index = 0;
	if (mask != 0)
	{
		BfmeCellVRB *end = last;

		do
		{
			if ((mask & 1) != 0)
			{
				BfmeCellVRB *p;

				for (p = first; p != end; ++p)
					reinterpret_cast<ShroudManagerImpl008FBA40Element *>(p)->updatePlayerCells008FC3B0(
						reinterpret_cast<ShroudManagerImpl008FBA40 *>(m_bfme00), index);
			}

			mask >>= 1;
			++index;
		}
		while (mask != 0);
	}

	return 1;
}
