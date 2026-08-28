// cl: /EHs-c-
// Open-BFME5: one 159-byte __thiscall copy constructor, 0x004F07F0.  Retail is
// a member-for-member copy of a 0x58-byte object with ONE gap:
//
//     nothing is written to [esi] at all -- no vftable store, no copy
//     dwords at 4 and 8, bytes at 0xC, 0xD and 0xE, dwords from 0x10 to 0x38
//     the member at 0x3C copied by an out-of-line call to 0x00887C90
//     dwords from 0x40 to 0x54
//     mov eax,esi ; pop esi ; ret 4
//
// WHAT THE BYTES SHOW.  `ret 4` and `mov eax,esi` make it a one-argument
// constructor returning this, and every load is from the argument at the same
// displacement its store uses on this, so it is a copy constructor.  The
// FIRST FOUR BYTES ARE NEITHER STAMPED NOR COPIED: a polymorphic class would
// stamp a vftable there and the implicit copy constructor would copy a member,
// so this constructor is hand written and simply leaves the field at 0 alone.
//
// THE MEMBER AT 0x3C IS FOUR BYTES WIDE because the next field starts at 0x40,
// and it is the same identical-code-folded StringBase copy constructor at
// 0x00887C90 that 0x003A1120 reaches; the same caveat applies to which of that
// address's two ledger aliases names the type.
//
// The 0x34 and 0x38 copies are interleaved with the call's argument setup.
// That is scheduling: writing the members in declaration order reproduces it.
//
// IDENTITY IS NOT RECOVERED: the class and its fields are address-derived.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
struct ModelConditionInfo
{
	ModelConditionInfo( const ModelConditionInfo & );

	char m_unreconstructed_00[ 4 ];
};

class Rva004F07F0
{
public:
	Rva004F07F0( const Rva004F07F0 & );

	Int m_field00;
	Int m_field04;
	Int m_field08;
	char m_field0C;
	char m_field0D;
	char m_field0E;
	char m_pad0F;
	Int m_field10;
	Int m_field14;
	Int m_field18;
	Int m_field1C;
	Int m_field20;
	Int m_field24;
	Int m_field28;
	Int m_field2C;
	Int m_field30;
	Int m_field34;
	Int m_field38;
	ModelConditionInfo m_field3C;
	Int m_field40;
	Int m_field44;
	Int m_field48;
	Int m_field4C;
	Int m_field50;
	Int m_field54;
};

Rva004F07F0::Rva004F07F0( const Rva004F07F0 &o )
	: m_field04( o.m_field04 ), m_field08( o.m_field08 ),
		  m_field0C( o.m_field0C ), m_field0D( o.m_field0D ),
		  m_field0E( o.m_field0E ), m_field10( o.m_field10 ),
		  m_field14( o.m_field14 ), m_field18( o.m_field18 ),
		  m_field1C( o.m_field1C ), m_field20( o.m_field20 ),
		  m_field24( o.m_field24 ), m_field28( o.m_field28 ),
		  m_field2C( o.m_field2C ), m_field30( o.m_field30 ),
		  m_field34( o.m_field34 ), m_field38( o.m_field38 ),
		  m_field3C( o.m_field3C ), m_field40( o.m_field40 ),
		  m_field44( o.m_field44 ), m_field48( o.m_field48 ),
		  m_field4C( o.m_field4C ), m_field50( o.m_field50 ),
		  m_field54( o.m_field54 )
{
}
