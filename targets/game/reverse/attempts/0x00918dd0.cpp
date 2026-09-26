// ?setPositiveValue@Rva00918DD0Owner@@QAEXM@Z
// partial score=0.9 date=2026-09-06
extern const float BfmeZeroRange;
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
	m_first = (value > BfmeZeroRange) ? value : BfmeZeroRange;
	if (value > BfmeZeroRange) {
		m_second = value;
		m_flags &= ~0x20000;
	} else {
		m_second = BfmeZeroRange;
		m_flags &= ~0x20000;
	}
}
