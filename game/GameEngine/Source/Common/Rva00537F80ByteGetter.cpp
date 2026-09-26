// Retail 0x00537F80 reads the first byte of its receiver and returns it.
// The carved boundary proves the three-byte getter, but no identity evidence
// names its owning type.
// ?get@Rva00537F80ByteGetter@@QBEEXZ present-unmatched
class Rva00537F80ByteGetter
{
public:
	unsigned char get() const;

private:
	unsigned char m_value;
};

unsigned char Rva00537F80ByteGetter::get() const
{
	return m_value;
}
