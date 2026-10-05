// Eight two-field setup stubs.
//
// The longer sibling of the setup stubs at 0x007E95A0: same opening -- a
// global read into a callee-saved register, a no-argument member call, a
// FourCC stamped into +0x1C -- but two writes instead of one, the second
// carrying the stub's own second argument.
//
// The tags read as ASCII little-endian, "acct" for five of them and "rank" for
// three, which is the only thing that separates the two halves of the family.
// String literals retain retail's exact contents; globals remain externs.
// The build verifies each literal against the referenced retail address.

// retail 0x007E8AC0: ?run@Rva007E8AC0@@QAEXXZ
class Rva007E8AC0
{
public:
	void run(void);
};

struct BfmeSetupRecord
{
	void bfmeWrite(const char *text, int value);		// retail 0x007E8A10
	void bfmeWriteAlt(const char *text, int value);		// retail 0x007E88D0

	char m_bfmeHead[0x1C];
	unsigned int m_bfmeTag;					// +0x1C
};

extern int TheBfmeSetupGlobal007E94A0;
extern int TheBfmeSetupGlobal007E94E0;
extern int TheBfmeSetupGlobal007E9520;
extern int TheBfmeSetupGlobal007E9560;
extern int TheBfmeSetupGlobal007E9860;
extern int TheBfmeSetupGlobal007F26A0;
extern int TheBfmeSetupGlobal007F26E0;
extern int TheBfmeSetupGlobal007F2720;


// ?bfmeSetupPair_007E94A0@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_007E94A0(BfmeSetupRecord *record, int second)
{
	int value = TheBfmeSetupGlobal007E94A0;

	((Rva007E8AC0 *)record)->run();

	record->m_bfmeTag = 0x61636374;					// 'acct'

	record->bfmeWrite("TXN", value);
	record->bfmeWrite("name", second);
}

// ?bfmeSetupPair_007E94E0@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_007E94E0(BfmeSetupRecord *record, int second)
{
	int value = TheBfmeSetupGlobal007E94E0;

	((Rva007E8AC0 *)record)->run();

	record->m_bfmeTag = 0x61636374;					// 'acct'

	record->bfmeWrite("TXN", value);
	record->bfmeWrite("name", second);
}

// ?bfmeSetupPair_007E9520@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_007E9520(BfmeSetupRecord *record, int second)
{
	int value = TheBfmeSetupGlobal007E9520;

	((Rva007E8AC0 *)record)->run();

	record->m_bfmeTag = 0x61636374;					// 'acct'

	record->bfmeWrite("TXN", value);
	record->bfmeWrite("email", second);
}

// ?bfmeSetupPair_007E9560@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_007E9560(BfmeSetupRecord *record, int second)
{
	int value = TheBfmeSetupGlobal007E9560;

	((Rva007E8AC0 *)record)->run();

	record->m_bfmeTag = 0x61636374;					// 'acct'

	record->bfmeWrite("TXN", value);
	record->bfmeWrite("name", second);
}

// ?bfmeSetupPair_007E9860@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_007E9860(BfmeSetupRecord *record, int second)
{
	int value = TheBfmeSetupGlobal007E9860;

	((Rva007E8AC0 *)record)->run();

	record->m_bfmeTag = 0x61636374;					// 'acct'

	record->bfmeWrite("TXN", value);
	record->bfmeWrite("name", second);
}

// ?bfmeSetupPair_007F26A0@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_007F26A0(BfmeSetupRecord *record, int second)
{
	int value = TheBfmeSetupGlobal007F26A0;

	((Rva007E8AC0 *)record)->run();

	record->m_bfmeTag = 0x72616E6B;					// 'rank'

	record->bfmeWrite("TXN", value);
	record->bfmeWriteAlt("numberOfReporters", second);
}

// ?bfmeSetupPair_007F26E0@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_007F26E0(BfmeSetupRecord *record, int second)
{
	int value = TheBfmeSetupGlobal007F26E0;

	((Rva007E8AC0 *)record)->run();

	record->m_bfmeTag = 0x72616E6B;					// 'rank'

	record->bfmeWrite("TXN", value);
	record->bfmeWrite("sessionId", second);
}

// ?bfmeSetupPair_007F2720@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_007F2720(BfmeSetupRecord *record, int second)
{
	int value = TheBfmeSetupGlobal007F2720;

	((Rva007E8AC0 *)record)->run();

	record->m_bfmeTag = 0x72616E6B;					// 'rank'

	record->bfmeWrite("TXN", value);
	record->bfmeWrite("sessionId", second);
}
