// cl: /EHs-c-

extern void (*TheBfmeFree)(void *p, unsigned int bytes);

class BfmeChildA
{
public:
	~BfmeChildA(void);

	void operator delete(void *p, unsigned int bytes) { TheBfmeFree(p, bytes); }

private:
	char m_bfmePad[0x10];
};

class Gen_008AB930
{
public:
	~Gen_008AB930(void) { delete m_bfmeChild; }

	void *scalarDelete(unsigned int flags);

	virtual void bfmeSlot0(void);

private:
	char m_bfmeHead[0x10 - 4];
	BfmeChildA *m_bfmeChild;
};

void *Gen_008AB930::scalarDelete(unsigned int flags)
{
	this->~Gen_008AB930();
	if (flags & 1)
		operator delete(this);
	return this;
}
