// ?update@WindowManager@@UAEXXZ
// partial score=0.35 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/stringbaseunicode /ICode/Libraries/Source/WWVegas/WWLib
//
// WindowManager::update, retail RVA 0x0046E850 (813 bytes).
//
// The owner is the WindowManager published at 0x012F19E8.  Its APT records
// begin at +0xA8 and are 0x14 bytes wide; the callback map used here begins at
// +0x80.  LoadScreen::update reaches this body through WindowManager's sixth
// virtual slot, which is the identity anchor for this otherwise anonymous
// retail body.

// The substring constructor in this body is the StringBase<char> constructor,
// not AsciiString's incremental-link wrapper.  Make that already-defined WWLib
// type visible so the placement construction below emits the retail body at
// 0x00888F90 directly.
#define private public
#include "string_base.h"
#undef private

#include "Common/AsciiString.h"
typedef unsigned short wchar_t;
#include "Common/UnicodeString.h"

inline void *operator new( unsigned int, void *place )
{
	return place;
}

typedef int Int;

struct RGBColor;

class Shell
{
public:
	void pop();
};

extern Shell *TheShell;

class Mouse
{
public:
	void setCursorTooltip( UnicodeString tooltip, Int index,
		const RGBColor *color, float delay );
};

extern Mouse *TheMouse;

class Rva005A44F0FieldAddress
{
public:
	char *get();
};

class GameWindowManager
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual bool isReadyForTooltip();
};

extern GameWindowManager *TheWindowManager;

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual UnicodeString fetch( AsciiString label, bool *exists = 0 );
};

extern GameTextInterface *TheGameText;

extern int (*g_bfmeNowVNH)();
extern int bfmeIsSet();
extern void bfmeGo929E( void *buffer );
extern __declspec(dllimport) int __cdecl bfmeCmp1026( char *left,
	char *right, int count );
extern __declspec(dllimport) int __cdecl bfmeAtoi1027( char *text );

// These three helpers are still address-derived because their retail bodies
// are generated rows.  Their call conventions and receiving object are proven
// by the update body itself; each name is pinned to exactly one body in the
// symbol ledger, rather than routing through a generated fallback name.
class WindowManager
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void update();

	void rva00467F20AptWindowStep( Int index );
	void rva0046E170PublishValues();
};

extern void __cdecl rva00462A20RefreshValues();
extern void __cdecl rva00894780UpdateTimer( Int elapsed );

extern WindowManager *g_theWindowManager;

class Rva0046A130Table
{
public:
	void *find( const AsciiString &key );
};

struct Rva0046A130Node
{
	unsigned char m_keyAndLink[8];
	void *m_value;
};

class Rva0046A130Value
{
public:
	virtual void slot00();
	virtual void dispatch( const char *text );
};

class BfmeBaseGL
{
public:
	__declspec(dllimport) BfmeBaseGL();
	~BfmeBaseGL();

	void *m_bfmeVftGL;
	unsigned char m_bfmeBaseGapGL[8];
};

extern char g_bfmeMsg1043[];
extern void __stdcall _CxxThrowException( void *object, void *throwInfo );

