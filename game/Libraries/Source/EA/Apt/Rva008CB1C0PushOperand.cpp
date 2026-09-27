// cl: /DNDEBUG /MD /EHsc
// Two Apt bytecode handlers beside Rva008CB260AppendToken (0x008CB260).
// Address-derived identity: each reads an inline operand from *reader->m_pos
// (advancing the cursor), finds or makes a value node, appends it to the
// target's count/array pair, then returns if bit 30 of the node's flag word
// is set or else tail-dispatches the node's first virtual function.
//
// 0x008CB1C0: two-byte operand indexes the node table at +0x60.
// 0x008CB200: four-byte float operand goes through Rva008A4EA0MakeFloat.

struct Rva008CB1C0Reader
{
	char *m_pos;
};

struct Rva008CB1C0Node
{
	virtual void invoke();
	unsigned int m_flags;
};

class AptValue;
AptValue *__cdecl Rva008A4EA0MakeFloat(float value);

struct Rva008CB1C0Target
{
	int m_count;
	void *m_pad4;
	Rva008CB1C0Node **m_items;
	char m_padC[0x54];
	Rva008CB1C0Node **m_table;
};

// ?rva008CB1C0PushIndexed@@YAXPAURva008CB1C0Target@@PAURva008CB1C0Reader@@@Z
void rva008CB1C0PushIndexed(Rva008CB1C0Target *target, Rva008CB1C0Reader *reader)
{
	unsigned short index;
	char *pos = reader->m_pos;
	((char *)&index)[0] = *pos++;
	((char *)&index)[1] = *pos++;
	reader->m_pos = pos;

	Rva008CB1C0Node *node = target->m_table[index];
	target->m_items[target->m_count] = node;
	target->m_count++;

	unsigned char flags = (unsigned char)(node->m_flags >> 30);
	if (flags & 1)
		return;

	node->invoke();
}

// ?rva008CB200PushFloat@@YAXPAURva008CB1C0Target@@PAURva008CB1C0Reader@@@Z
void rva008CB200PushFloat(Rva008CB1C0Target *target, Rva008CB1C0Reader *reader)
{
	float value;
	char *pos = reader->m_pos;
	((char *)&value)[0] = *pos++;
	((char *)&value)[1] = *pos++;
	((char *)&value)[2] = *pos++;
	((char *)&value)[3] = *pos++;
	reader->m_pos = pos;

	Rva008CB1C0Node *node = (Rva008CB1C0Node *)Rva008A4EA0MakeFloat(value);
	target->m_items[target->m_count] = node;
	target->m_count = target->m_count + 1;

	unsigned char flags = (unsigned char)(node->m_flags >> 30);
	if (flags & 1)
		return;

	node->invoke();
}
