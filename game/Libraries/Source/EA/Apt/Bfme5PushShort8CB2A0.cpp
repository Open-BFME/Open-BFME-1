// Decode a little-endian signed immediate and push its AptInteger value.
class AptInteger
{
public:
	virtual void AddRef();
	static AptInteger *Create(int value);
	unsigned m_flags;
};

struct BfmeCursor8CB2A0
{
	const unsigned char *m_next;
};

struct BfmeStack8CB2A0
{
	int m_count;
	int m_reserved;
	AptInteger **m_values;
};

void __cdecl bfmePushShort8CB2A0(BfmeStack8CB2A0 *stack, BfmeCursor8CB2A0 *cursor)
{
	short immediate;
	unsigned char *parts = (unsigned char *)&immediate;
	const unsigned char *source = cursor->m_next;
	parts[0] = *source++;
	parts[1] = *source++;
	cursor->m_next = source;
	AptInteger *value = AptInteger::Create(immediate);
	stack->m_values[stack->m_count++] = value;
	if (((unsigned char)(value->m_flags >> 30) & 1) == 0)
		value->AddRef();
}
