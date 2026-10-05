// Twenty-four bodies that pick one of FOUR entries out of a static record and
// write two dwords through two out-parameters.  They come in two spellings that
// differ only in where the selector comes from.
//
// WHAT THE BYTES SHOW.  One dword of stack is reserved and STORED ZERO, then
// immediately overwritten and read back:
//
//     push ecx / mov dword ptr [esp],0 / <selector> / mov eax,[esp]
//     and eax,3
//     *param0 = record.second[eax];
//     *param1 = record.first[eax];
//
// The selector is `mov [esp],esp` in thirteen of them and `rdtsc` +
// `mov [esp],eax` in the other eleven.  Both are read back out of the slot
// rather than used in the register, and the dead zero-store survives, so the
// source really does initialise a local, assign to it, and then read it.
//
// THE TWO ASM LINES ARE NOT A LIFT.  Neither selector has a C++ spelling that
// survives this compiler.  `(unsigned)&v` folds to `lea eax,[esp]` and never
// materialises the store -- the C++ body comes out at 34 bytes against retail's
// 45 -- and marking the local `volatile` produces a DIFFERENT 48- and 38-byte
// shape, not this one.  MSVC 7.1 has no rdtsc intrinsic at all.  Everything
// around the one-instruction `__asm` is ordinary C++.
//
// ONE AXIS, AND IT IS A DATA ADDRESS.  Every one of the twenty-four names a
// DIFFERENT record.  Within a body the two loads are always exactly 0x14 apart,
// which is five dwords: the record holds two parallel five-entry dword arrays,
// the second at +0x14, and only the first four entries of each are reachable
// through `and eax,3`.  Across bodies the records step by 0x28 -- exactly the
// size of that record -- and several runs are contiguous, so these are almost
// certainly elements of one larger array.  That is an observation about
// ADDRESSES, not something the instructions prove, so each record is declared
// as its own object here.  What is NOT optional: twenty-four distinct addresses
// at one site means twenty-four distinct objects, and collapsing them onto one
// would still gate green while being wrong.
//
// IDENTITY IS NOT RECOVERED.  Function and record names are derived from
// addresses.  The DIR32 operands are filled from retail and are not evidence.
//
// Constructor users identify shared records as integer keys and seeds.
// The other records retain their unproven pointer declarations.

struct TwoBitSelectorRecord
{
	int *m_first[ 5 ];
	int *m_second[ 5 ];
};

struct BigObfSelectorRecord
{
	unsigned int m_key[ 5 ];
	unsigned int m_seed[ 5 ];
};

struct BigObfSelectorRecord012B7788
{
	unsigned int m_key[ 4 ];
	unsigned int m_padding;
	unsigned int m_seed[ 4 ];
};


#define BFME_SELECT_BY_STACK_RECORD( NAME, RECORD, TYPE, FIRST, SECOND )                          \
	extern TYPE RECORD;                                                                              \
	void NAME( int **outSecond, int **outFirst )                              \
	{                                                                         \
		unsigned int selector = 0;                                            \
		__asm { mov selector, esp }                                           \
		unsigned int index = selector & 3;                                    \
		*outSecond = reinterpret_cast<int *>( RECORD.SECOND[ index ] );                                 \
		*outFirst = reinterpret_cast<int *>( RECORD.FIRST[ index ] );                                   \
	}

#define BFME_SELECT_BY_TIMESTAMP_RECORD( NAME, RECORD, TYPE, FIRST, SECOND )                      \
	extern TYPE RECORD;                                                                              \
	void NAME( int **outSecond, int **outFirst )                              \
	{                                                                         \
		unsigned int selector = 0;                                            \
		__asm { rdtsc }                                                       \
		__asm { mov selector, eax }                                           \
		unsigned int index = selector & 3;                                    \
		*outSecond = reinterpret_cast<int *>( RECORD.SECOND[ index ] );                                 \
		*outFirst = reinterpret_cast<int *>( RECORD.FIRST[ index ] );                                   \
	}

