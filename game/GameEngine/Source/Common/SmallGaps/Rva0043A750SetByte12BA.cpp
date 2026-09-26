// ?setByte12BA@Rva0043A740Owner@@QAEXE@Z
// The adjacent setter at 0x0043A740 names the shared address-derived owner and
// proves the next byte field at offset 0x12BA.

// cl: /O2 /DNDEBUG /MD /EHsc
class Rva0043A740Owner
{
public:
	void setByte12BA(unsigned char value);

private:
	unsigned char m_beforeByte12B9[0x12B9];
	unsigned char m_byte12B9;
	unsigned char m_byte12BA;
};

void Rva0043A740Owner::setByte12BA(unsigned char value)
{
	m_byte12BA = value;
}
