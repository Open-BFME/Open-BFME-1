// Duplicate a stack top and retain its counted value unless saturated.
class BfmeValue8C9DE0
{
public:
	virtual void addRef();
	unsigned m_flags;
};

struct BfmeStack8C9DE0
{
	int m_count;
	int m_reserved;
	BfmeValue8C9DE0 **m_values;
};

void __cdecl bfmeDuplicateStackTop8C9DE0(BfmeStack8C9DE0 *stack)
{
	BfmeValue8C9DE0 *value = stack->m_values[stack->m_count - 1];
	stack->m_values[stack->m_count++] = value;
	if (((unsigned char)(value->m_flags >> 30) & 1) == 0)
		value->addRef();
}
