// One 40-byte __thiscall member that asks a predicate of itself and then writes
// the SAME answer twice -- once through a call and once into a byte member:
//
//     push esi / mov esi,ecx / call <test>
//     test al,al / mov ecx,esi / je .off
//     push 1 / call <apply> / mov byte ptr [esi+0x4E],1 / pop esi / ret
//   .off:
//     push 0 / call <apply> / mov byte ptr [esi+0x4E],0 / pop esi / ret
//
// WHAT THE BYTES SHOW.  The predicate takes nothing and answers in al, so it is
// a niladic __thiscall member returning a one-byte type.  `mov ecx,esi` is
// hoisted ABOVE the branch, so both arms call the same __thiscall member on the
// same receiver and differ only in the immediate they push -- 1 against 0 -- and
// in the immediate they store.  The store is `mov byte ptr`, so the member is
// one byte wide, and it is written AFTER the call in both arms.
//
// THE ARMS ARE NOT MERGED, and that is the finding: a single `apply( flag )`
// followed by a single `m_at4E = flag` would have materialised the boolean in a
// register and stored it once.  Retail duplicates the call, the store and the
// epilogue, which is what an if/else with a constant in each arm compiles to.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the callee
// pins are address-derived and additive.

class Gen003BD7D0Node;
class Gen003BD8D0Arg;
class Gen003BF540Owner;

class Rva003BF540
{
public:
	void update();
	bool test();
	void apply( bool on );
	Gen003BD7D0Node * find( int id );
	bool ready( int id );
	void select( int id );
	bool act( Gen003BD8D0Arg * a );
	char m_pad00[ 0x28 ];
	Gen003BF540Owner * m_at28;
	char m_pad2C[ 0x8 ];
	int  m_at34;
	char m_pad38[ 0x16 ];
	bool m_at4E;
};
void Rva003BF540::update()
{
	if( test() )
	{
		apply( true );
		m_at4E = true;
	}
	else
	{
		apply( false );
		m_at4E = false;
	}
}

// ---------------------------------------------------------------- same class
// Two more members of the SAME class, and the evidence that they are: both
// reach 0x003BD7D0 -- a lookup taking one dword and answering a pointer -- and
// 0x003BEB50 also calls the very same niladic predicate at 0x003BEAF0 that
// `update` above calls, on the same receiver.  One class, one set of pins.
//
//   0x003BEB50  find(arg) into edi, then test(), then three tests in a row, and
//               a duplicated `mov al,1` / `xor al,al` tail -- constant results
//               in both arms, not a `setcc` of the condition.
//   0x003BD880  find(m_at34) / release it if non-null / store the new value /
//               find it again / claim it if non-null.  The store of the new
//               value is scheduled BETWEEN the push and the call, which is why
//               the argument register is loaded before the member is written.

class Gen003BD8D0Sub
{
public:
	char m_pad00[ 0x18 ];
	bool m_at18;
};

class Gen003BD8D0Arg
{
public:
	char               m_pad00[ 0xEC ];
	Gen003BD8D0Sub *   m_atEC;
};

class Gen003BD8D0Built;

struct Gen003A43C0Element
{
	char m_pad00[ 0xA4 ];
	void *m_value;
};

struct Gen003A43C0Span
{
	Gen003A43C0Element *const *m_begin;
	Gen003A43C0Element *const *m_end;
	unsigned int size() const { return m_end - m_begin; }
};

// These two calls are the existing retail thunks reached by enter.  Their
// surrounding class names are not recovered, so keep the call-site views
// neutral while preserving the observed thiscall ABI and routes.
class Gen003BD7D0Game;
class Rva0060A900 { public: void run(); };
struct Rva006122A0Item;
class AsciiString;
class Rva006122A0Mgr { public: Rva006122A0Item *find(const AsciiString &); };

extern void j_00032010();
extern void j_0004a1ab();

