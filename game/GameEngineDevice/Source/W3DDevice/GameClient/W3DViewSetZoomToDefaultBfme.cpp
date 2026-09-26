// Retail 0x00743060, W3DView::setZoomToDefault.
// The neighboring setZoom and setHeightAboveGround bodies use the same view
// offsets. The height sampler and zoom-limit calls identify the two embedded
// helper objects used by this method.

typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Rva0045A000
{
public:
	char m_padding00[ 0x1C ];
	Bool m_ready;
};

class Rva006DF250
{
public:
	virtual Real minimum();
	virtual Real maximum();
};

extern void d_0073a9b0( void );
extern void j_00046fa1( void );

class W3DView
{
public:
	virtual void setZoom( Real zoom );
	void setZoomToDefault();

private:
	char m_padding0004[ 0x0C - 0x04 ];
	Coord3D m_pos;
	char m_padding0018[ 0x3C - 0x18 ];
	Real m_cameraZoom;
	Real m_cameraHeight;
	char m_padding0044[ 0x1DC - 0x44 ];
	Bool m_rotatingCamera;
	char m_padding01DD[ 0x204 - 0x1DD ];
	Bool m_cameraUpdate;
	char m_padding0205[ 0x228 - 0x205 ];
	Bool m_zoomingCamera;
	char m_padding0229[ 0x27C - 0x229 ];
	Bool m_cameraMovementAlternate;
	Bool m_cameraMovementFinished;
	char m_padding027E[ 0x2354 - 0x27E ];
	int m_cameraMovementMode;
	char m_padding2358[ 0x23E0 - 0x2358 ];
	Real m_cameraOffsetZ;
	char m_padding23E4[ 0x23F8 - 0x23E4 ];
	Real m_groundLevel;
	char m_padding23FC[ 0x240C - 0x23FC ];
	Bool m_cameraHasMovedSinceRequest;
	char m_padding240D[ 0x2448 - 0x240D ];
	Rva0045A000 m_heightField;
	char m_padding2468[ 0x24B8 - 0x2468 ];
	Rva006DF250 m_zoomLimits;

	void setCameraTransform();
};

void W3DView::setZoomToDefault()
{
	if( m_cameraMovementMode != 0 )
		return;
	if( m_rotatingCamera )
		return;
	if( m_cameraUpdate )
		return;
	if( m_zoomingCamera )
		return;
	if( m_cameraMovementFinished )
		return;
	if( m_cameraMovementAlternate )
		return;

	typedef Real ( *TerrainHeight )( Real, Real );
	Real terrainHeight = ( ( TerrainHeight )d_0073a9b0 )( m_pos.x, m_pos.y );
	if( m_heightField.m_ready )
	{
		typedef Real ( Rva0045A000::*Sample )( Real, Real );
		union
		{
			void ( *function )( void );
			Sample member;
		} thunk;
		thunk.function = j_00046fa1;
		terrainHeight = ( m_heightField.*thunk.member )( m_pos.x, m_pos.y );
	}

	m_cameraZoom = ( m_zoomLimits.maximum() + terrainHeight ) / m_cameraOffsetZ;
	m_cameraHeight = m_zoomLimits.maximum();
	m_rotatingCamera = false;
	m_cameraUpdate = false;
	m_cameraMovementAlternate = false;
	m_zoomingCamera = false;
	m_cameraMovementFinished = false;
	m_cameraHasMovedSinceRequest = false;
	setCameraTransform();
}
