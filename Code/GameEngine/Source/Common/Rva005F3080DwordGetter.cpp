// cl: /O2
// ?get@Rva005F3080Owner@@QBEIXZ
//
// Retail loads the dword at this plus 0x0C and returns it.
// The carved boundary proves the accessor body, but no semantic owner is known.

class Rva005F3080Owner
{
public:
	unsigned int get() const;

	unsigned int m_pad00[3];
	unsigned int m_value;
};

unsigned int Rva005F3080Owner::get() const
{
	return m_value;
}
