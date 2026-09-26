// Two sixteen-byte bodies that park a fixed address in the object's first dword
// and hand the next dword to a call:
//
//     mov eax,[ecx+4] / push eax / mov dword ptr [ecx],<DIR32> /
//     call <REL32> / ret
//
// THIS IS A THIN ROW AND IT IS WORTH SAYING SO.  Two of the four operand fields
// are relocation sites build.py fills from retail, so only EIGHT bytes here are
// evidence -- the minimum this project accepts.  What those eight prove is
// still a real shape: a dword read from offset 4, pushed as the single argument;
// a dword-wide store to offset 0; and a direct call after which esp is NOT
// adjusted, so the callee cleans the stack.
//
// Both rows store the SAME address (RVA 0x00C73728 in .rdata) and call the SAME
// target, 0x009F6BC8 -- which is a `jmp dword ptr [.idata]` import stub, so in
// retail this reaches a DLL.  With one stack argument and no caller cleanup the
// callee is either __stdcall or a __thiscall member taking one argument; the two
// encode identically here because ecx already holds `this`.  It is spelled as a
// __stdcall free function, which claims no owning class.
//
// The store lands between the argument load and the call, but that is
// scheduling: the bytes do not fix whether the store or the call came first in
// the source.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived.  The stored .rdata
// address reads like a vftable, but a vftable store and `m_p = &SomeConst;` are
// the same four copied bytes.

extern const int Rdata00C73728;

void __stdcall b_009f6bc8( int value );

#define BFME_STORE_THEN_FORWARD( NAME )                                   \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void dispatch();                                                  \
		const int *m_target;                                              \
		int m_value;                                                      \
	};                                                                    \
	void NAME::dispatch()                                                 \
	{                                                                     \
		m_target = &Rdata00C73728;                                        \
		b_009f6bc8( m_value );                                            \
	}

BFME_STORE_THEN_FORWARD( Rva0005BC00 )
BFME_STORE_THEN_FORWARD( Rva0005BE30 )
