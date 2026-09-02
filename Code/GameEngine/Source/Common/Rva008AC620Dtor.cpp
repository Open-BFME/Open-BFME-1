// cl: /EHsc

extern void (*TheBfmeFree)(void *p, unsigned int bytes);
extern void (__cdecl *g_bfmeFreeDWF)(void *p);

class BfmeChildB
{
public:
	~BfmeChildB(void);

	void operator delete(void *p, unsigned int bytes) { TheBfmeFree(p, bytes); }

private:
	char m_bfmePad[0x10];
};

class Gen_uwm_008be6d0
{
public:
	~Gen_uwm_008be6d0(void);

private:
	char m_pad[8];
};

class Gen_008AC620Base
{
public:
	~Gen_008AC620Base(void) { delete m_child; }

	virtual void bfmeSlot0(void);

protected:
	char m_pad4[0x0C - 4];
	void *m_ptr;
	BfmeChildB *m_child;
	char m_pad14[0x24 - 0x14];
};

class Gen_008AC620 : public Gen_008AC620Base
{
public:
	~Gen_008AC620(void);

private:
	Gen_uwm_008be6d0 m_d;
	int m_flag;
};

Gen_008AC620::~Gen_008AC620(void)
{
	if (m_flag == 1)
		g_bfmeFreeDWF(m_ptr);
}
