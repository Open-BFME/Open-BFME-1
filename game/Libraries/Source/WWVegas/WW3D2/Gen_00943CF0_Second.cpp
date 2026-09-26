// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// ?second@Gen_00943CF0@@AAEXPAX000@Z -- retail 0x009433A0, 135 bytes, ret 0x10.
// Called by the matched Gen_00943CF0::process (0x00943CF0) and
// Gen_00943CF0::update (0x009434E0) with the three cell values that
// Gen_00943CF0::first (0x009432B0) computes for a RenderObjClass.
// The body walks a linearised quad tree of 0x1C-byte cells: a count at +0,
// then a MultiListClass at +4 whose Internal_Add (0x009DBF60) takes the
// object's MultiListObjectClass base at +8. update() compares the packed
// value stored at +0x94 with the same three values, so the store is kept as
// the raw offset it already uses.
// Retail keeps the cell walk in ESI: that needs the cell pointer declared
// before the two shifted fields, not after them.
#include "rendobj.h"
#include "multilist.h"

struct Gen_00943CF0_Cell
{
	int count;
	MultiListClass<RenderObjClass> list;
};

class Gen_00943CF0
{
	void second(void *value, void *x, void *y, void *span);

	unsigned char m_unmodelled00[0x18];
	Gen_00943CF0_Cell *m_cells18;
	unsigned m_dword1C;
	unsigned m_unmodelled20;
	unsigned m_dword24;
};

void Gen_00943CF0::second(void *value, void *x, void *y, void *span)
{
	Gen_00943CF0_Cell *cell = m_cells18;
	unsigned bit = m_dword24 >> 1;
	unsigned stride = m_dword1C >> 2;
	while (stride != 0) {
		if (((unsigned)span & bit) != 0)
			break;
		++cell->count;
		int index = ((unsigned)x & bit) != 0;
		index += ((unsigned)y & bit) ? 2 : 0;
		cell += index * stride + 1;
		stride >>= 2;
		bit >>= 1;
	}
	RenderObjClass *object = (RenderObjClass *)value;
	cell->list.Add(object, false);
	*(unsigned *)((char *)value + 0x94) =
		((unsigned)x << 20) | ((unsigned)y << 10) | (unsigned)span;
}
