// Three more: the backward half of an insertion sort, a state stop and a
// two-flag text write.

// ?bfmeInsert@@YAXPAHH@Z
void __cdecl bfmeInsert(int *last, int value)
{
	int *hole = last;
	int *previous = last - 1;

	while (value < *previous)
	{
		*hole = *previous;

		hole = previous;

		--previous;
	}

	*hole = value;
}

class Gen_00516AE0
{
public:
	void bfmeStop(int unused);

private:
	char m_bfmeHead[0x3A8];					// +0x000
	int m_bfmeState;					// +0x3A8
	char m_bfmeGap[0x28];					// +0x3AC
	unsigned int m_bfmeFlags;				// +0x3D4
};

// ?bfmeStop@Gen_00516AE0@@QAEXH@Z
void Gen_00516AE0::bfmeStop(int unused)
{
	if (m_bfmeState == 1)
	{
		m_bfmeState = 7;

		m_bfmeFlags = m_bfmeFlags & ~2;
	}
}

// ?bfmeFormat@@YGXHPAD_N@Z
void __stdcall bfmeFormat(int value, char *out, bool plain)
{
	if (!plain)
	{
		out[0] = '0';
		out[1] = 0;
	}

	if (value == 0 && !plain)
		out[0] = '1';
}
