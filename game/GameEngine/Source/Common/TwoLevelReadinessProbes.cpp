// The three byte-identical 27-byte readiness probes at 0x0016CC10, 0x0016DCB0
// and 0x0016DE20:
//
//     mov eax,[ecx+0x24] / test eax,eax / je false
//     mov ecx,[eax+0x1C] / test ecx,ecx / je true
//     mov eax,ecx / mov edx,[eax] / jmp dword ptr [edx+0x1C]
//     true: mov al,1 / ret
//     false: xor al,al / ret
//
// WHAT THE BYTES SHOW.  `this` in ecx, nothing on the stack, and returns that
// write AL ONLY: __thiscall taking no arguments and returning bool.  Two links
// are walked -- the member at +0x24, then that object's member at +0x1C -- and
// each has its own answer when it is null: a MISSING FIRST link is false, a
// missing second link is TRUE.  The two constants differing that way is the
// whole content of the function.
//
// `jmp dword ptr [edx+0x1C]` is a TAIL CALL, not a dispatch-and-return: the
// second link's slot 0x1C is entered with the frame already torn down and its
// bool becomes this function's bool directly.  Both constant returns sit AFTER
// the jump, which is /O2 laying the fall-through path through the call.
//
// THE REGISTER CHOICE IS A SOURCE FACT, and it is what took two rounds to get
// right.  Caching the second link in a local produces `mov eax,[eax+0x1C]`
// followed by `mov edx,[eax] / mov ecx,eax` -- correct behaviour, wrong bytes.
// Retail loads it straight into ecx and then copies it OUT to eax to reach the
// vftable, which is what MSVC emits when the source names the member expression
// TWICE, once in the test and once as the call's object: the value is wanted as
// `this` from the start, so it is materialised in ecx and the vftable load
// borrows eax.  A local hoists it into the general register instead.  Same
// behaviour, different bytes; the spelling below is the one that matches.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Three addresses in one drawer, each its own
// predicate over its own pair of classes.
//
// IDENTITY IS NOT RECOVERED.  The names are address-derived and disclaim
// identity.

#define BFME_TWO_LEVEL_READINESS( NAME )                                      \
	class NAME##Inner                                                         \
	{                                                                         \
	public:                                                                   \
		virtual void slot00(); virtual void slot04();                         \
		virtual void slot08(); virtual void slot0C();                         \
		virtual void slot10(); virtual void slot14();                         \
		virtual void slot18();                                                \
		virtual bool isReady() const;                                         \
	};                                                                        \
	class NAME##Mid                                                           \
	{                                                                         \
	public:                                                                   \
		char m_leading[ 0x1C ];                                               \
		NAME##Inner *m_inner;                                                 \
	};                                                                        \
	class NAME##Outer                                                         \
	{                                                                         \
	public:                                                                   \
		char m_leading[ 0x24 ];                                               \
		NAME##Mid *m_mid;                                                     \
		bool isReady() const;                                                 \
	};                                                                        \
	bool NAME##Outer::isReady() const                                         \
	{                                                                         \
		NAME##Mid *mid = m_mid;                                               \
		if ( mid != 0 )                                                       \
		{                                                                     \
			if ( mid->m_inner != 0 )                                          \
			{                                                                 \
				return mid->m_inner->isReady();                               \
			}                                                                 \
			return true;                                                      \
		}                                                                     \
		return false;                                                         \
	}

BFME_TWO_LEVEL_READINESS( Rva0016CC10 )
BFME_TWO_LEVEL_READINESS( Rva0016DCB0 )
BFME_TWO_LEVEL_READINESS( Rva0016DE20 )
