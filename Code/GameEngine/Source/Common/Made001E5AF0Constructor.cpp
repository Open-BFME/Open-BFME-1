// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Made001E5AF0 constructor, retail 0x002DED90, 97 bytes. The class
// is declared in Q4MakeNotifyLink.cpp as a 0x68-byte derived of GenBase002DF2B0.
// Base ctor runs, derived vtable 0x010CF270 is installed, the 12-byte member at
// +0x58 is zeroed and handed to a thiscall with its two pointer fields, then
// the word at +0x64 is cleared.

typedef int Int;

class Q4Owner001E5A20;

class GenBase002DF2B0
{
public:
	GenBase002DF2B0();
	~GenBase002DF2B0();
	virtual void slot();

	char m_gap04[0x34 - 4];
	Q4Owner001E5A20 *m_owner;
	char m_gap38[0x54 - 0x38];
	char m_flag;
	char m_tail55[3];
};

class Made001E5AF0Member
{
public:
	Made001E5AF0Member()
	{
		m_start = 0;
		m_finish = 0;
		m_end = 0;
	}
	~Made001E5AF0Member();
	void assign(void *first, void *last);

	void *volatile m_start;
	void *volatile m_finish;
	void *m_end;
};

class Made001E5AF0 : public GenBase002DF2B0
{
public:
	__declspec(noinline) Made001E5AF0();
	virtual void slot();

private:
	Made001E5AF0Member m_member;
	Int m_64;
};

// ??0Made001E5AF0@@QAE@XZ
Made001E5AF0::Made001E5AF0()
{
	Made001E5AF0Member *p = &m_member;
	void *last = p->m_finish;
	void *first = p->m_start;
	p->assign(first, last);
	m_64 = 0;
}
