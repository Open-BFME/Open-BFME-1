// cl: /DNDEBUG /MD /EHsc

// Retail 0x00491550. W3DTerrainLogic::newMap -- BFME loads a member at +0x10
// rather than ZH's TheTerrainRenderObject global, then tails into
// TerrainLogic::newMap.

void loadRoadsAndBridges( void *render, bool saveGame );

class TerrainLogic
{
public:
	virtual void newMap( bool saveGame );
};

class W3DTerrainLogic : public TerrainLogic
{
public:
	virtual void newMap( bool saveGame );

private:
	unsigned char m_unmodelled_04[ 0x10 - 4 ];
	void *m_render;					// +0x10
};

// ?newMap@W3DTerrainLogic@@UAEX_N@Z
void W3DTerrainLogic::newMap( bool saveGame )
{
	loadRoadsAndBridges( m_render, saveGame );
	TerrainLogic::newMap( saveGame );
}
