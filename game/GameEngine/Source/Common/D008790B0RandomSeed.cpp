// Retail VA 0x012D4CB8 / 0x012D4CBC: all three generator bodies load/store these
// dwords; .data contains 0d 00 00 00 75 00 00 00. No standalone EA global name is established.
int g_rva012D4CB8 = 13;
int g_rva012D4CBC = 117;

int d_008790b0(int reset)
{
	int carry;
	int seed;
	if (reset) {
		seed = 13;
		carry = 117;
	} else {
		carry = g_rva012D4CBC;
		seed = g_rva012D4CB8;
	}
	int next = (seed * 0x3E322 + carry * 0x8149A) % 0xF408B;
	g_rva012D4CBC = seed;
	g_rva012D4CB8 = next;
	return next;
}
