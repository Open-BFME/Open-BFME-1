// cl: /EHs-c-
//
// Seven small __thiscall members from the 0x005E97B0..0x0060D680 slice.  None
// calls anything, none has an unwind frame, and none touches a global, so each
// is decided by its own bytes and by the offsets it reads or writes.
//
// The class each one hangs off is invented as a carrier: nothing in a body like
// `mov [ecx+0x28C],eax` names its receiver, so the receiver is spelled as a
// padded block with the one field the body proves and a name derived from the
// member's own address.  What IS evidence is the offset, the width, and the
// direction of every access, and those are transcribed exactly.
//
// THE TWO PAIRS ARE THE SAME SHAPE AT DIFFERENT OFFSETS, which is what makes
// each shape a reading rather than a one-off fit:
//
//   0x006079B0 / 0x00607E20 -- load a dword from the receiver, store it through
//   the pointer argument, then load a byte from the receiver into al and
//   return.  Returning in al without zero-extension is a `bool`, and the dword
//   goes out through an out-parameter rather than being returned, so the
//   signature is `bool f(T *out) const`.  The two rows read (0x1CC, 0x1D0) and
//   (0x208, 0x20C): the same pair of adjacent fields in two different classes.
//
//   0x00607990 / 0x00607E00 -- index an array of pointers held in the receiver
//   with the int argument, then return that pointer adjusted by 4, or null if
//   it was null.  `test eax,eax / je / add eax,4` is MSVC's derived-to-base
//   POINTER conversion (WideSlotSetup.cpp measured the same shape); a plain
//   `p + 1` or a member read would not preserve null.  So the array holds
//   pointers to a class with a base at offset 4 and the member returns that
//   base.  The two rows index arrays at +0x08 and +0x48.
//
// THE OTHER THREE:
//
//   0x0060C180 stores the pointer argument into the receiver at +0x28C.
//
//   0x005FAFB0 copies three consecutive dwords out of the receiver at
//   +0x18C..+0x194 into the three dwords the pointer argument names.  The
//   compiler folds each source offset into its addressing mode, so the source
//   names three fields, not one struct: a struct copy through `this` would
//   materialise the address once, which is exactly what the next row does.
//
//   0x0060A680 does materialise it: `add ecx,0x94` and then three stores at
//   [ecx], [ecx+4], [ecx+8].  That is the receiver's own three-dword field at
//   +0x94 being assigned as a unit from the three dwords the argument names,
//   so it is spelled as a struct assignment while 0x005FAFB0 is spelled as
//   three field copies.  The contrast between the two bodies is the evidence
//   for both spellings.
//
// IDENTITY IS NOT RECOVERED.  Every name here is derived from an address.

typedef int Int;

// ---------------------------------------------------------------------------
// 0x0060C180 -- store the argument at +0x28C.
// ---------------------------------------------------------------------------
class T4Host0060C180
{
public:
	void set( void *value );
private:
	unsigned char m_pad[ 0x28c ];
	void *m_field28C;
};

void T4Host0060C180::set( void *value )
{
	m_field28C = value;
}

// ---------------------------------------------------------------------------
// 0x005FAFB0 -- copy three fields out to the caller.
// ---------------------------------------------------------------------------
struct T4Triple
{
	Int m_x;
	Int m_y;
	Int m_z;
};

class T4Host005FAFB0
{
public:
	void get( T4Triple *out ) const;
private:
	unsigned char m_pad[ 0x18c ];
	Int m_field18C;
	Int m_field190;
	Int m_field194;
};

void T4Host005FAFB0::get( T4Triple *out ) const
{
	out->m_x = m_field18C;
	out->m_y = m_field190;
	out->m_z = m_field194;
}

// ---------------------------------------------------------------------------
// 0x0060A680 -- assign the receiver's three-dword field at +0x94.
// ---------------------------------------------------------------------------
class T4Host0060A680
{
public:
	void set( const T4Triple *value );
private:
	unsigned char m_pad[ 0x94 ];
	T4Triple m_field94;
};

void T4Host0060A680::set( const T4Triple *value )
{
	m_field94 = *value;
}

// ---------------------------------------------------------------------------
// 0x006079B0 / 0x00607E20 -- out-parameter plus bool result.
// ---------------------------------------------------------------------------
#define T4_OUT_AND_FLAG( NAME, PAD )                                          \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		bool get( Int *out ) const;                                           \
	private:                                                                  \
		unsigned char m_pad[ PAD ];                                           \
		Int m_value;                                                          \
		bool m_flag;                                                          \
	};                                                                        \
	bool NAME::get( Int *out ) const                                          \
	{                                                                         \
		*out = m_value;                                                       \
		return m_flag;                                                        \
	}

T4_OUT_AND_FLAG( T4Host006079B0, 0x1cc )
T4_OUT_AND_FLAG( T4Host00607E20, 0x208 )

// ---------------------------------------------------------------------------
// 0x00607990 / 0x00607E00 -- indexed pointer array, returned as a base at +4.
// ---------------------------------------------------------------------------
class T4ItemLead
{
public:
	void *m_lead;
};

class T4ItemBase
{
public:
	void *m_field;
};

class T4Item : public T4ItemLead, public T4ItemBase
{
};

#define T4_INDEXED_BASE( NAME, PAD )                                          \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		T4ItemBase *get( Int index ) const;                                   \
	private:                                                                  \
		unsigned char m_pad[ PAD ];                                           \
		T4Item *m_items[ 1 ];                                                 \
	};                                                                        \
	T4ItemBase *NAME::get( Int index ) const                                  \
	{                                                                         \
		return m_items[ index ];                                              \
	}

T4_INDEXED_BASE( T4Host00607990, 0x08 )
T4_INDEXED_BASE( T4Host00607E00, 0x48 )
