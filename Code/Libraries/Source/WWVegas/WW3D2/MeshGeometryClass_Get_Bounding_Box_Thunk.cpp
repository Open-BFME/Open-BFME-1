// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the MeshGeometryClass::Get_Bounding_Box naked dump to clean C++.
//
// Zero Hour's meshgeometry.cpp body. The WWASSERT is a no-op under NDEBUG and
// retail has no trace of it, so the two assignments are the whole function.
//
// The subtraction fixes the layout: `fld [ecx+0x74] / fsub [ecx+0x68]` puts
// BoundBoxMax at +0x74 and BoundBoxMin at +0x68.
//
// The addition does not read off as directly. MSVC does not emit the operands
// in source order and is not even consistent between components -- for
// Max + Min it loads Min.X first but Max.Y and Max.Z first. So an operand order
// that looks wrong for one component is not evidence; only flipping the whole
// expression and re-comparing settles it, and ZH's Max + Min is what matches.
//
// The twelve bytes of frame are one Vector3 temporary: each expression keeps
// its X component in st(0) and spills Y and Z, which is why the stores to the
// destination come out fxch'd rather than in order.
//
// Retail pins the layout: the bounds live at this+0x68 and this+0x74, and the
// box's Center and Extent are at +0x00 and +0x0C.

// Vector3 replicated from the reference WWMath header rather than hand-rolled:
// the user-defined copy constructor and assignment operator, and constructor
// bodies that assign rather than use an initialiser list, are what let MSVC
// keep each component in the FPU instead of round-tripping the temporaries
// through memory with integer moves.
class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3(void) {};
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }

	Vector3 &operator = (const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }

	friend Vector3 operator * (const Vector3 &a, float k);
	friend Vector3 operator + (const Vector3 &a, const Vector3 &b);
	friend Vector3 operator - (const Vector3 &a, const Vector3 &b);
};

inline Vector3 operator * (const Vector3 &a, float k)
{
	return Vector3((a.X * k), (a.Y * k), (a.Z * k));
}

inline Vector3 operator + (const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}

inline Vector3 operator - (const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/aabox.h
class AABoxClass
{
public:
	Vector3 Center;										///< retail this+0x00
	Vector3 Extent;										///< retail this+0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshgeometry.h
class MeshGeometryClass
{
public:
	void Get_Bounding_Box(AABoxClass *set_box);

private:
	unsigned char m_unreconstructed_00[0x68];
	Vector3 BoundBoxMin;								///< retail this+0x68
	Vector3 BoundBoxMax;								///< retail this+0x74
};

// ?Get_Bounding_Box@MeshGeometryClass@@QAEXPAVAABoxClass@@@Z
void MeshGeometryClass::Get_Bounding_Box(AABoxClass *set_box)
{
	set_box->Center = (BoundBoxMax + BoundBoxMin) * 0.5f;
	set_box->Extent = (BoundBoxMax - BoundBoxMin) * 0.5f;
}
