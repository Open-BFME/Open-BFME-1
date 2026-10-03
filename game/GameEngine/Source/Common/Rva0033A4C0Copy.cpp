// cl: /O2 /Ob0

// Retail 0x0033A4C0 calls the ILT thunk at 0x0001AB86, defined as
// ?j_0001ab86@@YAXXZ in game/gen_small/thunks_012.cpp and nothing else. The
// base copy is therefore routed through the thunk's own address; see
// Rva0033A4F0Copy.cpp for the same shape.
extern void j_0001ab86();

class Rva0033CopyBase
{
private:
	char m_pad[8];
};

class Rva0033A4C0 : public Rva0033CopyBase
{
	int m_08;
	int m_0C;

public:
	Rva0033A4C0(const Rva0033A4C0 &other);
};

Rva0033A4C0::Rva0033A4C0(const Rva0033A4C0 &other)
{
	typedef void (Rva0033CopyBase::*CopyCall)(const Rva0033CopyBase &);
	union { void (*address)(); CopyCall member; } copy = { j_0001ab86 };
	(static_cast<Rva0033CopyBase *>(this)->*copy.member)(other);
	m_08 = other.m_08;
	m_0C = other.m_0C;
}
