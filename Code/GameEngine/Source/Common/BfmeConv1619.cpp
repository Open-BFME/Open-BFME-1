// Open-BFME5 conversions.

class BfmeStrVTN
{
public:
	BfmeStrVTN(const BfmeStrVTN &other);
	char *m_bfme00;
};

class BfmeHostVTN;

class BfmeSinkVTN
{
public:
	BfmeHostVTN *bfmeTouchVTN();
};

class BfmeHostVTN
{
public:
	int m_bfme00;
	BfmeSinkVTN *m_bfme04;
	char m_bfmePad08[0x18];
	BfmeStrVTN m_bfme20;
};

class BfmeOwnVTN
{
public:
	BfmeStrVTN bfmeNameVTN();
};

BfmeStrVTN BfmeOwnVTN::bfmeNameVTN()
{
	BfmeHostVTN *host = *(BfmeHostVTN **)((char *)this - 0x60);
	volatile int scratch = 0;

	if (host != 0 && host->m_bfme04 != 0)
		host = host->m_bfme04->bfmeTouchVTN();

	return host->m_bfme20;
}
