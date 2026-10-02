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

// The shroud circle walker at retail 0x008F9BB0 is
// ?bfmeCallXO@@YA_NHHHUBfmeArgXO@@@Z -- three ints then the four-word struct,
// passed by value.  This file's wrapper builds the struct in the outgoing
// argument area and pushes the three words after it, which is the same stack
// shape, so only the declared parameter types were wrong here.
bool __cdecl bfmeCallXO(int cellX, int cellY, int cellRadius, BfmeArgXO arg);

class BfmeOwnerXO
{
public:
	void bfmeSendXO(void *a1, void *a2, int a3, int a4, void *a5, unsigned int a6);
};

void BfmeOwnerXO::bfmeSendXO(void *a1, void *a2, int a3, int a4, void *a5, unsigned int a6)
{
	if (a6 != 0 && a3 >= 0 && a4 >= 0 && a4 < 2 && a5 != 0)
		bfmeCallXO((int)a1, (int)a2, a3, BfmeArgXO(this, a6 & 0xffff, a4, a5));
}
