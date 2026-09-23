// ?_bfme_refreshProfile@BfmeAptScreenSkirmish@@QAEXXZ
// partial score=0.9978 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Retail 0x0057CAC0: AptSkirmish profile-combo refresh callback.
// Evidence: the matched close, persona-accept, persona-remove, and gadget-init
// callers invoke this member on BfmeAptScreenSkirmish. The two APT profile
// labels in retail are NewProfile and DeleteProfile. The preference subobject
// is at +0x3ac and the combo pointer at +0x420, as in the matched caller TUs.
//
// ABI evidence: retail's 0x0009F820 helper is the source-backed
// Rva0009F820Host::copyStringAt14 accessor; the list cleanup target
// 0x0009F2F0 is STLport's UnicodeString list clear (12-byte nodes). Physical
// callees at 0x004B39D0, 0x004B4F40, and 0x004B3C70 confirm reset, by-value
// string add, and (window, index, bool) selection signatures. The matched
// SkirmishPreferences::getUserName body returns UnicodeString by value.
//
// Best probe: ours=456, retail=456, 24 relocations, one nonreloc byte. The
// only mismatch is the receiver displacement in `lea ecx,[esp+...]` at +0xdc
// (byte +0xdf: retail 0x2c, ours 0x1c). compareNoCaseRaw at 0x0009ECA0 does
// not read ECX; no caller/source evidence identifies which valid object the
// original expression used, so this final source-shape choice remains open.

#include <list>

extern const char g_bfmeEmptyUnicode[];

template <typename T> class StringBase
{
public:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );

	void set( const StringBase<T> &other );
	int compareNoCaseRaw( const T *left, const T *right, int length ) const throw();

private:
	struct Header
	{
		int references;
		unsigned short length;
		unsigned short capacity;
		T text[ 1 ];
	};

	Header *m_data;

	public:
	__forceinline int compareNoCase( const StringBase<T> &other ) const throw()
	{
		const int otherLength = other.m_data ? other.m_data->length : 0;
		const T *otherText = other.m_data ? other.m_data->text : (const T *)g_bfmeEmptyUnicode;
		const int thisLength = m_data ? m_data->length : 0;
		const T *thisText = m_data ? m_data->text : (const T *)g_bfmeEmptyUnicode;
		const int commonLength = thisLength < otherLength ? thisLength : otherLength;
		const int result = compareNoCaseRaw( thisText, otherText, commonLength );
		return result == 0 ? thisLength - otherLength : result;
	}

	void releaseBuffer();
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() { releaseBuffer(); }

	UnicodeString &operator=( const UnicodeString &other )
	{
		set( other );
		return *this;
	}
};

class ProfileList : public std::list<UnicodeString>
{
};

class Rva0009F820Host
{
public:
	ProfileList copyStringAt14();

};

class SkirmishPreferences
{
public:
	UnicodeString getUserName();

private:
	char m_unmodelled[ 0x20 ];
};

class GameWindow {};

class PopulateRemoteIPComboBoxEntry : public UnicodeString
{
public:
	PopulateRemoteIPComboBoxEntry( const UnicodeString &source )
		: UnicodeString( source ) {}
	PopulateRemoteIPComboBoxEntry(
		const PopulateRemoteIPComboBoxEntry &source )
		: UnicodeString( source ) {}
};

extern void GadgetComboBoxReset( GameWindow *comboBox );
extern int GadgetComboBoxAddEntryPopulateRemoteIPComboBox(
	GameWindow *comboBox, PopulateRemoteIPComboBoxEntry text, int color );
extern int GadgetComboBoxAddEntry(
	GameWindow *comboBox, UnicodeString text, int color );
extern void GadgetComboBoxSetSelectedPos(
	GameWindow *comboBox, int selected, bool dontHide );

extern void j_00007004();
extern void j_00008bc0();
extern void j_00010898();
extern void j_0002f338();
extern void j_000439c3();
extern void j_000480f4();

#pragma comment(linker, "/alternatename:?GadgetComboBoxReset@@YAXPAVGameWindow@@@Z=?j_00007004@@YAXXZ")
#pragma comment(linker, "/alternatename:?GadgetComboBoxAddEntryPopulateRemoteIPComboBox@@YAHPAVGameWindow@@VPopulateRemoteIPComboBoxEntry@@H@Z=?j_0002f338@@YAXXZ")
#pragma comment(linker, "/alternatename:?GadgetComboBoxSetSelectedPos@@YAXPAVGameWindow@@H_N@Z=?j_000439c3@@YAXXZ")
#pragma comment(linker, "/alternatename:?copyStringAt14@Rva0009F820Host@@QAE?AVProfileList@@XZ=?j_00008bc0@@YAXXZ")
#pragma comment(linker, "/alternatename:?getUserName@SkirmishPreferences@@QAE?AVUnicodeString@@XZ=?j_00010898@@YAXXZ")

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

extern GameTextInterface *TheGameText;

class BfmeAptScreenSkirmish
{
public:
	void _bfme_refreshProfile();

private:
	char m_unmodelled_00[ 0x3ac ];
	SkirmishPreferences m_preferences;
	char m_unmodelled_3cc[ 0x54 ];
	GameWindow *m_profileCombo;
};

#pragma comment(linker, "/alternatename:?compareNoCaseRaw@?$StringBase@G@@ABEHPBG0H@Z=?j_000480f4@@YAXXZ")

// ?_bfme_refreshProfile@BfmeAptScreenSkirmish@@QAEXXZ
void BfmeAptScreenSkirmish::_bfme_refreshProfile()
{
	GadgetComboBoxReset( m_profileCombo );

	ProfileList profiles =
		((Rva0009F820Host *)&m_preferences)->copyStringAt14();
	std::list<UnicodeString>::iterator node = profiles.begin();
	UnicodeString profile;
	int index = 0;
	while( node != profiles.end() )
	{
		profile = *node;
		GadgetComboBoxAddEntryPopulateRemoteIPComboBox(
			m_profileCombo, profile, -1 );

		if( ( (const StringBase<unsigned short> *)&profile )->compareNoCase(
			*(const StringBase<unsigned short> *)&m_preferences.getUserName() ) == 0 )
			GadgetComboBoxSetSelectedPos( m_profileCombo, index, false );

		++node;
		++index;
	}

	GadgetComboBoxAddEntry(
		m_profileCombo, TheGameText->fetch( "APT:NewProfile" ), -1 );
	GadgetComboBoxAddEntry(
		m_profileCombo, TheGameText->fetch( "APT:DeleteProfile" ), -1 );
}
