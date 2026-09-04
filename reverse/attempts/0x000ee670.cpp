// ?getAt@AsciiStringVectorHolder@@QBE?AVAsciiString@@I@Z
// partial score=0.92 date=2026-09-04
// ?getAt@AsciiStringVectorHolder@@QBE?AVAsciiString@@I@Z
// partial score=0.92 date=2026-09-04
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Gy /O2 /Ob1
// stlport
// AsciiStringVectorHolder::getAt at 0x000EE670 (77B).

class AsciiString
{
public:
	AsciiString(const AsciiString &);

private:
	void *m_data;
};

extern char TheEmptyAsciiString;

class AsciiStringVectorHolder
{
public:
	AsciiString getAt(unsigned int index) const;

private:
	char m_pad[8];
	AsciiString *m_begin;	// +8
	AsciiString *m_finish;	// +0xc
};

AsciiString AsciiStringVectorHolder::getAt(unsigned int index) const
{
	volatile int dead = 0;
	AsciiString *begin = m_begin;
	unsigned int n = (unsigned int)(m_finish - begin);
	if (index < n)
		return begin[index];
	return *(const AsciiString *)&TheEmptyAsciiString;
}
