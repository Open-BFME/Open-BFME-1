// cl: /DNDEBUG /MD /EHsc

class Rva00489380
{
public:
	signed char isNegative() const;

private:
	unsigned char m_padding[0x08];
	int m_value;
};

signed char Rva00489380::isNegative() const
{
	return m_value < 0;
}
