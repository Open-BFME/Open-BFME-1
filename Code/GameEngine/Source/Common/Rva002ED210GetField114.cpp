// The carved body at 0x002ED210 reads one Boolean byte at this+0x114.
// No evidence proves a semantic owner, so the class name keeps the retail address.
class Rva002ED210
{
public:
	bool getField114() const;

private:
	unsigned char m_padding[0x114];
	bool m_field114;
};

bool Rva002ED210::getField114() const
{
	return m_field114;
}
