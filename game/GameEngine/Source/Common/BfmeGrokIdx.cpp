// cl: /O2 /EHsc

class BfmeRecWL
{
public:
	BfmeRecWL(const BfmeRecWL &);
	~BfmeRecWL();
	char m_body[40];
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
	return m_recs[idx];
}
