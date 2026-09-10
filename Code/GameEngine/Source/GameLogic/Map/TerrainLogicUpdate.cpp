// cl: /ICode/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/GameEngine/Source/Common/System /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// TerrainLogic::update (retail 0x001A2BE0, 285 B) on BFME's TerrainLogic layout.
//
// The ZH body is verbatim; only three facts differ from the vendored header and
// all three are BFME-specific, so they live in this TU-local mirror instead of
// the shared TerrainLogic.h: eight extra virtuals ahead of setWaterHeight
// (slot 28, ZH 21), eight bytes ahead of m_bridgeDamageStatesChanged and eight
// more ahead of m_waterToUpdate (0x38 / 0x4C in the object), and five logic
// frames per second instead of thirty.
#include "PreRTS.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/GameLogic.h"

class Rva001A2BE0TerrainLogic : public Snapshot, public SubsystemInterface
{
public:
	virtual ~Rva001A2BE0TerrainLogic();
	virtual void init( void );
	virtual void reset( void );
	virtual void update( void );	// ?update@TerrainLogic@@UAEXXZ
	virtual Bool loadMap( AsciiString filename, Bool query );
	virtual void newMap( Bool saveGame );
	virtual Real getGroundHeight( Real x, Real y, Coord3D* normal = NULL ) const;
	virtual void bfmeSlot07( void );
	virtual void bfmeSlot08( void );
	virtual void bfmeSlot09( void );
	virtual void bfmeSlot10( void );
	virtual void bfmeSlot11( void );
	virtual void bfmeSlot12( void );
	virtual void bfmeSlot13( void );
	virtual void bfmeSlot14( void );
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D* normal = NULL, Bool clip = true) const;
	virtual void getExtent( Region3D *extent ) const;
	virtual void getExtentIncludingBorder( Region3D *extent ) const;
	virtual void getMaximumPathfindExtent( Region3D *extent ) const;
	virtual Coord3D findClosestEdgePoint( const Coord3D *closestTo ) const;
	virtual Coord3D findFarthestEdgePoint( const Coord3D *farthestFrom ) const;
	virtual Bool isClearLineOfSight(const Coord3D& pos, const Coord3D& posOther) const;
	virtual AsciiString getSourceFilename( void );
	virtual PathfindLayerEnum alignOnTerrain( Real angle, const Coord3D& pos, Bool stickToGround, Matrix3D& mtx);
	virtual Bool isUnderwater( Real x, Real y, Real *waterZ = NULL, Real *terrainZ = NULL );
	virtual Bool isCliffCell( Real x, Real y) const;
	virtual const WaterHandle* getWaterHandle( Real x, Real y );
	virtual const WaterHandle* getWaterHandleByName( AsciiString name );
	virtual Real getWaterHeight( const WaterHandle *water );
	virtual void setWaterHeight( const WaterHandle *water, Real height, Real damageAmount, Bool forcePathfindUpdate );

protected:
	UnsignedByte	*m_mapData;
	Int	m_mapDX;
	Int	m_mapDY;
	VecICoord2D m_boundaries;
	Int m_activeBoundary;
	Waypoint *m_waypointListHead;
	Bridge *m_bridgeListHead;
	Int m_bfmePad0[2];
	Bool m_bridgeDamageStatesChanged;
	AsciiString m_filenameString;
	Bool m_waterGridEnabled;
	Int m_bfmePad1[2];
	enum { MAX_DYNAMIC_WATER = 64 };
	struct DynamicWaterEntry
	{
		const WaterHandle *waterTable;
		Real changePerFrame;
		Real targetHeight;
		Real damageAmount;
		Real currentHeight;
	} m_waterToUpdate[ MAX_DYNAMIC_WATER ];
	Int m_numWaterToUpdate;
};

enum { BFME_LOGICFRAMES_PER_SECOND = 5 };

// ?update@TerrainLogic@@UAEXXZ
void Rva001A2BE0TerrainLogic::update( void )
{
	m_bridgeDamageStatesChanged = false;

	if( m_numWaterToUpdate )
	{
		const WaterHandle *water;
		Real changePerFrame, damageAmount, targetHeight, currentHeight;
		Bool finalTransition,
				 doDamageThisFrame = (TheGameLogic->getFrame() % BFME_LOGICFRAMES_PER_SECOND) == 0;

		for( Int i = m_numWaterToUpdate - 1; i >= 0; --i )
		{
			water = m_waterToUpdate[ i ].waterTable;
			changePerFrame = m_waterToUpdate[ i ].changePerFrame;
			targetHeight = m_waterToUpdate[ i ].targetHeight;
			damageAmount = m_waterToUpdate[ i ].damageAmount;
			currentHeight = m_waterToUpdate[ i ].currentHeight;

			finalTransition = FALSE;
			if( changePerFrame > 0 )
			{
				if( currentHeight + changePerFrame >= targetHeight )
					finalTransition = TRUE;
			}
			else
			{
				if( currentHeight + changePerFrame <= targetHeight )
					finalTransition = TRUE;
			}

			if( finalTransition == TRUE )
			{
				setWaterHeight( water, targetHeight, damageAmount, TRUE );
				for( Int j = i; j < m_numWaterToUpdate; j++ )
					m_waterToUpdate[ i ] = m_waterToUpdate[ j ];
				m_numWaterToUpdate -= 1;
			}
			else
			{
				if( doDamageThisFrame == FALSE )
					damageAmount = 0.0f;
				currentHeight += changePerFrame;
				m_waterToUpdate[ i ].currentHeight = currentHeight;
				setWaterHeight( water, currentHeight, damageAmount, FALSE );
			}
		}
	}
}
