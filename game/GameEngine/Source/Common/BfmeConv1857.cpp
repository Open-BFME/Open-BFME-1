extern "C" char g_bfmeFormatYA[];
extern "C" int __cdecl bfmeScanYA(const char *text, const char *format, ...);

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
		bfmeScanYA(text, g_bfmeFormatYA, &m_bfmeValueYA);
		break;
	}
}
