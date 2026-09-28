// ?d_009138d0@@YAXXZ
// partial score=0.57 date=2026-09-28
// Banked near miss for retail 0x009138D0 (51 bytes). Shape 0.57: the
// vector/resize/CopyIndexed logic is right but retail enters with source in
// EBX, vector in ESI and count in EDI with no frame - a compiler-private
// register ABI that needs its same-TU caller context to inherit.
#include "vector4.h"
#include "vp.h"
class Rva009138D0Vector
{
public:
	virtual bool Resize(int newsize, const Vector4 *array = 0);
	Vector4 *m_data;
	int m_count;
	int m_capacity;
};
class Rva009138D0Source
{
public:
	const Vector4 *m_data;
	int m_pad;
	int m_indexData;
};
Vector4 *__fastcall Rva009138D0Copy(Rva009138D0Vector *vector, Rva009138D0Source *source,
	int count, const unsigned int *index)
{
	if (source == 0)
	{
		return 0;
	}
	if (vector->m_capacity < count)
	{
		vector->Resize(count * 2, 0);
	}
	VectorProcessorClass::CopyIndexed(vector->m_data, source->m_data, index, count);
	return vector->m_data;
}
