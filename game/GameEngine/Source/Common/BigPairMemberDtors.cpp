// cl: /DNDEBUG /MD /EHsc
// Sixteen 76-byte __thiscall destructors, one shape.  Retail:
//
//     push -1 / push <ehdata> / fs:[0] frame ; EH state 0, `this` at [esp+4]
//     lea ecx,[esi+<OFFSET>] / call <REL32-A>   ; destroy the member at OFFSET
//     mov ecx,esi / EH state -1 / call <REL32-B>; destroy the member at 0
//
// WHAT THE BYTES SHOW.  No vptr store anywhere, so the owner is NOT
// polymorphic and neither subobject has an inlinable empty virtual destructor:
// both destructors are real out-of-line calls.  The higher offset is destroyed
// first, which is reverse declaration order for MEMBERS (and equally for
// BASES -- the bytes cannot separate those two here, and member declarations
// are the weaker claim, so that is what this file spells).  `mov ecx,esi` for
// the second call is offset zero.
//
// The EH state goes 0 before the first call and -1 before the second, which is
// the unwind funclet's record that after the first destructor returns only the
// offset-0 subobject is still alive.
//
// TWO AXES, BOTH READ DIRECTLY: the OFFSET (a disp8) and the two REL32
// destructors.  Sixteen members over eleven distinct callees; one member names
// the same callee for both subobjects.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  The EH
// data is a DIR32 relocation site the byte gate takes from the target; both
// destructors are REL32 and are pinned in targets/game/reverse/symbols.csv.

class AsciiString;
struct Rva00078B80Elem;
struct Gen_t_00197bc0_p8cd;
struct Gen_t_002360c0_k4;
struct Gen_t_002dbbf0_p8cd;
struct Gen002E1260;
struct Gen_t_00770380_p8cd;

namespace _STL
{
    template<class T> class allocator;
    template<class T, class A> class vector { public: ~vector(); };
    template<class K, class V> struct pair;
    template<class T> struct _Select1st;
    template<class T> struct _Identity;
    template<class T> struct less;
    template<class K, class V, class E, class C, class A>
    class _Rb_tree { public: ~_Rb_tree(); };
}

typedef _STL::vector<AsciiString, _STL::allocator<AsciiString> > AsciiStringVector;
typedef _STL::vector<Rva00078B80Elem, _STL::allocator<Rva00078B80Elem> > Vector00078B80;
typedef _STL::pair<const int, Gen_t_00197bc0_p8cd> Pair00197BC0;
typedef _STL::_Rb_tree<int, Pair00197BC0, _STL::_Select1st<Pair00197BC0>, _STL::less<int>, _STL::allocator<Pair00197BC0> > Tree00197BC0;
typedef _STL::_Rb_tree<Gen_t_002360c0_k4, Gen_t_002360c0_k4, _STL::_Identity<Gen_t_002360c0_k4>, _STL::less<Gen_t_002360c0_k4>, _STL::allocator<Gen_t_002360c0_k4> > Tree002360C0;
typedef _STL::vector<Gen_t_002dbbf0_p8cd, _STL::allocator<Gen_t_002dbbf0_p8cd> > Vector002DBBF0;
typedef _STL::vector<Gen002E1260, _STL::allocator<Gen002E1260> > Vector002E1260;
typedef _STL::vector<Gen_t_00770380_p8cd, _STL::allocator<Gen_t_00770380_p8cd> > Vector00770380;

class ActiveBodyModuleData { public: virtual ~ActiveBodyModuleData(); };
class AttributeModifierAuraUpdateModuleDataMemberD { public: ~AttributeModifierAuraUpdateModuleDataMemberD(); };
class AttributeHandleStandIn { public: ~AttributeHandleStandIn(); };
class Rva0090D090 { public: virtual ~Rva0090D090(); };
class SubsystemInterface { public: virtual ~SubsystemInterface(); };

template<class T> class StringBase
{
    void releaseBuffer();
    friend class RowMember00887940;
};
class StringClass
{
    void Free_String();
    friend class RowMember009DB7A0;
};

