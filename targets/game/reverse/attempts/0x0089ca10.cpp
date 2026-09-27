// ?d_0089ca10@@YAXXZ
// partial score=0.69 date=2026-09-27
// cl: /O2 /DNDEBUG /MD
// Banked near-miss for 0x0089CA10 (395B): open-address string-map find with
// an 8-slot forward/backward window around the hashed bucket.
// Reaches 395B with shape 0.689 but the frame prologue drifts
// (retail: mov eax,[esp+4]; mov eax,[eax]; sub esp,8 + bx hash load;
// ours: larger sub + cx load). Root cause unresolved: frame/blocker.

extern "C" char g_bfmeEmptyString1285[];
int __cdecl bfmeCompareVSC(const char *left, const char *right);

struct BfmeStringData0089CA10
{
	unsigned short m_refCount;
	unsigned short m_size;
	unsigned short m_maxSize;
	unsigned short m_hash;
};

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

static __forceinline int matchEntry0089CA10(
	BfmeStringData0089CA10 *data, const BfmeStringData0089CA10 *keyData)
{
	if (data == keyData)
		return 1;
	if (data->m_hash != keyData->m_hash)
		return 0;
	volatile unsigned char equal = (unsigned char)(bfmeCompareVSC(
		reinterpret_cast<const char *>(data) + 8,
		reinterpret_cast<const char *>(keyData) + 8) == 0);
	return equal;
}

BfmeStringEntry0089CA10 *BfmeStringMap0089CA10::findInMap0089CA10(const BfmeStringKey0089CA10 &key)
{
	BfmeStringData0089CA10 *keyData = key.m_data;
	unsigned short keyHash = keyData->m_hash;
	unsigned int bucket = (unsigned int)(m_count - 1) & keyHash;
	BfmeStringEntry0089CA10 *entry = m_entries + bucket;
	BfmeStringData0089CA10 *data = entry->m_data;
	if (data == 0)
		return 0;
	if (data != reinterpret_cast<BfmeStringData0089CA10 *>(g_bfmeEmptyString1285)
		&& matchEntry0089CA10(data, keyData))
		return entry;
	int start = (int)bucket - 8;
	int high;
	if (start < 0)
	{
		start = 0;
		high = 0x10;
		if (m_count < 0x11)
			high = m_count - 1;
	}
	else
	{
		high = (int)bucket + 8;
		if (m_count - 1 < high)
		{
			high = m_count - 1;
			start = high - 0x10;
			if (start < 0)
				start = 0;
		}
	}
	int forward = high - (int)bucket;
	unsigned int cursor = bucket;
	if (forward != 0)
	{
		do
		{
			--forward;
			++cursor;
			entry = m_entries + cursor;
			data = entry->m_data;
			if (data == 0)
				return 0;
			if (data != reinterpret_cast<BfmeStringData0089CA10 *>(g_bfmeEmptyString1285)
				&& matchEntry0089CA10(data, keyData))
				return entry;
		} while (forward != 0);
	}
	int backward = (int)bucket - start;
	cursor = bucket;
	while (backward != 0)
	{
		--cursor;
		entry = m_entries + cursor;
		data = entry->m_data;
		--backward;
		if (data == 0)
			return 0;
		if (data == reinterpret_cast<BfmeStringData0089CA10 *>(g_bfmeEmptyString1285))
			continue;
		if (matchEntry0089CA10(data, keyData))
			return entry;
	}
	return 0;
}
