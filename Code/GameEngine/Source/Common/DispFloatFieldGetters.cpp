// 53 seven-byte __thiscall members with one shape:
//
//     fld dword ptr [ecx+<DISP>] / ret
//
// One dword is loaded onto the x87 stack and left there, which is the return
// convention for `float` -- a `double` member would be `fld qword ptr`, and an
// integer return would not touch x87 at all.  So this family is separated from
// the plain dword getters by the opcode alone.
//
// WHAT THE BYTES SHOW AND WHAT THEY DO NOT.  The displacement is a disp32 in
// every member -- MSVC 7.1 uses disp8 whenever the offset fits in a signed
// byte, so every offset here is at least 0x80, and the encoding itself is why
// this family is separable from the far larger disp8 one.  The operand size and
// the displacement are read straight off the instruction stream; nothing else
// about these functions is asserted.  Members before the accessed one are
// spelled as a lead array because their types are not witnessed here, only
// their total size.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define BFME_DISP_FLOAT_GETTER( NAME, DISP )                                       \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		float get() const;                                                    \
                                                                              \
		char  m_lead[ DISP ];                                                 \
		float m_value;                                                        \
	};                                                                        \
	float NAME::get() const                                                   \
	{                                                                         \
		return m_value;                                                       \
	}

#define BFME_DISP8_FLOAT_GETTER( NAME, DISP )                                      \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		float get() const;                                                    \
                                                                              \
		char  m_lead[ DISP ];                                                 \
		float m_value;                                                        \
	};                                                                        \
	float NAME::get() const                                                   \
	{                                                                         \
		return m_value;                                                       \
	}

