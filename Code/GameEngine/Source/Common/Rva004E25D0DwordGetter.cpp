class Rva004E25D0DwordGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[0x18];
	unsigned int m_value;
};

unsigned int Rva004E25D0DwordGetter::get() const
{
	return m_value;
}
