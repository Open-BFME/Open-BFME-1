// ?method@Rva00365C20Owner@@QAEXABURva00365C20SourceRecord@@HHURva00365C20Payload6@@HABURva00365C20Tail@@@Z
// partial score=0.5245 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

struct Rva00365C20Payload6
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
};

struct Rva00365C20Tail
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	unsigned char m_10;
	unsigned char m_padding[ 3 ];
	UnicodeString m_14;
	AsciiString m_18;
};

typedef char Rva00365C20TailSize[ sizeof( Rva00365C20Tail ) == 0x1c ? 1 : -1 ];

struct Rva00365C20SourceRecord
{
	AsciiString m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
};

class BfmeOwnVUM
{
public:
	BfmeOwnVUM();
	~BfmeOwnVUM();
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();

	AsciiString m_04;
	int m_08;
	int m_0c;
	Rva00365C20Payload6 m_10;
	char m_28[ 0x0c ];
	int m_34;
	unsigned char m_38;
	unsigned char m_39;
	char m_3a[ 2 ];
	int m_3c;
	int m_40;
	int m_44;
	int m_48;
	AsciiString m_4c;
	char m_50[ 0x28 ];
	UnicodeString m_78;
	char m_7c[ 0x30 ];
	AsciiString m_ac;
	AsciiString m_b0;
};

struct P6Elem00365520
{
	char m_body[ 0xb4 ];
};

class Gen00365520
{
public:
	void bfmeAppend( const P6Elem00365520 *value );
};

class Rva00365C20PlayerArmy
{
public:
	char m_head[ 0x30 ];
	std::vector<BfmeOwnVUM> m_armies;
	char m_tail[ 0x1c ];
};

typedef char Rva00365C20PlayerArmySize[
	sizeof( Rva00365C20PlayerArmy ) == 0x58 ? 1 : -1 ];

class Rva00365C20Owner
{
public:
	void method( const Rva00365C20SourceRecord &source00, int source08, int source0c,
		Rva00365C20Payload6 source14, int index,
		const Rva00365C20Tail &source44 );

private:
	char m_head[ 0x18 ];
	std::vector<Rva00365C20PlayerArmy> m_playerArmies;
};

// ?method@Rva00365C20Owner@@QAEXABURva00365C20SourceRecord@@HHURva00365C20Payload6@@HABURva00365C20Tail@@@Z
void Rva00365C20Owner::method( const Rva00365C20SourceRecord &source00,
	int source08, int source0c, Rva00365C20Payload6 source14,
	int index, const Rva00365C20Tail &source44 )
{
	if( index < 0 )
		return;
	if( (unsigned int)index > m_playerArmies.size() - 1 )
		return;

	BfmeOwnVUM record;
	record.m_04.set( source00.m_00 );
	record.m_0c = source0c;
	record.m_08 = source08;
	record.m_10 = source14;
	record.m_39 = source44.m_10;
	record.m_3c = source44.m_00 + 1;
	record.m_44 = source44.m_08;
	record.m_40 = source44.m_04;
	record.m_48 = source44.m_0c;
	reinterpret_cast<StringBase<unsigned short> &>( record.m_78 ).set(
		reinterpret_cast<const StringBase<unsigned short> &>( source44.m_14 ) );
	record.m_4c.set( source44.m_18 );
	((Gen00365520 &)m_playerArmies[ index ]).bfmeAppend(
		(const P6Elem00365520 *)&record );
}

