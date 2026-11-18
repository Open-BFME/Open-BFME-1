// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB
// stlport
//
// The constructor identity is pinned at ILT 0x00013921 and named by the
// function-local helper in bfmeBeginYS. Retail unwind metadata identifies the
// first member as a vector; the list sentinel contains an opaque 12-byte
// record. The attach at 0x00754970 grows that vector through the pointer
// instantiation's _M_insert_overflow at 0x00753FC0 (not vector<int>'s at
// 0x0037F7D0), so its element is a pointer to a 12-byte record.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <vector>

class Gen_00755E70;

#include "../../../../../GameEngine/Include/Common/NameKeyType.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern "C" NameKeyGenerator *g_theNameKeyGenerator;
extern char g_bfmeDefault996[];			// retail 0x0112233C "(NULL)"

struct Rva00754970Record
{
	void *m_rva00754970Source;
	Gen_00755E70 *m_rva00754970Owner;
	NameKeyType m_rva00754970Key;
};

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
	_STL::vector<Rva00754970Record *> m_rva00754F70Vector;
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

class Gen_00755E70
{
public:
	void bfmeBeginYS(void);

	void bfmeFinishYS(void);

	char m_rva00754970Head[4];
	void *m_rva00754970Source;			// +0x04
	char m_rva00754970Gap[0x274];
	Rva00754970Record *m_rva00754970Record;	// +0x27C
};

// ?bfmeAttachYS@BfmeHelperYS@@QAEXPAVGen_00755E70@@@Z (retail 0x00754970,
// reached through ILT 0x1019 from bfmeBeginYS)
void BfmeHelperYS::bfmeAttachYS(Gen_00755E70 *owner)
{
	Rva00754970Record *record = new Rva00754970Record;
	record->m_rva00754970Source = owner->m_rva00754970Source;
	record->m_rva00754970Owner = owner;
	record->m_rva00754970Key = g_theNameKeyGenerator->nameToKey(g_bfmeDefault996);
	m_rva00754F70Vector.push_back(record);
	owner->m_rva00754970Record = record;
}

BfmeHelperYS *g_bfmeCurrentYS;				// retail 0x01304B64

// ?bfmeBeginYS@Gen_00755E70@@QAEXXZ
void Gen_00755E70::bfmeBeginYS(void)
{
	static BfmeHelperYS s_bfmeHelperYS;

	BfmeHelperYS *helper = &s_bfmeHelperYS;

	g_bfmeCurrentYS = helper;

	helper->bfmeAttachYS(this);

	bfmeFinishYS();
}
