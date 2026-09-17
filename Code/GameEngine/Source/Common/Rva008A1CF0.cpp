// Address-derived identity: the only caller is anonymous ?d_008d3860 and
// there is no named caller, vtable slot, string literal, or witnessed class
// layout for this body.  The offsets below are taken from retail disassembly.
// The body is a thiscall int(int) lookup with inline strcmp and no direct
// retail REL32 callees; the reviewed source probes exact at 135 bytes.
// cl: /O2 /Ob1
extern "C" int strcmp(const char *a, const char *b);

#pragma intrinsic(strcmp)

class Rva008A1CF0Item
{
public:
	const char *m_ptr00;
	int m_value04;
};

class Rva008A1CF0Group
{
public:
	unsigned char m_pad00[0x30];
	int m_count30;
	Rva008A1CF0Item *m_items34;
};

class Rva008A1CF0Owner
{
public:
	unsigned char m_pad00[0x10];
	Rva008A1CF0Group *m_group10;
};

class Rva008A1CF0Slot
{
public:
	void *m_ptr00;
	const char *m_ptr04;
	unsigned char m_pad08[4];
	Rva008A1CF0Owner *m_owner0c;
};

class Rva008A1CF0
{
public:
	int rva008A1CF0(int idx);

	unsigned char m_pad00[0x24];
	Rva008A1CF0Slot *m_table24;
};

int Rva008A1CF0::rva008A1CF0(int idx)
{
	Rva008A1CF0Group *g = m_table24[idx].m_owner0c->m_group10;
	int n = g->m_count30;
	int i = 0;

	if (n > 0)
	{
		Rva008A1CF0Slot *s = &m_table24[idx];
		Rva008A1CF0Item *items = g->m_items34;
		const char *name = s->m_ptr04;
		Rva008A1CF0Item *item = items;

		do
		{
			if (strcmp(name, item->m_ptr00) == 0)
				return items[i].m_value04;

			++i;
			++item;
		}
		while (i < n);
	}

	return -1;
}
