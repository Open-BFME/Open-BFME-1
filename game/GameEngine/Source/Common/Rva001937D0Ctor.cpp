// cl: /O2 /Ob0

class Rva0033CopyBase
{
public:
	Rva0033CopyBase(const Rva0033CopyBase &other);

private:
	char m_pad[8];
};

class Rva001937D0 : public Rva0033CopyBase
{
	int m_08;

public:
	Rva001937D0(const Rva0033CopyBase &other, const int *extra);
};

Rva001937D0::Rva001937D0(const Rva0033CopyBase &other, const int *extra)
	: Rva0033CopyBase(other)
	, m_08(*extra)
{
}
