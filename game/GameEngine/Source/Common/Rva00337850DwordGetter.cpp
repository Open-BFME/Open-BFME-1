// ?get@Rva00337850DwordField@@QBEHXZ
// Retail 0x00337850 returns the dword at this+0x04. No owning type or field
// meaning is proven, so the class name keeps the retail address.

class Rva00337850DwordField
{
public:
	int get() const;

private:
	int m_pad00;
	int m_value;
};

int Rva00337850DwordField::get() const
{
	return m_value;
}

// cl: /DNDEBUG /MD /EHsc
