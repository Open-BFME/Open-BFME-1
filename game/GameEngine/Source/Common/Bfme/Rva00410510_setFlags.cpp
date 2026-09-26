// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x00410510 (21 bytes).
// Retail ORs one dword argument into the proven member at this+0x11C.

class Rva00410510
{
public:
	void setFlags(unsigned value);

private:
	unsigned char m_unmodelled_000[0x11C];
	unsigned m_flags;
};

void Rva00410510::setFlags(unsigned value)
{
	m_flags |= value;
}
