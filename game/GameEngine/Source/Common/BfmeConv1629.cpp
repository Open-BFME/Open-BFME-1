// Open-BFME5 conversions.

class BfmeStrVTZ
{
public:
	BfmeStrVTZ(const BfmeStrVTZ &other);
	~BfmeStrVTZ();
	char *m_bfme00;
};

class BfmeRecVTZ
{
public:
	BfmeRecVTZ(const BfmeStrVTZ &first, const BfmeStrVTZ &second, int third,
		int fourth, char fifth);
	BfmeStrVTZ m_bfme00;
	BfmeStrVTZ m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	char m_bfme10;
	char m_bfme11;
};

BfmeRecVTZ::BfmeRecVTZ(const BfmeStrVTZ &first, const BfmeStrVTZ &second, int third,
	int fourth, char fifth)
	: m_bfme00(first), m_bfme04(second), m_bfme08(third), m_bfme0c(fourth),
	  m_bfme10(0), m_bfme11(fifth)
{
}
