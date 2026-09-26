// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x001C0010, 287 bytes. The matched AIMoveToStateSA_computePath
// caller reaches this one-output-coordinate member through ILT 0x00027BC9.
// Rva00027BC9Object is that caller's address-derived Object view, not a
// recovered original method name. See docs/analysis/0x003e8e10.md sections
// 1b and 1c: cached position +38; matrix +08; geometry +AC and flag +B0.
// The direct callee 0x0087DC00 copies the geometry's +18/+1C/+20 vector.
// The zero-flag path transforms it and invokes View slot +30 five times.
// The inline helper preserves the geometry pointer across the flag test;
// the Vector3 temporary completes the transform before any output store.
#include "vector3.h"

struct Coord3D
{
	float x;
	float y;
	float z;
	void set(float a, float b, float c) { x=a; y=b; z=c; }
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
	unsigned int m_rva001C0010_00;
	bool m_rva001C0010_04;
	char m_rva001C0010_05[0x18-5];
	Rva0087DC00Vec m_rva001C0010_18;
	bool useCached001C0010() const { return m_rva001C0010_04; }
};

class Rva001C0010View
{
public:
	virtual void reserved00(); virtual void reserved01(); virtual void reserved02();
	virtual void reserved03(); virtual void reserved04(); virtual void reserved05();
	virtual void reserved06(); virtual void reserved07(); virtual void reserved08();
	virtual void reserved09(); virtual void reserved10(); virtual void reserved11();
	virtual void drawMarker001C0010Slot30( const Coord3D *pos, float size, unsigned int color, int flag );
};

#define TheTacticalView ( *(Rva001C0010View **)0x012F1600 )

class Rva00027BC9Object
{
public:
	void getPosition( Coord3D *out );

private:
	char m_unmodelled00[ 8 ];
	float m_transform[ 12 ];
	Coord3D m_position;
	char m_unmodelled44[ 0xac - 0x44 ];
	Rva0087DC00 m_rva001C0010_ac;

};

static __forceinline void geometryPosition001C0010(Rva0087DC00 *source, const Coord3D *position, const float *transform, Coord3D *out)
{
	if ( source->useCached001C0010() )
	{
		*out = *position;
		return;
	}

	Rva0087DC00Vec vec;
	source->get( &vec );

	Vector3 result;
	result.X = transform[2]*vec.z + transform[1]*vec.y + transform[0]*vec.x + transform[3];
	result.Y = transform[6]*vec.z + transform[5]*vec.y + transform[4]*vec.x + transform[7];
	result.Z = transform[10]*vec.z + transform[9]*vec.y + transform[8]*vec.x + transform[11];

	out->set(result.X, result.Y, result.Z);

	TheTacticalView->drawMarker001C0010Slot30( out, 3.0f, 0xff00ff77, 0 );
	TheTacticalView->drawMarker001C0010Slot30( out, 6.0f, 0xff00ff77, 0 );
	TheTacticalView->drawMarker001C0010Slot30( out, 9.0f, 0xff00ff77, 0 );
	TheTacticalView->drawMarker001C0010Slot30( out, 12.0f, 0xff00ff77, 0 );
	TheTacticalView->drawMarker001C0010Slot30( out, 15.0f, 0xff00ff77, 0 );
}

void Rva00027BC9Object::getPosition(Coord3D *out)
{
	geometryPosition001C0010(&m_rva001C0010_ac, &m_position, m_transform, out);
}
