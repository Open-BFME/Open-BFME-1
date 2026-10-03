// Retail VA 0x012D4CB8: all three generator bodies load/store one dword;
// .data contains 0d 00 00 00. No standalone EA global name is established.
int g_rva012D4CB8 = 13;
extern int g_bfmeCarry790B0;

int d_008790b0(int reset)
{
	int carry;
	int seed;
	if (reset) {
		seed = 13;
		carry = 117;
	} else {
		carry = g_bfmeCarry790B0;
		seed = g_rva012D4CB8;
	}
	int next = (seed * 0x3E322 + carry * 0x8149A) % 0xF408B;
	g_bfmeCarry790B0 = seed;
	g_rva012D4CB8 = next;
	return next;
}
