// Address-derived reconstruction of the eight-byte signed ratio getter at 0x007E3C10.

class Rva007E3C10SignedRatio
{
public:
	int ratio() const;

private:
	char m_pad00[ 0x40 ];
	int m_numerator;
	int m_denominator;
};

int Rva007E3C10SignedRatio::ratio() const
{
	return m_numerator / m_denominator;
}
