// ?Rva009B5830ReconstructBlock@@YAXPAURva009B5830State@@H@Z
// partial score=0.7 date=2026-09-02
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

extern int g_bfmeVp6ModeDispatch[];
extern void (*g_bfmeVp6ReconA)(void *, unsigned char *, unsigned char *, int, int);
extern void (*g_bfmeVp6ReconB)(void *, int, unsigned char *, int);
extern void (*g_bfmeVp6ReconC)(void *, int, unsigned char *, int);

void Rva009B54D0PrepareBlock(Rva009B5830State *, void *, int);

void Rva009B5830ReconstructBlock(Rva009B5830State *state, int block)
{
	if (state->mode == 0) {
		g_bfmeVp6ReconA(state->coefficients,
			state->predictionA + state->baseOffset,
			state->predictionC + state->baseOffset,
			state->pitch, state->stride);
		return;
	}

	if (g_bfmeVp6ModeDispatch[state->mode] != 0) {
		Rva009B54D0PrepareBlock(state, state->coefficients, block);
		g_bfmeVp6ReconB(state->coefficients, state->pitch,
			state->predictionA + state->baseOffset, state->stride);
		return;
	}

	if (state->mode == 5) {
		g_bfmeVp6ReconA(state->coefficients,
			state->predictionA + state->baseOffset,
			state->predictionB + state->baseOffset,
			state->pitch, state->stride);
		return;
	}

	g_bfmeVp6ReconC(state->coefficients, state->pitch,
		state->predictionA + state->baseOffset, state->stride);
}
