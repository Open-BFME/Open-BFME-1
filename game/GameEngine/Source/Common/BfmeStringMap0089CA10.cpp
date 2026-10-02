// cl: /O2 /DNDEBUG /MD
// Open-address string-map find at retail 0x0089CA10: hashes the key into a
// bucket, then probes up to 8 slots forward and 8 backward inside the table.

// The shared empty EA string block at 0x012D5298 is one global, EA's
// EAStringC::StringDataC g_rva012D5298Empty (defined in
// game/GameEngine/Source/Common/Data/Rva012D5298.cpp).  MSVC mangles the type
// into a global's name, so the reference must carry that exact spelling; the
// TU-local BfmeStringData0089CA10 view is only reached through a cast.
class EAStringC
{
public:
	class StringDataC;
};
extern EAStringC::StringDataC g_rva012D5298Empty;

int __cdecl bfmeCompareVSC(const char *left, const char *right);

struct BfmeStringData0089CA10
{
	unsigned short m_refCount;
	unsigned short m_size;
	unsigned short m_maxSize;
	unsigned short m_hash;
};

static inline BfmeStringData0089CA10 *localEmptyString1285()
{
	return reinterpret_cast<BfmeStringData0089CA10 *>(&g_rva012D5298Empty);
}

struct BfmeStringKey0089CA10
{
	BfmeStringData0089CA10 *m_data;
};

struct BfmeStringEntry0089CA10
{
	BfmeStringData0089CA10 *m_data;
	void *m_value;
};

class BfmeStringMap0089CA10
{
	int m_count;
	BfmeStringEntry0089CA10 *m_entries;

public:
	BfmeStringEntry0089CA10 *findInMap0089CA10(const BfmeStringKey0089CA10 &key);
};

static inline bool matchEntry0089CA10(
	const BfmeStringEntry0089CA10 *entry, const BfmeStringKey0089CA10 &key)
{
	if (entry->m_data == key.m_data)
		return true;
	if (entry->m_data->m_hash != key.m_data->m_hash)
		return false;
	return bfmeCompareVSC(reinterpret_cast<const char *>(entry->m_data) + 8,
		reinterpret_cast<const char *>(key.m_data) + 8) == 0;
}

BfmeStringEntry0089CA10 *BfmeStringMap0089CA10::findInMap0089CA10(const BfmeStringKey0089CA10 &key)
{
	unsigned short keyHash = key.m_data->m_hash;
	int bucket = (m_count - 1) & keyHash;
	BfmeStringData0089CA10 *data = m_entries[bucket].m_data;
	if (data == 0)
		return 0;
	if (data != localEmptyString1285()
		&& matchEntry0089CA10(&m_entries[bucket], key))
		return &m_entries[bucket];
	int start = bucket - 8;
	int high;
	if (start < 0)
	{
		start = 0;
		high = 16;
		if (m_count <= 16)
			high = m_count - 1;
	}
	else
	{
		high = bucket + 8;
		if (high > m_count - 1)
		{
			high = m_count - 1;
			start = high - 16;
			if (start < 0)
				start = 0;
		}
	}
	int cursor = bucket;
	int forward = high - bucket;
	while (forward != 0)
	{
		--forward;
		++cursor;
		data = m_entries[cursor].m_data;
		if (data == 0)
			return 0;
		if (data != localEmptyString1285()
			&& matchEntry0089CA10(&m_entries[cursor], key))
			return &m_entries[cursor];
	}
	cursor = bucket;
	int backward = bucket - start;
	while (backward != 0)
	{
		--cursor;
		data = m_entries[cursor].m_data;
		--backward;
		if (data == 0)
			return 0;
		if (data != localEmptyString1285()
			&& matchEntry0089CA10(&m_entries[cursor], key))
			return &m_entries[cursor];
	}
	return 0;
}
