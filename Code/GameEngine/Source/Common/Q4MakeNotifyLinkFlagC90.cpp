// cl: /EHsc -D_STLP_NO_EXCEPTIONS
// stlport
//
// Two 166-byte siblings of Q4MakeNotifyLink.cpp. Same allocate / four-arg
// INI parse / copy byte 0x528->0x54 / inlined list push_back at owner+0x538,
// then one extra `mov byte ptr [owner+DISP], 1` that keeps the owner pointer
// live so the list head moves into EBX.
//
// 0x001E5C90: new 0x64, DISP 0x4DC, ctor ??0BfmeThingUBA@@QAE@XZ @ 0x002DB0B0
// 0x001E5FD0: new 0x70, DISP 0x51F, ctor ??0Rva002DCBA0@@QAE@XZ @ 0x002DCBA0
//
// Names: constructors already matched. Wrapper names are address-derived.

#include <list>

class Q4Owner001E5A20
{
public:
	char m_gap0[ 0x4DC ];
	char m_flag4DC;
	char m_gap4DD[ 0x51F - 0x4DD ];
	char m_flag51F;
	char m_gap520[ 0x528 - 0x520 ];
	char m_flag;
	char m_gap529[ 0x538 - 0x529 ];
	_STL::list<void *> m_list;
};

class GenBase002DF2B0
{
public:
	GenBase002DF2B0();
	virtual void slot();

	char m_gap04[ 0x34 - 4 ];
	Q4Owner001E5A20 *m_owner;
	char m_gap38[ 0x54 - 0x38 ];
	char m_flag;
	char m_tail55[ 3 ];
};

class BfmeThingUBA : public GenBase002DF2B0
{
public:
	__declspec(noinline) BfmeThingUBA();
	virtual void slot();
	char m_tail[ 0x64 - 0x58 ];
};

class Rva002DCBA0 : public GenBase002DF2B0
{
public:
	__declspec(noinline) Rva002DCBA0();
	virtual void slot();
	char m_tail[ 0x70 - 0x58 ];
};

class INI;
void q4Notify001E5C90( INI *a, BfmeThingUBA *m, void *store, const void *userData );
void q4Notify001E5FD0( INI *a, Rva002DCBA0 *m, void *store, const void *userData );

void Rva001E5C90( void *a, Q4Owner001E5A20 *b )
{
	BfmeThingUBA *m = new BfmeThingUBA;
	m->m_owner = b;
	q4Notify001E5C90( static_cast<INI *>(a), m, 0, 0 );
	m->m_flag = b->m_flag;
	b->m_list.push_back( m );
	b->m_flag4DC = 1;
}

