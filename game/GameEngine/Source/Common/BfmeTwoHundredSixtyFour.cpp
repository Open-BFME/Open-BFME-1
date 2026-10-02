// cl: /Od
// Four values and a flag passed straight on, together with the addresses of two
// bytes the callee fills in, built without optimisation.

// Retail's bytes call the forwarder the ledger defines at 0x0082DFE0 as
// ?bfmeFwdV26@@YAPAXHHHHHHD@Z (game/GameEngine/Source/Common/BfmeConv1466.cpp):
// six int arguments and a trailing byte.  The four pointers this function
// forwards are the first four of them, so they are passed through unchanged.
void *bfmeFwdV26(int a, int b, int c, int d, int e, int f, char ch);

void bfmeGoPA(void *one, void *two, void *three, void *four, unsigned char five)
{
	unsigned char second;

	unsigned char first;

	bfmeFwdV26((int)one, (int)two, (int)three, (int)four, (int)&second,
		(int)&first, (char)five);
}
