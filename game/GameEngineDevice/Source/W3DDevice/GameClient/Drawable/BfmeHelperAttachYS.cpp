// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB
// stlport
//
// The constructor identity is pinned at ILT 0x00013921 and named by the
// function-local helper in bfmeBeginYS. Retail unwind metadata identifies the
// first member as vector<int>; the list sentinel contains an opaque 12-byte
// record.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <vector>

class Gen_00755E70;

struct Rva00754F70Entry
{
	int m_words[3];
};

typedef _STL::list<Rva00754F70Entry, _STL::allocator<Rva00754F70Entry> > Rva00754F70List;

class BfmeHelperYS
{
public:
	BfmeHelperYS(void);

	~BfmeHelperYS(void);

	void bfmeAttachYS(Gen_00755E70 *owner);

private:
	_STL::vector<int> m_rva00754F70Vector;
	Rva00754F70List m_rva00754F70List;
	volatile int m_rva00754F70Count10;
	volatile int m_rva00754F70Count14;
	volatile int m_rva00754F70Count18;
	volatile int m_rva00754F70Count1c;
	volatile int m_rva00754F70Count20;
	volatile int m_rva00754F70Count24;
	char m_rva00754F70Tail[8];
};

BfmeHelperYS::BfmeHelperYS(void) :
	m_rva00754F70Vector(),
	m_rva00754F70List()
{
	m_rva00754F70Count10 = 0;
	m_rva00754F70Count14 = 0;
	m_rva00754F70Count18 = 0;
	m_rva00754F70Count1c = 0;
	m_rva00754F70Count20 = 0;
	m_rva00754F70Count24 = 0;
}

BfmeHelperYS *g_bfmeCurrentYS;				// retail 0x01304B64

class Gen_00755E70
{
public:
	void bfmeBeginYS(void);

	void bfmeFinishYS(void);
};

// ?bfmeBeginYS@Gen_00755E70@@QAEXXZ
void Gen_00755E70::bfmeBeginYS(void)
{
	static BfmeHelperYS s_bfmeHelperYS;

	BfmeHelperYS *helper = &s_bfmeHelperYS;

	g_bfmeCurrentYS = helper;

	helper->bfmeAttachYS(this);

	bfmeFinishYS();
}
