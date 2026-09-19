// Retail 0x002BC810 reads the dword at this-relative offset 4.
// The binary does not prove a semantic owner, so the method keeps its RVA.

class Rva002BC810DwordGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[0x4];
	unsigned int m_value;
};

unsigned int Rva002BC810DwordGetter::get() const
{
	return m_value;
}
