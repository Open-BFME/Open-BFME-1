// Open-BFME5 conversions.

class BfmeStrAVTV
{
public:
	BfmeStrAVTV(const BfmeStrAVTV &other);
	~BfmeStrAVTV();
	char *m_bfme00;
};

class BfmeStrBVTV
{
public:
	BfmeStrBVTV(const BfmeStrBVTV &other);
	~BfmeStrBVTV();
	char *m_bfme00;
};

class BfmeEntVTV
{
public:
	BfmeEntVTV(const BfmeEntVTV &other);
	BfmeStrAVTV m_bfme00;
	int m_bfme04;
	BfmeStrBVTV m_bfme08;
};

BfmeEntVTV::BfmeEntVTV(const BfmeEntVTV &other)
	: m_bfme00(other.m_bfme00), m_bfme04(other.m_bfme04), m_bfme08(other.m_bfme08)
{
}
