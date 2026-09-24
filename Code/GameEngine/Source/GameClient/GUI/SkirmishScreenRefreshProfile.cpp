// ?_bfme_refreshProfile@BfmeAptScreenSkirmish@@QAEXXZ
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Retail 0x0057CAC0: AptSkirmish profile-combo refresh callback.
// Evidence: the matched close, persona-accept, persona-remove, and gadget-init
// callers invoke this member on BfmeAptScreenSkirmish. The two APT profile
// labels in retail are NewProfile and DeleteProfile. The preference subobject
// is at +0x3ac and the combo pointer at +0x420, as in the matched caller TUs.
//
// ABI evidence: retail's 0x0009F820 helper copies an STLport list at
// host +0x14 via the list copy ctor at 0x0009F6E0. Its address-qualified
// Rva0009F820String result is this list view. The list cleanup target
// 0x0009F2F0 is STLport's UnicodeString list clear (12-byte nodes). Physical
// callees at 0x004B39D0, 0x004B4F40, and 0x004B3C70 confirm reset, by-value
// string add, and (window, index, bool) selection signatures. The matched
// SkirmishPreferences::getUserName body returns UnicodeString by value.
//
// The raw no-case helper at 0x0009ECA0 reads only its three stack arguments.
// Its unused ECX receiver is an address in the caller frame at +0x2c, while
// the profile string lives at +0x1c. The explicit offset reproduces that
// dead ABI argument without changing the comparison or its caller-visible data.
// The profile callback identity comes from matched callers and APT labels.

#include <list>

extern const char g_bfmeEmptyUnicode[];

template <typename T> class StringBase
{
	friend class UnicodeString;
public:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );

	void set( const StringBase<T> &other );
private:
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
		const int result = reinterpret_cast<const StringBase<T> *>(reinterpret_cast<const char *>(this) + 0x10)->compareNoCaseRaw( thisText, otherText, commonLength );
		return result == 0 ? thisLength - otherLength : result;
	}

private:
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

// The matched accessor's mangled result uses an address-derived name. Its
// callee copies an STLport list, so retain the descriptive ProfileList base.
class Rva0009F820String : public ProfileList
{
};

class Rva0009F820Host
{
public:
	Rva0009F820String copyStringAt14();

};

class SkirmishPreferences
{
public:
	UnicodeString getUserName();

private:
	char m_unmodelled[ 0x20 ];
};

class GameWindow {};

extern void GadgetComboBoxReset( GameWindow *comboBox );
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
#pragma comment(linker, "/alternatename:?GadgetComboBoxSetSelectedPos@@YAXPAVGameWindow@@H_N@Z=?j_000439c3@@YAXXZ")
#pragma comment(linker, "/alternatename:?copyStringAt14@Rva0009F820Host@@QAE?AVRva0009F820String@@XZ=?j_00008bc0@@YAXXZ")
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

	Rva0009F820String profiles =
		((Rva0009F820Host *)&m_preferences)->copyStringAt14();
	std::list<UnicodeString>::iterator node = profiles.begin();
	UnicodeString profile;
	int index = 0;
	while( node != profiles.end() )
	{
		profile = *node;
		GadgetComboBoxAddEntry(
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
