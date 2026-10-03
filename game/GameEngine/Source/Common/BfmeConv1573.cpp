// Open-BFME5 conversions.

// stlport
#include <string>

extern template _STL::basic_string<char> &_STL::basic_string<char>::assign(
	const char *, const char *);

extern "C" unsigned int __cdecl strlen(const char *text);

struct BfmeTimeVSE
{
	unsigned short m_bfme00;
	unsigned short m_bfme02;
	unsigned short m_bfme04;
	unsigned short m_bfme06;
	unsigned short m_bfme08;
	unsigned short m_bfme0a;
	unsigned short m_bfme0c;
	unsigned short m_bfme0e;
};

extern "C" __declspec(dllimport) void __stdcall GetLocalTime(BfmeTimeVSE *now);
extern "C" __declspec(dllimport) int __cdecl sprintf(char *dest, const char *format, ...);

typedef _STL::basic_string<char> BfmeStrVSE;

class BfmeStampVSE
{
public:
	void bfmeStampVSE();
	char m_bfmePad000[0x14c];
	BfmeStrVSE m_bfme14c;
};

void BfmeStampVSE::bfmeStampVSE()
{
	BfmeTimeVSE now;
	char text[16];

	GetLocalTime(&now);
	sprintf(text, "%d/%d/%d", now.m_bfme02, now.m_bfme06, now.m_bfme00);
	m_bfme14c.assign((const char *)text, (const char *)(text + strlen(text)));
}
