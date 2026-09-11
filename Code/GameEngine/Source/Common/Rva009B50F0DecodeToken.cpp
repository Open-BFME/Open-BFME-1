// Open-BFME5: VP6 arithmetic-coded mode token decoder, retail RVA
// 0x009B50F0.  The caller at 0x009B5AF0 supplies the decoder context,
// previous mode, and probability plane.  The matched 0x009B4600 helper
// establishes the arithmetic-decoder state at context offset 0x150.
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

int Rva009B4600DecodeBool(void *state, int probability);

int Rva009B50F0DecodeToken(unsigned char *ctx, int prev, int plane)
{
	void *state = ctx + 0x150;
	int result;

	if (Rva009B4600DecodeBool(state, ctx[0x77C + 10 * plane + prev])) {
		result = prev;
		goto done;
	}

	unsigned char *node = ctx + 0x7A4 + 9 * (10 * plane + prev);
	if (Rva009B4600DecodeBool(state, node[0])) {
		if (Rva009B4600DecodeBool(state, node[2])) {
			if (Rva009B4600DecodeBool(state, node[6]))
				result = Rva009B4600DecodeBool(state, node[8]) + 8;
			else
				result = Rva009B4600DecodeBool(state, node[7]) + 5;
			goto done;
		}

		result = 1;
		if (Rva009B4600DecodeBool(state, node[5]))
			result = 7;
		goto done;
	}

	if (Rva009B4600DecodeBool(state, node[1]))
		result = Rva009B4600DecodeBool(state, node[4]) + 3;
	else
		result = Rva009B4600DecodeBool(state, node[3]) * 2;

done:
	return result;
}
