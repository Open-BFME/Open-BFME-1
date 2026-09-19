// ?get@Rva00695A00FloatGetter@@QBEMXZ
// Retail 0x00695A00 returns the float at this+0x54. No owning type or field
// meaning is proven, so the class name keeps the retail address.

class Rva00695A00FloatGetter
{
public:
	float get() const;

private:
	char m_padding[0x54];
	float m_value;
};

float Rva00695A00FloatGetter::get() const
{
	return m_value;
}
