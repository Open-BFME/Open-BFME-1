// cl: /O2
// 0x002BBC30 reads the opaque 32-bit field at receiver offset +0x1C.

class Rva002BBC30DwordReader
{
public:
	unsigned int read();

private:
	unsigned char m_padding[ 0x1C ];
	unsigned int m_value;
};

unsigned int Rva002BBC30DwordReader::read()
{
	return m_value;
}
