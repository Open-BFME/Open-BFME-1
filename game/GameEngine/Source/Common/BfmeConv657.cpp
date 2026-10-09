// VA 0x012F1030: dword counter shared by RVAs 0x003BCF00, 0x0043BCF0
// and 0x004C1240. Retail .data holds four zero bytes; EA's name is unproven.
int g_rva012F1030 = 0;

// The id is a function-local static: its guard bit lives at VA 0x00EF1034 and
// the value at VA 0x00EF102C (both .bss, both touched only by this body).
int bfmeGoCWB()
{
	static int s_bfmeIdCWB = g_rva012F1030++;
	return s_bfmeIdCWB;
}
