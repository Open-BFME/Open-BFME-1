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
	BfmeIterator1285 *bfmeFirst1285();
};

BfmeIterator1285 *BfmeIteratorList1285::bfmeFirst1285()
{
	BfmeIterator1285 *array = m_array;
	if (array == 0)
		return 0;

	int count = m_count;
	const BfmeIterator1285 *walk;
	int index = 0;
	if (count > 0)
	{
		walk = array;
		for (; index < count; ++index, ++walk)
		{
			void *data = walk->m_data;
			if (data != 0 && data != (void *)&g_rva012D5298Empty)
				return array + index;
		}
	}
	return 0;
}
