// Retail RVA 0x00282F90, 3 bytes.
// The carved boundary proves a trivial first-dword accessor, but no caller or
// class table proves a semantic owner, so the identity stays address-derived.

class Rva00282F90Owner
{
public:
	int rva00282F90() const;

	int m_rva00282F90Value;
};

int Rva00282F90Owner::rva00282F90() const
{
	return m_rva00282F90Value;
}
