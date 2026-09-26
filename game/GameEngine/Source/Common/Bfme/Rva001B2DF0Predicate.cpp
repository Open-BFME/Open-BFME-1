// cl: /DNDEBUG /MD /EHsc

class Rva001B2DF0
{
public:
	int predicate() const;

private:
	unsigned char m_padding_00[0x3C];
	unsigned int m_field_3C;
	unsigned int m_field_40;
	unsigned char m_padding_44[0x10];
	unsigned int m_field_54;
};

int Rva001B2DF0::predicate() const
{
	if (m_field_54 == 0 && m_field_3C == 0 && m_field_40 == 0)
		return 0x3FFFFFFF;
	return 1;
}
