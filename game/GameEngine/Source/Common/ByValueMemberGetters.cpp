// Fifteen 12-byte accessors that return a one-word member BY VALUE, in three
// families that differ in nothing but the member's offset.
//
//     mov ecx,[ecx+DISP] / mov eax,[esp+4] / mov [eax],ecx / ret 4
//
// WHAT THE BYTES SHOW.  `this` arrives in ecx and the function takes one stack
// dword which it never reads as a value -- it writes THROUGH it and then returns
// it in eax.  That is the MSVC 7.1 hidden return-value pointer: a __thiscall
// member whose return type is a class small enough to hold one dword but still a
// class, so it is returned in memory rather than in eax.  A member returning
// `int` or a raw pointer would simply leave the value in eax and `ret 0`; the
// four bytes of stack argument and the copy through them exist only because the
// return type is a UDT.
//
// The body reads exactly one dword of `this` and copies it, so the returned
// class holds exactly one word and the getter is a plain `return m_x;`.  No
// null check, no reference count, no virtual call: whatever the wrapper is, its
// copy constructor is trivial enough that /O2 reduced it to this single store.
//
// THE ONE VARYING AXIS is the displacement, and it partitions the fifteen into
// three families -- six at +8, five at +0xC, four at +0x10:
//
//     +0x08  0x00801230 0x008014D0 0x00802220 0x008022E0 0x008028B0 0x00802E60
//     +0x0C  0x008014E0 0x00847F60 0x00848000 0x008480B0 0x00848150
//     +0x10  0x00847F70 0x00848010 0x008480C0 0x00848160
//
// and the interleaving is what identifies them as members of the same classes
// rather than fifteen unrelated getters: 0x008014D0/0x008014E0 are adjacent, as
// are 0x00847F60/0x00847F70, 0x00848000/0x00848010, 0x008480B0/0x008480C0 and
// 0x00848150/0x00848160.  Four classes each publish their +0xC and +0x10 words
// through adjacent accessors emitted in declaration order.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Fifteen distinct addresses, and members of
// at least four different classes by the adjacency above; they coincide in bytes
// only because a one-word by-value getter has nothing else to say.  Aliasing
// them would assert that fifteen functions are one.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image witnesses a name for the
// holders or for the returned wrapper, so every name is derived from its own
// address.

class GetterWord
{
public:
	void *m_value;
};

#define BFME_BY_VALUE_GETTER_08( NAME )                                       \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		GetterWord get() const;                                               \
                                                                              \
		int m_pad0;                                                           \
		int m_pad1;                                                           \
		GetterWord m_value;                                                   \
	};                                                                        \
	GetterWord NAME::get() const                                              \
	{                                                                         \
		return m_value;                                                       \
	}

#define BFME_BY_VALUE_GETTER_0C( NAME )                                       \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		GetterWord get() const;                                               \
                                                                              \
		int m_pad0;                                                           \
		int m_pad1;                                                           \
		int m_pad2;                                                           \
		GetterWord m_value;                                                   \
	};                                                                        \
	GetterWord NAME::get() const                                              \
	{                                                                         \
		return m_value;                                                       \
	}

#define BFME_BY_VALUE_GETTER_10( NAME )                                       \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		GetterWord get() const;                                               \
                                                                              \
		int m_pad0;                                                           \
		int m_pad1;                                                           \
		int m_pad2;                                                           \
		int m_pad3;                                                           \
		GetterWord m_value;                                                   \
	};                                                                        \
	GetterWord NAME::get() const                                              \
	{                                                                         \
		return m_value;                                                       \
	}

BFME_BY_VALUE_GETTER_08( Rva00801230Owner )
BFME_BY_VALUE_GETTER_08( Rva008014D0Owner )
BFME_BY_VALUE_GETTER_08( Rva00802220Owner )
BFME_BY_VALUE_GETTER_08( Rva008022E0Owner )
BFME_BY_VALUE_GETTER_08( Rva008028B0Owner )
BFME_BY_VALUE_GETTER_08( Rva00802E60Owner )

BFME_BY_VALUE_GETTER_0C( Rva008014E0Owner )
BFME_BY_VALUE_GETTER_0C( Rva00847F60Owner )
BFME_BY_VALUE_GETTER_0C( Rva00848000Owner )
BFME_BY_VALUE_GETTER_0C( Rva008480B0Owner )
BFME_BY_VALUE_GETTER_0C( Rva00848150Owner )

BFME_BY_VALUE_GETTER_10( Rva00847F70Owner )
BFME_BY_VALUE_GETTER_10( Rva00848010Owner )
BFME_BY_VALUE_GETTER_10( Rva008480C0Owner )
BFME_BY_VALUE_GETTER_10( Rva00848160Owner )
