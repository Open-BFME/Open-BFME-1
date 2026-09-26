extern int BfmeVfZQ;

class BfmeOwnerZQ
{
public:
	BfmeOwnerZQ *bfmeInitZQ(void *first, void *second, void *third, void *fourth);
	void bfmeBaseInitZQ(void *first, void *second, void *third, void *fourth, int fifth, int sixth);

	void *m_bfmeVfZQ;
};

BfmeOwnerZQ *BfmeOwnerZQ::bfmeInitZQ(void *first, void *second, void *third, void *fourth)
{
	bfmeBaseInitZQ(first, second, third, fourth, 1, 0);
	m_bfmeVfZQ = &BfmeVfZQ;

	return this;
}
