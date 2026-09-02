// cl: /O2 /Ob0
// Open-BFME5: thiscall ctor at 0x0081D760. vptr, WideStr copy at +4,
// six dword fields, then a trailing byte cleared.

class WideStr
{
public:
	WideStr(const WideStr &other);

private:
	void *m_data;
};

class Rva0081D760
{
public:
	Rva0081D760(const WideStr &s, int a, int b, int c, int d, int e, int f);
	virtual void pad();	// declared only so the vptr is set before m_str

private:
	WideStr m_str;		// +0x04
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	char m_20;
};

Rva0081D760::Rva0081D760(const WideStr &s, int a, int b, int c, int d, int e, int f)
	: m_str(s)
{
	m_08 = a;
	m_0C = b;
	m_10 = c;
	m_14 = d;
	m_18 = e;
	m_1C = f;
	m_20 = 0;
}
