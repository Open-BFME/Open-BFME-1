// ?get@Rva00643C80DwordGetter@@QBEIXZ
// Retail 0x00643C80 returns the dword at this. No owning type or field
// meaning is proven, so the class name keeps the retail address.

class Rva00643C80DwordGetter
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

unsigned int Rva00643C80DwordGetter::get() const
{
	return m_value;
}
