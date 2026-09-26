// cl: /O2
// Address-derived recovery for the otherwise unidentified byte setter at
// retail 0x0016A830.  It has no named caller; do not assign ParticleSystem's
// setSkipParentXfrm identity to this unrelated +0x33B field.

class Rva0016A830ByteSlot
{
public:
	void set(unsigned char value);

private:
	unsigned char m_beforeValue[0x33B];
	unsigned char m_value;
};

void Rva0016A830ByteSlot::set(unsigned char value)
{
	m_value = value;
}
