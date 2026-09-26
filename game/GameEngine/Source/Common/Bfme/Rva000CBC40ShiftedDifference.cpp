// cl: /DNDEBUG /MD /EHsc

class Rva000CBC40
{
public:
	int shiftedDifference() const;

private:
	unsigned char m_padding[0xB8];
	int m_base;
	int m_value;
};

int Rva000CBC40::shiftedDifference() const
{
	return (m_value - m_base) >> 2;
}
