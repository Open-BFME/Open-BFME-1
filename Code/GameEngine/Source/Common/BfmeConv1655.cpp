// Open-BFME5 conversions.

class BfmeStrVUV
{
public:
	BfmeStrVUV(const BfmeStrVUV &other);
	~BfmeStrVUV() { bfmeClearVUV(); }
	void bfmeClearVUV();

	const char *bfmeTextVUV() const
	{
		return m_bfme00 != 0 ? m_bfme00 + 8 : "";
	}

	char *m_bfme00;
};

class BfmeSinkVUV
{
public:
	virtual void bfmeSlot0VUV();
	virtual void bfmeSlot1VUV();
	virtual void *bfmeSlot2VUV(const char *first, const char *second, const char *third,
		const char *fourth, const char *fifth, const char *sixth, int seventh);
};

class BfmeOwnVUV
{
public:
	void *bfmeLogVUV(BfmeStrVUV first, BfmeStrVUV second, BfmeStrVUV third,
		BfmeStrVUV fourth, BfmeStrVUV fifth, BfmeStrVUV sixth, int seventh);
	char m_bfmePad00[8];
	BfmeSinkVUV *m_bfme08;
};

void *BfmeOwnVUV::bfmeLogVUV(BfmeStrVUV first, BfmeStrVUV second, BfmeStrVUV third,
	BfmeStrVUV fourth, BfmeStrVUV fifth, BfmeStrVUV sixth, int seventh)
{
	return m_bfme08->bfmeSlot2VUV(first.bfmeTextVUV(), second.bfmeTextVUV(),
		third.bfmeTextVUV(), fourth.bfmeTextVUV(), fifth.bfmeTextVUV(),
		sixth.bfmeTextVUV(), seventh);
}
