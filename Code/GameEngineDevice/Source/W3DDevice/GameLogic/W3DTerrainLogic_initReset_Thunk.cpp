// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DTerrainLogic::init and ::reset, retail 0x006BE0E0 and
// 0x006BE110.
//
// The Zero Hour bodies unchanged. W3DTerrainLogic.cpp is not in this tree, so
// the class is spelled locally around the four members both bodies write:
//
//   m_mapDX    +0x000c        m_mapMinZ  +0x18f8
//   m_mapDY    +0x0010        m_mapMaxZ  +0x18fc
//
// The 0x18e4-byte gap between m_mapDY and m_mapMinZ is the interesting part --
// whatever sits in it is most of the class. m_mapMaxZ is stored as the
// immediate 0x3f800000, so it is a Real holding 1.0f, and m_mapMinZ shares the
// zeroed register with the two Ints above it.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void init(void);						///< ILT 0x00027994
	virtual void reset(void);						///< ILT 0x0001B707

protected:
	char m_unreconstructed_04[0x0c - 4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h
class WorldHeightMap
{
public:
	static void freeListOfMapObjects(void);			///< ILT 0x00047127
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameLogic/W3DTerrainLogic.h
class W3DTerrainLogic : public TerrainLogic
{
public:
	virtual void init(void);
	virtual void reset(void);

private:
	int m_mapDX;									///< retail this+0x000c
	int m_mapDY;									///< retail this+0x0010
	char m_unreconstructed_14[0x18f8 - 0x14];
	float m_mapMinZ;								///< retail this+0x18f8
	float m_mapMaxZ;								///< retail this+0x18fc
};

//-------------------------------------------------------------------------------------------------
// ?init@W3DTerrainLogic@@UAEXXZ
void W3DTerrainLogic::init( void )
{

	// enhancing functionality
	TerrainLogic::init();
	m_mapDX = 0;
	m_mapDY = 0;
	m_mapMinZ = 0;
	m_mapMaxZ = 1;

}  // end init

//-------------------------------------------------------------------------------------------------
// ?reset@W3DTerrainLogic@@UAEXXZ
void W3DTerrainLogic::reset( void )
{
	TerrainLogic::reset();
	m_mapDX = 0;
	m_mapDY = 0;
	m_mapMinZ = 0;
	m_mapMaxZ = 1;
	WorldHeightMap::freeListOfMapObjects();
}  // end reset
