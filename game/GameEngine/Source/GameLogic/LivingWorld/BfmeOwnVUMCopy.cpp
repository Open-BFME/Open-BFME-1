// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x00362F30 (229 bytes): the BfmeOwnVUM copy constructor. It stores
// the vftable ??_7BfmeOwnVUM (0x00CE8F34), constructs the five string members
// empty and zeroes the word blocks, then calls the matched element assign
// LivingWorldArmy::copyFrom (ILT 0x000470F0 -> 0x00361B30). Callers reach it
// through ILT 0x0001FE6F (the vector<BfmeOwnVUM> copy and push_back loops).

#include <wchar.h>
#include <string.h>
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"

class LivingWorldArmy
{
public:
	void copyFrom( const LivingWorldArmy &other );
};

class BfmeOwnVUM
{
public:
	BfmeOwnVUM( const BfmeOwnVUM &other );
	virtual void bfmeSlot0VUM();
	virtual void bfmeSlot1VUM();
	virtual void bfmeSlot2VUM();
	virtual void bfmeSlot3VUM();
	virtual void bfmeSlot4VUM();

private:
	struct SixWords
	{
		SixWords() { memset( this, 0, sizeof( *this ) ); }
		int m0, m1, m2, m3, m4, m5;
	};
	struct ThreeWords
	{
		ThreeWords() { memset( this, 0, sizeof( *this ) ); }
		int m0, m1, m2;
	};
	struct TenWords
	{
		TenWords() { memset( this, 0, sizeof( *this ) ); }
		int m0, m1, m2, m3, m4, m5, m6, m7, m8, m9;
	};

	AsciiString m_name;
	int m_08;
	int m_0c;
	SixWords m_10;
	ThreeWords m_28;
	int m_34;
	unsigned char m_38;
	unsigned char m_39;
	int m_3c;
	int m_40;
	int m_44;
	int m_48;
	AsciiString m_4c;
	TenWords m_50;
	UnicodeString m_78;
	SixWords m_7c;
	SixWords m_94;
	AsciiString m_ac;
	AsciiString m_b0;
};

typedef char BfmeOwnVUMCopySize[ ( sizeof( BfmeOwnVUM ) == 0xB4 ) ? 1 : -1 ];

// ??0BfmeOwnVUM@@QAE@ABV0@@Z
BfmeOwnVUM::BfmeOwnVUM( const BfmeOwnVUM &other )
{
	( (LivingWorldArmy *)this )->copyFrom( (const LivingWorldArmy &)other );
}
