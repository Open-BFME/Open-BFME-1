// cl: /O2

// WorldHeightMap::getUVData, retail 0x0074CF30; evidence:
// targets/game/reverse/identity_evidence/q32-worldheightmap-getuvdata.md
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h
class WorldHeightMap
{
public:
	bool getUVData(int xIndex, int yIndex, float U[4], float V[4], bool fullTile);

protected:
	bool getUVForTileIndex(int ndx, short tileNdx, float U[4], float V[4], bool fullTile);

private:
	char m_pad00[8];
	int m_width;
	char m_pad0c[0x14];
	int m_dataSize;
	char m_pad24[0x68];
	short *m_tileNdxes;
	char m_pad90[0x12050];
	int m_drawOriginX;
	int m_drawOriginY;
};

bool WorldHeightMap::getUVData(int xIndex, int yIndex, float U[4], float V[4], bool fullTile)
{
	int i = (m_drawOriginY + yIndex) * m_width + m_drawOriginX + xIndex;
	if (i < m_dataSize)
	{
		if (m_tileNdxes)
			return getUVForTileIndex(i, m_tileNdxes[i], U, V, fullTile);
	}
	return false;
}
