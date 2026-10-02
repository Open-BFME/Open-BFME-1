// cl: /O2 /Ob0

void j_0001ab86();

class Rva0033CopyBase
{
private:
	char m_pad[8];
};

class Rva0033ACD0 : public Rva0033CopyBase
{
	char m_08;

public:
	Rva0033ACD0(const Rva0033ACD0 &other);
};

Rva0033ACD0::Rva0033ACD0(const Rva0033ACD0 &other)
{
	typedef void (Rva0033CopyBase::*CopyCall)(const Rva0033CopyBase &);
	union { void (*address)(); CopyCall member; } copy = { j_0001ab86 };
	(static_cast<Rva0033CopyBase *>(this)->*copy.member)(other);
	m_08 = other.m_08;
}
