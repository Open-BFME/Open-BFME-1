// Open-BFME5 conversions.

extern "C" unsigned int __cdecl strlen(const char *text);

class BfmeVecVSD
{
public:
	void bfmeEraseVSD(void *first, void *last);
	void *m_bfme00;
	void *m_bfme04;
};

class BfmeItemVSD
{
public:
	void bfmeSetVSD(const char *text, int length);
	void bfmeStoreVSD(const char *text, int value);
	char *m_bfme00;
	int m_bfme04;
	BfmeVecVSD m_bfme08;
};

void BfmeItemVSD::bfmeStoreVSD(const char *text, int value)
{
	m_bfme08.bfmeEraseVSD(m_bfme08.m_bfme00, m_bfme08.m_bfme04);

	int length;

	if (text != 0)
		length = strlen(text);
	else
		length = 0;

	bfmeSetVSD(text, length);

	m_bfme04 = value;
}
