// ?rva0054FF80@Rva0054FF80Owner@@QAEXAAVAsciiString@@0@Z
// partial score=0.776 date=2026-09-18
// ?rva0054FF80@Rva0054FF80Owner@@QAEXAAVAsciiString@@0@Z
// Retail RVA 0x0054FF80, 1116 bytes.  The owning class is not proven by the
// ICF-shared body; the address-derived owner keeps that uncertainty explicit.
// The +0x3C preferences object and +0x74..+0x84 gadget fields are witnessed
// by the callers and by the matched OnlineLogin constructor.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include <list>
#include "string_base.h"

#pragma inline_depth(255)

extern "C" int __cdecl memcmp( const void *, const void *, unsigned int );
#pragma intrinsic( memcmp )

class AsciiString
{
	friend bool operator==( const AsciiString &, const AsciiString & );

public:
	AsciiString() : m_data( 0 ) {}
	AsciiString( const AsciiString &other )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other );
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	bool isEmpty() const
	{
		const StringBase<char> *base = (const StringBase<char> *)this;
		return base->m_data == 0 || base->m_data->length == 0;
	}

	int compare( const AsciiString &other ) const
	{
		const StringBase<char> *otherBase = (const StringBase<char> *)&other;
		const StringBase<char> *base = (const StringBase<char> *)this;
		const int length = otherBase->m_data
			? otherBase->m_data->length : 0;
		const char *text = otherBase->m_data
			? &otherBase->m_data->data[ 0 ] : "";
		const int myLength = base->m_data ? base->m_data->length : 0;
		const char *myText = base->m_data
			? &base->m_data->data[ 0 ] : "";
		const int result = memcmp( myText, text,
			myLength < length ? myLength : length );
		if ( result != 0 )
			return result;
		return myLength - length;
	}

private:
	void *m_data;
};

inline bool operator==( const AsciiString &left, const AsciiString &right )
{
	return left.compare( right ) == 0;
}

class UnicodeString
{
public:
	UnicodeString() : m_data( 0 ) {}
	UnicodeString( const UnicodeString &other )
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&other );
	}
	~UnicodeString()
	{
		((StringBase<unsigned short> *)this)->releaseBuffer();
	}

	void translate( const AsciiString &source );
	static const UnicodeString TheEmptyString;

	bool isEmpty() const
	{
		const StringBase<unsigned short> *base =
			(const StringBase<unsigned short> *)this;
		return base->m_data == 0 || base->m_data->length == 0;
	}

private:
	void *m_data;
};

class GameWindow;

extern int GameSpyColor[];

extern void GadgetComboBoxReset( GameWindow *window );
extern void GadgetComboBoxSetIsEditable( GameWindow *window, bool editable );
extern void GadgetTextEntrySetText( GameWindow *window, UnicodeString text );
extern int GadgetComboBoxAddEntry( GameWindow *window, UnicodeString text,
	int color );
extern void GadgetComboBoxSetSelectedPos( GameWindow *window, int selected,
	bool notify );
extern void GadgetCheckBoxSetChecked( GameWindow *window, bool checked );
extern void GadgetComboBoxSetText( GameWindow *window, UnicodeString text );

#pragma comment(linker, "/alternatename:?GadgetComboBoxReset@@YAXPAVGameWindow@@@Z=?j_00007004@@YAXXZ")
#pragma comment(linker, "/alternatename:?GadgetComboBoxSetIsEditable@@YAXPAVGameWindow@@_N@Z=?j_0004813a@@YAXXZ")
#pragma comment(linker, "/alternatename:?GadgetTextEntrySetText@@YAXPAVGameWindow@@VUnicodeString@@@Z=?j_0000c874@@YAXXZ")
#pragma comment(linker, "/alternatename:?GadgetComboBoxAddEntry@@YAHPAVGameWindow@@VUnicodeString@@H@Z=?j_0002f338@@YAXXZ")
#pragma comment(linker, "/alternatename:?GadgetComboBoxSetSelectedPos@@YAXPAVGameWindow@@H_N@Z=?j_000439c3@@YAXXZ")
#pragma comment(linker, "/alternatename:?GadgetCheckBoxSetChecked@@YAXPAVGameWindow@@_N@Z=?j_0002e875@@YAXXZ")
#pragma comment(linker, "/alternatename:?GadgetComboBoxSetText@@YAXPAVGameWindow@@VUnicodeString@@@Z=?j_00022237@@YAXXZ")

