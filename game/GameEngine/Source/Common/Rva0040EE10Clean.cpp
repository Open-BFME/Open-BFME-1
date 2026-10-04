// cl: /O2 /Ob0

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class BfmeStrEE
{
public:
	void *m_data;
};

class BfmeHoldEE
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
};

class BfmeStrVM0
{
public:
	void bfmeRelVM0();
};

class BfmeObjEE
{
public:
	void bfmeGoEE();
	char m_00[0x34];
	BfmeHoldEE *m_34;
	char m_38[0x28];
	char m_60;
	char m_61[0x63];
	void *m_C4;
	void *m_C8;
	BfmeStrEE m_CC;
	char m_D0[0xC];
	int m_DC;
	int m_E0;
	char m_E4[0x24];
	char m_108;
};

void BfmeObjEE::bfmeGoEE()
{
	BfmeHoldEE *p = m_34;
	m_108 = 0;
	m_60 = 0;
	if (p)
	{
		// Retail 0x0040ECA0 is BfmeStrVM0::bfmeRelVM0, defined once in
		// game/GameEngine/Source/Common/BfmeConv1435.cpp. Minimal view;
		// the cast is pointer-size neutral.
		((BfmeStrVM0 *)this)->bfmeRelVM0();
		m_34->v7();
		m_34 = 0;
	}
	BfmeStrEE *s = &m_CC;
	m_C4 = 0;
	m_C8 = 0;
	if (s->m_data && *(short *)((char *)s->m_data + 4))
		// Retail pushes 0x01336E50, WWLib's AsciiString::TheEmptyString
		// (defined once in BoneFXUpdate_initTimes.cpp), and calls the
		// narrow StringBase<char>::set (0x00887C90, StringBase.cpp).
		((StringBase<char> *)s)->set(AsciiString::TheEmptyString);
	int n = -1;
	m_E0 = n;
	m_DC = n;
}
