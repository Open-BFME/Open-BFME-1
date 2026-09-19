// cl: /O2 /G6

typedef int Int;
typedef unsigned short UnsignedShort;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);

extern char g_bfmeEmptyF9[];

struct BfmeAsciiDataF9
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

class BfmeStrF9
{
public:
	Int getLength(void) const { return m_data ? m_data->m_len : 0; }
	const char *str(void) const { return m_data ? (const char *)(m_data + 1) : g_bfmeEmptyF9; }

	Int compare(const BfmeStrF9 &other) const
	{
		Int lenOther = other.getLength();
		const char *pOther = other.str();
		Int lenThis = getLength();
		const char *pThis = str();
		Int shorter = lenThis < lenOther ? lenThis : lenOther;
		Int diff = memcmp(pThis, pOther, shorter);
		if (diff)
			return diff;
		return lenThis - lenOther;
	}

	bool operator==(const BfmeStrF9 &rhs) const { return compare(rhs) == 0; }

	BfmeAsciiDataF9 *m_data;
};

struct BfmeShapeF9
{
	int m_pad[7];
	BfmeStrF9 m_1C;
	char m_20;
	char m_pad20[3];
};

class BfmeObjF9
{
public:
	void rva0087FA50(const BfmeStrF9 &name, char flag);

	unsigned char m_pad[0x2C];
	BfmeShapeF9 *m_start;
	BfmeShapeF9 *m_finish;
};

void BfmeObjF9::rva0087FA50(const BfmeStrF9 &name, char flag)
{
	char found = flag;
	for (BfmeShapeF9 *shape = m_start; shape != m_finish; ++shape)
	{
		found |= shape->m_1C == name && shape->m_20;
	}
	if (!found)
		return;
	for (BfmeShapeF9 *shape = m_start; shape != m_finish; ++shape)
	{
		if (!(shape->m_1C == name))
			shape->m_20 = flag;
	}
}
