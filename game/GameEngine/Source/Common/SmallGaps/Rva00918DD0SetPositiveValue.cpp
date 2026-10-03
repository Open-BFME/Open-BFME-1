// ?setPositiveValue@Rva00918DD0Owner@@QAEXM@Z
// Opaque address-derived owner: field offsets and the constant relocation are
// taken from the retail body; no semantic class identity is asserted here.
extern const float g_rva01075350;

struct Rva00918DD0Owner {
	char m_pad[0x10];
	unsigned int m_flags;
	char m_pad2[0x10c - 0x14];
	float m_first;
	char m_pad3[0x15c - 0x110];
	float m_second;
	void setPositiveValue(float value);
};

void Rva00918DD0Owner::setPositiveValue(float value)
{
	m_first = (value > g_rva01075350) ? value : g_rva01075350;
	m_second = (value > g_rva01075350) ? value : g_rva01075350;
	m_flags &= ~0x20000;
}
