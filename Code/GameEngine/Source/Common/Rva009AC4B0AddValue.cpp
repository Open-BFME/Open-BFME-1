// Open-BFME5 conversion of the VP6 signed table update at 0x009AC4B0.

struct Rva009AC4B0State
{
	unsigned char m_pad0[0x1c];
	int m_value;
};

extern int g_rva01143064[];
extern int g_rva01142c68[];

void Rva009AC4B0AddValue(Rva009AC4B0State *state, int positive, int index)
{
	if (positive != 0) {
		state->m_value += g_rva01143064[-index];
	} else {
		state->m_value += g_rva01142c68[index];
	}
}
