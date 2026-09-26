// Twelve __thiscall constructors that open with the vftable-plus-zeroed-dword
// head and then store their arguments straight into the members that follow it.
//
// The head is the one FunctorBindInvokers.cpp measured and
// FunctorBindWrapperCtors.cpp landed constructors for: a vftable slot at +0x00
// and one unmodelled dword at +0x04, split into a base whose own constructor
// zeroes that dword.  Every body here begins
//
//     mov eax,ecx / ... / mov [eax+4],0 / mov [eax],<vftable>
//
// -- `mov eax,ecx` with no other use of eax is a constructor returning `this`,
// and the +0x04 store landing BEFORE the +0x00 store is the base's dead vftable
// write being dropped, which a single class cannot produce (probed: it emits
// the vftable first).  What differs between the six shapes below is only what
// is stored after that, so they are grouped by argument shape and each body is
// named for its own address; no class name has been recovered for any of them.

class VptrZeroHead
{
public:
	VptrZeroHead() : m_unmodelled_04( 0 ) {}

	virtual void vptrZeroAnchor();

	unsigned int m_unmodelled_04;
};

// mov dl,[esp+8] / mov eax,ecx / mov ecx,[esp+4] / <head> /
// mov [eax+8],ecx / mov [eax+0xC],dl / ret 8
#define BFME_VPTR_ZERO_PTR_BYTE_CTOR( NAME )                                  \
	class NAME : public VptrZeroHead                                          \
	{                                                                         \
	public:                                                                   \
		NAME( void *pointer, unsigned char flag );                            \
                                                                              \
		void          *m_pointer;                                             \
		unsigned char  m_flag;                                                \
	};                                                                        \
	NAME::NAME( void *pointer, unsigned char flag )                           \
		: m_pointer( pointer ), m_flag( flag ) {}

// mov edx,[esp+8] / mov eax,ecx / mov ecx,[esp+4] / <head> /
// mov [eax+8],ecx / mov [eax+0xC],edx / ret 8
#define BFME_VPTR_ZERO_PTR_PTR_CTOR( NAME )                                   \
	class NAME : public VptrZeroHead                                          \
	{                                                                         \
	public:                                                                   \
		NAME( void *first, void *second );                                    \
                                                                              \
		void *m_first;                                                        \
		void *m_second;                                                       \
	};                                                                        \
	NAME::NAME( void *first, void *second )                                   \
		: m_first( first ), m_second( second ) {}

// The same two stores fed by the arguments the other way round:
// mov edx,[esp+4] / mov eax,ecx / mov ecx,[esp+8] / <head> /
// mov [eax+8],ecx / mov [eax+0xC],edx / ret 8.  The stores are still in
// declaration order -- it is the initialisers that cross.
#define BFME_VPTR_ZERO_PTR_PTR_SWAPPED_CTOR( NAME )                           \
	class NAME : public VptrZeroHead                                          \
	{                                                                         \
	public:                                                                   \
		NAME( void *first, void *second );                                    \
                                                                              \
		void *m_second;                                                       \
		void *m_first;                                                        \
	};                                                                        \
	NAME::NAME( void *first, void *second )                                   \
		: m_second( second ), m_first( first ) {}

// mov dl,[esp+8] / mov eax,ecx / mov cl,[esp+4] / <head> /
// mov [eax+8],cl / mov [eax+9],dl / ret 8
#define BFME_VPTR_ZERO_BYTE_BYTE_CTOR( NAME )                                 \
	class NAME : public VptrZeroHead                                          \
	{                                                                         \
	public:                                                                   \
		NAME( unsigned char first, unsigned char second );                    \
                                                                              \
		unsigned char m_first;                                                \
		unsigned char m_second;                                                \
	};                                                                        \
	NAME::NAME( unsigned char first, unsigned char second )                   \
		: m_first( first ), m_second( second ) {}

// mov eax,ecx / mov cl,[esp+4] / <head> / mov [eax+8],cl / ret 4
#define BFME_VPTR_ZERO_BYTE_CTOR( NAME )                                      \
	class NAME : public VptrZeroHead                                          \
	{                                                                         \
	public:                                                                   \
		NAME( unsigned char flag );                                           \
                                                                              \
		unsigned char m_flag;                                                 \
	};                                                                        \
	NAME::NAME( unsigned char flag ) : m_flag( flag ) {}

// mov eax,ecx / <head> / ret 4 -- one dword argument consumed and nothing
// stored from it.
#define BFME_VPTR_ZERO_UNUSED_ARG_CTOR( NAME )                                \
	class NAME : public VptrZeroHead                                          \
	{                                                                         \
	public:                                                                   \
		NAME( void *ignored );                                                \
	};                                                                        \
	NAME::NAME( void * ) {}

// mov dl,[esp+8] / mov eax,ecx / mov ecx,[esp+4] / mov [eax+8],ecx /
// mov ecx,[esp+0xC] / <head> / mov [eax+0xC],dl / mov [eax+0x10],ecx / ret 0xC
#define BFME_VPTR_ZERO_PTR_BYTE_PTR_CTOR( NAME )                              \
	class NAME : public VptrZeroHead                                          \
	{                                                                         \
	public:                                                                   \
		NAME( void *first, unsigned char second, void *third );               \
                                                                              \
		void          *m_first;                                               \
		unsigned char  m_second;                                              \
		void          *m_third;                                               \
	};                                                                        \
	NAME::NAME( void *first, unsigned char second, void *third )              \
		: m_first( first ), m_second( second ), m_third( third ) {}

BFME_VPTR_ZERO_PTR_BYTE_CTOR( Rva00160BB0VptrZeroObject )
BFME_VPTR_ZERO_PTR_BYTE_CTOR( Rva00160CA0VptrZeroObject )
BFME_VPTR_ZERO_PTR_BYTE_CTOR( Rva0016AA20VptrZeroObject )
BFME_VPTR_ZERO_PTR_BYTE_CTOR( Rva001F6FC0VptrZeroObject )
BFME_VPTR_ZERO_PTR_BYTE_CTOR( Rva00204360VptrZeroObject )
BFME_VPTR_ZERO_PTR_BYTE_CTOR( Rva00297440VptrZeroObject )

BFME_VPTR_ZERO_PTR_PTR_CTOR( Rva0015B940VptrZeroObject )
BFME_VPTR_ZERO_PTR_PTR_CTOR( Rva0016D590VptrZeroObject )

BFME_VPTR_ZERO_PTR_PTR_SWAPPED_CTOR( Rva00264A70VptrZeroObject )

BFME_VPTR_ZERO_BYTE_BYTE_CTOR( Rva00149F20VptrZeroObject )

BFME_VPTR_ZERO_BYTE_CTOR( Rva002ED590VptrZeroObject )
BFME_VPTR_ZERO_PTR_BYTE_PTR_CTOR( Rva002ED5C0VptrZeroObject )
BFME_VPTR_ZERO_BYTE_CTOR( Rva002ED600VptrZeroObject )

BFME_VPTR_ZERO_UNUSED_ARG_CTOR( Rva00385E50VptrZeroObject )


