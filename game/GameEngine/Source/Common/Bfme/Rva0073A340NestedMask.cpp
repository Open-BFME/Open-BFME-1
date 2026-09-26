// cl: /DNDEBUG /MD /EHsc

struct Rva0073A340Nested
{
	unsigned char m_padding[0x10];
	unsigned m_flags;
};

class Rva0073A340
{
public:
	int nestedMask() const;

private:
	unsigned char m_padding[0x40];
	Rva0073A340Nested *m_nested;
};

int Rva0073A340::nestedMask() const
{
	return m_nested->m_flags & 2;
}
