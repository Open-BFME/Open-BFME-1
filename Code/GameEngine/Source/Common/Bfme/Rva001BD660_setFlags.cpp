// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x001BD660 (21 bytes).
// The member is identified only by its proven offset: retail ORs one dword
// argument into this+0x114 and returns with one argument popped.

class Rva001BD660
{
public:
	void setFlags(unsigned value);

private:
	unsigned char m_unmodelled_000[0x114];
	unsigned m_flags;
};

void Rva001BD660::setFlags(unsigned value)
{
	m_flags |= value;
}
