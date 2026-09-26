// cl: /DNDEBUG /MD /EHsc

class Rva00385510
{
public:
	int shiftedDifference() const;

private:
	unsigned char m_padding[0x54];
	int m_subtract;
	int m_value;
};

int Rva00385510::shiftedDifference() const
{
	return (m_value - m_subtract) >> 2;
}
