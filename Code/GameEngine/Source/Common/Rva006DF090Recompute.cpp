// cl: /O2 /DNDEBUG /MD /EHsc
// Same object as ??0Rva006DF550@@QAE@XZ (vtable 0x0111E188). After virtual
// slots 0x30..0x40 run, +0x18 is dirty unless +4/+8/+0xC/+0x10 equal
// 120, 300, 37.5 and the double constant at 0x01085F58.

extern double Gen01085F58;

class Rva006DF550
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void v40();

	void recompute();

	float m_04;
	float m_08;
	float m_0C;
	float m_10;
	float m_14;
	char m_18;
};

void Rva006DF550::recompute()
{
	v30();
	v34();
	v38();
	v3c();
	v40();
	if (m_0C == 37.5f && (double)m_10 == Gen01085F58 && m_04 == 120.0f && m_08 == 300.0f)
		m_18 = 0;
	else
		m_18 = 1;
}
