// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DTerrainLogic::newMap at retail 0x00491550.
//
// The retail object keeps the terrain-render state consumed by the road loader
// at +0x10.  This TU-local slice records only that proven layout dependency.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual ~TerrainLogic();
	char m_baseFields[0x0C];
	virtual void newMap( Bool saveGame );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameLogic/W3DTerrainLogic.h
class W3DTerrainLogic : public TerrainLogic
{
public:
	void *m_terrainRenderState;
	virtual void newMap( Bool saveGame );
};

void bfme_loadRoadsAndBridges( void *terrainRenderState, Bool saveGame );

void W3DTerrainLogic::newMap( Bool saveGame )
{
	bfme_loadRoadsAndBridges( m_terrainRenderState, saveGame );
	TerrainLogic::newMap( saveGame );
}
