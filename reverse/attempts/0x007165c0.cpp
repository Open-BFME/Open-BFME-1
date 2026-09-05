// ??0BfmeFeFieldsCtor@@QAE@XZ
// partial score=0.55 date=2026-09-05
// Open-BFME: retail RVA 0x007165C0. Constructor-shaped (mov eax,ecx at entry,
// ecx never reloaded, ret at end returns eax=this per the MSVC ctor ABI) but
// the body never touches [ecx+off] -- every write targets a fixed absolute
// address instead, so the "members" are really unrelated file-scope globals
// that happen to sit in the same BSS block as this object. Six of them are
// already pinned by name (g_bfmeFlagsFE, g_bfmePointersFE, g_bfmeGateBT,
// g_bfmeProbeBT, g_bfme914Ptr, g_bfmePtr986B); the rest are address-derived
// placeholders (g_Rva<VA>) per the identity policy -- real names unknown.
// Statement order mirrors retail's instruction order exactly (not address
// order): the store sequence is scrambled by two independently-materialized
// zero registers (ecx, then edx, then back to ecx once more for +0x88before
// resuming edx), which this source reproduces verbatim rather than "fixing".

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern int g_bfmeFlagsFE[4];        // retail 0x012F9C5C
extern int *g_bfmePointersFE[4];    // retail 0x012F9CA4
extern volatile int g_bfmeGateBT;   // retail 0x012F9D04
extern volatile int g_bfmeProbeBT;  // retail 0x012F9D0C
extern void *g_bfme914Ptr;          // retail 0x012F9CD0
extern char *g_bfmePtr986B;         // retail 0x012F9CE4

extern int g_Rva012F9C40;
extern int g_Rva012F9C44;
extern int g_Rva012F9C48;
extern int g_Rva012F9C4C;
extern int g_Rva012F9C50;
extern int g_Rva012F9C54;
extern int g_Rva012F9C58;
extern int g_Rva012F9C6C;
extern int g_Rva012F9C70;
extern int g_Rva012F9C74;
extern int g_Rva012F9C78;
extern int g_Rva012F9C7C;
extern int g_Rva012F9C80;
extern int g_Rva012F9C88;
extern int g_Rva012F9C8C;
extern int g_Rva012F9C90;
extern int g_Rva012F9C94;
extern int g_Rva012F9C98;
extern int g_Rva012F9C9C;
extern int g_Rva012F9CA0;
extern int g_Rva012F9CB4;
extern int g_Rva012F9CB8;
extern int g_Rva012F9CBC;
extern int g_Rva012F9CC0;
extern int g_Rva012F9CC4;
extern int g_Rva012F9CC8;
extern int g_Rva012F9CFC;
extern int g_Rva012F9D08;
extern int g_Rva012F9D10;
extern char g_Rva012F9D00;
extern int g_Rva012F9D14;
extern int g_Rva012F9D18;
extern int g_Rva012F9D1C;
extern int g_Rva012F9D20;
extern int g_Rva012F9CCC;
extern int g_Rva012F9CD4;
extern int g_Rva012F9CD8;
extern int g_Rva012F9CDC;
extern int g_Rva012F9CE0;
extern int g_Rva012F9CE8;
extern int g_Rva012F9CEC;
extern int g_Rva012F9CF0;
extern int g_Rva012F9CF4;

class BfmeFeFieldsCtor
{
public:
	BfmeFeFieldsCtor(void);
};

// ?Rva007165C0FeFieldsCtor@@QAE@XZ (address-derived name; identity unknown)
BfmeFeFieldsCtor::BfmeFeFieldsCtor(void)
{
	int zero1 = 0;

	g_Rva012F9C40 = zero1;
	g_Rva012F9C44 = zero1;
	g_Rva012F9C48 = zero1;
	g_Rva012F9C4C = zero1;
	g_Rva012F9C50 = zero1;
	g_Rva012F9C54 = zero1;
	g_Rva012F9C58 = zero1;
	g_bfmeFlagsFE[0] = zero1;
	g_bfmeFlagsFE[1] = zero1;
	g_bfmeFlagsFE[2] = zero1;
	g_bfmeFlagsFE[3] = zero1;
	g_Rva012F9C6C = zero1;
	g_Rva012F9C70 = zero1;
	g_Rva012F9C74 = zero1;
	g_Rva012F9C78 = zero1;
	g_Rva012F9C7C = zero1;
	g_Rva012F9C80 = zero1;
	g_Rva012F9C88 = zero1;
	g_Rva012F9C8C = zero1;
	g_Rva012F9C90 = zero1;
	g_Rva012F9C94 = zero1;
	g_Rva012F9C98 = zero1;
	g_Rva012F9C9C = zero1;
	g_Rva012F9CA0 = zero1;
	g_bfmePointersFE[0] = 0;
	g_bfmePointersFE[1] = 0;

	_ReadWriteBarrier();
	int zero2 = 0;
	_ReadWriteBarrier();

	g_bfmePointersFE[2] = 0;
	g_bfmePointersFE[3] = 0;
	g_Rva012F9CB4 = zero1;
	g_Rva012F9CB8 = zero1;
	g_Rva012F9CBC = zero1;
	g_Rva012F9CC0 = zero1;
	g_Rva012F9CC4 = zero1;

	g_Rva012F9CFC = zero2;
	g_bfmeGateBT = zero2;
	g_Rva012F9D08 = zero2;
	g_bfmeProbeBT = zero2;
	g_Rva012F9D10 = zero2;
	g_Rva012F9D00 = (char)zero2;
	g_Rva012F9D14 = zero2;
	g_Rva012F9D18 = zero2;
	g_Rva012F9D1C = zero2;
	g_Rva012F9D20 = zero2;

	g_Rva012F9CC8 = zero1;

	g_Rva012F9CCC = zero2;
	g_bfme914Ptr = 0;
	g_Rva012F9CD4 = zero2;
	g_Rva012F9CD8 = zero2;
	g_Rva012F9CDC = zero2;
	g_Rva012F9CE0 = zero2;
	g_bfmePtr986B = 0;
	g_Rva012F9CE8 = zero2;
	g_Rva012F9CEC = zero2;
	g_Rva012F9CF0 = zero2;
	g_Rva012F9CF4 = -1;
}
