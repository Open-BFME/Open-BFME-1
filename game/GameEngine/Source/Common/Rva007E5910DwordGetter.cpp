// Retail 0x007E5910 reads the dword at this plus 4.
class Rva007E5910DwordGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[0x4];
	unsigned int m_value;
};

unsigned int Rva007E5910DwordGetter::get() const
{
	return m_value;
}
