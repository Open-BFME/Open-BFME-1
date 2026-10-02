// cl: /O2 /Ob0

void j_0000fa3d();

class Rva0060FD30Base
{
private:
	char m_pad[0x0C];
};

class Rva0060FD30 : public Rva0060FD30Base
{
	int m_0C;

public:
	Rva0060FD30(const Rva0060FD30 &other);
};

Rva0060FD30::Rva0060FD30(const Rva0060FD30 &other)
{
	typedef void (Rva0060FD30Base::*CopyCall)(const Rva0060FD30Base &);
	union { void (*address)(); CopyCall member; } copy = { j_0000fa3d };
	(static_cast<Rva0060FD30Base *>(this)->*copy.member)(other);
	m_0C = other.m_0C;
}
