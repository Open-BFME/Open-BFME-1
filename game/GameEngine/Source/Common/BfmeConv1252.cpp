// Open-BFME5 conversions.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath

#include "../../../Libraries/Source/WWVegas/WWMath/colmath.h"

struct BfmeVec1252
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

class BfmeV1252
{
public:
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
	int m_bfme0c;
};

void get_far_extent(const Vector3 &normal, const Vector3 &extent,
	Vector3 *posfarpt);

int bfmeTest1252(void *a, BfmeV1252 *b)
{
	BfmeVec1252 t;

	get_far_extent(*reinterpret_cast<const Vector3 *>(a),
		*reinterpret_cast<const Vector3 *>(&b->m_bfme0c),
		reinterpret_cast<Vector3 *>(&t));
	t.m_bfme00 = b->m_bfme00 - t.m_bfme00;
	t.m_bfme04 = b->m_bfme04 - t.m_bfme04;
	t.m_bfme08 = b->m_bfme08 - t.m_bfme08;
	return CollisionMath::Overlap_Test(
		*reinterpret_cast<const PlaneClass *>(a),
		*reinterpret_cast<const Vector3 *>(&t)) == 1;
}
