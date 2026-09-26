// cl: /O2 /Ob0

class Rva0033CopyBase
{
public:
	Rva0033CopyBase(const Rva0033CopyBase &other);

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
	: Rva0033CopyBase(other)
	, m_08(other.m_08)
	, m_0C(other.m_0C)
{
}
