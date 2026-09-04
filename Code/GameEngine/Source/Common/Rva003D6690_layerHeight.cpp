// cl: /DNDEBUG /MD /EHsc
//
// Rva003D6690::apply, retail 0x003D6690, 116 bytes.
//
// Four-arg thiscall on d_003d5070: pack layer from src+0xC bits [6..11];
// signed-reject the closed range [0x11,0x40]; otherwise write cell-center
// world coords (i+0.5)*10 into +4/+8 and getLayerHeight(x,y,layer,0,1)
// into +0xC. Int return (not bool) for xor-eax / mov-eax-1.

enum PathfindLayerEnum
{
	LAYER_GROUND = 0
};

class Coord3D;

class TerrainLogic
{
public:
	virtual void _pad00( void );
	virtual void _pad04( void );
	virtual void _pad08( void );
	virtual void _pad0C( void );
	virtual void _pad10( void );
	virtual void _pad14( void );
	virtual void _pad18( void );
	// +0x1C
	virtual float getLayerHeight( float x, float y, PathfindLayerEnum layer,
		Coord3D * normal, bool clip ) const;
};

extern TerrainLogic * TheTerrainLogic; // 0x012EF4CC
extern float g_bfmeADL;                 // 0x0107533C = 0.5f
extern float g_bfmeDirectionWeight1285; // 0x01075C74 = 10.0f

struct Gen003D6690Flags
{
	char m_pad00[ 0x0C ];
	unsigned m_flags;
};

class Rva003D6690
{
public:
	int apply( void * unused0, Gen003D6690Flags * src, int cellX, int cellY );

private:
	char m_pad00[ 0x4 ];
	float m_at04;
	float m_at08;
	float m_at0C;
};

// ?apply@Rva003D6690@@QAEHPAXPAUGen003D6690Flags@@HH@Z
int Rva003D6690::apply( void * unused0, Gen003D6690Flags * src, int cellX, int cellY )
{
	(void)unused0;
	int layer = (int)( ( src->m_flags >> 6 ) & 0x3F );
	if( layer >= 0x11 && layer <= 0x40 )
		return 0;

	float x = ( cellX + g_bfmeADL ) * g_bfmeDirectionWeight1285;
	m_at04 = x;
	float y = ( cellY + g_bfmeADL ) * g_bfmeDirectionWeight1285;
	m_at08 = y;
	m_at0C = TheTerrainLogic->getLayerHeight( x, y,
		(PathfindLayerEnum)layer, 0, true );
	return 1;
}
