// Eight allocate-and-construct helpers, each returning a freshly built object of
// a DIFFERENT class over the same two bases.
//
// WHAT THE BYTES SHOW.
//
//     push 0x0C / call <allocator> / add esp,4      // twelve bytes, cdecl
//     test eax,eax / je -> xor eax,eax / ret        // MSVC's new-expression guard
//     [eax+4]  = 0x01129744                         // same constant in all eight
//     [eax+8]  = <the incoming parameter>
//     [eax]    = <varies>
//     [eax+4]  = <varies>                           // overwrites the first store
//
// Twelve bytes holding two pointer-sized slots at 0 and 4 plus one data dword at
// 8, with slot 4 written TWICE -- once with a constant shared by all eight rows,
// then again with a per-row constant -- is a MULTIPLE-INHERITANCE construction.
// The second base owns slot 4 and the data dword; its own constructor sets its
// vftable and stores the argument; the most-derived constructor then overwrites
// BOTH slots with its own two vftables.  The first base's vftable store into
// slot 0 is absent because the derived store to slot 0 follows immediately and
// the compiler drops it; the slot-4 store survives only because the data store
// sits between the two.  Single inheritance cannot produce two vftable slots,
// and a plain member would not be written with a constant that every one of the
// eight rows shares.
//
// The guarded null return is the ordinary shape of `return new T( x );`, and the
// allocator is a CLASS-SPECIFIC operator new: the global one lives elsewhere in
// this image, while every one of these eight reaches the same 0x007F0130.  That
// one allocator being shared across eight different derived classes puts it on a
// COMMON BASE, not on each class.
//
// ONE AXIS.  The pair of derived vftables.  The base vftable, the object size,
// the allocator and the argument slot are identical in all eight.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived.  The vftable operands
// are DIR32 sites filled from retail and prove nothing by themselves; what they
// do establish is that there are EIGHT distinct derived classes and exactly ONE
// second base, so they are modelled that way rather than collapsed.
//
// WHAT THE BYTES CANNOT DECIDE.  How many virtuals either base declares, what
// the stored dword means, and whether the first base has any data at all (it
// cannot, since the second base's vftable sits at offset 4).

void *Gen007F0130( unsigned int size );

class Q3MakeBaseA
{
public:
	virtual void primary();
	static void *operator new( unsigned int size ) { return Gen007F0130( size ); }
};

class Q3MakeBaseB
{
public:
	virtual void secondary();
	void *m_payload;
	Q3MakeBaseB( void *payload ) { m_payload = payload; }
};

#define BFME_MAKE_DERIVED( NAME )                                             \
	class NAME##Object : public Q3MakeBaseA, public Q3MakeBaseB               \
	{                                                                         \
	public:                                                                   \
		NAME##Object( void *payload ) : Q3MakeBaseB( payload ) {}             \
		virtual void primary();                                               \
		virtual void secondary();                                             \
	};                                                                        \
	NAME##Object *NAME( void *payload )                                       \
	{                                                                         \
		return new NAME##Object( payload );                                   \
	}

BFME_MAKE_DERIVED( Rva007E9B40 )
BFME_MAKE_DERIVED( Rva007F1C20 )
BFME_MAKE_DERIVED( Rva007F2150 )
BFME_MAKE_DERIVED( Rva007F2E60 )
BFME_MAKE_DERIVED( Rva007F3410 )
BFME_MAKE_DERIVED( Rva007F40F0 )
BFME_MAKE_DERIVED( Rva007FBB20 )
BFME_MAKE_DERIVED( Rva007FCF80 )
