// ??1Rva0049DA40Object@@UAE@XZ
// partial score=0.28 date=2026-09-21
// Retail 0x0049DA40, 467 bytes (ledger carries a 464B scaffold; the real
// boundary is the add esp,0x10 / ret at +0x1d2-+0x1d3, int3 padding after).
// Reached only from the compiler-generated scalar-deleting-destructor thunk
// Gen_dtor_0049E750 (Code/gen_small/dtors_005.cpp); its own identity stays
// address-derived, but every callee resolves to an already-landed or pinned
// symbol: SubsystemInterface::~SubsystemInterface (base dtor),
// ControlBarSchemeManager::~ControlBarSchemeManager (via thunk j_0000fd3f,
// ControlBarScheme.cpp), operator delete (mem_ops.cpp), and TheWindowManager
// (global 0x012F1B40) through its own vtable slot 0x78.
//
// The class installs vtable 0x010FB888 (tools/vtable_lookup.py: slot 2 is
// SubsystemInterface::loadIniFilesFromLegend, so this derives from
// SubsystemInterface) and then releases a long straight-line run of owned
// interface pointers before chaining to the base destructor:
//   +0x08, +0x0c, +0x10, +0x14, +0x2f0, +0x2f4: single-owner pointers, each
//     deleted through their own vtable slot 0 with flag 1 (scalar deleting
//     destructor) then cleared.
//   +0x98, +0x278, +0xf8: pointers released through vtable slot 0x20 (no
//     args) THEN deleted through vtable slot 4 with flag 1, then cleared.
//   +0x2c (next at node+0x60) and +0x28 (next at node+0x14): singly linked
//     lists, each node deleted through its own vtable slot 0 with flag 1.
//   +0x1a0..+0x1ec: a 20-entry GameWindow* array (the same
//     MAX_COMMANDS_PER_SET=20 count ControlBar_findContainedObject.cpp
//     uses), each entry passed to TheWindowManager's vtable slot 0x78 and
//     the two parallel arrays at +0x100 and +0x150 cleared alongside it.
//   +0x58: one more GameWindow* passed to the same TheWindowManager slot
//     0x78 call, unconditionally (retail does not null-check this one).

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
};

class GameWindow;

class GameWindowManager
{
public:
#define BFME_WM_SLOT( n ) virtual void slot##n( void ) = 0;
	BFME_WM_SLOT( 00 ) BFME_WM_SLOT( 01 ) BFME_WM_SLOT( 02 ) BFME_WM_SLOT( 03 )
	BFME_WM_SLOT( 04 ) BFME_WM_SLOT( 05 ) BFME_WM_SLOT( 06 ) BFME_WM_SLOT( 07 )
	BFME_WM_SLOT( 08 ) BFME_WM_SLOT( 09 ) BFME_WM_SLOT( 10 ) BFME_WM_SLOT( 11 )
	BFME_WM_SLOT( 12 ) BFME_WM_SLOT( 13 ) BFME_WM_SLOT( 14 ) BFME_WM_SLOT( 15 )
	BFME_WM_SLOT( 16 ) BFME_WM_SLOT( 17 ) BFME_WM_SLOT( 18 ) BFME_WM_SLOT( 19 )
	BFME_WM_SLOT( 20 ) BFME_WM_SLOT( 21 ) BFME_WM_SLOT( 22 ) BFME_WM_SLOT( 23 )
	BFME_WM_SLOT( 24 ) BFME_WM_SLOT( 25 ) BFME_WM_SLOT( 26 ) BFME_WM_SLOT( 27 )
	BFME_WM_SLOT( 28 ) BFME_WM_SLOT( 29 )
	virtual void slot30( GameWindow *w ) = 0; // offset 0x78
#undef BFME_WM_SLOT
};

extern GameWindowManager *TheWindowManager;

// Single-owner pointer with a scalar deleting destructor at vtable slot 0.
class SimpleOwned
{
public:
	virtual void deletingDtor( unsigned int flags ) = 0;
};

// Release()/deletingDtor() pair: slot 0x20 (index 8, no args) then slot 4
// (index 1, flag 1).
class ReleaseThenDelete
{
public:
	virtual void slot00( void ) = 0;
	virtual void deletingDtor( unsigned int flags ) = 0;
	virtual void slot02( void ) = 0;
	virtual void slot03( void ) = 0;
	virtual void slot04( void ) = 0;
	virtual void slot05( void ) = 0;
	virtual void slot06( void ) = 0;
	virtual void slot07( void ) = 0;
	virtual void release( void ) = 0;
};

// Singly linked list node, "next" at +0x60, deleted via slot 0 with flag 1.
class ListNodeA
{
public:
	virtual void deletingDtor( unsigned int flags ) = 0;
	char m_pad[ 0x60 - 4 ];
	ListNodeA *m_next;
};

