// Retail 0x006C0770 reads the dword at this-relative offset 0x10.
// The binary does not prove a semantic owner, so the method keeps its RVA.

class Rva006C0770DwordGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[0x10];
	unsigned int m_value;
};

unsigned int Rva006C0770DwordGetter::get() const
{
	return m_value;
}
