// Retail 0x0009C1C0 reads the dword at this+0x0C and returns it.
// The carved boundary proves the getter, but no identity evidence names its
// owning type.
// ?get@Rva0009C1C0DwordGetter@@QBEIXZ present-unmatched
class Rva0009C1C0DwordGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[0x0C];
	unsigned int m_value;
};

unsigned int Rva0009C1C0DwordGetter::get() const
{
	return m_value;
}
