// cl: /EHs-c-
// Open-BFME5: one 375-byte __thiscall copy constructor, 0x003A1120.  Retail is
// a member-for-member copy of a 0xB8-byte object and nothing else:
//
//     eleven dwords at 0x00..0x28, each `mov reg,[edi+N] / mov [esi+N],reg`
//     eleven twelve-byte members at 0x2C, 0x38, 0x44, 0x50, 0x5C, 0x68, 0x74,
//         0x80, 0x8C, 0x98 and 0xA4, each copied through a POINTER pair
//         (`lea edx,[edi+N] / lea eax,[esi+N]` then three moves)
//     one member at 0xB0 copied by an out-of-line call to 0x00887C90
//     one dword at 0xB4
//     mov eax,esi ; pop esi ; ret 4
//
// THE TWO COPY FORMS SEPARATE SCALARS FROM CLASS MEMBERS.  A dword member is
// copied with a bare displacement on both sides; a twelve-byte member is copied
// through a pointer held in a register, which is what an inlined implicit copy
// constructor looks like.  So the first eleven fields are scalars and the next
// eleven are one three-dword CLASS repeated -- the same distinction
// V3ThirdBaseInlineCopyCtors.cpp needed, and spelling the twelve-byte members
// as three ints apiece puts the bare-displacement form on all of them.
//
// THE MEMBER AT 0xB0 IS FOUR BYTES WIDE because the next field starts at 0xB4,
// and its copy constructor is out of line.  0x00887C90 carries two ledger names
// -- ??0ModelConditionInfo@@QAE@ABU0@@Z and ??4AudioEventRTS@@QAEAAV0@ABV0@@Z,
// both 135 bytes in string_base.cpp -- so it is one identical-code-folded
// StringBase member and which of the two aliases names the TYPE here is not
// decided by these bytes.  The first is spelled because a member being COPY
// CONSTRUCTED needs a constructor, not an assignment operator.
//
// IDENTITY IS NOT RECOVERED: the class and its fields are address-derived, and
// the field names carry their offsets.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
struct ModelConditionInfo
{
	ModelConditionInfo( const ModelConditionInfo & );

	char m_unreconstructed_00[ 4 ];
};

class Rva003A1120Triple
{
public:
	Int m_a, m_b, m_c;
};

class Rva003A1120
{
public:
	Rva003A1120( const Rva003A1120 & );

	Int m_field00;
	Int m_field04;
	Int m_field08;
	Int m_field0C;
	Int m_field10;
	Int m_field14;
	Int m_field18;
	Int m_field1C;
	Int m_field20;
	Int m_field24;
	Int m_field28;
	Rva003A1120Triple m_field2C;
	Rva003A1120Triple m_field38;
	Rva003A1120Triple m_field44;
	Rva003A1120Triple m_field50;
	Rva003A1120Triple m_field5C;
	Rva003A1120Triple m_field68;
	Rva003A1120Triple m_field74;
	Rva003A1120Triple m_field80;
	Rva003A1120Triple m_field8C;
	Rva003A1120Triple m_field98;
	Rva003A1120Triple m_fieldA4;
	ModelConditionInfo m_fieldB0;
	Int m_fieldB4;
};

Rva003A1120::Rva003A1120( const Rva003A1120 &o )
	: m_field00( o.m_field00 ), m_field04( o.m_field04 ),
		  m_field08( o.m_field08 ), m_field0C( o.m_field0C ),
		  m_field10( o.m_field10 ), m_field14( o.m_field14 ),
		  m_field18( o.m_field18 ), m_field1C( o.m_field1C ),
		  m_field20( o.m_field20 ), m_field24( o.m_field24 ),
		  m_field28( o.m_field28 ), m_field2C( o.m_field2C ),
		  m_field38( o.m_field38 ), m_field44( o.m_field44 ),
		  m_field50( o.m_field50 ), m_field5C( o.m_field5C ),
		  m_field68( o.m_field68 ), m_field74( o.m_field74 ),
		  m_field80( o.m_field80 ), m_field8C( o.m_field8C ),
		  m_field98( o.m_field98 ), m_fieldA4( o.m_fieldA4 ),
		  m_fieldB0( o.m_fieldB0 ), m_fieldB4( o.m_fieldB4 )
{
}
