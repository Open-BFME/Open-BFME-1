// cl: /DNDEBUG /MD /EHsc
// Five virtual forwarders at 0x00848170/0x008481B0/0x008481F0/0x008482A0/
// 0x008482E0, same family as the eight at 0x00847D30..0x00847EA0.
// IDENTITY IS NOT RECOVERED: no caller, string or vtable names the holder or
// the member, so every name is derived from its own address.
//
// WHAT THE BYTES SHOW. Each body reads the dword at [this+0] as a vtable
// pointer, pushes its incoming arguments twice (once to save p1 in esi,
// once as the callee's argument list), calls one slot through that vtable
// with ecx still holding `this`, then returns the saved first argument:
//
//     mov edx,[esp+N] / push esi / push edx / ... / mov eax,[ecx] /
//     call [eax+SLOT] / mov eax,esi / pop esi / ret N
//
// ecx is never reloaded, so the callee's receiver is `this` itself: the
// polymorphic member sits at offset +0, where its address equals `this`
// and no lea is needed. The callee's return value is discarded
// (`mov eax,esi` overwrites it), so the source calls the slot and then
// returns the first argument:
//
//     void *Owner::forward(...) { m_member.slot(...); return p1; }
//
// The three 57-byte bodies take nine pointers and call slot +8/+4/+4; the
// two 52-byte bodies take six pointers plus a trailing double (rebuilt on
// the frame with `fld [esp+N] / sub esp,8 / fstp [esp]`) and call slot +8.
// Each body keeps its own owner; separate functions, not aliases.

#define BFME_FWD9_08( OWNER, MEMBER )                                          \
	class MEMBER                                                               \
	{                                                                          \
	public:                                                                    \
		virtual void s0();                                                     \
		virtual void s4();                                                     \
		virtual void s8(void *p1, void *p2, void *p3, void *p4, void *p5,       \
			void *p6, void *p7, void *p8, void *p9);                           \
	};                                                                         \
	class OWNER                                                                \
	{                                                                          \
	public:                                                                    \
		void *forward(void *p1, void *p2, void *p3, void *p4, void *p5,         \
			void *p6, void *p7, void *p8, void *p9);                           \
		MEMBER m_member;                                                       \
	};                                                                         \
	void *OWNER::forward(void *p1, void *p2, void *p3, void *p4, void *p5,      \
		void *p6, void *p7, void *p8, void *p9)                                \
	{                                                                          \
		m_member.s8(p1, p2, p3, p4, p5, p6, p7, p8, p9);                        \
		return p1;                                                             \
	}

#define BFME_FWD9_04( OWNER, MEMBER )                                          \
	class MEMBER                                                               \
	{                                                                          \
	public:                                                                    \
		virtual void s0();                                                     \
		virtual void s4(void *p1, void *p2, void *p3, void *p4, void *p5,       \
			void *p6, void *p7, void *p8, void *p9);                           \
	};                                                                         \
	class OWNER                                                                \
	{                                                                          \
	public:                                                                    \
		void *forward(void *p1, void *p2, void *p3, void *p4, void *p5,         \
			void *p6, void *p7, void *p8, void *p9);                           \
		MEMBER m_member;                                                       \
	};                                                                         \
	void *OWNER::forward(void *p1, void *p2, void *p3, void *p4, void *p5,      \
		void *p6, void *p7, void *p8, void *p9)                                \
	{                                                                          \
		m_member.s4(p1, p2, p3, p4, p5, p6, p7, p8, p9);                        \
		return p1;                                                             \
	}

#define BFME_FWDD_08( OWNER, MEMBER )                                          \
	class MEMBER                                                               \
	{                                                                          \
	public:                                                                    \
		virtual void s0();                                                     \
		virtual void s4();                                                     \
		virtual void s8(void *p1, void *p2, void *p3, void *p4, void *p5,       \
			void *p6, double v);                                               \
	};                                                                         \
	class OWNER                                                                \
	{                                                                          \
	public:                                                                    \
		void *forward(void *p1, void *p2, void *p3, void *p4, void *p5,         \
			void *p6, double v);                                               \
		MEMBER m_member;                                                       \
	};                                                                         \
	void *OWNER::forward(void *p1, void *p2, void *p3, void *p4, void *p5,      \
		void *p6, double v)                                                    \
	{                                                                          \
		m_member.s8(p1, p2, p3, p4, p5, p6, v);                                \
		return p1;                                                             \
	}

// ?forward@Rva00848170Owner@@QAEPAXPAX00000000@Z
BFME_FWD9_08( Rva00848170Owner, Rva00848170Member )
// ?forward@Rva008481B0Owner@@QAEPAXPAX00000000@Z
BFME_FWD9_04( Rva008481B0Owner, Rva008481B0Member )
// ?forward@Rva008481F0Owner@@QAEPAXPAX00000N@Z
BFME_FWDD_08( Rva008481F0Owner, Rva008481F0Member )
// ?forward@Rva008482A0Owner@@QAEPAXPAX00000000@Z
BFME_FWD9_04( Rva008482A0Owner, Rva008482A0Member )
// ?forward@Rva008482E0Owner@@QAEPAXPAX00000N@Z
BFME_FWDD_08( Rva008482E0Owner, Rva008482E0Member )
