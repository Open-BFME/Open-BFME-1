// cl: /MD
// Open-BFME5 conversions.

#include <exception>

class FunctorNotSet : public std::exception
{
public:
	FunctorNotSet() : std::exception() {}
};


class BfmeB1042
{
public:
	virtual void bfmeV01042();
	virtual void bfmeDo1042(int a);
	virtual void bfmeRun1042();
};

class BfmeB1042N
{
public:
	virtual void bfmeV01042N();
	virtual void bfmeDoN1042();
};

class BfmeA1042N
{
public:
	void bfmeGo1042D(void);

	BfmeB1042N *m_bfmeP;
};

void BfmeA1042N::bfmeGo1042D(void)
{
	BfmeB1042N *p = m_bfmeP;

	if (p == 0) {
		throw FunctorNotSet();
	}

	p->bfmeDoN1042();
}

class BfmeA1042
{
public:
	void bfmeGo1042A(int a);
	void bfmeGo1042B(int a);
	void bfmeGo1042C(int a);

	BfmeB1042 *m_bfmeP;
};

void BfmeA1042::bfmeGo1042A(int a)
{
	BfmeB1042 *p = m_bfmeP;

	if (p == 0) {
		throw FunctorNotSet();
	}

	p->bfmeDo1042(a);
}

void BfmeA1042::bfmeGo1042B(int a)
{
	BfmeB1042 *p = m_bfmeP;

	if (p == 0) {
		throw FunctorNotSet();
	}

	p->bfmeDo1042(a);
}

void BfmeA1042::bfmeGo1042C(int a)
{
	BfmeB1042 *p = m_bfmeP;

	if (p == 0) {
		throw FunctorNotSet();
	}

	p->bfmeDo1042(a);
}

struct BfmeR1042
{
	char *m_bfmeName;
};

// 0x00942BC0, matched as Gen_00942BC0::process (Gen_00942BC0.cpp).
class Gen_00942BC0
{
public:
	void process(void *t, void *a, void *b);
};

extern const unsigned short BFMEEmptyUnicodeString;

class BfmeC1042
{
public:
	void bfmeGo1042E(BfmeR1042 *p);

	char m_bfmePad[4];
	Gen_00942BC0 m_bfmeSub;
	char m_bfmePad2[0xd7];
	char m_bfmeFlag;
};

void BfmeC1042::bfmeGo1042E(BfmeR1042 *p)
{
	char *t;

	if (p->m_bfmeName != 0)
		t = p->m_bfmeName + 8;
	else
		t = (char *)&BFMEEmptyUnicodeString;

	m_bfmeSub.process(t, 0, 0);
	m_bfmeFlag = 1;
}

