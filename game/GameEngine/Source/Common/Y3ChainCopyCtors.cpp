// cl: /DNDEBUG /MD /EHsc
// Eight 92-byte __thiscall copy constructors, one shape, forming a single
// nine-deep chain.  Retail:
//
//     push -1 / push <ehdata> / fs:[0] frame          ; EH state -1
//     esi = this ; edi = source ; [esp+8] = this
//     ecx = [edi] ; if (ecx) { eax = [ecx]; call [eax+4] } else eax = 0
//     [esi] = eax                                     ; pointer member, cloned
//     EH state 0
//     push edi+4 / ecx = esi+4 / call <REL32>         ; construct at +4
//     eax = this ; unlink frame ; ret 4
//
// WHAT THE BYTES SHOW.  `this` in ecx, one dword parameter, `eax = this` on
// exit and `ret 4`: a __thiscall one-argument constructor.  The argument is
// dereferenced, never written, and is handed to the second subobject at the
// same +4 displacement the destructor family a few hundred bytes away uses --
// so it is a reference to the SAME class, i.e. a COPY CONSTRUCTOR.
//
// THE FIRST FOUR BYTES ARE A POINTER THAT IS CLONED, NOT COPIED.  The source
// pointer is loaded into ecx and tested there -- the local-binding tell -- and
// then slot 1 is dispatched on it with no arguments, yielding the dword that is
// stored at offset 0.  Slot 0 of that same vftable is what the matching
// destructors call with `push 1`, the scalar deleting destructor, so slot 1 is
// the next virtual after a virtual destructor.  Both arms deliver the value in
// a register (`xor eax,eax` on the null arm), so this is ONE assignment fed by
// a conditional expression.
//
// THE STORE ORDER DATES THE ASSIGNMENT.  `mov [esi],eax` lands BEFORE the
// EH-state store, which is where a compiler-emitted subobject initialisation
// sits and a source-level assignment does not; and the state that is entered
// is 0, meaning an exception from the +4 constructor must unwind something
// already built.  A four-byte thing at offset 0 that (a) is initialised by the
// compiler and (b) needs unwinding is a BASE CLASS with a destructor -- the
// same four-byte pointer-holding first base that puts the second base at
// exactly +4 in the destructor family.
//
// THE CHAIN.  Each body's REL32 goes to the previous body in this file:
//
//     005CF080 -> 005CEB10 -> 005CE420 -> 005CDC20 -> 005CD770
//              -> 005CD2D0 -> 005CBE40 -> 005CB130 -> 005C92F0
//
// Naming a callee that is DEFINED here would inline it, and retail's `call`
// proves it stayed opaque, so every level's callee is declared as its own
// class with no definition -- the same weaker claim BigChainBaseDtors.cpp
// makes, and for the same reason.  The bottom callee, 0x005C92F0, is not
// converted here; it is a deep-cloning copy constructor over a three-pointer
// vector and belongs to a different shape.
//
// THE ONE OUTLIER IS AN EXTRA EMPTY INHERITANCE LEVEL.  Seven of the eight
// spell the derived-to-base conversion `add edi,4 / push edi`; 0x005CB130
// spells it `lea eax,[edi+4] / push eax`.  Measured: MSVC 7.1 emits the `lea`
// form when the second base is reached through ONE MORE class -- an empty
// intermediate that adds no data and does not move the offset.  Nothing else
// tried reproduces it (member instead of base, explicit cast, pointer
// argument, non-const parameter all give the `add` form), so the extra level
// is what the byte difference asserts, and only that.
//
// THIS CHAIN IS NOT ASSERTED TO BE THE DESTRUCTOR CHAIN.  Six of these bodies
// sit exactly 0x70 after an 89-byte destructor from BigChainBaseDtors.cpp and
// the two chains' edges agree over those six levels, which is what one would
// expect of one class per level owning both.  But at the bottom the two
// disagree: the destructor at 0x005CB0C0 destroys its +4 base through
// 0x005C9EC0, an 89-byte body of the destructor shape, while the constructor
// at 0x005CB130 builds its +4 base through 0x005C92F0, a vector-cloning body.
// One class cannot have both, so either the pairing is a layout coincidence or
// one of the two chain models is wrong.  That is left OPEN: nothing here is
// spelled in terms of the destructor family's classes.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  The EH
// data is a DIR32 site the byte gate takes from the target; the second-base
// constructors are REL32 and are pinned in targets/game/reverse/symbols.csv.

class ChainVictim
{
public:
	virtual ~ChainVictim();
	virtual ChainVictim *clone() const;
};

class ChainCloneHold
{
public:
	ChainVictim *m_p;
	ChainCloneHold( const ChainCloneHold &other )
	{
		ChainVictim *p = other.m_p;
		m_p = p ? p->clone() : 0;
	}
	~ChainCloneHold() { if ( m_p ) delete m_p; }
};

#define BFME_COPY_SECOND_BASE( ADDR )                                     \
	class Sub##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		Sub##ADDR( const Sub##ADDR &other );                              \
	};

#define BFME_COPY_CTOR( NAME, SECOND )                                    \
	class NAME : public ChainCloneHold, public SECOND                     \
	{                                                                     \
	public:                                                               \
		NAME( const NAME &other );                                        \
	};                                                                    \
	NAME::NAME( const NAME &other )                                       \
		: ChainCloneHold( other ), SECOND( other ) {}

BFME_COPY_SECOND_BASE( 005C92F0 )
BFME_COPY_SECOND_BASE( 005CB130 )
BFME_COPY_SECOND_BASE( 005CBE40 )
BFME_COPY_SECOND_BASE( 005CD2D0 )
BFME_COPY_SECOND_BASE( 005CD770 )
BFME_COPY_SECOND_BASE( 005CDC20 )
BFME_COPY_SECOND_BASE( 005CE420 )
BFME_COPY_SECOND_BASE( 005CEB10 )

class Mid005CB130 : public Sub005C92F0 {};

class Rva005CB130 : public ChainCloneHold, public Mid005CB130
{
public:
	Rva005CB130( const Rva005CB130 &other );
};

Rva005CB130::Rva005CB130( const Rva005CB130 &other )
	: ChainCloneHold( other ), Mid005CB130( other ) {}

BFME_COPY_CTOR( Rva005CBE40, Sub005CB130 )
BFME_COPY_CTOR( Rva005CD2D0, Sub005CBE40 )
BFME_COPY_CTOR( Rva005CD770, Sub005CD2D0 )
BFME_COPY_CTOR( Rva005CDC20, Sub005CD770 )
BFME_COPY_CTOR( Rva005CE420, Sub005CDC20 )
BFME_COPY_CTOR( Rva005CEB10, Sub005CE420 )
BFME_COPY_CTOR( Rva005CF080, Sub005CEB10 )
