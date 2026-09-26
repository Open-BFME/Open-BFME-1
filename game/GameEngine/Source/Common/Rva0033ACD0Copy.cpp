// cl: /O2 /Ob0

class Rva0033CopyBase
{
public:
	Rva0033CopyBase(const Rva0033CopyBase &other);

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
	: Rva0033CopyBase(other)
	, m_08(other.m_08)
{
}
