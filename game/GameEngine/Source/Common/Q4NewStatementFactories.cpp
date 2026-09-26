// cl: /EHsc
//
// 69-byte free functions that allocate one object, default-construct it and
// DISCARD the result:
//
//     push <SIZE> / call operator new / add esp,4
//     test eax,eax / je epilogue        (shared -- no xor eax on the null arm)
//     mov ecx,eax / call <CTOR>
//
// WHAT THE BYTES SHOW.  Same allocate-then-construct core as the
// Q4NewNiladicFactories.cpp family, but the two epilogues FOLD INTO ONE and
// the null arm has no `xor eax,eax`: the value of the new-expression is never
// used, which under MSVC 7.1 only comes out of `new X;` as an expression
// STATEMENT in a function returning void -- `return new X;` keeps the split
// epilogue (see the fifteen matched 98-byte AptScreenFactories.cpp factories).
// The constructed object registers itself; the caller keeps no pointer.
//
// IDENTITY IS NOT RECOVERED.  The class is named after its constructor's
// address, the function after its own, and `char m_storage[SIZE]` carries
// sizeof(X) without making a layout claim.

#define Q4_NEW_STATEMENT_FACTORY( GEN, SIZE, MAKER )                       \
	class GEN                                                              \
	{                                                                      \
	public:                                                                \
		GEN();                                                             \
		char m_storage[ SIZE ];                                            \
	};                                                                     \
	void MAKER()                                                           \
	{                                                                      \
		new GEN;                                                           \
	}

Q4_NEW_STATEMENT_FACTORY( Gen00522E00, 0x4c, construct00510AC0 )
