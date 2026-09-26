// cl: /O2 /Ob0

class Inner001B49C0
{
public:
	char pad[0x5C];
	unsigned char m_5C;
};

class Obj001B49C0
{
public:
	char pad[0x208];
	Inner001B49C0 *m_208;
};

unsigned char __stdcall rva001b49c0(Obj001B49C0 *p)
{
	if (p->m_208)
		return p->m_208->m_5C;
	return 0;
}
