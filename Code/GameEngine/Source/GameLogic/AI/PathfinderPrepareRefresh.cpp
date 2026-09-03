// ?bfmePrepareRefresh@Pathfinder@@QAEXXZ

typedef int Bool;

class Pathfinder;

class PathfindCell
{
public:
	char m_bfmeHead[4];
	PathfindCell *m_next;
};

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
	PathfindLayer *layer = m_layers;
	int count = 15;
	while (count != 0)
	{
		if (layer->isUsed())
		{
			if (layer->m_bfmeOther != 0)
				layer->bfmeNotifyPlain();
			else
				layer->bfmeNotifyBridge();
		}
		layer++;
		--count;
	}

	PathfindCell *cell = m_openList;
	while (cell != 0)
	{
		releaseCell(cell, 1);
		cell = cell->m_next;
	}

	m_bfmeDirtyA = 0;
	m_bfmeDirtyB = 0;
}
