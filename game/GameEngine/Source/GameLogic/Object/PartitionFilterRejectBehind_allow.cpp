// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug

#include "../../../../Libraries/Source/WWVegas/WWMath/matrix3d.h"

typedef bool Bool;
typedef float Real;

#define BfmeZeroRange (*(const Real *)0x01075350)

class BfmeDeltaOwner
{
public:
	void bfmeDeltaTo(void *one, char *two);
};

#pragma comment(linker, "/alternatename:?bfmeDeltaTo@BfmeDeltaOwner@@QAEXPAXPAD@Z=?j_0002eb59@@YAXXZ")

// BFME stores this filter's object pointer at +0x08.
class Object
{
public:
	const Matrix3D *getTransformMatrix(void) const
	{
		return (const Matrix3D *)((const char *)this + 0x08);
	}
};

// The unmodeled word preserves the BFME offset without changing the shared
// PartitionFilter declaration used by the other filter bodies.
class PartitionFilterRejectBehind
{
public:
	virtual Bool allow(Object *other);

private:
	unsigned int m_unreconstructed_04;
	Object *m_obj;
};

// ?allow@PartitionFilterRejectBehind@@UAE_NPAVObject@@@Z
Bool PartitionFilterRejectBehind::allow(Object *other)
{
	Vector3 dir = m_obj->getTransformMatrix()->Get_X_Vector();
	Real len2 = dir.Length2();
	if (len2 != BfmeZeroRange)
		dir *= WWMath::Inv_Sqrt(len2);

	Vector3 v;
	((BfmeDeltaOwner *)m_obj)->bfmeDeltaTo(&v, (char *)other);

	Real dot = dir.X * v.X + dir.Y * v.Y + dir.Z * v.Z;
	if (dot > BfmeZeroRange)
		return true;

	return false;
}
