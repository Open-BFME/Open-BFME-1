// Two errands: a row of listeners called back to front with the word passed on,
// and a newcomer marked when it is not already known before three lists take it
// in.

class BfmeThingIO;

struct BfmeSlotIO
{
	void (__cdecl *m_bfmeTell)(void *what, BfmeThingIO *thing, void *note);
	void *m_bfmeNote;
};

class BfmeThingIO
{
public:
	void bfmeTellIO(void *what);

private:
	unsigned char m_bfmeHead[0x24];		// 0x00
	BfmeSlotIO *m_bfmeSlots;		// 0x24
	unsigned char m_bfmeGap[4];		// 0x28
	unsigned int m_bfmeCount;		// 0x2c
};

void BfmeThingIO::bfmeTellIO(void *what)
{
	unsigned int at = m_bfmeCount;

	while (at > 0)
	{
		m_bfmeSlots[at - 1].m_bfmeTell(what, this, m_bfmeSlots[at - 1].m_bfmeNote);

		--at;
	}
}

struct BfmePairIP
{
	unsigned char m_bfmeFirst;		// 0x0
	unsigned char m_bfmeSecond;		// 0x1
};


class BfmeItemIP
{
public:
	virtual void bfmeSpare000IP(void) = 0;
	virtual void bfmeSpare001IP(void) = 0;
	virtual void bfmeSpare002IP(void) = 0;
	virtual void bfmeSpare003IP(void) = 0;
	virtual unsigned char bfmeIsIP(void) = 0;
	virtual void bfmeSpare005IP(void) = 0;
	virtual void bfmeSpare006IP(void) = 0;
	virtual void bfmeSpare007IP(void) = 0;
	virtual void bfmeSpare008IP(void) = 0;
	virtual void bfmeSpare009IP(void) = 0;
	virtual void bfmeMarkIP(BfmePairIP *both) = 0;
};

class BfmeListIP
{
public:
	virtual void bfmeSpare000IP(void);
	virtual void bfmeSpare001IP(void);
	virtual void bfmeSpare002IP(void);
	virtual void bfmeAddIP(BfmeItemIP *item);

private:
	unsigned char m_bfmeBody[0x14];		// 0x04
};

class BfmeThingIP
{
public:
	void bfmeTakeIP(BfmeItemIP *item);

private:
	unsigned char m_bfmeHead[4];		// 0x00
	BfmeListIP m_bfmeLists[3];		// 0x04
};

void BfmeThingIP::bfmeTakeIP(BfmeItemIP *item)
{
	if (item->bfmeIsIP() == 0)
	{
		BfmePairIP both;

		both.m_bfmeFirst = 1;
		both.m_bfmeSecond = 1;

		item->bfmeMarkIP(&both);

		BfmeListIP *at = m_bfmeLists;

		for (int left = 3; left != 0; --left)
		{
			at->bfmeAddIP(item);

			++at;
		}
	}
}

