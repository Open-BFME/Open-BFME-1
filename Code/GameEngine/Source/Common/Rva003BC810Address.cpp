// The carved body returns the address of the field at this+0x20.

class Rva003BC810Address
{
public:
	void *address();

private:
	char m_prefix[ 0x20 ];
	unsigned char m_field;
};

void *Rva003BC810Address::address()
{
	return &m_field;
}
