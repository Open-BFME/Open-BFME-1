// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: the 43-byte flag setter at 0x00417CB0, address-derived name.
// Converted out of Code/gen_asm/d_004171c0.asm.
//
// IDENTITY IS NOT ASSERTED. The bytes say: a __thiscall setter for a bool at
// this+0x140 that returns immediately when the value is unchanged, stores it,
// and then runs one of two members -- the true branch as a TAIL JUMP with the
// incoming argument slot overwritten with 0, the false branch as a plain call.
//
// Relocation note: two additive reverse/symbols.csv pins, both address-derived
// and both disclaiming identity: 0x00417A70 (reached by the `jmp rel32`
// through ILT 0x000294B5) and 0x00411BE0 (ILT 0x0003D13B). The tail jump
// resolves through the same candidate list as a call, so a `jmp` relocation
// is no harder than an `e8`.

class Gen_00417cb0
{
public:
	void setFlag(bool value);
	void tail(void *arg);
	void alt(void);

private:
	unsigned char m_unknown00[0x140];
	bool m_flag;					// +0x140
};

void Gen_00417cb0::setFlag(bool value)
{
	if (m_flag == value)
		return;

	m_flag = value;
	if (value)
		tail(0);
	else
		alt();
}
