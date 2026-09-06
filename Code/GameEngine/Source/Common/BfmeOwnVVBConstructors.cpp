// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the two constructors of the BfmeOwnVVB owner whose destructor
// landed in BfmeOwnVVBDestructor.cpp: 0x001903F0 (id, arg) and 0x00190340
// (arg, id drawn from the global counter g_bfmeBFAE). The node-list pointer at
// +4 is zeroed before the vptr store, so it lives in a non-virtual base; the
// two AsciiString members default to null, the six-element table is built by
// the CRT vector constructor iterator over an out-of-line element ctor/dtor,
// then init(arg) runs on the finished object.
class BfmeOwnVVBNode;

class BfmeOwnVVBNodeList
{
public:
	BfmeOwnVVBNodeList() : m_nodes(0) {}
	BfmeOwnVVBNode *m_nodes;
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();
private:
	char *m_data;
};

class BfmeElemBX
{
public:
	BfmeElemBX();
	~BfmeElemBX();
private:
	char m_body[4];
};

extern int g_bfmeBFAE;

class BfmeOwnVVB : public BfmeOwnVVBNodeList
{
public:
	BfmeOwnVVB(int id, void *arg);
	BfmeOwnVVB(void *arg);
	virtual ~BfmeOwnVVB();
private:
	void init(void *arg);
	AsciiString m_name;
	int m_id;
	char *m_owned;
	char m_gap1[0x20];
	AsciiString m_description;
	int m_gap38;
	void *m_extra3c;
	char m_gap40[8];
	BfmeElemBX m_elements[6];
};

BfmeOwnVVB::BfmeOwnVVB(int id, void *arg)
	: m_id(id), m_extra3c(0)
{
	init(arg);
}

BfmeOwnVVB::BfmeOwnVVB(void *arg)
	: m_id(g_bfmeBFAE++), m_extra3c(0)
{
	init(arg);
}
