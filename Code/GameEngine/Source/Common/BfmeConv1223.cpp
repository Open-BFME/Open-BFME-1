// Open-BFME5 conversions.

class BfmeSub1223
{
public:
	int bfmeLen1223();
	int m_bfme00;
};

class BfmeA1223
{
public:
	int bfmeSize1223();
	char m_bfmePad00[8];
	BfmeSub1223 m_bfme08;
	char m_bfmePad0c[0x1c - 0x0c];
	int m_bfme1c;
};

int BfmeA1223::bfmeSize1223()
{
	return m_bfme08.bfmeLen1223() + (m_bfme1c & 0xff) + 3;
}
