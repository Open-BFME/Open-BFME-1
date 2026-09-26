// Two related families, six copies each, that both hand a virtual call a
// two-byte object whose two fields are set to 1.
//
// Six 55-byte bodies at 0x00113D50, 0x00113E70, 0x005F0CC0, 0x005F30F0,
// 0x005F54B0 and 0x005F7F50:
//
//     push ecx / push ebx / push esi / mov esi,[esp+0x10] / mov eax,[esi]
//     lea ecx,[esp+8] / mov bl,1 / push ecx / mov ecx,esi
//     mov [esp+0xC],bl / mov [esp+0xD],bl / call dword ptr [eax+0x28]
//     mov edx,[esi] / lea eax,[esp+0x10] / push eax / mov ecx,esi
//     mov [esp+0x14],bl / mov [esp+0x15],bl / call dword ptr [edx+0x28]
//     pop esi / pop ebx / pop ecx / ret 4
//
// Six 48-byte bodies at 0x0014F1E0, 0x0015FAC0, 0x0015FB00, 0x0016D520,
// 0x0018CAB0 and 0x0018CD20:
//
//     push ecx / push esi / mov esi,[esp+0xC] / push edi / mov edi,ecx
//     mov al,1 / lea ecx,[esp+8] / mov [esp+8],al / mov [esp+9],al
//     mov eax,[esi] / push ecx / mov ecx,esi / call dword ptr [eax+0x28]
//     mov edx,[esi] / add edi,0x24 / push edi / mov ecx,esi
//     call dword ptr [edx+0x74] / pop edi / pop esi / pop ecx / ret 4
//
// WHAT THE BYTES SHOW.  The leading `push ecx` allocates a four-byte frame slot,
// not an argument: nothing reads it and the matching `pop ecx` discards it.  The
// slot is written with TWO ADJACENT BYTE STORES of the same 1, and its ADDRESS
// is what gets pushed -- so the callee receives a two-field object by reference
// whose fields are both set true.  A two-byte class with two bool members is the
// only layout that produces two byte stores one apart and a size that fits the
// slot.
//
// In the 55-byte shape the SECOND such object lands in the incoming parameter's
// own stack slot.  That is not a write into the caller's frame: the parameter
// was copied into esi on entry and its slot is dead, so the compiler reuses it
// as the second temporary.  Two distinct slots for two objects is the tell that
// the source declares two, not one reused -- rewriting the same local produces
// re-stores into the SAME slot, which is a different body (verified against that
// spelling before this one was kept).
//
// The 48-byte shape adds a second virtual call through slot 0x74 whose only
// argument is `this + 0x24`, computed into edi before ecx is clobbered.  A
// member subobject passed by reference; `this` is otherwise never dereferenced,
// so the calling class carries no vftable of its own.
//
// CALLING CONVENTION.  Both end in `ret 4` with one stack argument.  The
// 48-byte shape reads ecx, so it is unambiguously __thiscall.  The 55-byte shape
// never reads ecx, and its bytes are IDENTICAL for a __thiscall member that
// ignores `this` and for a free __stdcall function -- both spellings were
// compiled and compare equal.  It is written here as a member to match its
// sibling, which is the weaker of the two claims in this file.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Twelve addresses across five different
// translation units in the retail image; each is its own instantiation over its
// own pair of classes, coinciding only because the dispatched slots and the
// argument shapes coincide.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image names the callers, the
// callees, or the flag pair, so every name here is address-derived and
// disclaims identity.

