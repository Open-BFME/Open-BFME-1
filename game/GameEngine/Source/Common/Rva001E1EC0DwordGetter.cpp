// cl: /O2
// ?get@Rva001E1EC0Owner@@QBEIXZ
//
// Retail loads the dword at this and returns it.
// The carved boundary proves the accessor body, but no semantic owner is known.

class Rva001E1EC0Owner
{
public:
	unsigned int get() const;

	unsigned int m_value;
};

unsigned int Rva001E1EC0Owner::get() const
{
	return m_value;
}
