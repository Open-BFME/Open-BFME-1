extern void (*TheBfmeFree)(void *p, unsigned int bytes);

// 0x0089C880 is matched in functions.csv as Gen0089C880::handle(); the only
// declaration of that class lives in a TU, so it is redeclared here.
class Gen0089C880
{
public:
	void handle(void);
};

class BfmeSubB1035
{
public:
	~BfmeSubB1035(void);
	void bfmeDestroy1035(void);

	void operator delete(void *p, unsigned int bytes) { TheBfmeFree(p, bytes); }

private:
	char m_bfmePad[0x10];
};

void BfmeSubB1035::bfmeDestroy1035(void)
{
	((Gen0089C880 *)this)->handle();
	delete this;
}
