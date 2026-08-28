// cl: /DNDEBUG /MD /EHsc
// readable body of ?setPosition@RadiusDecal@@: Code/GameEngine/Source/GameClient/RadiusDecal.cpp

// RadiusDecal::setPosition, retail 0x004583A0. The decal itself is behind the
// pointer at +0x04 and does nothing when that is null; the position it carries
// is three floats at +0x08 of whatever it points at.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

class RadiusDecalShadow
{
public:
	unsigned char m_unmodelled_00[ 8 ];
	Coord3D m_position;						// +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecal
{
public:
	void setPosition( const Coord3D &pos );

private:
	unsigned char m_unmodelled_00[ 4 ];
	RadiusDecalShadow *m_shadow;			// +0x04
};

// ?setPosition@RadiusDecal@@QAEXABUCoord3D@@@Z
void RadiusDecal::setPosition( const Coord3D &pos )
{
	if( m_shadow )
		m_shadow->m_position = pos;
}