typedef std::list<AsciiString> AsciiStringList;
typedef AsciiStringList::iterator AsciiStringListIterator;

class GameSpyLoginPreferences
{
public:
	AsciiStringList getEmails( void );
	AsciiString getPasswordForEmail( AsciiString email );
	AsciiStringList getNicksForEmail( AsciiString email );

private:
	unsigned char m_unmodelled[ 0x38 ];
};

#pragma comment(linker, "/alternatename:?getEmails@GameSpyLoginPreferences@@QAE?AV?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@XZ=?j_0000604b@@YAXXZ")
#pragma comment(linker, "/alternatename:?getPasswordForEmail@GameSpyLoginPreferences@@QAE?AVAsciiString@@V2@@Z=?j_0001f7b7@@YAXXZ")
#pragma comment(linker, "/alternatename:?getNicksForEmail@GameSpyLoginPreferences@@QAE?AV?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@VAsciiString@@@Z=?j_000191b9@@YAXXZ")

class Rva0054FF80Owner
{
public:
	void rva0054FF80( AsciiString &lastEmail, AsciiString &lastName );

private:
	unsigned char m_unmodelled[ 0x3c ];
	GameSpyLoginPreferences m_loginPreferences;
	GameWindow *m_control74;
	GameWindow *m_control78;
	GameWindow *m_control7C;
	GameWindow *m_control80;
	GameWindow *m_control84;
};

extern void j_0004557a();

void Rva0054FF80Owner::rva0054FF80( AsciiString &lastEmail,
	AsciiString &lastName )
{
	if ( *(unsigned char *)0x012F4AB2 )
		return;

	{
	GameWindow *emailCombo = m_control74;
	*(unsigned char *)0x012F4AB2 = 1;
	GadgetComboBoxReset( emailCombo );
	GadgetComboBoxSetIsEditable( m_control74, true );
	GadgetComboBoxReset( m_control78 );
	GadgetComboBoxSetIsEditable( m_control78, true );

	GadgetTextEntrySetText( m_control7C, UnicodeString::TheEmptyString );

	AsciiStringList cachedEmails = m_loginPreferences.getEmails();
	int selectedPosition = -1;
	AsciiStringListIterator emailIt = cachedEmails.begin();
	while ( emailIt != cachedEmails.end() )
	{
		UnicodeString translated;
		translated.translate( *emailIt );
		int position = GadgetComboBoxAddEntry( m_control74, translated,
			GameSpyColor[ 0 ] );
		if ( *emailIt == lastEmail )
			selectedPosition = position;
		++emailIt;
	}

	if ( selectedPosition >= 0 )
	{
		GadgetComboBoxSetSelectedPos( m_control74, selectedPosition, false );

		UnicodeString password;
		password.translate(
			m_loginPreferences.getPasswordForEmail( lastEmail ) );
		if ( m_control7C != 0 && m_control80 != 0 )
			GadgetCheckBoxSetChecked( m_control80, !password.isEmpty() );
		GadgetTextEntrySetText( m_control7C, password );
	}
	else
	{
		UnicodeString translated;
		translated.translate( lastEmail );
		GadgetComboBoxSetText( m_control74, translated );
	}

	AsciiStringList cachedNames = m_loginPreferences.getNicksForEmail(
		lastEmail );
	AsciiStringListIterator nameIt = cachedNames.begin();
	selectedPosition = -1;
	while ( nameIt != cachedNames.end() )
	{
		UnicodeString translated;
		translated.translate( *nameIt );
		int position = GadgetComboBoxAddEntry( m_control78, translated,
			GameSpyColor[ 0 ] );
		if ( *nameIt == lastName )
			selectedPosition = position;
		++nameIt;
	}

	if ( selectedPosition >= 0 )
		GadgetComboBoxSetSelectedPos( m_control78, selectedPosition, false );

	*(unsigned char *)0x012F4AB2 = 0;
	union
	{
		void (*raw)( void );
		void (Rva0054FF80Owner::*member)( void );
	} apply;
	apply.raw = j_0004557a;
	(this->*apply.member)();
	}
}
