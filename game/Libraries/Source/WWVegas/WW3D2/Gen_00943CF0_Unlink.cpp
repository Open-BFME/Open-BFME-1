// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// ?unlink@Gen_00943CF0@@AAEXPAX@Z -- retail 0x00943430, 166 bytes, ret 4.
// Inverse of Gen_00943CF0::second (0x009433A0): the packed value stored at
// object+0x94 (x << 20 | y << 10 | span) is unpacked, the same linearised
// quad-tree walk of 0x1C-byte cells decrements each visited cell's count, and
// the object is removed from the final cell's MultiListClass
// (Internal_Remove at 0x009DC100). The object's 0x94 slot is then reset to -1.
// The two masked fields compile through the signed-modulo shape, so they are
// taken from an int.
#include "rendobj.h"
#include "multilist.h"

struct Gen_00943CF0_Cell
{
	int count;
	MultiListClass<RenderObjClass> list;
};

class Gen_00943CF0
{
	void unlink(void *value);

	unsigned char m_unmodelled00[0x18];
	Gen_00943CF0_Cell *m_cells18;
	unsigned m_dword1C;
	unsigned m_unmodelled20;
	unsigned m_dword24;
};

void Gen_00943CF0::unlink(void *value)
{
	int packed = *(int *)((char *)value + 0x94);
	int x = packed >> 20;
	int y = (packed >> 10) % 1024;
	int span = packed % 1024;
	unsigned bit = m_dword24 >> 1;
	Gen_00943CF0_Cell *cell = m_cells18;
	unsigned stride = m_dword1C >> 2;
	while (stride != 0) {
		if ((span & bit) != 0)
			break;
		--cell->count;
		int index = (x & bit) != 0;
		index += (y & bit) ? 2 : 0;
		cell += index * stride + 1;
		stride >>= 2;
		bit >>= 1;
	}
	RenderObjClass *object = (RenderObjClass *)value;
	cell->list.Remove(object);
	*(int *)((char *)value + 0x94) = -1;
}
