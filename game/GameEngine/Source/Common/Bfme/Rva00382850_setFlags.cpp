// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x00382850 (21 bytes).
// Retail ORs one dword argument into the proven member at this+0x110.

class Rva00382850
{
public:
	void setFlags(unsigned value);

private:
	unsigned char m_unmodelled_000[0x110];
	unsigned m_flags;
};

void Rva00382850::setFlags(unsigned value)
{
	m_flags |= value;
}
