extern void (*TheBfmeFree)(void *p, unsigned int bytes);

// 0x0089C880 is matched in functions.csv as Gen0089C880::handle(); the only
// declaration of that class lives in a TU, so it is redeclared here.
class Gen0089C880
{
public:
	void handle(void);
};

// The destructor route 8976E0 -> 89CC70 -> 89C900 ends at the matched
// Q3EhMember0089C900 cleanup. The first jump body owns this call target.
extern void j_008976e0();

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
	if (this)
	{
		((void (__fastcall *)(BfmeSubB1035 *))j_008976e0)(this);
		BfmeSubB1035::operator delete(this, sizeof(BfmeSubB1035));
	}
}
