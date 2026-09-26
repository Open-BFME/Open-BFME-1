extern "C" int __cdecl ghttpGetA(char *url, int post, char *callback, void *param);

extern "C" char bfmeUrlXK[];
extern "C" char bfmeCbXK[];

struct BfmeRecXK
{
	void *m_bfmeOwnerXK;
	unsigned char m_bfmeTailXK[8];
};

class BfmeMapXK
{
public:
	BfmeRecXK *&bfmeAtXK(const int &k);

	unsigned char m_bfmeHeadXK[0x10];
};

class BfmeHostXK
{
public:
	void bfmeStartXK();

	unsigned char m_bfmeHeadXK[0x5c];
	BfmeMapXK m_bfme5CXK;
};

void BfmeHostXK::bfmeStartXK()
{
	int req = ghttpGetA(bfmeUrlXK, 0, bfmeCbXK, this);

	if (req)
	{
		BfmeRecXK *r = new BfmeRecXK;

		r->m_bfmeOwnerXK = this;
		m_bfme5CXK.bfmeAtXK(req) = r;
	}
}
