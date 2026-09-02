// ?choose@Rva0020DAD0Thing@@QBEHXZ
// partial score=0.95 date=2026-09-02
// cl: /O2
// Open-BFME: 43-byte flag select at retail 0x0020DAD0. Holder at this+8,
// inner triple at holder+0x90. The 12-byte frame is a by-value triple whose
// middle dword is CSE'd into the flag test, so only first and third are stored.
// /O2 emits add-eax (5B) + mov-ecx,eax (2B) = 7B versus retail add-ecx (6B).

struct Rva0020DAD0Triple
{
	int m_first;
	int m_flags;
	int m_third;

	int pick() const
	{
		Rva0020DAD0Triple t = *this;
		return (t.m_flags & 0x40) ? 0x1e : 0x14;
	}
};

struct Rva0020DAD0Holder
{
	char m_pad[0x90];
	Rva0020DAD0Triple m_inner;
};

class Rva0020DAD0Thing
{
public:
	int choose() const;

private:
	char m_pad[8];
	Rva0020DAD0Holder *m_holder;
};

int Rva0020DAD0Thing::choose() const
{
	return m_holder->m_inner.pick();
}
