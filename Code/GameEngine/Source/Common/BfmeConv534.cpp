class BFMERetailAsciiString;

template <typename T> class StringBase
{
	friend class BFMERetailAsciiString;

private:
	StringBase(const T *text);
	StringBase(const StringBase &other);
	void releaseBuffer();
	void *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString(const char *text) : StringBase<char>(text) {}
	BFMERetailAsciiString(const BFMERetailAsciiString &other) : StringBase<char>(other) {}
	~BFMERetailAsciiString() { releaseBuffer(); }
};

class BfmeInnerBUE
{
public:
	virtual void bfmeSpareBUE0();
	virtual void bfmeRunBUE(void *what);
	virtual void bfmeSpareBUE2();
	virtual void bfmeSpareBUE3();
	virtual void bfmeSpareBUE4();
	virtual void bfmeSpareBUE5();
	virtual void bfmeSpareBUE6();
	virtual void bfmeSpareBUE7();
	virtual void bfmeSpareBUE8();
	virtual void bfmeSpareBUE9();
	virtual void bfmeSpareBUE10();
	virtual void bfmeSpareBUE11();
	virtual void bfmeSpareBUE12();
	virtual void bfmeSpareBUE13();
	virtual void bfmeSpareBUE14();
	virtual void bfmeSpareBUE15();
	virtual void bfmeSpareBUE16();
	virtual void bfmeSpareBUE17();
	virtual void bfmeSpareBUE18();
	virtual void bfmeSpareBUE19();
	virtual void bfmeSpareBUE20();
	virtual void bfmeSpareBUE21();
	virtual void bfmeSpareBUE22();
	virtual void bfmeSpareBUE23();
	virtual void bfmeSpareBUE24();
	virtual void bfmeSpareBUE25();
	virtual void bfmeSpareBUE26();
	virtual void bfmeSpareBUE27();
	virtual BFMERetailAsciiString bfmeGetBUE();
};

struct BfmeSubBUE
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerBUE m_bfmeInner;
};

class BfmeOuterBUE
{
public:
	bool bfmeAskBUE();
};

class BfmeThingBUE
{
public:
	void bfmeGoBUE(void *what);
	BFMERetailAsciiString bfmeGetBUE();
	unsigned char m_bfmeHead[0xd0];
	BfmeSubBUE *m_bfmeSub;
};

void BfmeThingBUE::bfmeGoBUE(void *what)
{
	if (((BfmeOuterBUE *)((char *)this - 0x10))->bfmeAskBUE())
		m_bfmeSub->m_bfmeInner.bfmeRunBUE(what);
}

BFMERetailAsciiString BfmeThingBUE::bfmeGetBUE()
{
	return ((BfmeOuterBUE *)((char *)this - 0x10))->bfmeAskBUE()
		? m_bfmeSub->m_bfmeInner.bfmeGetBUE()
		: (const char *)0x0107301c;
}
