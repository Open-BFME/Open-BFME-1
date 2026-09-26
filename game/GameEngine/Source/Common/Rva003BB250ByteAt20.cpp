// cl: /DNDEBUG /MD /O2
// Retail 0x003BB250 reads the byte at this+0x20 and returns it.
// The adjacent GenBase003BB1E0 constructor and clear body prove the field
// offset, but no caller proves a semantic class or method name.

class Rva003BB250ByteAt20
{
public:
	unsigned char get() const;

private:
	char m_pad00[0x20];
	unsigned char m_value;
};

// ?get@Rva003BB250ByteAt20@@QBEEXZ
unsigned char Rva003BB250ByteAt20::get() const
{
	return m_value;
}
