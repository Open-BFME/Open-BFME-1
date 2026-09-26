// cl: /O2 /Ob0

class Rva0033CopyBase
{
public:
	Rva0033CopyBase(const Rva0033CopyBase &other);

private:
	char m_pad[8];
};

struct Rva0033A7B0Extra
{
	int a;
	int b;
};

class Rva0033A7B0 : public Rva0033CopyBase
{
	int m_08;
	int m_0C;

public:
	Rva0033A7B0(const Rva0033CopyBase &other, const Rva0033A7B0Extra *extra);
};

Rva0033A7B0::Rva0033A7B0(const Rva0033CopyBase &other, const Rva0033A7B0Extra *extra)
	: Rva0033CopyBase(other)
	, m_08(extra->a)
	, m_0C(extra->b)
{
}