#define BFME_SELECT_BY_STACK( NAME, RECORD ) \
	BFME_SELECT_BY_STACK_RECORD( NAME, RECORD, TwoBitSelectorRecord, m_first, m_second )
#define BFME_SELECT_BIG_BY_STACK( NAME, RECORD ) \
	BFME_SELECT_BY_STACK_RECORD( NAME, RECORD, BigObfSelectorRecord, m_key, m_seed )
#define BFME_SELECT_BY_TIMESTAMP( NAME, RECORD ) \
	BFME_SELECT_BY_TIMESTAMP_RECORD( NAME, RECORD, TwoBitSelectorRecord, m_first, m_second )
#define BFME_SELECT_BIG_BY_TIMESTAMP( NAME, RECORD ) \
	BFME_SELECT_BY_TIMESTAMP_RECORD( NAME, RECORD, BigObfSelectorRecord, m_key, m_seed )

BFME_SELECT_BIG_BY_STACK( Rva00072B80, g_ObfRecord012A7304 )
BFME_SELECT_BIG_BY_STACK( Rva00072C00, g_ObfRecord012A7354 )
BFME_SELECT_BIG_BY_STACK( Rva003C7EA0, g_ObfRecord012B4864 )
BFME_SELECT_BIG_BY_STACK( Rva003C7EE0, g_ObfRecord012B488C )
BFME_SELECT_BIG_BY_STACK( Rva00526430, g_ObfRecord012B7738 )
BFME_SELECT_BY_STACK_RECORD( Rva005264B0, g_ObfRecord012B7788, BigObfSelectorRecord012B7788, m_key, m_seed )
BFME_SELECT_BIG_BY_STACK( Rva0054D600, g_ObfRecord012B79A4 )
BFME_SELECT_BY_STACK( Rva0054D640, g_twoBitSelectorRecord012B79CC )
BFME_SELECT_BY_STACK( Rva0054D6C0, g_twoBitSelectorRecord012B7A1C )
BFME_SELECT_BY_STACK( Rva0054D700, g_twoBitSelectorRecord012B7A44 )
BFME_SELECT_BY_STACK( Rva0056CCC0, g_twoBitSelectorRecord012B7E70 )
BFME_SELECT_BY_STACK( Rva0056CD40, g_twoBitSelectorRecord012B7EC0 )
BFME_SELECT_BY_STACK( Rva0058F530, g_twoBitSelectorRecord012B829C )

extern BigObfSelectorRecord g_ObfRecord012A6FF4;
void Rva00062870(int **outSecond, int **outFirst)
{
	unsigned int selector = 0;
	__asm { rdtsc }
	__asm { mov selector, eax }
	unsigned int index = selector & 3;
	*outSecond = (int *)g_ObfRecord012A6FF4.m_seed[index];
	*outFirst = (int *)g_ObfRecord012A6FF4.m_key[index];
}
BFME_SELECT_BY_TIMESTAMP( Rva00099350, g_twoBitSelectorRecord012A7D38 )
BFME_SELECT_BIG_BY_TIMESTAMP( Rva003875C0, g_ObfRecord012B446C )
BFME_SELECT_BIG_BY_TIMESTAMP( Rva00387600, g_ObfRecord012B4494 )
BFME_SELECT_BY_TIMESTAMP( Rva0054D680, g_twoBitSelectorRecord012B79F4 )
BFME_SELECT_BY_TIMESTAMP( Rva0054D740, g_twoBitSelectorRecord012B7A6C )
BFME_SELECT_BY_TIMESTAMP( Rva0054D780, g_twoBitSelectorRecord012B7A94 )
BFME_SELECT_BY_TIMESTAMP( Rva0054D7C0, g_twoBitSelectorRecord012B7ABC )
BFME_SELECT_BY_TIMESTAMP( Rva0056CD00, g_twoBitSelectorRecord012B7E98 )
BFME_SELECT_BY_TIMESTAMP( Rva0056CD80, g_twoBitSelectorRecord012B7EE8 )
BFME_SELECT_BY_TIMESTAMP( Rva00619B10, g_twoBitSelectorRecord012B90B8 )
