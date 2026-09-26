// cl: /O2 /Ob0

class Rva0033CopyBase
{
public:
	Rva0033CopyBase(const Rva0033CopyBase &other);

private:
	char m_pad[8];
};

class Rva0033A7E0 : public Rva0033CopyBase
{
	char m_08;

public:
	Rva0033A7E0(const Rva0033CopyBase &other, const char *extra);
};

Rva0033A7E0::Rva0033A7E0(const Rva0033CopyBase &other, const char *extra)
	: Rva0033CopyBase(other)
	, m_08(*extra)
{
}
