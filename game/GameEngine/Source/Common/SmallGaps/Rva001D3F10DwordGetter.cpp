// ?get@Rva001D3F10DwordField@@QBEHXZ
// Retail 0x001D3F10 returns the dword at this+0x04.  No owning type or field
// meaning is proven, so the class name keeps the retail address.

class Rva001D3F10DwordField
{
public:
	int get() const;

private:
	int m_pad00;
	int m_value;
};

int Rva001D3F10DwordField::get() const
{
	return m_value;
}
