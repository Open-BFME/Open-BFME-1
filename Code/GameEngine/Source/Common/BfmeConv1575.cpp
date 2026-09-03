// Open-BFME5 conversions.

extern "C" unsigned int __cdecl strlen(const char *text);

class BfmeStrVSF
{
public:
	void bfmeSetVSF(const char *text, int length);
	char *m_bfme00;
};

struct BfmeInfoVSF
{
	int m_bfme00;
	const char *m_bfme04;
	const char *m_bfme08;
};

extern "C" char g_bfmeFlagVSF;
extern "C" BfmeStrVSF g_bfmeNameVSF;
extern "C" BfmeStrVSF g_bfmeHostVSF;

int bfmeApplyVSF(const BfmeInfoVSF *info)
{
	int length;

	g_bfmeFlagVSF = 1;

	if (info->m_bfme04 != 0)
		length = strlen(info->m_bfme04);
	else
		length = 0;

	g_bfmeNameVSF.bfmeSetVSF(info->m_bfme04, length);

	if (info->m_bfme08 != 0)
		length = strlen(info->m_bfme08);
	else
		length = 0;

	g_bfmeHostVSF.bfmeSetVSF(info->m_bfme08, length);

	return 1;
}
