// cl: /O2 /Ob0
//
// 18-byte flag + virtual: test byte [this+8], 0x10; if clear, call
// vtable[+0x0C](this+0x30); always xor eax,eax / ret.

class Rva00478F40
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void slot(void *p);

	int apply();

private:
	char m_pad4[4];
	unsigned char m_flags;
	char m_pad9[0x27];
	char m_sub;
};

int Rva00478F40::apply()
{
	if ((m_flags & 0x10) == 0)
		slot(&m_sub);
	return 0;
}
