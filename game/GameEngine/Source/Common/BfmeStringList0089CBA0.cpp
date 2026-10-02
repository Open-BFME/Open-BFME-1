// cl: /O2 /DNDEBUG /MD

struct BfmeStringData0089CBA0
{
	unsigned short m_refCount;
	unsigned short m_size;
	unsigned short m_maxSize;
	unsigned short m_hash;
};

struct BfmeStringEntry0089CBA0
{
	BfmeStringData0089CBA0 *m_data;
	void *m_value;
};

class BfmeString0089CBA0
{
	BfmeStringData0089CBA0 *m_data;
};

// The shared empty EA string block at 0x012D5298 is defined once, as
// EAStringC::StringDataC, in game/GameEngine/Source/Common/Data/Rva012D5298.cpp;
// this TU only compares its address, through its own local view of the block.
class EAStringC
{
public:
	class StringDataC;
};
extern EAStringC::StringDataC g_rva012D5298Empty;
int bfmeCompareVSC(const char *left, const char *right);

class BfmeStringList0089CBA0
{
	int m_count;
	BfmeStringEntry0089CBA0 *m_array;

public:
	BfmeStringEntry0089CBA0 *find(const BfmeString0089CBA0 &key);
};

BfmeStringEntry0089CBA0 *BfmeStringList0089CBA0::find(const BfmeString0089CBA0 &key)
{
	for (int i = 0; i < m_count; ++i)
	{
		BfmeStringEntry0089CBA0 *entry = m_array + i;
		BfmeStringData0089CBA0 *data = entry->m_data;
		if (data != 0 && data != (BfmeStringData0089CBA0 *)&g_rva012D5298Empty)
		{
			BfmeStringData0089CBA0 *keyData = *reinterpret_cast<BfmeStringData0089CBA0 * const *>(&key);
			if (data == keyData)
				return entry;
			if (data->m_hash == keyData->m_hash)
			{
				volatile unsigned char equal = (unsigned char)(bfmeCompareVSC(
					reinterpret_cast<const char *>(data) + 8,
					reinterpret_cast<const char *>(keyData) + 8) == 0);
				if (equal)
					return entry;
			}
		}
	}
	return 0;
}
