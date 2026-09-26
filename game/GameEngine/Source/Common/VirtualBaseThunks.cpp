// Ten compiler-generated VIRTUAL-BASE thunks.  Each is a vtable entry that
// steps `this` back by a displacement the OBJECT carries, then jumps to the
// real override:
//
//     sub ecx,[ecx-4] / jmp <REL32>
//
// WHAT THE BYTES SHOW.  This is the adjustor thunk's shape with the constant
// replaced by a LOAD from four bytes ahead of the vtable pointer.  A fixed
// offset cannot be used because the distance from a virtual base back to the
// most-derived object is not fixed at compile time -- it depends on the
// complete object -- so the compiler stores it next to the vptr and reads it
// here.  That word is the vtordisp, and MSVC emits it only for a class with a
// VIRTUAL base whose virtual function the class overrides and which has a
// constructor or destructor of its own.
//
// LIKE THE FIXED-OFFSET ADJUSTOR THUNKS, THESE ARE NOT HAND-WRITTEN FUNCTIONS.
// They are declared the only way that reproduces them: by declaring the virtual
// inheritance that makes the compiler emit them.  The override is only
// DECLARED and is pinned at the address the REL32 names, so the thunk is the
// claimed body and the override is an external.
//
// THE ONLY AXIS IS THE REL32 TARGET.  There is no offset axis at all -- the
// displacement is data, not an immediate -- which is why all ten bodies are
// byte-identical once the displacement is masked.
//
// IDENTITY IS NOT RECOVERED.  Every class name is derived from the thunk's own
// address; the override pins are address-derived and additive.

#define BFME_VIRTUAL_BASE_THUNK( NAME )                                   \
	class NAME##Shared                                                    \
	{                                                                     \
	public:                                                               \
		virtual void handle();                                            \
		int m_value;                                                      \
	};                                                                    \
	class NAME : virtual public NAME##Shared                              \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		virtual void handle();                                            \
		int m_own;                                                        \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_own = 0;                                                        \
	}

BFME_VIRTUAL_BASE_THUNK( Rva001B3DF0 )
BFME_VIRTUAL_BASE_THUNK( Rva001B3E00 )
BFME_VIRTUAL_BASE_THUNK( Rva001B3E10 )
BFME_VIRTUAL_BASE_THUNK( Rva001B3E20 )
BFME_VIRTUAL_BASE_THUNK( Rva001B3E40 )
BFME_VIRTUAL_BASE_THUNK( Rva001D3F50 )
BFME_VIRTUAL_BASE_THUNK( Rva001D3F70 )
BFME_VIRTUAL_BASE_THUNK( Rva001D3F90 )
BFME_VIRTUAL_BASE_THUNK( Rva001D3FD0 )
BFME_VIRTUAL_BASE_THUNK( Rva001D3FF0 )
