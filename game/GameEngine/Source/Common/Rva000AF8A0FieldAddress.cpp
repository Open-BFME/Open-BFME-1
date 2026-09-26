// cl: /O2

class Rva000AF8A0FieldAddress
{
public:
	unsigned char *get();

private:
	unsigned char m_padding[0x50];
	unsigned char m_value;
};

unsigned char *Rva000AF8A0FieldAddress::get()
{
	return &m_value;
}
