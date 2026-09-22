// ?transformPointsAt0018F660@Gen_0018F210@@QAEXPBVMatrix3D@@@Z
// partial score=0.961 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath
// Address-derived BFME5 Vector3 transform body at retail RVA 0x0018F660.
// Same indexed Vector3 storage family as 0x0018F540 and 0x0018F5A0
// (Gen_0018F210: values at +0x10, count at +0x14, dirty flag at +0x30).
#include "matrix3d.h"

struct BfmeVector3BG
{
	int x;
	int y;
	int z;
};

class Gen_0018F210
{
public:
	void transformPointsAt0018F660(const Matrix3D *matrix);

private:
	char m_head[0x10];
	BfmeVector3BG *m_values;
	int m_count;
	int m_capacity;
	char m_gap[0x14];
	bool m_valuesDirty;
};

void Gen_0018F210::transformPointsAt0018F660(const Matrix3D *matrix)
{
	if (!matrix) {
		return;
	}

	const Matrix3D &A = *matrix;
	const Vector4 &R0 = A[0], &R1 = A[1], &R2 = A[2];

	for (int i = 0; i < m_count; ++i) {
		Vector3 input((float)m_values[i].x, (float)m_values[i].y, (float)m_values[i].z);

		// Matrix3D::Transform_Vector's aliased path: in and out are the same
		// vector, so the source is read back through a copy.
		Vector3 tmp = input;
		Vector3 *v = &tmp;

		input.X = (R0[0] * v->X + R0[1] * v->Y + R0[2] * v->Z + R0[3]);
		input.Y = (R1[0] * v->X + R1[1] * v->Y + R1[2] * v->Z + R1[3]);
		input.Z = (R2[0] * v->X + R2[1] * v->Y + R2[2] * v->Z + R2[3]);

		m_values[i].x = (int)input.X;
		m_values[i].y = (int)input.Y;
		m_values[i].z = (int)input.Z;
	}

	m_valuesDirty = true;
}
