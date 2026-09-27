// cl: /DNDEBUG /MD /EHsc
// Eight identical 17-byte virtual forwarders at 0x00847D30..0x00847EA0.
// IDENTITY IS NOT RECOVERED: no caller, string or vtable names the holder or
// the member, so every name is derived from its own address.
//
// WHAT THE BYTES SHOW. Each body reads the dword at [this+0] as a vtable
// pointer, pushes its one incoming argument twice (once to save it in esi,
// once as the callee's argument), calls the slot at +0x20 or +0x24 through
// that vtable with ecx still holding `this`, then returns the saved argument
// in eax:
//
//     mov eax,[ecx] / push esi / mov esi,[esp+8] / push esi /
//     call [eax+SLOT] / mov eax,esi / pop esi / ret 4
//
// ecx is never reloaded, so the callee's receiver is `this` itself: the
// polymorphic member sits at offset +0, where its address equals `this` and
// no lea is needed. The callee's return value is discarded (`mov eax,esi`
// overwrites it), so the source calls the slot and then returns the argument:
//
//     void *Owner::forward(void *p) { m_member.slot(p); return p; }
//
// The eight bodies alternate slot +0x20 / +0x24 in four adjacent pairs, so
// each pair's member exposes both slots and each body keeps its own owner.
//
// SEPARATE FUNCTIONS, NOT ALIASES. Eight distinct addresses that coincide in
// bytes only because a one-argument virtual forward has nothing else to say.

#define BFME_SLOT_FORWARDER_20( OWNER, MEMBER )                               \
	class MEMBER                                                               \
	{                                                                          \
	public:                                                                    \
		virtual void bfmeSlot_00(void);                                        \
		virtual void bfmeSlot_04(void);                                        \
		virtual void bfmeSlot_08(void);                                        \
		virtual void bfmeSlot_0C(void);                                        \
		virtual void bfmeSlot_10(void);                                        \
		virtual void bfmeSlot_14(void);                                        \
		virtual void bfmeSlot_18(void);                                        \
		virtual void bfmeSlot_1C(void);                                        \
		virtual void bfmeSlot_20(void *p);                                     \
	};                                                                         \
	class OWNER                                                                \
	{                                                                          \
	public:                                                                    \
		void *forward(void *p);                                                \
                                                                               \
		MEMBER m_member;                                                       \
	};                                                                         \
	void *OWNER::forward(void *p)                                              \
	{                                                                          \
		m_member.bfmeSlot_20(p);                                               \
		return p;                                                              \
	}

#define BFME_SLOT_FORWARDER_24( OWNER, MEMBER )                               \
	class MEMBER                                                               \
	{                                                                          \
	public:                                                                    \
		virtual void bfmeSlot_00(void);                                        \
		virtual void bfmeSlot_04(void);                                        \
		virtual void bfmeSlot_08(void);                                        \
		virtual void bfmeSlot_0C(void);                                        \
		virtual void bfmeSlot_10(void);                                        \
		virtual void bfmeSlot_14(void);                                        \
		virtual void bfmeSlot_18(void);                                        \
		virtual void bfmeSlot_1C(void);                                        \
		virtual void bfmeSlot_20(void);                                        \
		virtual void bfmeSlot_24(void *p);                                     \
	};                                                                         \
	class OWNER                                                                \
	{                                                                          \
	public:                                                                    \
		void *forward(void *p);                                                \
                                                                               \
		MEMBER m_member;                                                       \
	};                                                                         \
	void *OWNER::forward(void *p)                                              \
	{                                                                          \
		m_member.bfmeSlot_24(p);                                               \
		return p;                                                              \
	}

BFME_SLOT_FORWARDER_20( Rva00847D30Owner, Rva00847D30Member )
BFME_SLOT_FORWARDER_24( Rva00847D50Owner, Rva00847D50Member )
BFME_SLOT_FORWARDER_20( Rva00847DA0Owner, Rva00847DA0Member )
BFME_SLOT_FORWARDER_24( Rva00847DC0Owner, Rva00847DC0Member )
BFME_SLOT_FORWARDER_20( Rva00847E10Owner, Rva00847E10Member )
BFME_SLOT_FORWARDER_24( Rva00847E30Owner, Rva00847E30Member )
BFME_SLOT_FORWARDER_20( Rva00847E80Owner, Rva00847E80Member )
BFME_SLOT_FORWARDER_24( Rva00847EA0Owner, Rva00847EA0Member )
