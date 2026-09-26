// Open-BFME5 conversions.

class BfmeStrNVUY
{
public:
	BfmeStrNVUY(const BfmeStrNVUY &other);
	~BfmeStrNVUY() { bfmeClearNVUY(); }
	char *m_bfme00;

private:
	void bfmeClearNVUY();
};

class BfmeStrWVUY
{
public:
	BfmeStrWVUY() { m_bfme00 = 0; }
	~BfmeStrWVUY() { bfmeClearWVUY(); }
	void bfmeTranslateVUY(const BfmeStrNVUY &text);
	unsigned short *m_bfme00;

private:
	void bfmeClearWVUY();
};

class BfmeOwnVUY
{
public:
	char bfmeApplyVUY(BfmeStrNVUY text);
	virtual void bfmeSlot0VUY();
	virtual void bfmeSlot1VUY();
	virtual void bfmeSlot2VUY();
	virtual void bfmeSlot3VUY();
	virtual char bfmeSlot4VUY(BfmeStrWVUY *text);
};

char BfmeOwnVUY::bfmeApplyVUY(BfmeStrNVUY text)
{
	BfmeStrWVUY wide;

	wide.bfmeTranslateVUY(text);

	return bfmeSlot4VUY(&wide);
}
