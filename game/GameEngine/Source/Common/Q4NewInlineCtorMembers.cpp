// cl: /EHsc
//
// Nine 99-byte __thiscall members that allocate an object, run ONE out-of-line
// constructor on it, and then store THREE .rdata addresses at +0, +0x14, +0x18:
//
//     push <SIZE> / mov edi,ecx / call operator new / mov esi,eax
//     test / je null
//     push edi / mov ecx,esi / call <BASE CTOR>
//     mov [esi],<V0> / mov [esi+0x14],<V1> / mov [esi+0x18],<V2>
//     return esi              (null path returns 0)
//
// WHAT THE BYTES SHOW.  Same `return new T(this)` as Q4NewOwnerFactories.cpp
// with T's constructor INLINED instead of called: one out-of-line base
// constructor taking the receiver, then three constant stores.  The three
// constants are vftables -- 0x00D11D9C, 0x00D11DB0 and 0x00D11DB4 for the
// first member are a contiguous .rdata run of 4, 1 and 8 code pointers, and
// every member's trio is contiguous the same way.
//
// THE STORE ORDER DECIDES MEMBER AGAINST BASE, AND IT COST A REFUTATION.
// Three vptrs at 0, 0x14 and 0x18 look like a class with three polymorphic
// BASES, but that spelling emits the two SECONDARY vptrs first and the primary
// last -- the exact reverse of retail.  MSVC's constructor order is: base
// constructors, then this class's own vptrs, then MEMBER constructors.  Retail
// stores +0 first and +0x14, +0x18 after, so +0x14 and +0x18 belong to member
// subobjects whose (inlined, trivial) constructors run after the derived vptr
// is planted.  Multiple inheritance is REFUTED here by instruction order alone.
//
// So each class is: one polymorphic base at 0 whose constructor is out of line
// and takes the receiver, occupying 0x14 bytes; a polymorphic member at 0x14;
// a polymorphic member at 0x18; and, where SIZE exceeds 0x1c, trailing bytes.
// The trailing bytes are attributed to the constructed class because the vptr
// offsets fix everything below 0x1c -- which class actually owns them is NOT
// decided by the bytes.  The derived class must override something, or MSVC
// would reuse the base's vftable and emit no store at +0 at all; that is why
// one override is declared.  The virtual COUNTS here are minimal placeholders:
// the real slot counts are visible in .rdata but nothing in these 99 bytes
// depends on them, so they are not claimed.
//
// THE VARYING AXIS IS TWO FIELDS: the allocation size and the base
// constructor's REL32.  Nine members, nine distinct constructors, sizes
// 0x1c (x4), 0x5c, 0x40, 0x28, 0x34 (x2) -- the repeats pair with different
// callees, so the fields are independent.  The three vftable addresses are
// DIR32 operands copied from retail and are NOT evidence; they do force the
// model, though: nine distinct address trios at the same three sites means
// nine distinct classes, and one class reused would gate green while failing
// verify_dir32_consistency.
//
// IDENTITY IS NOT RECOVERED.  Every name is address-derived.
//
#define Q4_MID( T )                                                       	class HostX##T;                                                       	class BaseX##T                                                        	{                                                                     	public:                                                               		BaseX##T( HostX##T *owner );                                      		virtual void b0();                                                		char m_data[ 0x10 ];                                              	};                                                                    	class MidX##T { public: virtual void m0(); };                         	class TailX##T { public: virtual void t0(); };

#define Q4_BODY( T, PAD )                                                 	class GenX##T : public BaseX##T                                       	{                                                                     	public:                                                               		GenX##T( HostX##T *owner ) : BaseX##T( owner ) { }                		virtual void b0();                                                		MidX##T m_mid;                                                    		TailX##T m_tail;                                                  		PAD                                                               	};                                                                    	class HostX##T { public: GenX##T *create(); };                        	GenX##T *HostX##T::create() { return new GenX##T( this ); }

Q4_MID( 005EB6B0 )
Q4_BODY( 005EB6B0,  )

Q4_MID( 005EB830 )
Q4_BODY( 005EB830,  )

Q4_MID( 005EB930 )
Q4_BODY( 005EB930,  )

Q4_MID( 005EBA30 )
Q4_BODY( 005EBA30,  )

Q4_MID( 005EBB30 )
Q4_BODY( 005EBB30, char m_pad[ 0x40 ]; )

Q4_MID( 005ED230 )
Q4_BODY( 005ED230, char m_pad[ 0x24 ]; )

Q4_MID( 005ED360 )
Q4_BODY( 005ED360, char m_pad[ 0xc ]; )

Q4_MID( 005ED510 )
Q4_BODY( 005ED510, char m_pad[ 0x18 ]; )

Q4_MID( 005ED630 )
Q4_BODY( 005ED630, char m_pad[ 0x18 ]; )

