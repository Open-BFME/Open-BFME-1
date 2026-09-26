// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef float Real;

extern "C" double __cdecl sqrt(double value);
#pragma intrinsic(sqrt)

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}

	Real x, y, z;

	Real length( void ) const { return (Real)sqrt( x*x + y*y + z*z ); }

	// BFME's Coord3D::Scale(const Coord3DBase &, float); its out-of-line copy
	// is the matched ?Scale@Coord3D@@QAEAAV1@ABUCoord3DBase@@M@Z at 0x007E5D70.
	Coord3D &Scale( const Coord3D &that, Real scale )
	{
		x = that.x * scale;
		y = that.y * scale;
		z = that.z * scale;
		return *this;
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	// Weapon::computeApproachTarget (0x001E43D0) calls this on the target with
	// the source where Zero Hour asks ThePartitionManager->getVectorTo.
	Coord3D rva001E3E40(const Object *other) const;

	// Pinned at 0x001E3E20 (reached through ILT 0x0000B069).
	Coord3D getPlanarDirectionTo(const Object *other) const;

private:
	unsigned char m_fields[0xbc];
	Real m_real0BC;					// +0x0BC
};

// The planar delta to `other`, shortened by both objects' +0xBC radii; zero
// when those radii overlap.
Coord3D Object::rva001E3E40(const Object *other) const
{
	Coord3D delta = getPlanarDirectionTo(other);
	Real dist = delta.length();
	Real radii = other->m_real0BC + m_real0BC;
	Coord3D result;
	if (dist <= radii)
	{
		result.x = 0.0f;
		result.y = 0.0f;
		result.z = 0.0f;
	}
	else
	{
		result.Scale(delta, (dist - radii) / dist);
	}
	return result;
}
