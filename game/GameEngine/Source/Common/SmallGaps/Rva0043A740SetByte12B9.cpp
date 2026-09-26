// ?setByte12B9@Rva0043A740Owner@@QAEXE@Z
// cl: /O2 /DNDEBUG /MD /EHsc
// Address-derived owner: the only direct xref is an anonymous ILT thunk.

class Rva0043A740Owner
{
public:
	void setByte12B9(unsigned char value);

private:
	unsigned char m_beforeByte12B9[0x12B9];
	unsigned char m_byte12B9;
};

void Rva0043A740Owner::setByte12B9(unsigned char value)
{
	m_byte12B9 = value;
}
