// cl: /DNDEBUG /MD
// Retail 0x00728800: clear the flip state for the current terrain tile.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h
class WorldHeightMap
{
public:
	unsigned char m_pad00[8];
	int m_xExtent;
	int m_yExtent;
};

extern void d_00749830(void);
typedef void (WorldHeightMap::*SetFlipState)(int, int, bool);
union SetFlipStateThunk
{
	void (*plain)(void);
	SetFlipState member;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainBackground.h
class W3DTerrainBackground
{
public:
	void clearFlipStates(void);

private:
	unsigned char m_pad00[0x40];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	WorldHeightMap *m_map;
};

// ?clearFlipStates@W3DTerrainBackground@@QAEXXZ
void W3DTerrainBackground::clearFlipStates(void)
{
	WorldHeightMap *map = m_map;
	int limitX = map->m_xExtent;
	int limitY = map->m_yExtent;
	limitX--;
	limitY--;
	int xOrig = m_xOrigin;
	int yOrig = m_yOrigin;
	int width = m_width;
	int i = 0;
	if (width >= 0)
	{
		do
		{
			int j = 0;
			if (width >= 0)
			{
				volatile int x = xOrig + i;
				do
				{
					int cx = x;
					if (cx >= limitX)
						cx = limitX;
					int y = yOrig + j;
					if (y >= limitY)
						y = limitY;
					SetFlipStateThunk thunk;
					thunk.plain = d_00749830;
					(m_map->*thunk.member)(cx, y, false);
					width = m_width;
					j++;
				}
				while (j <= width);
			}
			width = m_width;
			i++;
		}
		while (i <= width);
	}
}
