// cl: /DNDEBUG /MD /EHsc /I game/Libraries/Source/WWVegas/WWLib /I game/Libraries/Source/WWVegas/WWMath /I game/Libraries/Source/WWVegas/WWDebug /I game/Libraries/Source/WWVegas/WWSaveLoad /I game/Libraries/Include
// 0x002218A0 (142 B): reached through ILT 0x000087EC from slot 42 (+0xA8) of
// the secondary vtable 0x010AB140, which the ContestableContain constructors
// install. The inherited interface and the method's original name are not
// proven, so the owner, argument and method keep the address token.
// this-0x1c and this-0x18 are the two owner pointers ahead of the subobject.
// The argument's +0x08 float block is read as Matrix3D::Get_X_Vector reads
// it and +0x38 is a three-float position (Thing's layout witness places
// m_transform at +0x08 and m_cachedPos at +0x38), but the argument type is
// not proven to be a Thing.

#include "matrix3d.h"

struct Rva002218A0Coord
{
	float x, y, z;

	void set(const Rva002218A0Coord *a)
	{
		x = a->x;
		y = a->y;
		z = a->z;
	}

	void sub(const Rva002218A0Coord *a)
	{
		x -= a->x;
		y -= a->y;
		z -= a->z;
	}
};

class Rva002218A0Argument
{
public:
	unsigned char m_head[8];
	Matrix3D m_matrix08;
	Rva002218A0Coord m_coord38;
};

class Rva002218A0Info
{
public:
	unsigned char m_head[0x138];
	float m_float138;
};

class Rva002218A0Other
{
public:
	unsigned char m_head[0x38];
	Rva002218A0Coord m_coord38;
};

class Rva002218A0Subobject
{
public:
	char Rva002218A0(const Rva002218A0Argument *arg) const;
};

// ?Rva002218A0@Rva002218A0Subobject@@QBEDPBVRva002218A0Argument@@@Z
char Rva002218A0Subobject::Rva002218A0(const Rva002218A0Argument *arg) const
{
	if (arg == 0)
		return 0;

	const Rva002218A0Info *info = *(Rva002218A0Info *const *)((const char *)this - 0x1c);
	if (info->m_float138 < 0.0f)
		return 0;

	const Rva002218A0Other *other = *(Rva002218A0Other *const *)((const char *)this - 0x18);
	if (arg->m_coord38.z - other->m_coord38.z > info->m_float138)
		return 0;

	Vector3 dir = arg->m_matrix08.Get_X_Vector();
	Rva002218A0Coord delta;
	delta.set(&other->m_coord38);
	delta.sub(&arg->m_coord38);
	delta.z = 0.0f;

	if (Vector3::Dot_Product(dir, Vector3(delta.x, delta.y, delta.z)) < 0.0f)
		return 0;

	return 1;
}
