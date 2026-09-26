// Open-BFME5 conversions.

extern "C" unsigned strlen(const char *s);
#pragma intrinsic(strlen)

__declspec(dllimport) void __cdecl bfmeCopyVGK(char *d, const char *s);

class BfmeThingVGK
{
public:
	void bfmeGoVGK(const char *s);
	char m_bfmePad[0xa4];
	char m_bfmeBuf[0x20];
};

void BfmeThingVGK::bfmeGoVGK(const char *s)
{
	if (s && strlen(s) < 0x20)
		bfmeCopyVGK(m_bfmeBuf, s);
}
