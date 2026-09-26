// Push an integer Apt value created from the process-global seed.
class AptInteger
{
public:
	virtual void AddRef();
	static AptInteger *Create(int value);
	unsigned m_flags;
};

extern int g_rva00891FA0Value;

struct BfmeStack8C8120
{
	int m_count;
	int m_reserved;
	AptInteger **m_values;
};

void __cdecl bfmePushInteger8C8120(BfmeStack8C8120 *stack)
{
	AptInteger *value = AptInteger::Create(g_rva00891FA0Value);
	stack->m_values[stack->m_count++] = value;
	if (((unsigned char)(value->m_flags >> 30) & 1) == 0)
		value->AddRef();
}
