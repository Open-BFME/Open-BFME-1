// ?Rva009B50F0DecodeToken@@YAHPAEHH@Z
// partial score=0.95 date=2026-09-02
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

int Rva009B4600DecodeBool(void *state, int probability);

int Rva009B50F0DecodeToken(unsigned char *ctx, int prev, int plane)
{
	int flag;
	void *state = ctx + 0x150;

	if (Rva009B4600DecodeBool(state, ctx[0x77C + 10 * plane + prev]))
		return prev;

	unsigned char *node = ctx + 0x7A4 + 9 * (10 * plane + prev);

	if (Rva009B4600DecodeBool(state, node[0])) {
		if (Rva009B4600DecodeBool(state, node[2])) {
			if (Rva009B4600DecodeBool(state, node[6]))
				return Rva009B4600DecodeBool(state, node[8]) + 8;
			return Rva009B4600DecodeBool(state, node[7]) + 5;
		}
		flag = 1;
		switch (Rva009B4600DecodeBool(state, node[5])) {
		case 0:
			return flag;
		default:
			return 7;
		}
	} else {
		if (Rva009B4600DecodeBool(state, node[1]))
			return Rva009B4600DecodeBool(state, node[4]) + 3;
		return Rva009B4600DecodeBool(state, node[3]) * 2;
	}

	return 1;
}
