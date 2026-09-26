// Retail 0x00840910, 40 bytes, split by the ledger across its two return arms.
//
// A 16-bit index bounded against 0x100 with an unsigned compare -- ax against
// an immediate, jae rather than jge -- so the parameter is an unsigned short
// and the table has 0x100 entries. It is then widened with movzx before being
// scaled by four, which is the same unsignedness showing again.
//
// The table entry is tested against the other argument rather than compared,
// so the argument is a mask and the answer is whether any bit survives.
//
// Both exits set the whole register, so the return is int.
//
// The three rows it was split across add up to 40, not the 38 the body's own
// instructions suggest at a glance -- the five-byte false arm is the last of
// them.

typedef unsigned short UnsignedShort;

extern int TheBfmeMaskTable[0x100];					// 0x0112EC4C

// ?Gen_00840910@@YGHHG@Z
int __stdcall Gen_00840910(int mask, UnsignedShort index)
{
	if (index < 0x100 && (TheBfmeMaskTable[index] & mask) != 0)
		return 1;

	return 0;
}
