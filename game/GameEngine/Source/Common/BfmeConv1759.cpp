extern const float g_rva01075350;

// Retail 0x01098AD4 is MSVC's own literal pool entry __real@40200000 (2.5f),
// not a global (same verdict as linked BfmeConv2032.cpp / Bfme5ThirtySeven.cpp
// / Bfme5NinetyNine.cpp worklist rows). Spelled as the literal so the read
// resolves to the defined compiler literal at the same address.
extern void j_00043ced(void);

class BfmeSrcBT
{
public:
	// Retail calls this through ILT 0x00043CED (?j_00043ced@@YAXXZ ->
	// FUN_004ed3b0, ?bfmeGapSq@Gen_000ED3B0@@QBEMPBV1@@Z). Routed through the
	// thunk (same idiom as linked Rva00462DE0HashLookup.cpp) to preserve the
	// retail ILT reloc; calling the body directly would retarget the call.
	float bfmeCalcBT(void *value)
	{
		typedef float (BfmeSrcBT::*MemberThunk)(void *);
		union {
			void (*function)(void);
			MemberThunk member;
		} thunk;
		thunk.function = j_00043ced;
		return (this->*thunk.member)(value);
	}
};

class BfmeDataBT
{
public:
	unsigned char m_bfmeHeadBT[0x18];
	float m_bfmeHeightBT;
};

class BfmeOwnBT
{
public:
	char bfmeTestBT(BfmeSrcBT *source, void *value);

	unsigned char m_bfmeHeadBT[4];
	BfmeDataBT *m_bfmeDataBT;
};

char BfmeOwnBT::bfmeTestBT(BfmeSrcBT *source, void *value)
{
	float delta = m_bfmeDataBT->m_bfmeHeightBT - 2.5f;

	if (delta < g_rva01075350)
		return 0;

	if (delta == g_rva01075350)
		return 0;

	if (source->bfmeCalcBT(value) < delta * delta)
		return 1;

	return 0;
}
