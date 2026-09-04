// ?applyField@BfmeApplyFieldHolder@@QAEXABVRva0060FD30Base@@@Z
// partial score=0.92 date=2026-09-04
// ?applyField@BfmeApplyFieldHolder@@QAEXABVRva0060FD30Base@@@Z
// partial score=0.92 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

class Rva0060FD30Base
{
public:
	Rva0060FD30Base(const Rva0060FD30Base &other);
	unsigned char *m_ptr;
	unsigned char m_rest[8];
};

class Gen00001B18
{
public:
	unsigned char m_beforeAc[0xac];
	unsigned int m_fieldAc;
};

Gen00001B18 *Make00001B18(void);

class BfmeApplyFieldHolder
{
public:
	void applyField(const Rva0060FD30Base &src);

private:
	unsigned char m_before[0x14];
	Rva0060FD30Base m_obj;
	unsigned int m_field20;
};

void BfmeApplyFieldHolder::applyField(const Rva0060FD30Base &src)
{
	if (src.m_ptr)
	{
		m_obj.Rva0060FD30Base::Rva0060FD30Base(src);
		Gen00001B18 *p = (Gen00001B18 *)m_obj.m_ptr;
		if (!p)
			m_field20 = Make00001B18()->m_fieldAc;
		else
			m_field20 = p->m_fieldAc;
	}
}