class Gen003BD7D0Node
{
public:
	char m_pad00[ 0x1E ];
	bool m_at1E;
	char m_pad1F[ 0x29 ];
	Gen003A43C0Span m_items;
	__forceinline void activate(void *target, int first, int second)
 {
  typedef void (Gen003BD7D0Node::*Call)(void *, int, int);
  union { void (*function)(); Call member; } route;
  route.function = j_00032010;
  (this->*route.member)(target, first, second);
 }
	void leave();
	void enter();
	Gen003BD8D0Built * build( Gen003BD8D0Arg * a, int b, int c );
};

// Existing ILTs retain unresolved helper identity without introducing aliases.
// 6160B0 forwards its incoming ECX to LivingWorldManager::rva00615cb0.
extern void j_00032010();
extern void j_0004a1ab();
class Gen003BD7D0Game {
public:
 __forceinline void notify(void *value, int one)
 {
  typedef void (Gen003BD7D0Game::*Call)(void *, int);
  union { void (*function)(); Call member; } route;
  route.function = j_0004a1ab;
  (this->*route.member)(value, one);
 }
};
extern "C" char *g_bfmeGameCW;

class Gen003BF540Owner
{
public:
	bool consume( Gen003BD8D0Built * built );
};

// Same global as in V4GlobalStateQuery.cpp; that file reads +0xEB0, this one
// reads the byte at +0x8E.
class Glo012ED5C8Type
{
public:
	char m_pad00[ 0x8E ];
	bool m_at8E;
	char m_pad8F[ 0xE21 ];
	int  m_atEB0;
};

extern Glo012ED5C8Type * Glo012ED5C8;

bool Rva003BF540::ready( int id )
{
	Gen003BD7D0Node *node = find( id );
	if( test() && node != 0 && node->m_at1E )
		return true;
	return false;
}

void Rva003BF540::select( int id )
{
	Gen003BD7D0Node *previous = find( m_at34 );
	if( previous )
		previous->leave();
	m_at34 = id;
	Gen003BD7D0Node *current = find( id );
	if( current )
		current->enter();
}

// ?enter@Gen003BD7D0Node@@QAEXXZ, retail 0x003A4A40 (112 bytes).
// The two pointer members are the same [+0x48,+0x4C) span established by
// Gen003BD7D0Node::match.  Retail first activates the global's +0x168 target,
// notifies the global once for every +0xA4 entry, then looks up this+8 and
// tail-dispatches the returned result.
void Gen003BD7D0Node::enter()
{
	activate( g_bfmeGameCW + 0x168, 1, 3 );
	unsigned int index = 0;
	if( m_items.size() > 0 )
	{
		do
		{
			Gen003A43C0Element *entry = m_items.m_begin[ index ];
			reinterpret_cast<Gen003BD7D0Game *>( g_bfmeGameCW )->notify( entry->m_value, 1 );
			++index;
		}
		while( index < m_items.size() );
	}
	Rva006122A0Item *result = reinterpret_cast<Rva006122A0Mgr *>( g_bfmeGameCW )->find(
		*reinterpret_cast<const AsciiString *>( reinterpret_cast<char *>( this ) + 8 ) );
	reinterpret_cast<Rva0060A900 *>(result)->run();
}

// 0x003BD8D0 is a third member of the same class -- it reaches the same lookup at
// 0x003BD7D0 with the same key member at +0x34.  Its shape is three exits, and
// their ORDER is the finding: the `return true` sits inline between the two
// tests that can reach `return false`, which is placed after it, and the working
// block is last.  The byte it saves in bl, overwrites with 1 and puts back after
// the two calls is a re-entrancy guard; the answer is whatever the second call
// left in al, which survives the restore untouched.
bool Rva003BF540::act( Gen003BD8D0Arg * a )
{
	if( !a )
		return false;
	if( !Glo012ED5C8->m_at8E )
		return true;
	Gen003BD7D0Node *node = find( m_at34 );
	if( !node )
		return false;
	Gen003BD8D0Sub *sub = a->m_atEC;
	bool saved = sub->m_at18;
	sub->m_at18 = true;
	Gen003BD8D0Built *built = node->build( a, 0, 0 );
	bool answer = m_at28->consume( built );
	a->m_atEC->m_at18 = saved;
	return answer;
}
