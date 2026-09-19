// cl: /O2 /MD

class Rva007AE760AddressField
{
public:
	unsigned char *get();

private:
	char m_padding[0x64];
	unsigned char m_value;
};

unsigned char *Rva007AE760AddressField::get()
{
	return &m_value;
}
