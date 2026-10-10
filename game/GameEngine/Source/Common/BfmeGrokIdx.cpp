// cl: /O2 /EHsc

class Open2Rec74A060
{
public:
	Open2Rec74A060(const Open2Rec74A060 &other);
	char m_body[40];
};

class BfmeRecWL
{
public:
	BfmeRecWL(const Open2Rec74A060 &other) : m_rec(other) {}
	~BfmeRecWL();
	Open2Rec74A060 m_rec;
};

class BfmeOwnerWL
{
public:
	BfmeRecWL getAt(int idx);

private:
	char m_pad[0x80C0];
	BfmeRecWL m_recs[1];
};

BfmeRecWL BfmeOwnerWL::getAt(int idx)
{
	return m_recs[idx].m_rec;
}
