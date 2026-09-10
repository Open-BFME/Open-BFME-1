// VP6 block reconstruction helper reached from the decoder's block walker.
// Retail boundary: [0x009B5830, 0x009B58E8).  The generated row at this
// address is replaced here with the actual BFME dispatch logic.
//
// The three spread-table cells are one shared void* blob declared by the
// codec installer.  Their callback signatures are recovered from the retail
// push order at 0x009B5830, not inferred from a Zero Hour wrapper.
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva009B5830State
{
	unsigned char pad0[8];
	int mode;
	unsigned char padC[0x70 - 0x0c];
	int baseOffset;
	int stride;
	unsigned char pad78[0x244 - 0x78];
	unsigned char *predictionA;
	unsigned char pad248[4];
	unsigned char *predictionB;
	unsigned char pad250[4];
	unsigned char *predictionC;
	unsigned char pad258[0x270 - 0x258];
	int pitch;
	unsigned char pad274[0x284 - 0x274];
	void *coefficients;
};

extern void *g_bfmeSlotD84;
extern void *g_bfmeSlotD88;
extern void *g_bfmeSlotD8C;
extern int g_rva00ED7770Vp6ModeDispatch[];

typedef void (__cdecl *Rva009B5830ReconD84)(
	void *, unsigned char *, unsigned char *, int, int);
typedef void (__cdecl *Rva009B5830ReconD88)(
	void *, int, unsigned char *, int);
typedef void (__cdecl *Rva009B5830ReconD8C)(
	void *, unsigned char *, int, int);

// Retail 0x009B5530 reads the state, coefficients, and block arguments at
// incoming [esp+4], [esp+8], and [esp+0xc]; declare that real body
// with the cdecl ABI instead of casting the generated no-argument row.
extern void __cdecl Rva009B5530Prepare(Rva009B5830State *, void *, int);

void Rva009B5830ReconstructBlock(Rva009B5830State *state, int block)
{
	if (state->mode == 0) {
		((Rva009B5830ReconD84)g_bfmeSlotD84)(state->coefficients,
			state->predictionA + state->baseOffset,
			state->predictionC + state->baseOffset,
			state->pitch, state->stride);
	} else if (g_rva00ED7770Vp6ModeDispatch[state->mode] != 0) {
		Rva009B5530Prepare(state, state->coefficients, block);
		((Rva009B5830ReconD88)g_bfmeSlotD88)(state->coefficients,
			state->pitch, state->predictionA + state->baseOffset,
			state->stride);
	} else if (state->mode == 5) {
		((Rva009B5830ReconD84)g_bfmeSlotD84)(state->coefficients,
			state->predictionA + state->baseOffset,
			state->predictionB + state->baseOffset,
			state->pitch, state->stride);
	} else {
		((Rva009B5830ReconD8C)g_bfmeSlotD8C)(state->coefficients,
			state->predictionA + state->baseOffset,
			state->pitch, state->stride);
	}
}
