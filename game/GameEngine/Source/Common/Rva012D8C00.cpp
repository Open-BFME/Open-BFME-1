// cl: /DNDEBUG /MD /O2
// Address-derived provider for the 16-byte Bink SSE rounding operand.
__declspec(align(16)) extern const unsigned short g_bfmeBinkRound[8] = {
	64, 64, 64, 64, 64, 64, 64, 64
};
