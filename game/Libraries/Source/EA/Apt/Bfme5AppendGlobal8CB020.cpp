// Append a process-global value to an Apt interpreter stack.
class BfmeValue8CB020
{
public:
	virtual void AddRef();
	unsigned m_flags;
};

struct Rva00899C20Registry;
extern Rva00899C20Registry *g_Va013387D8;

struct BfmeStack8CB020
{
	int m_count;
	int m_reserved;
	BfmeValue8CB020 **m_values;
};

void __cdecl bfmeAppendGlobal8CB020(BfmeStack8CB020 *stack)
{
	BfmeValue8CB020 *value = (BfmeValue8CB020 *)g_Va013387D8;
	stack->m_values[stack->m_count++] = value;
	if (((unsigned char)(value->m_flags >> 30) & 1) == 0)
		value->AddRef();
}
