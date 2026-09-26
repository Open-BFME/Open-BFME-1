// Open-BFME5 conversions.

class BfmeStrVSM
{
public:
	void bfmeAssignVSM(const BfmeStrVSM &other);
	char *m_bfme00;
};

struct BfmeEntVSM
{
	int m_bfme00;
	BfmeStrVSM m_bfme04;
};

class BfmeOwnVSM
{
public:
	char m_bfmePad000[0xf0];
	BfmeEntVSM *m_bfmef0;
	BfmeEntVSM *m_bfmef4;
};

class BfmeIterVSM
{
public:
	char bfmeFetchVSM(int index, BfmeEntVSM *out);
};

char BfmeIterVSM::bfmeFetchVSM(int index, BfmeEntVSM *out)
{
	BfmeOwnVSM *owner = *(BfmeOwnVSM **)((char *)this - 8);
	BfmeEntVSM *entry;

	if (index < 0 || index >= owner->m_bfmef4 - owner->m_bfmef0)
		return 0;

	entry = &(*(BfmeOwnVSM **)((char *)this - 8))->m_bfmef0[index];
	out->m_bfme00 = entry->m_bfme00;
	out->m_bfme04.bfmeAssignVSM(entry->m_bfme04);

	return 1;
}
