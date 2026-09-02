// ?bfmeReset@Gen_00588A30@@QAEXH@Z
// partial score=0.93 date=2026-09-03
void bfmeResetIndexed38(int index, int value);
void bfmeResetIndexed48(int index);
void bfmeResetIndexed49(int index, int value);
void bfmeResetIndexed44(int index, int value);

class Gen_00588A30
{
public:
	void bfmeReset(int index);

private:
	unsigned char m_bfmeState[1];
};

// ?bfmeReset@Gen_00588A30@@QAEXH@Z
void Gen_00588A30::bfmeReset(int index)
{
	unsigned char *state = m_bfmeState + index * 0x20;
	int active38 = *reinterpret_cast<int *>(state + 0x38);

	*reinterpret_cast<int *>(state + 0x2C) = 0;
	*reinterpret_cast<int *>(state + 0x30) = 0;
	*reinterpret_cast<int *>(state + 0x34) = 0;
	*reinterpret_cast<float *>(state + 0x3C) = 1.0f;
	*reinterpret_cast<int *>(m_bfmeState + (index + 2) * 0x20) = 0;

	if (active38 != 0)
	{
		bfmeResetIndexed38(index, 0);
		*reinterpret_cast<int *>(state + 0x38) = 0;
	}

	if (state[0x48] != 0)
	{
		bfmeResetIndexed48(index);
		state[0x48] = 0;
	}

	if (state[0x49] != 0)
	{
		bfmeResetIndexed49(index, 0);
		state[0x49] = 0;
	}

	if (*reinterpret_cast<int *>(state + 0x44) != 0)
	{
		bfmeResetIndexed44(index, 0);
		*reinterpret_cast<int *>(state + 0x44) = 0;
	}
}