// Singly linked list node, "next" at +0x14, deleted via slot 0 with flag 1.
class ListNodeB
{
public:
	virtual void deletingDtor( unsigned int flags ) = 0;
	char m_pad[ 0x14 - 4 ];
	ListNodeB *m_next;
};

extern void j_0000fd3f( void ); // ControlBarSchemeManager::~ControlBarSchemeManager thunk
extern void __cdecl operator delete( void *p );

struct SchemeCallTarget {};
typedef void ( SchemeCallTarget::*SchemeDtorCall )( void );

class Rva0049DA40Object : public SubsystemInterface
{
public:
	virtual ~Rva0049DA40Object();

	char m_pad_to_08[ 8 - 4 ];
	SimpleOwned *m_at08;                 // +0x08
	SimpleOwned *m_at0c;                 // +0x0c
	SimpleOwned *m_at10;                 // +0x10
	SimpleOwned *m_at14;                 // +0x14
	char m_pad_14_28[ 0x28 - 0x18 ];
	ListNodeB *m_at28;                   // +0x28
	ListNodeA *m_at2c;                   // +0x2c
	void *m_at30;                        // +0x30 (ControlBarSchemeManager*)
	char m_pad_34_58[ 0x58 - 0x34 ];
	GameWindow *m_at58;                  // +0x58
	char m_pad_5c_98[ 0x98 - 0x5c ];
	ReleaseThenDelete *m_at98;           // +0x98
	char m_pad_9c_f8[ 0xf8 - 0x9c ];
	ReleaseThenDelete *m_atf8;           // +0xf8
	char m_pad_fc_100[ 0x100 - 0xfc ];
	void *m_at100[ 0x14 ];               // +0x100 .. +0x14f
	void *m_at150[ 0x14 ];               // +0x150 .. +0x19f
	GameWindow *m_at1a0[ 0x14 ];         // +0x1a0 .. +0x1ef
	char m_pad_1f0_278[ 0x278 - 0x1f0 ];
	ReleaseThenDelete *m_at278;          // +0x278
	char m_pad_27c_2bc[ 0x2bc - 0x27c ];
	void *m_at2bc;                       // +0x2bc
	char m_pad_2c0_2f0[ 0x2f0 - 0x2c0 ];
	SimpleOwned *m_at2f0;                // +0x2f0
	SimpleOwned *m_at2f4;                // +0x2f4
};

Rva0049DA40Object::~Rva0049DA40Object()
{
	if( m_at98 != 0 )
		m_at98->release();
	if( m_at98 != 0 )
		m_at98->deletingDtor( 1 );
	m_at98 = 0;
	m_at2bc = 0;

	if( m_at08 != 0 )
		m_at08->deletingDtor( 1 );
	m_at08 = 0;

	if( m_at10 != 0 )
		m_at10->deletingDtor( 1 );
	m_at10 = 0;

	if( m_at0c != 0 )
		m_at0c->deletingDtor( 1 );
	m_at0c = 0;

	if( m_at14 != 0 )
		m_at14->deletingDtor( 1 );
	m_at14 = 0;

	void *scheme = m_at30;
	if( scheme != 0 )
	{
		union
		{
			void ( *raw )( void );
			SchemeDtorCall member;
		} schemeDtor;
		schemeDtor.raw = j_0000fd3f;
		( reinterpret_cast<SchemeCallTarget *>( scheme )->*schemeDtor.member )();
		operator delete( scheme );
	}
	m_at30 = 0;

	for( ListNodeA *node = m_at2c; node != 0; )
	{
		ListNodeA *next = node->m_next;
		node->deletingDtor( 1 );
		node = next;
		m_at2c = node;
	}

	for( ListNodeB *node = m_at28; node != 0; )
	{
		ListNodeB *next = node->m_next;
		node->deletingDtor( 1 );
		node = next;
		m_at28 = node;
	}

	if( m_at278 != 0 )
		m_at278->release();
	if( m_at278 != 0 )
		m_at278->deletingDtor( 1 );
	m_at278 = 0;

	if( m_atf8 != 0 )
		m_atf8->release();
	if( m_atf8 != 0 )
		m_atf8->deletingDtor( 1 );
	m_atf8 = 0;

	for( int i = 0; i < 0x14; ++i )
	{
		GameWindow *w = m_at1a0[ i ];
		m_at100[ i ] = 0;
		m_at150[ i ] = 0;
		TheWindowManager->slot30( w );
		m_at1a0[ i ] = 0;
	}

	TheWindowManager->slot30( m_at58 );
	m_at58 = 0;

	if( m_at2f0 != 0 )
		m_at2f0->deletingDtor( 1 );
	m_at2f0 = 0;

	if( m_at2f4 != 0 )
		m_at2f4->deletingDtor( 1 );
	m_at2f4 = 0;
}
