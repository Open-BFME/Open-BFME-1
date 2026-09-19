// ?setByte12B7@Rva0043A740Owner@@QAEXE@Z
// The adjacent setters prove this address-derived owner and byte-field family.

// cl: /O2 /DNDEBUG /MD /EHsc
class Rva0043A740Owner
{
public:
	void setByte12B7(unsigned char value);

private:
	unsigned char m_beforeByte12B7[0x12B7];
	unsigned char m_byte12B7;
};

void Rva0043A740Owner::setByte12B7(unsigned char value)
{
	m_byte12B7 = value;
}
