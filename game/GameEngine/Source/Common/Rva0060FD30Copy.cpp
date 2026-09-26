// cl: /O2 /Ob0

class Rva0060FD30Base
{
public:
	Rva0060FD30Base(const Rva0060FD30Base &other);

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
	: Rva0060FD30Base(other)
	, m_0C(other.m_0C)
{
}
