// cl: /O2
// ?get@Rva006185A0Owner@@QBEIXZ
//
// Retail loads the dword at this plus 0x0C and returns it.
// The carved boundary proves the accessor body, but no semantic owner is known.

class Rva006185A0Owner
{
public:
	unsigned int get() const;

	unsigned int m_pad00[3];
	unsigned int m_value;
};

unsigned int Rva006185A0Owner::get() const
{
	return m_value;
}
