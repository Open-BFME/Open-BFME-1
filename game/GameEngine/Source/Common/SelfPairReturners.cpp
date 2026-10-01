// Fifty-nine 28-byte bodies that return a two-field structure by value: the
// result of one call, paired with `this`.
//
//     mov eax,[esp+8] / push esi / push eax / mov esi,ecx / call <REL32>
//     mov ecx,[esp+8] / mov [ecx],eax / mov [ecx+4],esi / mov eax,ecx
//     pop esi / ret 8
//
// WHAT THE BYTES SHOW.  `ret 8` with `this` in ecx is __thiscall with two stack
// dwords, and the second of them is written through as a pair of fields and
// then returned in eax -- the MSVC hidden return pointer.  The arithmetic is
// what proves which is which: after `push esi` and `push eax` the frame is
// eight bytes deeper, yet `mov ecx,[esp+8]` reads the hidden pointer, so the
// intervening call must have popped four bytes of its own.  That makes the
// REL32 callee __thiscall on the same `this` with exactly one stack argument --
// the caller's own second argument, loaded into eax before the frame moves.
//
// An 8-byte plain-old-data pair returns in edx:eax, so a hidden return pointer
// proves the returned type is NOT pod; and the two stores into the return slot
// mean the result is CONSTRUCTED THERE rather than copied from a local (see
// SentinelPairReturners.cpp for the same distinction measured).
//
// THE ONLY AXIS IS THE REL32 TARGET.  Fifty-nine members, twenty-four distinct
// callees, every other byte identical.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived; callee pins are
// additive and address-derived.

struct SelfPair
{
	SelfPair( void *value, void *owner ) : m_value( value ), m_owner( owner ) {}
	void *m_value;
	void *m_owner;
};

class AsciiString;
struct BfmeHashFindAccess;
namespace rts { template <class T> struct hash; }
namespace _STL
{
template <class T> struct equal_to;
template <class T> class allocator;
template <class Value> struct _Hashtable_node;
template <class Value, class Key, class Hash, class Extract, class Equal, class Allocator>
class hashtable
{
    template <class Lookup> _Hashtable_node<Value> *_M_find(const Lookup &) const;
    friend struct ::BfmeHashFindAccess;
};
}

struct BfmeHashFindAccess
{
    template <class Value, class Extract>
    static __forceinline void *find(void *owner, void *argument)
    {
        typedef _STL::hashtable<Value, AsciiString, rts::hash<AsciiString>, Extract,
            _STL::equal_to<AsciiString>, _STL::allocator<Value> > Table;
        return reinterpret_cast<const Table *>(owner)->_M_find(*static_cast<const AsciiString *>(argument));
    }
};

