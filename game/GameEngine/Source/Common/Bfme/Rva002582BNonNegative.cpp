// cl: /DNDEBUG /MD /EHsc

class Rva002582B
{
public:
	bool isPositive() const;

private:
	unsigned char m_padding[0x08];
	int m_value;
};

bool Rva002582B::isPositive() const
{
	return m_value > 0;
}
