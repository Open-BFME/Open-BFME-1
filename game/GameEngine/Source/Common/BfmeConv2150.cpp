__declspec(dllimport) int __stdcall bfmeWait1012(void *h, int ms);
__declspec(dllimport) void __stdcall bfmeReleaseYE(void *h);

struct BfmeBlobYE
{
	unsigned char m_bfmeDataYE[36];
};

class BfmeOwnerYE
{
public:
	unsigned char m_bfmeHeadYE[0x48];
	void *m_bfme48YE;
};

class BfmeAudioYE
{
public:
	void bfmeSetYE(int a1, const BfmeBlobYE *a2, int a3, char a4);

	unsigned char m_bfmeHeadYE[4];
	BfmeOwnerYE *m_bfme04YE;
	BfmeBlobYE m_bfme08YE;
	int m_bfme2CYE;
	volatile int m_bfme30YE;
	unsigned char m_bfmeMidYE[0x40 - 0x34];
	char m_bfme40YE;
	char m_bfme41YE;
	volatile char m_bfme42YE;
};

void BfmeAudioYE::bfmeSetYE(int a1, const BfmeBlobYE *a2, int a3, char a4)
{
	void *h = m_bfme04YE->m_bfme48YE;
	char locked = 0;

	if (bfmeWait1012(h, -1) != 0x102)
		locked = 1;

	m_bfme2CYE = a1;
	m_bfme08YE = *a2;
	m_bfme42YE = 0;
	m_bfme30YE = a3;
	m_bfme40YE = a4;
	m_bfme41YE = 1;

	if (locked)
		bfmeReleaseYE(h);
}
