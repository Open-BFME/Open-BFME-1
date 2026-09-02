extern void (*TheBfmeFree)(void *p, unsigned int bytes);

class BfmeSubB1035
{
public:
	void bfmeClear1035(void);
	~BfmeSubB1035(void);
	void bfmeDestroy1035(void);

	void operator delete(void *p, unsigned int bytes) { TheBfmeFree(p, bytes); }

private:
	char m_bfmePad[0x10];
};

void BfmeSubB1035::bfmeDestroy1035(void)
{
	bfmeClear1035();
	delete this;
}
