// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

int bfmeNormUSC(void *p);

int Rva009B5090DecodeMode(unsigned char *ctx)
{
	void *state = ctx + 0x150;
	int value = bfmeNormUSC(state) * 2;
	value += bfmeNormUSC(state);

	switch (value) {
	case 0:
		return 0;
	case 1:
		return 2;
	case 2:
		return 3;
	case 3:
		return 4;
	}
	return 0;
}
