// 118 seven-byte __thiscall members with one shape:
//
//     mov al,[ecx+<DISP>] / ret
//
// One BYTE is read at a fixed displacement from `this` and left in al.  The
// return type is spelled `unsigned char` because only al is written and the
// upper bytes of eax are left holding whatever the caller had; the bytes cannot
// distinguish it from `signed char`, `bool` or a one-byte enum.
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

#define BFME_DISP_BYTE_GETTER( NAME, DISP )                                        \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		unsigned char get() const;                                            \
                                                                              \
		char          m_lead[ DISP ];                                         \
		unsigned char m_value;                                                \
	};                                                                        \
	unsigned char NAME::get() const                                           \
	{                                                                         \
		return m_value;                                                       \
	}

BFME_DISP_BYTE_GETTER( Rva0016A790ByteField, 0x32E )
BFME_DISP_BYTE_GETTER( Rva0016A8E0ByteField, 0x533 )
BFME_DISP_BYTE_GETTER( Rva001B3F40ByteField, 0xFC )
BFME_DISP_BYTE_GETTER( Rva001BD340ByteField, 0x92 )
BFME_DISP_BYTE_GETTER( Rva001BD3F0ByteField, 0x1F4 )
BFME_DISP_BYTE_GETTER( Rva001BD420ByteField, 0x348 )
BFME_DISP_BYTE_GETTER( Rva001BDB40ByteField, 0x49A )
BFME_DISP_BYTE_GETTER( Rva001BDB50ByteField, 0x499 )
BFME_DISP_BYTE_GETTER( Rva001BDB60ByteField, 0x49B )
BFME_DISP_BYTE_GETTER( Rva001BDB70ByteField, 0x49C )
BFME_DISP_BYTE_GETTER( Rva001BDBA0ByteField, 0x4CC )
BFME_DISP_BYTE_GETTER( Rva001BDD40ByteField, 0x531 )
BFME_DISP_BYTE_GETTER( Rva001BF140ByteField, 0x3A8 )
BFME_DISP_BYTE_GETTER( Rva001E0C20ByteField, 0x4E4 )
BFME_DISP_BYTE_GETTER( Rva001E0C90ByteField, 0x51C )
BFME_DISP_BYTE_GETTER( Rva001E0CA0ByteField, 0x51F )
BFME_DISP_BYTE_GETTER( Rva001E0CB0ByteField, 0x51D )
BFME_DISP_BYTE_GETTER( Rva001E0D40ByteField, 0x4F8 )
BFME_DISP_BYTE_GETTER( Rva001E0D50ByteField, 0x4FD )
BFME_DISP_BYTE_GETTER( Rva001E0D80ByteField, 0x534 )
BFME_DISP_BYTE_GETTER( Rva001E1770ByteField, 0x4ED )
BFME_DISP_BYTE_GETTER( Rva001E1780ByteField, 0x4EE )
BFME_DISP_BYTE_GETTER( Rva001E17A0ByteField, 0x72 )
BFME_DISP_BYTE_GETTER( Rva001EAB90ByteField, 0x4DC )
BFME_DISP_BYTE_GETTER( Rva001EABB0ByteField, 0x4FA )
BFME_DISP_BYTE_GETTER( Rva001EABC0ByteField, 0x4FB )
BFME_DISP_BYTE_GETTER( Rva001EB040ByteField, 0xE8 )
BFME_DISP_BYTE_GETTER( Rva001EB050ByteField, 0xE9 )
BFME_DISP_BYTE_GETTER( Rva001ECE90ByteField, 0x51E )
BFME_DISP_BYTE_GETTER( Rva001ED580ByteField, 0x158 )
BFME_DISP_BYTE_GETTER( Rva001ED590ByteField, 0x174 )
BFME_DISP_BYTE_GETTER( Rva001ED5A0ByteField, 0x175 )
BFME_DISP_BYTE_GETTER( Rva001ED5D0ByteField, 0x180 )
BFME_DISP_BYTE_GETTER( Rva001EF490ByteField, 0x4F9 )
BFME_DISP_BYTE_GETTER( Rva001F3600ByteField, 0x45D )
BFME_DISP_BYTE_GETTER( Rva00200860ByteField, 0x32B )
BFME_DISP_BYTE_GETTER( Rva00205600ByteField, 0x96 )
BFME_DISP_BYTE_GETTER( Rva0020FAF0ByteField, 0x95 )
BFME_DISP_BYTE_GETTER( Rva0021A240ByteField, 0x1A8 )
BFME_DISP_BYTE_GETTER( Rva002205D0ByteField, 0xB6 )
BFME_DISP_BYTE_GETTER( Rva0022A080ByteField, 0xCC )
BFME_DISP_BYTE_GETTER( Rva0022EF80ByteField, 0xA0 )
BFME_DISP_BYTE_GETTER( Rva002307D0ByteField, 0x11A )
BFME_DISP_BYTE_GETTER( Rva002489D0ByteField, 0x368 )
BFME_DISP_BYTE_GETTER( Rva0024A2B0ByteField, 0xD4 )
BFME_DISP_BYTE_GETTER( Rva0024FE60ByteField, 0x297 )
BFME_DISP_BYTE_GETTER( Rva00257800ByteField, 0xBC )
BFME_DISP_BYTE_GETTER( Rva0026E780ByteField, 0x328 )
BFME_DISP_BYTE_GETTER( Rva0026E790ByteField, 0xA8 )
BFME_DISP_BYTE_GETTER( Rva002897D0ByteField, 0x190 )
BFME_DISP_BYTE_GETTER( Rva002BB8B0ByteField, 0x424 )
BFME_DISP_BYTE_GETTER( Rva002BBA40ByteField, 0x490 )
BFME_DISP_BYTE_GETTER( Rva002C7D50ByteField, 0xD9 )
BFME_DISP_BYTE_GETTER( Rva002DB180ByteField, 0x508 )
BFME_DISP_BYTE_GETTER( Rva002DB1B0ByteField, 0x535 )
BFME_DISP_BYTE_GETTER( Rva002DE1B0ByteField, 0x4EC )
BFME_DISP_BYTE_GETTER( Rva002E2C20ByteField, 0x4C8 )
BFME_DISP_BYTE_GETTER( Rva00321F10ByteField, 0xFC )
BFME_DISP_BYTE_GETTER( Rva003829F0ByteField, 0x485 )
BFME_DISP_BYTE_GETTER( Rva00382A00ByteField, 0x668 )
BFME_DISP_BYTE_GETTER( Rva003A5D20ByteField, 0xD8 )
BFME_DISP_BYTE_GETTER( Rva003BC650ByteField, 0xD1 )
BFME_DISP_BYTE_GETTER( Rva003BC870ByteField, 0x288 )
BFME_DISP_BYTE_GETTER( Rva003BC880ByteField, 0x1C )
BFME_DISP_BYTE_GETTER( Rva003C5EB0ByteField, 0x8C )
BFME_DISP_BYTE_GETTER( Rva003C5EC0ByteField, 0xE9 )
BFME_DISP_BYTE_GETTER( Rva003C5ED0ByteField, 0xA8 )
BFME_DISP_BYTE_GETTER( Rva0040F610ByteField, 0xD4 )
// ?get@Rva00410420ByteField@@QBEEXZ
BFME_DISP_BYTE_GETTER( Rva00410420ByteField, 0x10 )
// ?get@Rva00410480ByteField@@QBEEXZ
BFME_DISP_BYTE_GETTER( Rva00410480ByteField, 0x54 )
// ?get@Rva004104D0ByteField@@QBEEXZ
BFME_DISP_BYTE_GETTER( Rva004104D0ByteField, 0x39 )
BFME_DISP_BYTE_GETTER( Rva00410450ByteField, 0x180 )
BFME_DISP_BYTE_GETTER( Rva004105A0ByteField, 0x3B0 )
BFME_DISP_BYTE_GETTER( Rva004105B0ByteField, 0x3AF )
BFME_DISP_BYTE_GETTER( Rva004105E0ByteField, 0x3B1 )
BFME_DISP_BYTE_GETTER( Rva00410840ByteField, 0x7CC )
BFME_DISP_BYTE_GETTER( Rva0042E300ByteField, 0x11D )
BFME_DISP_BYTE_GETTER( Rva0043A600ByteField, 0x259 )
BFME_DISP_BYTE_GETTER( Rva0043A6B0ByteField, 0x12B1 )
BFME_DISP_BYTE_GETTER( Rva0043AD60ByteField, 0x820 )
BFME_DISP_BYTE_GETTER( Rva0043AD90ByteField, 0x821 )
BFME_DISP_BYTE_GETTER( Rva0043B1D0ByteField, 0x540 )
BFME_DISP_BYTE_GETTER( Rva0044B330ByteField, 0x839 )
BFME_DISP_BYTE_GETTER( Rva0044B380ByteField, 0x838 )
BFME_DISP_BYTE_GETTER( Rva00458F40ByteField, 0x12B2 )
BFME_DISP_BYTE_GETTER( Rva00458F50ByteField, 0x12B3 )
BFME_DISP_BYTE_GETTER( Rva0049AB40ByteField, 0x14D )
BFME_DISP_BYTE_GETTER( Rva0049AB50ByteField, 0x14E )
BFME_DISP_BYTE_GETTER( Rva0049CA10ByteField, 0x150 )
BFME_DISP_BYTE_GETTER( Rva004A3A40ByteField, 0x347 )
BFME_DISP_BYTE_GETTER( Rva004A3A50ByteField, 0x151 )
BFME_DISP_BYTE_GETTER( Rva004A3A80ByteField, 0x152 )
BFME_DISP_BYTE_GETTER( Rva004A3A90ByteField, 0x153 )
BFME_DISP_BYTE_GETTER( Rva004C1120ByteField, 0x27C )
BFME_DISP_BYTE_GETTER( Rva004F0740ByteField, 0x429 )
BFME_DISP_BYTE_GETTER( Rva005052E0ByteField, 0x220 )
BFME_DISP_BYTE_GETTER( Rva005052F0ByteField, 0x218 )
BFME_DISP_BYTE_GETTER( Rva0051D020ByteField, 0xC6 )
BFME_DISP_BYTE_GETTER( Rva00521C40ByteField, 0x1AE )
BFME_DISP_BYTE_GETTER( Rva0052ADC0ByteField, 0x254 )
BFME_DISP_BYTE_GETTER( Rva005A6CA0ByteField, 0x91 )
BFME_DISP_BYTE_GETTER( Rva005A6CD0ByteField, 0x12B0 )
BFME_DISP_BYTE_GETTER( Rva005B4200ByteField, 0x12BD )
BFME_DISP_BYTE_GETTER( Rva005B51C0ByteField, 0xBC )
BFME_DISP_BYTE_GETTER( Rva005B7350ByteField, 0x1318 )
BFME_DISP_BYTE_GETTER( Rva005FAEF0ByteField, 0x198 )
BFME_DISP_BYTE_GETTER( Rva00607960ByteField, 0x1D1 )
BFME_DISP_BYTE_GETTER( Rva00637210ByteField, 0x6FC )
BFME_DISP_BYTE_GETTER( Rva0063A7D0ByteField, 0x52 )
BFME_DISP_BYTE_GETTER( Rva006429F0ByteField, 0xAD )
BFME_DISP_BYTE_GETTER( Rva00642A00ByteField, 0x13C )
BFME_DISP_BYTE_GETTER( Rva00642BD0ByteField, 0x3D8 )
BFME_DISP_BYTE_GETTER( Rva00695ED0ByteField, 0x632 )
BFME_DISP_BYTE_GETTER( Rva00696320ByteField, 0x62F )
BFME_DISP_BYTE_GETTER( Rva006D7590ByteField, 0x110 )
BFME_DISP_BYTE_GETTER( Rva006D7580ByteField, 0x104 )
BFME_DISP_BYTE_GETTER( Rva006E17E0ByteField, 0x81 )
BFME_DISP_BYTE_GETTER( Rva006E6E70ByteField, 0x93 )
BFME_DISP_BYTE_GETTER( Rva0006B4F0ByteField, 0xC4 )
BFME_DISP_BYTE_GETTER( Rva0073A740ByteField, 0x3009 )
BFME_DISP_BYTE_GETTER( Rva00745FF0ByteField, 0x23C0 )
BFME_DISP_BYTE_GETTER( Rva00746080ByteField, 0x2439 )
BFME_DISP_BYTE_GETTER( Rva007460E0ByteField, 0x248E )
BFME_DISP_BYTE_GETTER( Rva00746110ByteField, 0x2438 )
BFME_DISP_BYTE_GETTER( Rva007D0A90ByteField, 0x272 )
BFME_DISP_BYTE_GETTER( Rva007DCBC0ByteField, 0x306C )
class Rva00642C30ByteField
{
public:
	unsigned int get() const;

