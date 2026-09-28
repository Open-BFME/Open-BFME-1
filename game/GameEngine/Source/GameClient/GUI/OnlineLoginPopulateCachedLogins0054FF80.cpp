// Retail 0x0054FF80, 1116 bytes, RET 8: the OnlineLogin screen's cached-login
// population (the Zero Hour WOLLoginMenuInit email/nick block).  The matched
// caller BfmeAptScreenOnlineLogin::_bfme_refreshLoginState passes its own this
// in ECX, and the body ends by calling the matched
// BfmeAptScreenOnlineLogin::applyLoginGadgets0054FB10 on that same this, so the
// receiver is the OnlineLogin screen.  The ledger keeps the existing
// address-derived receiver name Rva0054FF80::call that the caller links to.
// The +0x3C preferences object and +0x74..+0x84 gadget fields agree with the
// matched OnlineLogin siblings.
//
// The retail TU expands the list destructor fully (clear loop, head reset and
// head free, no null test), which this compiler does only when the STLport
// _List_base::clear/~_List_base/~list are forced inline; those three
// specialisations below are the stock STLport bodies.  The busy flag at
// 0x012F4AB2 is file-static: an extern lets the flag store block the hoisted
// first gadget load that retail schedules ahead of it.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "string_base.h"

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


namespace _STL {
template <> __forceinline void _List_base<AsciiString, allocator<AsciiString> >::clear()
{
  _List_node<AsciiString>* __cur = (_List_node<AsciiString>*) this->_M_node._M_data->_M_next;
  while (__cur != this->_M_node._M_data) {
    _List_node<AsciiString>* __tmp = __cur;
    __cur = (_List_node<AsciiString>*) __cur->_M_next;
    _Destroy(&__tmp->_M_data);
    this->_M_node.deallocate(__tmp, 1);
  }
  this->_M_node._M_data->_M_next = this->_M_node._M_data;
  this->_M_node._M_data->_M_prev = this->_M_node._M_data;
}
template <> __forceinline _List_base<AsciiString, allocator<AsciiString> >::~_List_base()
{
  clear();
  _M_node.deallocate(_M_node._M_data, 1);
}
template <> __forceinline list<AsciiString, allocator<AsciiString> >::~list() {}
}
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


class Rva0054FF80
{
public:
	void call( AsciiString &lastEmail, AsciiString &lastName );

private:
	unsigned char m_unmodelled[ 0x3c ];
	GameSpyLoginPreferences m_loginPreferences;
	GameWindow *m_control74;
	GameWindow *m_control78;
	GameWindow *m_control7C;
	GameWindow *m_control80;
	GameWindow *m_control84;
};

class BfmeAptScreenOnlineLogin
{
public:
	bool applyLoginGadgets0054FB10();
};

static bool g_rva0054FF80Busy;

void Rva0054FF80::call( AsciiString &lastEmail,
	AsciiString &lastName )
{
	if ( g_rva0054FF80Busy )
		return;

	{
	g_rva0054FF80Busy = 1;
	GadgetComboBoxReset( m_control74 );
	GadgetComboBoxSetIsEditable( m_control74, true );
	GadgetComboBoxReset( m_control78 );
	GadgetComboBoxSetIsEditable( m_control78, true );

	GadgetTextEntrySetText( m_control7C, UnicodeString::TheEmptyString );

	AsciiStringList cachedEmails = m_loginPreferences.getEmails();
	int selectedPosition = -1;
	AsciiStringListIterator emailIt = cachedEmails.begin();
	while ( emailIt != cachedEmails.end() )
	{
		{
			UnicodeString translated;
			translated.translate( *emailIt );
			int position = GadgetComboBoxAddEntry( m_control74, translated,
				GameSpyColor[ 0 ] );
			if ( *emailIt == lastEmail )
				selectedPosition = position;
		}
		++emailIt;
	}

	if ( selectedPosition >= 0 )
	{
		GadgetComboBoxSetSelectedPos( m_control74, selectedPosition, false );

		UnicodeString password;
		password.translate(
			m_loginPreferences.getPasswordForEmail( lastEmail ) );
		if ( m_control7C != 0 )
		{
			if ( m_control80 != 0 )
				GadgetCheckBoxSetChecked( m_control80, !password.isEmpty() );
			GadgetTextEntrySetText( m_control7C, password );
		}
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
		{
			UnicodeString translated;
			translated.translate( *nameIt );
			int position = GadgetComboBoxAddEntry( m_control78, translated,
				GameSpyColor[ 0 ] );
			if ( *nameIt == lastName || selectedPosition < 0 )
				selectedPosition = position;
		}
		++nameIt;
	}

	if ( selectedPosition >= 0 )
		GadgetComboBoxSetSelectedPos( m_control78, selectedPosition, false );

	g_rva0054FF80Busy = 0;
	((BfmeAptScreenOnlineLogin *)this)->applyLoginGadgets0054FB10();
	}
}
