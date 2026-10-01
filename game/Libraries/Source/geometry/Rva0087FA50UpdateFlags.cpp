// cl: /O2 /G6

typedef int Int;
typedef unsigned short UnsignedShort;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);


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
    BfmeAsciiDataF9 *m_data;
};

// Local helpers avoid emitting shared BfmeStrF9 COMDAT copies.
static __forceinline Int getLength(const BfmeStrF9 &value)
{
    return value.m_data ? value.m_data->m_len : 0;
}

static __forceinline const char *str(const BfmeStrF9 &value)
{
    return value.m_data ? (const char *)(value.m_data + 1) : "";
}

static __forceinline Int compare(const BfmeStrF9 &value, const BfmeStrF9 &other)
{
    Int lenOther = getLength(other);
    const char *pOther = str(other);
    Int lenThis = getLength(value);
    const char *pThis = str(value);
    Int shorter = lenThis < lenOther ? lenThis : lenOther;
    Int diff = memcmp(pThis, pOther, shorter);
    if (diff)
        return diff;
    return lenThis - lenOther;
}

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
		found |= compare(shape->m_1C, name) == 0 && shape->m_20;
	}
	if (!found)
		return;
	for (BfmeShapeF9 *shape = m_start; shape != m_finish; ++shape)
	{
		if (!(compare(shape->m_1C, name) == 0))
			shape->m_20 = flag;
	}
}
