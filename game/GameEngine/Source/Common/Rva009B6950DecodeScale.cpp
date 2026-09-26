// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva009B4680State;

int Rva009B4600DecodeBool(void *state, int probability);
int Rva009B4680Normalize(Rva009B4680State *state);
int bfmeGoUSC(void *state, int count);

// ?Rva009B6950DecodeScale@@YAHPAE@Z
int Rva009B6950DecodeScale(unsigned char *ctx)
{
	void *state = ctx + 0x150;
	int sign;

	if (!Rva009B4600DecodeBool(state, 0xCD))
		return 0;

	sign = 1 - (Rva009B4680Normalize((Rva009B4680State *)state) << 1);

	if (!Rva009B4600DecodeBool(state, 0xAB))
		return sign << (3 - Rva009B4600DecodeBool(state, 0x53));

	if (!Rva009B4600DecodeBool(state, 0xC7)) {
		if (Rva009B4600DecodeBool(state, 0x8C))
			return (sign * 3) << 2;
		if (Rva009B4600DecodeBool(state, 0x7D))
			return sign << 4;
		if (Rva009B4600DecodeBool(state, 0x68))
			return (sign * 5) << 2;
		return (sign * 3) << 3;
	}

	return (bfmeGoUSC(state, 7) * sign) << 2;
}
