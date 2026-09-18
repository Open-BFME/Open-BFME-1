// ?getByte@Rva0037A850ByteGetter@@QBEEXZ
// cl: /DNDEBUG /MD

class Rva0037A850ByteGetter
{
public:
	unsigned char getByte(void) const;

private:
	unsigned char m_padding[0x2C];
	unsigned char m_value;
};

unsigned char Rva0037A850ByteGetter::getByte(void) const
{
	return m_value;
}