#define BFME_ROW_DTOR(ADDR, TYPE) \
    class RowMember##ADDR { public: ~RowMember##ADDR() { reinterpret_cast<TYPE *>(this)->TYPE::~TYPE(); } };

#define BFME_SUBOBJECT_DTOR( ADDR )                                       \
	class Mem##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		~Mem##ADDR();                                                     \
	};

#define BFME_PAIR_DTOR( NAME, HEAD, TAIL, PAD )                           \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		~NAME();                                                          \
		HEAD m_head;                                                      \
		char m_pad[ PAD ];                                                \
		TAIL m_tail;                                                      \
	};                                                                    \
	NAME::~NAME() {}

BFME_ROW_DTOR( 000658A0, AsciiStringVector )
BFME_ROW_DTOR( 00078B80, Vector00078B80 )
BFME_ROW_DTOR( 00128C50, ActiveBodyModuleData )
BFME_ROW_DTOR( 00129C80, AttributeModifierAuraUpdateModuleDataMemberD )
BFME_ROW_DTOR( 00197BC0, Tree00197BC0 )
BFME_SUBOBJECT_DTOR( 00197C60 )
BFME_ROW_DTOR( 002360C0, Tree002360C0 )
BFME_SUBOBJECT_DTOR( 002DAB10 )
BFME_ROW_DTOR( 002DBBF0, Vector002DBBF0 )
BFME_ROW_DTOR( 002E1260, Vector002E1260 )
BFME_ROW_DTOR( 0039D550, AttributeHandleStandIn )
BFME_ROW_DTOR( 00770380, Vector00770380 )
class RowMember00887940 { public: ~RowMember00887940() { reinterpret_cast<StringBase<char> *>(this)->releaseBuffer(); } };
BFME_ROW_DTOR( 009A1A40, SubsystemInterface )
BFME_ROW_DTOR( 0090D090, Rva0090D090 )
class RowMember009DB7A0 { public: ~RowMember009DB7A0() { reinterpret_cast<StringClass *>(this)->Free_String(); } };

BFME_PAIR_DTOR( Rva00078D90, RowMember009A1A40, RowMember00078B80, 7 )
BFME_PAIR_DTOR( Rva00129560, RowMember00128C50, RowMember00887940, 91 )
BFME_PAIR_DTOR( Rva00198550, RowMember00197BC0, Mem00197C60, 11 )
BFME_PAIR_DTOR( Rva00212BB0, RowMember00128C50, RowMember0039D550, 91 )
BFME_PAIR_DTOR( Rva00212C70, RowMember00128C50, RowMember0039D550, 91 )
BFME_PAIR_DTOR( Rva00213220, RowMember00128C50, RowMember00129C80, 91 )
BFME_PAIR_DTOR( Rva002832C0, RowMember00887940, RowMember00887940, 47 )
BFME_PAIR_DTOR( Rva002DAC90, Mem002DAB10, RowMember00887940, 87 )
BFME_PAIR_DTOR( Rva002DB120, Mem002DAB10, RowMember00887940, 95 )
BFME_PAIR_DTOR( Rva002DC670, Mem002DAB10, RowMember002DBBF0, 123 )
BFME_PAIR_DTOR( Rva002DD220, Mem002DAB10, RowMember00887940, 87 )
BFME_PAIR_DTOR( Rva002DEE50, Mem002DAB10, RowMember000658A0, 87 )
BFME_PAIR_DTOR( Rva002DF6D0, Mem002DAB10, RowMember00887940, 91 )
BFME_PAIR_DTOR( Rva002E9E10, RowMember00887940, RowMember002E1260, 7 )
BFME_PAIR_DTOR( Rva003B9270, RowMember00887940, RowMember002360C0, 7 )
BFME_PAIR_DTOR( Rva00770F40, RowMember00887940, RowMember00770380, 15 )
BFME_PAIR_DTOR( Rva0090E520, RowMember0090D090, RowMember009DB7A0, 59 )
BFME_PAIR_DTOR( Rva0090E620, RowMember0090D090, RowMember009DB7A0, 59 )
