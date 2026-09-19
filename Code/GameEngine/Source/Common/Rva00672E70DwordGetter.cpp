class Rva00672E70DwordGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[0x8];
	unsigned int m_value;
};

unsigned int Rva00672E70DwordGetter::get() const
{
	return m_value;
}
