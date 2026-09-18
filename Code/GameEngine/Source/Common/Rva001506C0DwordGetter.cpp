// Retail RVA 0x001506C0 reads a dword at this + 0x4 and returns it.
// The carved body does not prove its owning class or field name.

class Rva001506C0DwordField
{
public:
	int get() const;

private:
	char m_padding[4];
	int m_value;
};

int Rva001506C0DwordField::get() const
{
	return m_value;
}