#define BFME_SELF_PAIR_HASH_CALLEE(ADDR) \
    struct Rva##ADDR##Value; \
    struct Rva##ADDR##ExtractKey; \
    class Rva##ADDR##Lookup \
    { \
    public: \
        __forceinline void *evaluate(void *argument) \
        { return BfmeHashFindAccess::find<Rva##ADDR##Value, Rva##ADDR##ExtractKey>(this, argument); } \
    };

#define BFME_SELF_PAIR_CALLEE( ADDR )                                         \
	class Gen##ADDR                                                           \
	{                                                                         \
	public:                                                                   \
		void *evaluate( void *argument );                                     \
	};

#define BFME_SELF_PAIR_MAKER( NAME, CALLEE )                                  \
	class NAME : public CALLEE                                                \
	{                                                                         \
	public:                                                                   \
		SelfPair make( void *argument );                                      \
	};                                                                        \
	SelfPair NAME::make( void *argument )                                     \
	{                                                                         \
		return SelfPair( evaluate( argument ), this );                        \
	}


BFME_SELF_PAIR_HASH_CALLEE( 000D7180 )
BFME_SELF_PAIR_HASH_CALLEE( 000D7250 )
BFME_SELF_PAIR_HASH_CALLEE( 000F2010 )
BFME_SELF_PAIR_HASH_CALLEE( 001366A0 )
BFME_SELF_PAIR_HASH_CALLEE( 0038BF10 )
BFME_SELF_PAIR_HASH_CALLEE( 004246F0 )
BFME_SELF_PAIR_HASH_CALLEE( 00460B30 )
BFME_SELF_PAIR_HASH_CALLEE( 00460C00 )
BFME_SELF_PAIR_HASH_CALLEE( 00460CD0 )
BFME_SELF_PAIR_HASH_CALLEE( 0046A130 )
BFME_SELF_PAIR_HASH_CALLEE( 0046A200 )
BFME_SELF_PAIR_HASH_CALLEE( 0046A2D0 )
BFME_SELF_PAIR_HASH_CALLEE( 0046A3A0 )
BFME_SELF_PAIR_HASH_CALLEE( 0046A470 )
BFME_SELF_PAIR_HASH_CALLEE( 0046A540 )
BFME_SELF_PAIR_HASH_CALLEE( 0046A610 )
BFME_SELF_PAIR_HASH_CALLEE( 00583580 )
BFME_SELF_PAIR_HASH_CALLEE( 00613AE0 )
BFME_SELF_PAIR_HASH_CALLEE( 00613BB0 )
BFME_SELF_PAIR_HASH_CALLEE( 006931A0 )
BFME_SELF_PAIR_CALLEE( 0069CBC0 )
BFME_SELF_PAIR_HASH_CALLEE( 006A7F80 )
BFME_SELF_PAIR_HASH_CALLEE( 006A8050 )
BFME_SELF_PAIR_CALLEE( 009D76F0 )

BFME_SELF_PAIR_MAKER( Rva000D8600Maker, Rva000D7180Lookup )
BFME_SELF_PAIR_MAKER( Rva000D8630Maker, Rva000D7180Lookup )
BFME_SELF_PAIR_MAKER( Rva000D8660Maker, Rva000D7250Lookup )
BFME_SELF_PAIR_MAKER( Rva000D9750Maker, Rva000D7180Lookup )
BFME_SELF_PAIR_MAKER( Rva000D9780Maker, Rva000D7180Lookup )
BFME_SELF_PAIR_MAKER( Rva000F3BA0Maker, Rva000F2010Lookup )
BFME_SELF_PAIR_MAKER( Rva000F3BD0Maker, Rva000F2010Lookup )
BFME_SELF_PAIR_MAKER( Rva000F69B0Maker, Rva000F2010Lookup )
BFME_SELF_PAIR_MAKER( Rva000F69E0Maker, Rva000F2010Lookup )
BFME_SELF_PAIR_MAKER( Rva001372B0Maker, Rva001366A0Lookup )
BFME_SELF_PAIR_MAKER( Rva001372E0Maker, Rva001366A0Lookup )
BFME_SELF_PAIR_MAKER( Rva001376F0Maker, Rva001366A0Lookup )
BFME_SELF_PAIR_MAKER( Rva00137720Maker, Rva001366A0Lookup )
BFME_SELF_PAIR_MAKER( Rva0038EFC0Maker, Rva0038BF10Lookup )
BFME_SELF_PAIR_MAKER( Rva0038EFF0Maker, Rva0038BF10Lookup )
BFME_SELF_PAIR_MAKER( Rva00390720Maker, Rva0038BF10Lookup )
BFME_SELF_PAIR_MAKER( Rva00424EF0Maker, Rva004246F0Lookup )
BFME_SELF_PAIR_MAKER( Rva00424F20Maker, Rva004246F0Lookup )
BFME_SELF_PAIR_MAKER( Rva00425160Maker, Rva004246F0Lookup )
BFME_SELF_PAIR_MAKER( Rva00425190Maker, Rva004246F0Lookup )
BFME_SELF_PAIR_MAKER( Rva004614E0Maker, Rva00460B30Lookup )
BFME_SELF_PAIR_MAKER( Rva00461510Maker, Rva00460C00Lookup )
BFME_SELF_PAIR_MAKER( Rva00461540Maker, Rva00460CD0Lookup )
BFME_SELF_PAIR_MAKER( Rva004619D0Maker, Rva00460B30Lookup )
BFME_SELF_PAIR_MAKER( Rva00461BC0Maker, Rva00460C00Lookup )
BFME_SELF_PAIR_MAKER( Rva00461DD0Maker, Rva00460CD0Lookup )
BFME_SELF_PAIR_MAKER( Rva0046AFB0Maker, Rva0046A130Lookup )
BFME_SELF_PAIR_MAKER( Rva0046AFE0Maker, Rva0046A200Lookup )
BFME_SELF_PAIR_MAKER( Rva0046B010Maker, Rva0046A2D0Lookup )
BFME_SELF_PAIR_MAKER( Rva0046B040Maker, Rva0046A3A0Lookup )
BFME_SELF_PAIR_MAKER( Rva0046B070Maker, Rva0046A470Lookup )
BFME_SELF_PAIR_MAKER( Rva0046B0A0Maker, Rva0046A470Lookup )
BFME_SELF_PAIR_MAKER( Rva0046B0D0Maker, Rva0046A540Lookup )
BFME_SELF_PAIR_MAKER( Rva0046B100Maker, Rva0046A610Lookup )
BFME_SELF_PAIR_MAKER( Rva0046B130Maker, Rva0046A610Lookup )
BFME_SELF_PAIR_MAKER( Rva0046B3D0Maker, Rva0046A130Lookup )
BFME_SELF_PAIR_MAKER( Rva0046B400Maker, Rva0046A200Lookup )
BFME_SELF_PAIR_MAKER( Rva0046B430Maker, Rva0046A2D0Lookup )
BFME_SELF_PAIR_MAKER( Rva0046B460Maker, Rva0046A3A0Lookup )
BFME_SELF_PAIR_MAKER( Rva0046B630Maker, Rva0046A470Lookup )
BFME_SELF_PAIR_MAKER( Rva0046B720Maker, Rva0046A540Lookup )
BFME_SELF_PAIR_MAKER( Rva0046B810Maker, Rva0046A610Lookup )
BFME_SELF_PAIR_MAKER( Rva00583BC0Maker, Rva00583580Lookup )
BFME_SELF_PAIR_MAKER( Rva00583CA0Maker, Rva00583580Lookup )
BFME_SELF_PAIR_MAKER( Rva006144D0Maker, Rva00613AE0Lookup )
BFME_SELF_PAIR_MAKER( Rva00614500Maker, Rva00613BB0Lookup )
BFME_SELF_PAIR_MAKER( Rva006147E0Maker, Rva00613AE0Lookup )
BFME_SELF_PAIR_MAKER( Rva006148C0Maker, Rva00613BB0Lookup )
BFME_SELF_PAIR_MAKER( Rva00693660Maker, Rva006931A0Lookup )
BFME_SELF_PAIR_MAKER( Rva00693850Maker, Rva006931A0Lookup )
BFME_SELF_PAIR_MAKER( Rva0069ED40Maker, Gen0069CBC0 )
BFME_SELF_PAIR_MAKER( Rva006A0F50Maker, Gen0069CBC0 )
BFME_SELF_PAIR_MAKER( Rva006AB600Maker, Rva006A7F80Lookup )
BFME_SELF_PAIR_MAKER( Rva006AB630Maker, Rva006A7F80Lookup )
BFME_SELF_PAIR_MAKER( Rva006AB680Maker, Rva006A8050Lookup )
BFME_SELF_PAIR_MAKER( Rva006AC3E0Maker, Rva006A7F80Lookup )
BFME_SELF_PAIR_MAKER( Rva006AC410Maker, Rva006A7F80Lookup )
BFME_SELF_PAIR_MAKER( Rva006AC5A0Maker, Rva006A8050Lookup )
BFME_SELF_PAIR_MAKER( Rva009D7A40Maker, Gen009D76F0 )
BFME_SELF_PAIR_MAKER( Rva009D7860Maker, Gen009D76F0 )
