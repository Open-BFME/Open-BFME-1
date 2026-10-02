// Append the global fallback Apt value to an interpreter stack.
class AptValue
{
public:
	virtual void AddRef();
	unsigned m_flags;
};

AptValue *g_bfmeFallbackDB = 0;

struct BfmeStack8CAFF0
{
	int m_count;
	int m_reserved;
	AptValue **m_values;
};

void __cdecl bfmeAppendFallback8CAFF0(BfmeStack8CAFF0 *stack)
{
	AptValue *value = g_bfmeFallbackDB;
	stack->m_values[stack->m_count++] = value;
	if (((unsigned char)(value->m_flags >> 30) & 1) == 0)
		value->AddRef();
}
