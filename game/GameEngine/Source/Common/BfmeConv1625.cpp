// Open-BFME5 conversions.

class BfmeStrAVTW
{
public:
	BfmeStrAVTW(const BfmeStrAVTW &other);
	~BfmeStrAVTW();
	char *m_bfme00;
};

class BfmeStrBVTW
{
public:
	BfmeStrBVTW(const BfmeStrBVTW &other);
	~BfmeStrBVTW();
	char *m_bfme00;
};

struct BfmePairVTW
{
	int m_bfme00;
	BfmeStrBVTW m_bfme04;
};

class BfmeEntVTW
{
public:
	BfmeEntVTW(const BfmeStrAVTW &first, const BfmePairVTW &second);
	BfmeStrAVTW m_bfme00;
	int m_bfme04;
	BfmeStrBVTW m_bfme08;
};

BfmeEntVTW::BfmeEntVTW(const BfmeStrAVTW &first, const BfmePairVTW &second)
	: m_bfme00(first), m_bfme04(second.m_bfme00), m_bfme08(second.m_bfme04)
{
}
