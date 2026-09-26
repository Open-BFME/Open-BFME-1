// Byte getter at 0x00216B80: mov al, [ecx+0x4B1] / ret.
// Identity not recovered; the class name is the retail RVA.
class Rva00216B80
{
public:
	unsigned char get() const;

private:
	char m_lead[0x4B1];
	unsigned char m_value;
};

unsigned char Rva00216B80::get() const
{
	return m_value;
}
