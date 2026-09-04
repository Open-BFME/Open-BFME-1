// cl: -GX-
// stlport
//
// Open-BFME5: more PA-style vector::erase(first,last) 77B siblings on
// d_003ad560. Unique strides only (skip 0x20 ICF twins 0x003AF920/0x003B6FD0).

#include <vector>

#define BFME_PA_ERASE_ELEM( NAME, SIZE ) \
	struct NAME                          \
	{                                    \
		virtual ~NAME();                 \
		char m_body[ (SIZE) - 4 ];       \
		NAME();                          \
		NAME( const NAME & );            \
		NAME &operator=( const NAME & ); \
	};                                   \
	template class _STL::vector<NAME>

BFME_PA_ERASE_ELEM( Elem003AF800, 0x30 );
BFME_PA_ERASE_ELEM( Elem003AF860, 0x20 );
BFME_PA_ERASE_ELEM( Elem003AF8C0, 0x0C );
BFME_PA_ERASE_ELEM( Elem003AF980, 0x14 );
BFME_PA_ERASE_ELEM( Elem003AF9E0, 0x10 );
BFME_PA_ERASE_ELEM( Elem003B2540, 0x18 );
BFME_PA_ERASE_ELEM( Elem003B2830, 0x24 );
