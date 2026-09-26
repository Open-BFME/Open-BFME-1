// ?bfmePrepareRefresh@Pathfinder@@QAEXXZ

typedef int Bool;

class Pathfinder;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	char m_bfmeHead[4];
	PathfindCell *m_next;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindLayer
{
public:
	bool isUsed();

	char m_unreconstructed_00[0x3c];
	void *m_bfmeOther;
	char m_unreconstructed_40[4];

private:
	friend class Pathfinder;
	void bfmeNotifyPlain();
	void bfmeNotifyBridge();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void bfmePrepareRefresh(void);
	void releaseCell(PathfindCell *cell, Bool value);

	char m_bfmeHead[0x858];
	PathfindCell *m_openList;
	PathfindLayer m_layers[16];
	char m_bfmeAfterLayers[0x243f4 - 0xc9c];
	unsigned char m_bfmeDirtyA;
	unsigned char m_bfmeDirtyB;
};

void Pathfinder::bfmePrepareRefresh(void)
{
	PathfindLayer *currentLayer = m_layers;
	int remainingLayerCount = 15;
	while (remainingLayerCount != 0)
	{
		if (currentLayer->isUsed())
		{
			if (currentLayer->m_bfmeOther != 0)
				currentLayer->bfmeNotifyPlain();
			else
				currentLayer->bfmeNotifyBridge();
		}
		currentLayer++;
		--remainingLayerCount;
	}

	PathfindCell *openCell = m_openList;
	while (openCell != 0)
	{
		releaseCell(openCell, 1);
		openCell = openCell->m_next;
	}

	m_bfmeDirtyA = 0;
	m_bfmeDirtyB = 0;
}