#define BFME_FLAG_PAIR_TARGET( NAME )                                         \
	struct NAME##Flags                                                        \
	{                                                                         \
		bool m_first;                                                         \
		bool m_second;                                                        \
	};                                                                        \
	class NAME##Target                                                        \
	{                                                                         \
	public:                                                                   \
		virtual void slot00(); virtual void slot04();                         \
		virtual void slot08(); virtual void slot0C();                         \
		virtual void slot10(); virtual void slot14();                         \
		virtual void slot18(); virtual void slot1C();                         \
		virtual void slot20(); virtual void slot24();                         \
		virtual void applyFlags( const NAME##Flags &flags );                  \
	};

// The 55-byte shape: two independent flag pairs, two calls through slot 0x28.
#define BFME_FLAG_PAIR_TWICE( NAME )                                          \
	BFME_FLAG_PAIR_TARGET( NAME )                                             \
	class NAME##Caller                                                        \
	{                                                                         \
	public:                                                                   \
		void invoke( NAME##Target *target );                                  \
	};                                                                        \
	void NAME##Caller::invoke( NAME##Target *target )                         \
	{                                                                         \
		NAME##Flags first;                                                    \
		first.m_first = true;                                                 \
		first.m_second = true;                                                \
		target->applyFlags( first );                                          \
		NAME##Flags second;                                                   \
		second.m_first = true;                                                \
		second.m_second = true;                                               \
		target->applyFlags( second );                                         \
	}

// slot 0x74 lives eighteen slots past applyFlags, so the target of the second
// family carries the extra padding.
#define BFME_FLAG_PAIR_MEMBER_TARGET( NAME )                                  \
	struct NAME##Flags                                                        \
	{                                                                         \
		bool m_first;                                                         \
		bool m_second;                                                        \
	};                                                                        \
	class NAME##Target                                                        \
	{                                                                         \
	public:                                                                   \
		virtual void slot00(); virtual void slot04();                         \
		virtual void slot08(); virtual void slot0C();                         \
		virtual void slot10(); virtual void slot14();                         \
		virtual void slot18(); virtual void slot1C();                         \
		virtual void slot20(); virtual void slot24();                         \
		virtual void applyFlags( const NAME##Flags &flags );                  \
		virtual void slot2C(); virtual void slot30();                         \
		virtual void slot34(); virtual void slot38();                         \
		virtual void slot3C(); virtual void slot40();                         \
		virtual void slot44(); virtual void slot48();                         \
		virtual void slot4C(); virtual void slot50();                         \
		virtual void slot54(); virtual void slot58();                         \
		virtual void slot5C(); virtual void slot60();                         \
		virtual void slot64(); virtual void slot68();                         \
		virtual void slot6C(); virtual void slot70();                         \
		virtual void takeMember( const int &member );                         \
	};

// The 48-byte shape: one flag pair through slot 0x28, then the member at 0x24
// through slot 0x74.
#define BFME_FLAG_PAIR_THEN_MEMBER( NAME )                                    \
	BFME_FLAG_PAIR_MEMBER_TARGET( NAME )                                      \
	class NAME##Caller                                                        \
	{                                                                         \
	public:                                                                   \
		void invoke( NAME##Target *target );                                  \
		char m_leading[ 0x24 ];                                               \
		int m_member;                                                         \
	};                                                                        \
	void NAME##Caller::invoke( NAME##Target *target )                         \
	{                                                                         \
		NAME##Flags flags;                                                    \
		flags.m_first = true;                                                 \
		flags.m_second = true;                                                \
		target->applyFlags( flags );                                          \
		target->takeMember( m_member );                                       \
	}

BFME_FLAG_PAIR_TWICE( Rva00113D50 )
BFME_FLAG_PAIR_TWICE( Rva00113E70 )
BFME_FLAG_PAIR_TWICE( Rva005F0CC0 )
BFME_FLAG_PAIR_TWICE( Rva005F30F0 )
BFME_FLAG_PAIR_TWICE( Rva005F54B0 )
BFME_FLAG_PAIR_TWICE( Rva005F7F50 )

BFME_FLAG_PAIR_THEN_MEMBER( Rva0014F1E0 )
BFME_FLAG_PAIR_THEN_MEMBER( Rva0015FAC0 )
BFME_FLAG_PAIR_THEN_MEMBER( Rva0015FB00 )
BFME_FLAG_PAIR_THEN_MEMBER( Rva0016D520 )
BFME_FLAG_PAIR_THEN_MEMBER( Rva0018CAB0 )
BFME_FLAG_PAIR_THEN_MEMBER( Rva0018CD20 )
