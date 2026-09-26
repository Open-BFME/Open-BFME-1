extern void (*TheBfmeFree)(void *p, unsigned int bytes);

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA(void);

	void operator delete(void *p, unsigned int bytes) { TheBfmeFree(p, bytes); }

private:
	char m_bfmePad[0x18];
};

class Gen_00895670
{
public:
	Gen_00895670(BfmeDropObjectA *obj, void *extra);

private:
	void *m_zero;
	BfmeDropObjectA *m_obj;
	void *m_extra;
	char m_flag;
};

Gen_00895670::Gen_00895670(BfmeDropObjectA *obj, void *extra)
{
	m_zero = 0;
	m_obj = obj;
	if (obj)
		++*(int *)obj;
	m_extra = extra;
	m_flag = 0;
	if (obj && --*(int *)obj == 0)
		delete obj;
}
