// Every row of the host asked in turn until one of its pieces takes the word.
// Both the host and the key sit ahead of this sub-object, at eight and twelve
// bytes back.

class BfmeItemLF
{
public:
	virtual void bfmeSpare000LF(void) = 0;
	virtual void bfmeSpare001LF(void) = 0;
	virtual void bfmeSpare002LF(void) = 0;
	virtual void bfmeSpare003LF(void) = 0;
	virtual void bfmeSpare004LF(void) = 0;
	virtual void bfmeSpare005LF(void) = 0;
	virtual void bfmeSpare006LF(void) = 0;
	virtual unsigned char bfmeAskLF(void *key) = 0;
	virtual unsigned char bfmeTakeLF(void *what) = 0;
};

class BfmeSubLF
{
public:
	virtual void bfmeSpare000LF(void);
	virtual void bfmeSpare001LF(void);
	virtual void bfmeSpare002LF(void);
	virtual void bfmeSpare003LF(void);
	virtual void bfmeSpare004LF(void);
	virtual void bfmeSpare005LF(void);
	virtual void bfmeSpare006LF(void);
	virtual void bfmeSpare007LF(void);
	virtual void bfmeSpare008LF(void);
	virtual void bfmeSpare009LF(void);
	virtual void bfmeSpare010LF(void);
	virtual void bfmeSpare011LF(void);
	virtual void bfmeSpare012LF(void);
	virtual void bfmeSpare013LF(void);
	virtual void bfmeSpare014LF(void);
	virtual void bfmeSpare015LF(void);
	virtual void bfmeSpare016LF(void);
	virtual void bfmeSpare017LF(void);
	virtual void bfmeSpare018LF(void);
	virtual void bfmeSpare019LF(void);
	virtual void bfmeSpare020LF(void);
	virtual void bfmeSpare021LF(void);
	virtual void bfmeSpare022LF(void);
	virtual void bfmeSpare023LF(void);
	virtual BfmeItemLF *bfmeFindLF(void);
};

struct BfmeRowLF
{
	unsigned char m_bfmeHead[0xc];		// 0x0
	BfmeSubLF m_bfmeSub;			// 0xc
};

struct BfmeHostLF
{
	unsigned char m_bfmeHead[0x1f0];	// 0x000
	BfmeRowLF **m_bfmeRows;			// 0x1f0
};

struct BfmeOtherLF
{
	unsigned char m_bfmeHead[8];		// 0x0
	void *m_bfmeKey;			// 0x8
};

class BfmeThingLF
{
public:
	unsigned char bfmeAskLF(void *what);
};

unsigned char BfmeThingLF::bfmeAskLF(void *what)
{
	BfmeHostLF *host = *(BfmeHostLF **)((char *)this - 8);

	BfmeRowLF **row = host->m_bfmeRows;

	while (*row != 0)
	{
		BfmeItemLF *got = (*row)->m_bfmeSub.bfmeFindLF();

		if (got != 0)
		{
			BfmeOtherLF *other = *(BfmeOtherLF **)((char *)this - 0xc);

			if (got->bfmeAskLF(other->m_bfmeKey) != 0)
				return got->bfmeTakeLF(what);
		}

		++row;
	}

	return 1;
}
