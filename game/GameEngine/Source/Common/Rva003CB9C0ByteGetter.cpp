// cl: /DNDEBUG /MD /EHsc

class Rva003CB9C0ByteField
{
public:
	unsigned char get() const;

private:
	char m_pad[0x39];
	unsigned char m_value;
};

unsigned char Rva003CB9C0ByteField::get() const
{
	return m_value;
}
