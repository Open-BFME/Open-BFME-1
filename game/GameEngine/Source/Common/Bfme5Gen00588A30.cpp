// Open-BFME5: clean C++ recovery of the retail indexed-state reset at 0x00588A30.

void bfmeButtonStateEAF(char index, int state);
void bfmeAutoAbilityOffEAE(char index);
void bfmeFlashEAA(char index, char on);
void bfmeProductionCountZF(int slot, int count);

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
	int active38 = *reinterpret_cast<int *>(m_bfmeState + index * 0x20 + 0x38);
	unsigned char *state = m_bfmeState + index * 0x20;

	*reinterpret_cast<int *>(state + 0x2C) = 0;
	*reinterpret_cast<int *>(state + 0x30) = 0;
	*reinterpret_cast<int *>(state + 0x34) = 0;
	*reinterpret_cast<float *>(state + 0x3C) = 1.0f;
	*reinterpret_cast<int *>(m_bfmeState + (index + 2) * 0x20) = 0;

	if (active38 != 0)
	{
		bfmeButtonStateEAF((char)index, 0);
		*reinterpret_cast<int *>(state + 0x38) = 0;
	}

	if (state[0x48] != 0)
	{
		bfmeAutoAbilityOffEAE((char)index);
		state[0x48] = 0;
	}

	if (state[0x49] != 0)
	{
		bfmeFlashEAA((char)index, 0);
		state[0x49] = 0;
	}

	if (*reinterpret_cast<int *>(state + 0x44) != 0)
	{
		bfmeProductionCountZF(index, 0);
		*reinterpret_cast<int *>(state + 0x44) = 0;
	}
}
