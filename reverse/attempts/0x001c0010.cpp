// ?d_001c0010@@YAXXZ
// partial score=0.12 date=2026-09-21
// cl: /DNDEBUG /MD
// Rva00027BC9Object::getPosition, retail RVA 0x001C0010, 287 bytes.
// AIMoveToStateSA_computePath_rva00173680.cpp's already-matched
// Rva00173620State::computePath calls `goal->getPosition(&m_goalPosition)`
// on a Rva00027BC9Object*; that call resolves through the already-pinned
// symbol ?getPosition@Rva00027BC9Object@@QAEXPAUCoord3D@@@Z at 0x00027BC9,
// whose ILT jumps to this body (thunks_018.cpp; target=FUN_005c0010).
// When this+0xb0 is set, the position is just this+0x38 (Object::m_position
// per the caller file's layout). Otherwise the position is derived from a
// local 3x4 transform at this+0x08..+0x34 applied to a Rva0087DC00 vector
// read through this+0xac, and the derived point is drawn with four
// increasing-size TheTacticalView markers.

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Rva0087DC00Vec
{
	float x;
	float y;
	float z;
};

class Rva0087DC00
{
public:
	void get( Rva0087DC00Vec *out );
};

class View
{
public:
	virtual void reserved00(); virtual void reserved01(); virtual void reserved02();
	virtual void reserved03(); virtual void reserved04(); virtual void reserved05();
	virtual void reserved06(); virtual void reserved07(); virtual void reserved08();
	virtual void reserved09(); virtual void reserved10(); virtual void reserved11();
	virtual void drawDebugMarker( const Coord3D *pos, float size, unsigned int color, int flag );
};

#define TheTacticalView ( *(View **)0x012F1600 )

class Rva00027BC9Object
{
public:
	void getPosition( Coord3D *out );

private:
	char m_unmodelled00[ 8 ];
	float m_transform[ 12 ];
	Coord3D m_position;
	char m_unmodelled44[ 0xac - 0x44 ];
	Rva0087DC00 m_source;
	unsigned char m_unmodelledSourceTail[ 0xb0 - 0xac - sizeof( Rva0087DC00 ) ];
	unsigned char m_useSimplePosition;
};

void Rva00027BC9Object::getPosition( Coord3D *out )
{
	if ( m_useSimplePosition )
	{
		*out = m_position;
		return;
	}

	Rva0087DC00Vec vec;
	m_source.get( &vec );

	out->x = vec.x * m_transform[ 0 ] + vec.y * m_transform[ 1 ] +
		vec.z * m_transform[ 2 ] + m_transform[ 3 ];
	out->y = vec.x * m_transform[ 4 ] + vec.y * m_transform[ 5 ] +
		vec.z * m_transform[ 6 ] + m_transform[ 7 ];
	out->z = vec.x * m_transform[ 8 ] + vec.y * m_transform[ 9 ] +
		vec.z * m_transform[ 10 ] + m_transform[ 11 ];

	TheTacticalView->drawDebugMarker( out, 3.0f, 0xff00ff77, 0 );
	TheTacticalView->drawDebugMarker( out, 6.0f, 0xff00ff77, 0 );
	TheTacticalView->drawDebugMarker( out, 9.0f, 0xff00ff77, 0 );
	TheTacticalView->drawDebugMarker( out, 12.0f, 0xff00ff77, 0 );
	TheTacticalView->drawDebugMarker( out, 15.0f, 0xff00ff77, 0 );
}
