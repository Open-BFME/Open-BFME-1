// cl: /O2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME5: STLport vector<Gen00762250>::operator=, retail 0x00770830,
// 308 bytes.  The 0x38 element stride is read directly from the assignment
// and its helper calls.  The clear call at ILT 0x00011A8B enters the already
// matched vector<Gen00762250> destructor at 0x00770650, which is the strongest
// type evidence available for this anonymous assignment body.
//
// The remaining calls are the template helpers selected by this assignment:
// ILT 0x0002DB4B enters the 0x007690F0 allocate-and-copy body; ILT 0x00008341
// enters the 0x0075EAA0 width-56 copy body twice; ILT 0x00025D33 enters the
// 0x0076F8C0 width-56 member walk; and ILT 0x00027E35 enters the 0x00768BF0
// width-56 copy walk.  These are helper/stride facts, not semantic names for
// the anonymous body.  The current ledger has no named caller for 0x00770830
// or its 0x00030D5A entry thunk, so the assignment identity remains bounded by
// the matched vector destructor and this complete retail helper cluster.

#include <vector>

struct Gen00762250
{
	char m_payload[ 56 ];
	Gen00762250();
	Gen00762250( const Gen00762250 & );
	~Gen00762250();
	Gen00762250 &operator=( const Gen00762250 & );
};

template class _STL::vector<Gen00762250>;
