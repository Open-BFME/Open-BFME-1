// cl: /O2 /Ob0

// 0x0001AB86 is retail's 5-byte ILT thunk (?j_0001ab86@@YAXXZ); the base
// copy constructor's own identity is not recovered, so the __thiscall is
// routed through the thunk's address.
void j_0001ab86();

class Rva0033CopyBase
{
private:
	char m_pad[8];
};

class Rva0033ACA0 : public Rva0033CopyBase
{
	int m_08;
	int m_0C;

public:
	Rva0033ACA0(const Rva0033ACA0 &other);
};

Rva0033ACA0::Rva0033ACA0(const Rva0033ACA0 &other)
{
	typedef void (Rva0033CopyBase::*CopyCall)(const Rva0033CopyBase &);
	union { void (*address)(); CopyCall member; } copy = { j_0001ab86 };
	(static_cast<Rva0033CopyBase *>(this)->*copy.member)(other);
	m_08 = other.m_08;
	m_0C = other.m_0C;
}
