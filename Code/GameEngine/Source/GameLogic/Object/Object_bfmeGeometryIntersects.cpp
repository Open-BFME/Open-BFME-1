// cl: /DNDEBUG /MD /EHsc

// Open-BFME: retail 0x001BE980, 57 bytes.  This wrapper compares the oriented
// GeometryInfo footprints of two Objects.  The public retail spelling of this
// BFME-only operation has not survived, so the bfme prefix records that the
// identity is descriptive; the field layout and argument order are proven by
// the exact call sequence.

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x, y, z;
};

class GeometryInfo
{
public:
	Bool bfmeIntersects( const Coord3D &thisPosition, Real thisAngle,
		const GeometryInfo &otherGeometry, const Coord3D &otherPosition,
		Real otherAngle ) const;

private:
	unsigned char m_unmodelled[ 0x20 ];
};

class Object
{
public:
	Bool bfmeGeometryIntersects( const Object *other ) const;

private:
	unsigned char m_unmodelled_000[ 0x38 ];
	Coord3D m_position;                                  // +0x38
	Real m_orientation;                                 // +0x44
	unsigned char m_unmodelled_048[ 0x64 ];
	GeometryInfo m_geometryInfo;                         // +0xAC
};

// ?bfmeGeometryIntersects@Object@@QBE_NPBV1@@Z
Bool Object::bfmeGeometryIntersects( const Object *other ) const
{
	// These temporaries preserve retail's VC7.1 x87 spill and push order.
	Real otherAngle = other->m_orientation;
	Real thisAngle = m_orientation;
	return m_geometryInfo.bfmeIntersects( m_position, thisAngle,
		other->m_geometryInfo, other->m_position, otherAngle );
}
