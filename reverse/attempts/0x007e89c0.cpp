// ?getBool@Rva007E8810Message@@QAE_NPBD_N@Z
// partial score=0.82 date=2026-09-02
// ?getBool@Rva007E8810Message@@QAE_NPBD_N@Z
// partial score=0.82 date=2026-09-02
// ?getBool@Rva007E8810Message@@QAE_NPBD_N@Z
// partial score=0.82 date=2026-09-02
// cl: /O2
// Near miss for 0x007E89C0 getBool. Lookup and Rva007EE720 match; retail
// bool-izes through eax/ecx (mov eax,esi / xor ecx / test eax / setnz cl /
// mov al,cl) while MSVC 7.1 emits test esi / setnz al on both tails.

char *Rva007EBCA0(const char *record, const char *key);
extern "C" int Rva007EE720(const char *text, int defaultValue);

class Rva007E8810Message
{
public:
	bool getBool(const char *key, bool defaultValue);

private:
	char m_pad[0x10];
	const char *m_10;
};

bool Rva007E8810Message::getBool(const char *key, bool defaultValue)
{
	unsigned char d = defaultValue;
	int def = d != 0;
	const char *k = key;
	char *s = Rva007EBCA0(m_10, k);
	if (s == 0)
		return def != 0;
	return Rva007EE720(s, def) != 0;
}
