// Retail's call at 0x007F55A9 is a rel32 call to the six-byte MSVCR71 thunk at
// 0x009F6FA6 (?ji_009f6fa6@@YAXXZ, gen-import body in imports_000.cpp, IAT slot
// __imp__sscanf = 0x01359494), not a direct import.  Declared with an empty
// parameter list so the decorated name stays ?ji_009f6fa6@@YAXXZ, the convention
// the other matched callers of these thunks use (e.g. FeslMessage_getInt64_rva007E8930.cpp).
extern void ji_009f6fa6();
typedef int (__cdecl *Sscanf)(const char *buf, const char *fmt, void *out);
// The format operand is the "AptPalantir integer format literal" at 0x0107C7B4,
// ?g_aptPalantirNumberFormat@@3PADA, spelled here as the same global array the
// other matched AptPalantir callers declare.
extern char g_aptPalantirNumberFormat[];

class BfmeOwnerYA
{
public:
	void bfmeParseYA(const char *text);

	unsigned char m_bfmeHeadYA[0x68];
	int m_bfmeValueYA;
};

void BfmeOwnerYA::bfmeParseYA(const char *text)
{
	switch (text[0])
	{
	case 'f':
		m_bfmeValueYA = -200;
		break;
	case 'r':
		m_bfmeValueYA = -201;
		break;
	case 'c':
		m_bfmeValueYA = -202;
		break;
	case 't':
		m_bfmeValueYA = -203;
		break;
	default:
		((Sscanf)ji_009f6fa6)(text, g_aptPalantirNumberFormat, &m_bfmeValueYA);
		break;
	}
}
