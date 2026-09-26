extern char g_bfmeEmptyETA[];

class BfmeUniETA;

struct BfmeStrDataETA
{
	int m_bfmeRefETA;
	int m_bfmeLenETA;
	char m_bfmeTextETA[1];
};

class BfmeStrETA
{
public:
	BfmeStrETA(const BfmeUniETA &other);

	~BfmeStrETA() { releaseBuffer(); }

	const char *bfmeTextETA() const
	{
		return m_bfmeDataETA ? m_bfmeDataETA->m_bfmeTextETA : g_bfmeEmptyETA;
	}

	BfmeStrDataETA *m_bfmeDataETA;

private:
	void releaseBuffer();
};

class BfmeInfoETA
{
public:
	virtual void bfmeSlot00ETA();
	virtual void bfmeSlot01ETA();
	virtual void bfmeSlot02ETA();
	virtual void bfmeSlot03ETA();
	virtual void bfmeSlot04ETA();
	virtual void bfmeSlot05ETA();
	virtual void bfmeSlot06ETA();
	virtual void bfmeSlot07ETA();
	virtual void bfmeSlot08ETA();
	virtual void bfmeSlot09ETA();
	virtual void bfmeSlot10ETA();
	virtual void bfmeSlot11ETA();
	virtual void bfmeSlot12ETA();
	virtual void bfmeSlot13ETA();
	virtual void bfmeSlot14ETA();
	virtual void bfmeSlot15ETA();
	virtual void bfmeSlot16ETA();
	virtual void bfmeSlot17ETA();
	virtual void bfmeSlot18ETA();
	virtual void *bfmeSlot19ETA(const char *text);
};

extern BfmeInfoETA *g_bfmeInfoETA;

void *bfmeLookupETA(const BfmeUniETA &name)
{
	BfmeStrETA text(name);

	return g_bfmeInfoETA->bfmeSlot19ETA(text.bfmeTextETA());
}