void WindowManager::update()
{
	unsigned char *bytes = reinterpret_cast<unsigned char *>( this );

	if ( bytes[0x1AC] )
	{
		TheShell->pop();
		bytes[0x1AC] = 0;
	}

	if ( bytes[0x1AD] )
	{
		bytes[0x1AD] = 0;
		for ( Int i = 0; i < 12; ++i )
		{
			if ( (bytes[0xB8 + i * 0x14] & 1) != 0 )
				rva00467F20AptWindowStep( i );
		}
		bytes[0x1A4] = 1;
		rva00462A20RefreshValues();
		rva0046E170PublishValues();
	}

	Int now = g_bfmeNowVNH();
	Int elapsed = now - *reinterpret_cast<Int *>( bytes + 0x1A8 );
	if ( elapsed > 0x3C )
		elapsed = 0x3C;
	if ( bytes[0x1C4] && elapsed < 0x22 )
		elapsed = 0x22;
	bytes[0x1AE] = 1;
	rva00894780UpdateTimer( elapsed );
	bytes[0x1AE] = 0;
	*reinterpret_cast<Int *>( bytes + 0x1A8 ) = now;

	if ( !bfmeIsSet() )
		return;

	char *mouseField =
		*reinterpret_cast<char **>( ( (Rva005A44F0FieldAddress *)TheMouse )->get() );
	if ( mouseField == 0 || *reinterpret_cast<unsigned short *>( mouseField + 4 ) != 0 )
		return;

	if ( TheWindowManager == 0 || !TheWindowManager->isReadyForTooltip() )
		return;

	AsciiString name;
	char level[0x200];
	bfmeGo929E( level );
	if ( bfmeCmp1026( level, (char *)0x010F7314, 6 ) != 0 )
		return;

	// Retail makes this first, byte-valued call before parsing the complete
	// suffix.  Preserve it as observed at +0x141 rather than folding it into
	// the second atoi call.
	if ( bfmeAtoi1027( reinterpret_cast<char *>(
		static_cast<Int>( static_cast<signed char>( level[6] ) ) ) ) == 0 )
		return;
	Int index = bfmeAtoi1027( level + 6 );
	if ( index < 0 || index >= 12 )
		return;

	StringBase<char> *nameBase = reinterpret_cast<StringBase<char> *>( &name );
	nameBase->set( *reinterpret_cast<StringBase<char> *>(
		bytes + 0xA8 + index * 0x14 ) );

	if ( nameBase->m_data != 0 && nameBase->m_data->length > 0 )
	{
		Int length = nameBase->m_data->length;
		Int dot = length;
		for ( ;; )
		{
			if ( nameBase->m_data->data[dot] == '.' )
				break;
			--dot;
			if ( dot <= 0 )
				break;
		}
		if ( dot > 0 && nameBase->m_data->data[dot] == '.' )
		{
			char stemStorage[sizeof(StringBase<char>)] = { 0 };
			StringBase<char> *stem = reinterpret_cast<StringBase<char> *>(
				stemStorage );
			new ( stemStorage ) StringBase<char>( *nameBase, 0, dot - 1 );
			nameBase->set( *stem );
			stem->releaseBuffer();
		}

		char *suffix = level + 6;
		while ( *suffix != 0 && *suffix != '/' )
			++suffix;
		if ( *suffix == '/' )
		{
			char *tail = suffix + 1;
			Int tailLength = 0;
			while ( tail[tailLength] != 0 )
				++tailLength;
			nameBase->concat( tail, tailLength );
		}
		else
		{
			Int levelLength = 0;
			while ( level[levelLength] != 0 )
				++levelLength;
			nameBase->set( level, levelLength );
		}
	}

	if ( nameBase->m_data == 0 || nameBase->m_data->length == 0 )
		return;

	Rva0046A130Node *node = reinterpret_cast<Rva0046A130Node *>(
		reinterpret_cast<Rva0046A130Table *>( bytes + 0x80 )->find(
			*reinterpret_cast<AsciiString *>( &name ) ) );
	const char *nameText = nameBase->m_data
		? &nameBase->m_data->data[0] : (const char *)0x0107388B;

	if ( node != 0 )
	{
		Rva0046A130Value *value =
			reinterpret_cast<Rva0046A130Value *>( node->m_value );
		if ( value != 0 )
		{
			value->dispatch( nameText );
			return;
		}

		BfmeBaseGL error;
		error.m_bfmeVftGL = (void *)0x010766DC;
		_CxxThrowException( &error, g_bfmeMsg1043 );
		return;
	}

	if ( nameText[nameBase->m_data->length - 1] == '/' )
		return;

	AsciiString tooltipKey( (const char *)0x010F7308 );
	AsciiString tooltip = tooltipKey + *reinterpret_cast<AsciiString *>( &name );
	TheMouse->setCursorTooltip( TheGameText->fetch( tooltip ), -1, 0, 1.0f );
}
