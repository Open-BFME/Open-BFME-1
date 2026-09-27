// cl: /DNDEBUG /MD /EHsc
// stlport
// The 20-byte guard tail at 0x008403A0 and the 41-byte narrow copy loop at
// 0x00843EF0, neighbours of the wide streambuf members in
// stlport_streambuf_sputbackc_w.cpp (0x00840350) and the codecvt leaves in
// stlport_codecvt_always_noconv.cpp (0x00843E70/0x00843E80).
// IDENTITY IS NOT RECOVERED for either owner; every name is derived from
// an address.
//
// 0x008403A0 -- WHAT THE BYTES SHOW: mov eax,[ecx+8] / cmp eax,[ecx+0xC] /
// jae tail / add eax,2 / mov [ecx+8],eax / ret. The fall-through advances a
// cursor by one wide element; the tail calls vtable slot +0x20 on `this`
// with the pushed-in register gone (jmp [eax+0x20]). That is the wide
// streambuf "advance the get pointer or underflow" shape: the unsigned
// compare (jae, not jge) and the +2 stride are the tell. The source keeps
// the unsigned compare by spelling the cursor and limit unsigned.
//
// 0x00843EF0 -- WHAT THE BYTES SHOW: count = (last-first)/2 over the two
// pointer arguments, jle to the tail returning arg3, else a do/while loop
// copying (char)*src++ into *dst++. The store order inside the loop is the
// tell: retail advances the source (`add ecx,2`) BEFORE storing the byte
// (`mov [eax],dl`), so the source spells the advance through a byte-wise
// cast (`(const char *)src + 2`) rather than `++src`, which stores first.

struct Rva008403A0Owner
{
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual unsigned int s8();
	int m_4;
	unsigned int m_pos;
	unsigned int m_end;
	unsigned int advance();
};

// ?advance@Rva008403A0Owner@@QAEIXZ
unsigned int Rva008403A0Owner::advance()
{
	unsigned int pos = m_pos;
	if (pos < m_end)
	{
		pos += 2;
		m_pos = pos;
		return pos;
	}
	return s8();
}

// ?dup_00843ef0@@YAHPBG0PAD@Z
int dup_00843ef0(const unsigned short *first, const unsigned short *last, char *out)
{
	int count = (int)(last - first);
	if (count > 0)
	{
		int left = count;
		const unsigned short *src = first;
		char *dst = out;
		do
		{
			char v = (char)*src;
			src = (const unsigned short *)((const char *)src + 2);
			*dst = v;
			++dst;
			--left;
		} while (left != 0);
		return (int)dst;
	}
	return (int)out;
}
