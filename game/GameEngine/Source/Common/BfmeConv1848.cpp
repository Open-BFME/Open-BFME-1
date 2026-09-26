struct BfmeArgXO
{
	BfmeArgXO(void *owner, unsigned int tag, int slot, void *data)
	{
		m_bfmeOwnerXO = owner;
		m_bfmeTagXO = tag;
		m_bfmeSlotXO = slot;
		m_bfmeDataXO = data;
	}

	void *m_bfmeOwnerXO;
	unsigned int m_bfmeTagXO;
	int m_bfmeSlotXO;
	void *m_bfmeDataXO;
};

void __cdecl bfmeCallXO(void *a1, void *a2, int a3, BfmeArgXO arg);

class BfmeOwnerXO
{
public:
	void bfmeSendXO(void *a1, void *a2, int a3, int a4, void *a5, unsigned int a6);
};

void BfmeOwnerXO::bfmeSendXO(void *a1, void *a2, int a3, int a4, void *a5, unsigned int a6)
{
	if (a6 != 0 && a3 >= 0 && a4 >= 0 && a4 < 2 && a5 != 0)
		bfmeCallXO(a1, a2, a3, BfmeArgXO(this, a6 & 0xffff, a4, a5));
}
