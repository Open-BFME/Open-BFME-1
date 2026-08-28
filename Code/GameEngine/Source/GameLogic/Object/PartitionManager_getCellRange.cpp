// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionCell
{
private:
	unsigned char m_unreconstructed[0x68];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionManager
{
public:
	void getCellRange(PartitionCell **first, PartitionCell **last, int x1, int x2, int y);

private:
	unsigned char m_unreconstructed[0x24];
	int m_cellCountX;
	int m_cellCountY;
	PartitionCell *m_cells;
};

void PartitionManager::getCellRange(PartitionCell **first, PartitionCell **last, int x1, int x2, int y)
{
	if (x2 < 0 || x1 >= m_cellCountX || y < 0 || y >= m_cellCountY)
	{
		*last = 0;
		*first = 0;
		return;
	}

	PartitionCell *row = m_cells + y * m_cellCountX;
	*last = row;
	*first = row;
	if (x1 > 0)
		*first = row + x1;

	*last += x2 < m_cellCountX ? x2 + 1 : m_cellCountX;
}
