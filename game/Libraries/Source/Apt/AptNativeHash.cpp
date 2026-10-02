// cl: /O2 /DNDEBUG /MD

struct BfmeIterator1285
{
	void *m_data;
	void *m_extra;
};

// The shared empty string block at 0x012D5298, defined once in
// game/GameEngine/Source/Common/Data/Rva012D5298.cpp.  Only its address is
// compared against here.
class EAStringC
{
public:
	class StringDataC;
};

extern EAStringC::StringDataC g_rva012D5298Empty;

class BfmeIteratorList1285
{
	int m_count;
	BfmeIterator1285 *m_array;

public:
	BfmeIterator1285 *bfmeNext1285(BfmeIterator1285 *cur);
};

BfmeIterator1285 *BfmeIteratorList1285::bfmeNext1285(BfmeIterator1285 *cur)
{
	BfmeIterator1285 *arr = m_array;
	if (arr == 0)
		return 0;

	BfmeIterator1285 *p = cur + 1;
	BfmeIterator1285 *end = arr + m_count;
	if (p >= end)
		return 0;

	do
	{
		void *data = p->m_data;
		if (data != 0 && data != (void *)&g_rva012D5298Empty)
			return p;
		++p;
	}
	while (p < end);

	return 0;
}