BFME_DISP_FLOAT_GETTER( Rva000C9C20FloatField, 0x644 )
BFME_DISP_FLOAT_GETTER( Rva000FB8B0FloatField, 0x258 )
BFME_DISP_FLOAT_GETTER( Rva000FBFD0FloatField, 0x3B4 )
BFME_DISP_FLOAT_GETTER( Rva000FBFE0FloatField, 0x3B8 )
BFME_DISP_FLOAT_GETTER( Rva0016A640FloatField, 0x1A0 )
BFME_DISP_FLOAT_GETTER( Rva0016A6B0FloatField, 0x168 )
BFME_DISP_FLOAT_GETTER( Rva0016A880FloatField, 0x510 )
BFME_DISP_FLOAT_GETTER( Rva001B4080FloatField, 0x474 )
BFME_DISP_FLOAT_GETTER( Rva001BDA00FloatField, 0x3A8 )
BFME_DISP_FLOAT_GETTER( Rva001BDA10FloatField, 0x3AC )
BFME_DISP_FLOAT_GETTER( Rva001BDA60FloatField, 0x3EC )
BFME_DISP_FLOAT_GETTER( Rva001BDA70FloatField, 0x3F0 )
BFME_DISP_FLOAT_GETTER( Rva001BDA80FloatField, 0x3F4 )
BFME_DISP_FLOAT_GETTER( Rva001BDA90FloatField, 0x3F8 )
BFME_DISP_FLOAT_GETTER( Rva001BDB30FloatField, 0x40C )
BFME_DISP_FLOAT_GETTER( Rva001BF3F0FloatField, 0x19C )
BFME_DISP_FLOAT_GETTER( Rva001E0B80FloatField, 0x520 )
BFME_DISP_FLOAT_GETTER( Rva001E0B90FloatField, 0x524 )
BFME_DISP8_FLOAT_GETTER( Rva001E0BA0FloatField, 0x1C )
BFME_DISP_FLOAT_GETTER( Rva001E1080FloatField, 0x398 )
BFME_DISP_FLOAT_GETTER( Rva001ED5B0FloatField, 0x178 )
BFME_DISP_FLOAT_GETTER( Rva001ED5C0FloatField, 0x17C )
BFME_DISP_FLOAT_GETTER( Rva001FE010FloatField, 0x220 )
BFME_DISP_FLOAT_GETTER( Rva00207710FloatField, 0x16E0 )
BFME_DISP_FLOAT_GETTER( Rva00216B60FloatField, 0x4A8 )
BFME_DISP_FLOAT_GETTER( Rva00216B70FloatField, 0x4AC )
BFME_DISP_FLOAT_GETTER( Rva0022B300FloatField, 0x2F4 )
BFME_DISP_FLOAT_GETTER( Rva002321D0FloatField, 0x404 )
BFME_DISP_FLOAT_GETTER( Rva0025B500FloatField, 0x3C0 )
BFME_DISP_FLOAT_GETTER( Rva0026E7B0FloatField, 0x3E8 )
BFME_DISP_FLOAT_GETTER( Rva002B9F60FloatField, 0x3B0 )
BFME_DISP_FLOAT_GETTER( Rva002BB8F0FloatField, 0x478 )
BFME_DISP_FLOAT_GETTER( Rva00360720FloatField, 0x260 )
BFME_DISP_FLOAT_GETTER( Rva00360730FloatField, 0x25C )
BFME_DISP_FLOAT_GETTER( Rva003A3D70FloatField, 0xA8 )
BFME_DISP_FLOAT_GETTER( Rva003D5A70FloatField, 0x408 )
BFME_DISP_FLOAT_GETTER( Rva003F7AA0FloatField, 0x39C )
BFME_DISP_FLOAT_GETTER( Rva004107C0FloatField, 0x400 )
BFME_DISP_FLOAT_GETTER( Rva004107F0FloatField, 0x414 )
BFME_DISP_FLOAT_GETTER( Rva005BD560FloatField, 0xB0 )
BFME_DISP_FLOAT_GETTER( Rva005BD5C0FloatField, 0x94 )
BFME_DISP_FLOAT_GETTER( Rva005FF6D0FloatField, 0x180 )
BFME_DISP_FLOAT_GETTER( Rva005FF6E0FloatField, 0x184 )
BFME_DISP_FLOAT_GETTER( Rva00607950FloatField, 0x1C8 )
BFME_DISP8_FLOAT_GETTER( Rva00694880FloatField, 0x7C )
BFME_DISP_FLOAT_GETTER( Rva00694890FloatField, 0x80 )
BFME_DISP_FLOAT_GETTER( Rva006E7AE0FloatField, 0x301C )
BFME_DISP_FLOAT_GETTER( Rva006FCF40FloatField, 0xCC )
BFME_DISP_FLOAT_GETTER( Rva00746E80FloatField, 0x3018 )
BFME_DISP_FLOAT_GETTER( Rva00751AE0FloatField, 0x3C8 )
BFME_DISP_FLOAT_GETTER( Rva00751AF0FloatField, 0x3CC )
BFME_DISP_FLOAT_GETTER( Rva00751B00FloatField, 0x3D0 )
BFME_DISP_FLOAT_GETTER( Rva00751B10FloatField, 0x3D4 )
BFME_DISP_FLOAT_GETTER( Rva00751B20FloatField, 0x3E0 )
BFME_DISP_FLOAT_GETTER( Rva00751B30FloatField, 0x3E4 )
BFME_DISP_FLOAT_GETTER( Rva007B7CE0FloatField, 0x300C )

// One further member whose displacement is NEGATIVE.  That cannot be a member
// offset, so it is spelled as an explicit backward cast; the bytes cannot say
// whether it is a sub-object `this` pointing into the middle of a larger
// object, a container-of computation in the source, or something else, and no
// inheritance relationship is claimed.

#define BFME_DISP_FLOAT_GETTER_BEFORE( NAME, BACK )                           \
	class Sub##NAME                                                           \
	{                                                                         \
	public:                                                                   \
		float m_value;                                                        \
	};                                                                        \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		float get() const;                                                     \
	};                                                                        \
	float NAME::get() const                                                   \
	{                                                                         \
		return ( (const Sub##NAME *)( (const char *)this - ( BACK ) ) )->m_value; \
	}

BFME_DISP_FLOAT_GETTER_BEFORE( Rva001D4000FloatField, 0x37C )
