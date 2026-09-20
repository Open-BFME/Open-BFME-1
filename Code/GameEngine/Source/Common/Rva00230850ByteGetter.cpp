// Retail 0x00230850 reads the byte at this+0x121 and returns it.
// The carved boundary proves the getter, but no identity evidence names its
// owning type.
// ?get@Rva00230850ByteGetter@@QBEEXZ present-unmatched
class Rva00230850ByteGetter
{
public:
	unsigned char get() const;

private:
	char m_padding[0x121];
	unsigned char m_value;
};

unsigned char Rva00230850ByteGetter::get() const
{
	return m_value;
}