	char m_lead[0x3E4];
	unsigned char m_value;
};

unsigned int Rva00642C30ByteField::get() const
{
	return m_value;
}
BFME_DISP_BYTE_GETTER( Rva00910F30ByteField, 0x271 )

// Four further members whose displacement is outside the 0x80..0x8000 window
// the block above covers, and one whose displacement is NEGATIVE.  A negative
// displacement cannot be a member offset, so those are spelled as an explicit
// backward cast -- the bytes cannot say whether it is a sub-object `this`
// pointing into the middle of a larger object, a container-of computation in
// the source, or something else, and no inheritance relationship is claimed.

#define BFME_DISP_BYTE_GETTER_BEFORE( NAME, BACK )                            \
	class Sub##NAME                                                           \
	{                                                                         \
	public:                                                                   \
		unsigned char m_value;                                                \
	};                                                                        \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		unsigned char get() const;                                            \
	};                                                                        \
	unsigned char NAME::get() const                                           \
	{                                                                         \
		return ( (const Sub##NAME *)( (const char *)this - ( BACK ) ) )->m_value; \
	}

BFME_DISP_BYTE_GETTER( Rva00336EF0ByteField, 0x17624 )
BFME_DISP_BYTE_GETTER( Rva00337180ByteField, 0x17636 )
BFME_DISP_BYTE_GETTER( Rva006C5670ByteField, 0x2A98FC )
BFME_DISP_BYTE_GETTER( Rva00889BE0ByteField, 0x9F58 )
BFME_DISP_BYTE_GETTER( Rva005638C0ByteField, 0x48 )
