class StringBaseG
{
public:
	~StringBaseG() { releaseBuffer(); }

	void *m_bfmeBufDQ;

private:
	void releaseBuffer();
};

class GameTextInterface
{
public:
	virtual void bfmeSlot00GT();
	virtual void bfmeSlot01GT();
	virtual void bfmeSlot02GT();
	virtual void bfmeSlot03GT();
	virtual void bfmeSlot04GT();
	virtual void bfmeSlot05GT();
	virtual void bfmeSlot06GT();
	virtual void bfmeSlot07GT();
	virtual void bfmeSlot08GT();
	virtual void bfmeSlot09GT();
	virtual StringBaseG bfmeFetchDQ(const char *label, char *found);
};

extern GameTextInterface *TheGameText;

class InGameUI
{
public:
	virtual void bfmeSlot00UI();
	virtual void bfmeSlot01UI();
	virtual void bfmeSlot02UI();
	virtual void bfmeSlot03UI();
	virtual void bfmeSlot04UI();
	virtual void bfmeSlot05UI();
	virtual void bfmeSlot06UI();
	virtual void bfmeSlot07UI();
	virtual void bfmeSlot08UI();
	virtual void bfmeSlot09UI();
	virtual void bfmeSlot10UI();
	virtual void bfmeSlot11UI();
	virtual void bfmeSlot12UI();
	virtual void bfmeSlot13UI();
	virtual void bfmeSlot14UI();
	virtual void bfmeSlot15UI();
	virtual void bfmeSlot16UI();
	virtual void bfmeSlot17UI();
	virtual void bfmeSlot18UI();
	virtual void bfmeSlot19UI();
	virtual void bfmeSlot20UI();
	virtual void bfmeSlot21UI();
	virtual void bfmeShowDQ(StringBaseG *text, int mode);
};

extern InGameUI *TheInGameUI;

class BfmeHostDQ
{
public:
	void bfmeTickDQ();

	unsigned char m_bfmeHeadDQ[0x290];
	int m_bfmeCountDQ;
	unsigned char m_bfmeActiveDQ;
};

void BfmeHostDQ::bfmeTickDQ()
{
	if (m_bfmeActiveDQ == 0)
		return;

	if (m_bfmeCountDQ <= 0)
		return;

	if (--m_bfmeCountDQ != 0)
		return;

	char found;
	StringBaseG text = TheGameText->bfmeFetchDQ("LW:ClickToBegin", &found);

	if (found != 0)
		TheInGameUI->bfmeShowDQ(&text, 10);

	m_bfmeActiveDQ = 0;
}
