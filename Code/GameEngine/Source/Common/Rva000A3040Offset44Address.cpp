// The carved body returns the address of the field at this+0x2c.

class Rva000A3040Offset44Address
{
public:
	void *address();

private:
	char m_prefix[ 0x2c ];
	unsigned char m_field;
};

void *Rva000A3040Offset44Address::address()
{
	return &m_field;
}
