// This address-derived transform sits at retail RVA 0x0018F660. The only
// decoded caller remains a generated dump, so the type name keeps the RVA.
// The landed vector mutators at 0x0018F540 and 0x0018F5A0 establish these
// three-int elements and the storage fields at +0x10, +0x14, +0x18, and +0x30.
// Retail combines the row-zero Z and X products before it adds Y. The
// parentheses below preserve that x87 evaluation order.
// cl: /DNDEBUG /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath

#include "matrix3d.h"

struct BfmeVector3BG
{
	int x;
	int y;
	int z;
};

class Rva0018F660
{
public:
	void transformPoints(const Matrix3D *matrix);

private:
	char m_head[0x10];
	BfmeVector3BG *m_values;
	int m_count;
	int m_capacity;
	char m_gap[0x14];
	bool m_valuesDirty;
};

void Rva0018F660::transformPoints(const Matrix3D *matrix)
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

		input.X = ((R0[2] * v->Z + R0[0] * v->X) + R0[1] * v->Y) + R0[3];
		input.Y = (R1[0] * v->X + R1[1] * v->Y + R1[2] * v->Z + R1[3]);
		input.Z = (R2[0] * v->X + R2[1] * v->Y + R2[2] * v->Z + R2[3]);

		m_values[i].x = (int)input.X;
		m_values[i].y = (int)input.Y;
		m_values[i].z = (int)input.Z;
	}

	m_valuesDirty = true;
}
