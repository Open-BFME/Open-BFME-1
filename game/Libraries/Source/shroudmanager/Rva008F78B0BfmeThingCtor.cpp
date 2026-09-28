// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// ??0BfmeThingCDE@@QAE@PAX00@Z

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class CDEProvider;

class CDEVirtualBase
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3(void *value);
	virtual void *f4();
};

class CDELeading
{
public:
	virtual void f0();
	virtual CDEProvider *f1();
	virtual CDEProvider *f2();
};

class CDEProvider : public CDELeading, public virtual CDEVirtualBase
{
public:
	virtual void f0();
};

class BfmeThingCDE
{
public:
	BfmeThingCDE(void *what, void *owner, void *head);

	void *m_00;
	CDEProvider *m_04;
	CDEProvider *m_08;
	BfmeThingCDE **m_0c;
	BfmeThingCDE *m_10;
	BfmeThingCDE *m_14;
	BfmeThingCDE *m_18;
	void *m_1c;
	int m_20;
	int m_24[16];
	int m_64[16];
	unsigned char m_a4[16];
	unsigned int m_b4;
	unsigned int m_b8;
	int m_bc;
	int m_c0;
	int m_c4;
	int m_c8;
	int m_cc[2];
	unsigned int m_d4[2];
	unsigned char m_dc;
};

BfmeThingCDE::BfmeThingCDE(void *what, void *owner, void *head)
	: m_04((CDEProvider *)what),
	  m_00(owner),
	  m_08(0),
	  m_14(0),
	  m_18(0),
	  m_1c(0),
	  m_20(0),
	  m_b4(0xdeadbeef),
	  m_b8(0x0badf00d),
	  m_bc(-1),
	  m_c0(0),
	  m_dc(0)
{
	m_0c = (BfmeThingCDE **)head;
	BfmeThingCDE **link = (BfmeThingCDE **)head;
	m_10 = *link;
	if (m_10 != 0)
		m_10->m_0c = &m_10;
	*link = this;

	for (unsigned int i = 0; i < 16; ++i)
	{
		m_64[i] = 0;
		m_24[i] = 0;
		m_a4[i] = 0;
	}

	m_c4 = -1;
	m_c8 = -1;
	_ReadWriteBarrier();
	m_04->f3(this);
	m_08 = ((CDELeading *)m_04)->f2();
	if (m_08 != 0)
		m_08->f3(this);
}
