// cl: /DNDEBUG /MD /EHsc

class Rva0022FF10
{
public:
	int shiftedDifference() const;

private:
	unsigned char m_padding[0x12C];
	int m_base;
	int m_value;
};

int Rva0022FF10::shiftedDifference() const
{
	return (m_value - m_base) >> 4;
}
