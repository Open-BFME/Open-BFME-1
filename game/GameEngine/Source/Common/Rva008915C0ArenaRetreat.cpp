// Two bodies carved from one 41-byte dump at 0x008915C0 (the int3 run at +0x0E
// splits it).
//
// 0x008915C0 steps the shared arena cursor back by one 0x60-byte record, the
// inverse of Rva00897030Advance (Rva00897030ArenaHelpers.cpp); like it, it
// returns the new cursor, which is why retail goes through eax.
//
// 0x008915D0 assigns a two-bit field at bits 18-19 of the dword at +0x60:
// shl 18, xor with the old word, mask 0xC0000, xor back is MSVC's bitfield
// store. Its class is not identified, so it keeps the address.

extern char *g_bfmeArenaCursor;

// ?Rva008915C0Retreat@@YAPADXZ
char *Rva008915C0Retreat()
{
	return g_bfmeArenaCursor -= 0x60;
}

class Rva008915D0Flags
{
public:
	void setField(int value);

private:
	char m_unknown[0x60];
	unsigned m_lowBits : 18;
	unsigned m_field : 2;			// +0x60 bits 18-19
};

// ?setField@Rva008915D0Flags@@QAEXH@Z
void Rva008915D0Flags::setField(int value)
{
	m_field = value;
}
