// cl: /DNDEBUG /MD /EHsc /O2 /Ob0
//
// Open-BFME: retail 0x000EC440 size 31. __thiscall predicate: true if the
// pointer field at this+0x274 equals the argument, or if either dword at
// arg+0x10 / arg+0x14 is non-zero; false otherwise. All three "true" exits
// converge on the same retail "mov eax,1 / ret 4" tail, which retail's
// linker folded together with W3DShadowGeometry::init()'s identical
// "return TRUE;" body (0x000EC45F, already matched as dup_000ec45f) --
// coincidence of identical code, not a real call relationship.

struct Rva000EC440Arg
{
	char m_pad[0x10];
	void *m_f10;
	void *m_f14;
};

class Rva000EC440Host
{
public:
	char m_pad[0x274];
	Rva000EC440Arg *m_at274;

	int method(Rva000EC440Arg *arg);
};

int Rva000EC440Host::method(Rva000EC440Arg *arg)
{
	if (m_at274 != arg)
	{
		if (!arg->m_f10)
		{
			if (!arg->m_f14)
				return 0;
		}
	}
	return 1;
}
