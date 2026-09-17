// Six tiny __thiscall members that destroy a pointer held at a fixed offset in
// the object and then clear the slot:
//
//     push esi / push edi / mov edi,ecx / mov esi,[edi+OFFSET] /
//     test esi,esi / je L / mov ecx,esi / call <dtor REL32> /
//     push esi / call <operator delete REL32> / add esp,4 /
//     L: mov [edi+OFFSET],0 / pop edi / pop esi / ret
//
// WHAT THE BYTES SHOW.  The destructor is reached by a DIRECT call, not through
// a vtable slot and not through a `??_G` scalar deleting destructor, so the
// pointee's destructor is NON-VIRTUAL: `delete p` on a polymorphic type would
// have gone indirect.  `operator delete` takes the raw pointer with a cdecl
// `add esp,4`, which is the ordinary global one, not a pool overload.  Two
// registers are preserved across the pair of calls because BOTH `this` and the
// loaded pointer outlive them.
//
// TWO AXES, BOTH READ DIRECTLY: the member OFFSET and the destructor REL32.
// Six members over five destructors; every (destructor, offset) pair is
// distinct, so no two rows are the same source.
//
// THE FAMILY IS NOT ONE SHAPE.  Five members let the `je` land ON the
// zero-store, so the store is unconditional and the source reads
// `delete m_owned; m_owned = 0;`.  Rva00695D60 jumps PAST the store to the
// epilogue, which only happens when the store is inside the guard --
// `if( m_owned ) { delete m_owned; m_owned = 0; }`.  Both spellings are the
// same length; only the branch displacement tells them apart, and it does.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  The bytes
// cannot say what any of these classes are, what the destroyed objects are, or
// whether the six owners are six types or fewer -- only that each row's
// (offset, destructor) pair differs from every other row's.

#define S3_OWNED_CALLEE( ADDR )                                           \
	class Gen##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		~Gen##ADDR();                                                     \
	};

#define S3_OWNED_CALLEE_NAMED( NAME )                                     \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		~NAME();                                                          \
	};

#define S3_DELETE_AND_CLEAR_HEAD( NAME, CALLEE )                          \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void release();                                                   \
		CALLEE *m_owned;                                                  \
	};                                                                    \
	void NAME::release()                                                  \
	{                                                                     \
		delete m_owned;                                                   \
		m_owned = 0;                                                      \
	}

#define S3_DELETE_AND_CLEAR( NAME, CALLEE, OFFSET )                       \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void release();                                                   \
		char m_lead[ OFFSET ];                                            \
		CALLEE *m_owned;                                                  \
	};                                                                    \
	void NAME::release()                                                  \
	{                                                                     \
		delete m_owned;                                                   \
		m_owned = 0;                                                      \
	}

#define S3_GUARDED_DELETE_AND_CLEAR( NAME, CALLEE, OFFSET )               \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void release();                                                   \
		char m_lead[ OFFSET ];                                            \
		CALLEE *m_owned;                                                  \
	};                                                                    \
	void NAME::release()                                                  \
	{                                                                     \
		if( m_owned )                                                     \
		{                                                                 \
			delete m_owned;                                               \
			m_owned = 0;                                                  \
		}                                                                 \
	}

S3_OWNED_CALLEE( 009DB400 )
S3_OWNED_CALLEE( 0003FA7B )
S3_OWNED_CALLEE( 009DB4D0 )
S3_OWNED_CALLEE( 0000D33C )
S3_OWNED_CALLEE_NAMED( HLodDefClass )

S3_DELETE_AND_CLEAR_HEAD( Rva0010B990, Gen009DB400 )
S3_DELETE_AND_CLEAR_HEAD( Rva005907F0, Gen0003FA7B )
S3_DELETE_AND_CLEAR( Rva005929E0, Gen0003FA7B, 8 )
S3_DELETE_AND_CLEAR_HEAD( Rva0063B190, Gen009DB4D0 )
S3_GUARDED_DELETE_AND_CLEAR( Rva00695D60, Gen0000D33C, 2904 )
S3_DELETE_AND_CLEAR( Rva009706B0, HLodDefClass, 20 )
