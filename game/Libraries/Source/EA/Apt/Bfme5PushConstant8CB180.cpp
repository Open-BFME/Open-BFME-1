// Read a bytecode constant index and push its referenced value.
class BfmeValue8CB180
{
public:
	virtual void AddRef();
	unsigned m_flags;
};

struct BfmeCursor8CB180
{
	const unsigned char *m_next;
};

struct BfmeState8CB180
{
	int m_count;
	int m_reserved;
	BfmeValue8CB180 **m_stack;
	char m_other[0x54];
	BfmeValue8CB180 **m_constants;
};

void __cdecl bfmePushConstant8CB180(BfmeState8CB180 *state, BfmeCursor8CB180 *cursor)
{
	unsigned char index = *cursor->m_next++;
	BfmeValue8CB180 *value = state->m_constants[index];
	state->m_stack[state->m_count++] = value;
	if (((unsigned char)(value->m_flags >> 30) & 1) == 0)
		value->AddRef();
}
