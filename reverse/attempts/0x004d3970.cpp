// ?NetworkDirectConnectSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// partial score=0.97 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: NetworkDirectConnectSystem, retail 0x004D3970, 542 bytes.
// Converted from gen-dump d_004d3970. ZH twin lives in NetworkDirectConnect.cpp
// beside already-matched Update/Shutdown/Input/PopulateRemoteIPComboBox; this
// sibling keeps that TU untouched. BFME stores string length as a word at +4
// (not ZH wcslen), RequestSetName is vtable +0x60, and by-value UnicodeString
// args need the StringBase-forwarding copy for the EH saved-esp order.
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;

enum WindowMsgHandledType
{
	MSG_IGNORED = 0,
	MSG_HANDLED = 1
};

enum
{
	GWM_CREATE = 1,
	GWM_DESTROY = 2,
	GWM_INPUT_FOCUS = 0x17,
	GBM_SELECTED = 0x4008,
	GEM_EDIT_DONE = 0x4030
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	~StringBase();

public:
	StringBase( const StringBase<T> &other );
	void removeLastChar();

private:
	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString( const char *text ) : StringBase<char>( text ) {}
    AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
    ~AsciiString() {}

    AsciiString &operator=( const AsciiString &other );
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString( const WideChar *text ) : StringBase<WideChar>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<WideChar>( other ) {}
	~UnicodeString() {}

	UnicodeString &operator=( const UnicodeString &other );

	unsigned short getLength() const
	{
		return m_data ? m_data->m_length : 0;
	}

	void removeLastChar()
	{
		StringBase<WideChar>::removeLastChar();
	}
};

class GameWindow
{
public:
	Int winGetWindowId();
};

// UserPreferences layout: vptr@0, STLport map@+4, AsciiString filename.
class PreferenceMap
{
    void *m_header;
    void *m_nodeCount;
    void *m_pad;

public:
    AsciiString &operator[]( const AsciiString &key );
};

class LANPreferences
{
    void *m_vptr;
    PreferenceMap m_map;
    AsciiString m_filename;

public:
    LANPreferences();
    ~LANPreferences();
    Bool write();
    AsciiString &operator[]( const AsciiString &key ) { return m_map[key]; }
};

class LANAPI
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void RequestSetName( UnicodeString newName );
};

class Shell
{
public:
	void pop();
};

UnicodeString GadgetTextEntryGetText( GameWindow *window );
AsciiString UnicodeStringToQuotedPrintable( UnicodeString name );
void HostDirectConnectGame();
void JoinDirectConnectGame();

extern LANAPI *TheLAN;
extern Shell *TheShell;
extern GameWindow *editPlayerName;
extern Bool buttonPushed;
extern Bool LANbuttonPushed;
extern Int buttonBackID;
extern Int buttonHostID;
extern Int buttonJoinID;

// ?NetworkDirectConnectSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
WindowMsgHandledType NetworkDirectConnectSystem( GameWindow *window, UnsignedInt msg,
	UnsignedInt mData1, UnsignedInt mData2 )
{
    UnicodeString txtInput;

	switch( msg )
	{
		case GWM_CREATE:
			{
				break;
			}

		case GWM_DESTROY:
			{
				break;
			}

		case GWM_INPUT_FOCUS:
			{
				if( mData1 == 1 )
					*(Bool *)mData2 = true;

				return MSG_HANDLED;
			}

		case GBM_SELECTED:
			{
				if (buttonPushed)
					break;

				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();

				if ( controlID == buttonBackID )
				{
					UnicodeString name;
					name = GadgetTextEntryGetText(editPlayerName);

					LANPreferences prefs;
					prefs["UserName"] = UnicodeStringToQuotedPrintable(name);
					prefs.write();

            while (name.getLength() > 12)
						name.removeLastChar();
					TheLAN->RequestSetName(name);

					buttonPushed = true;
					LANbuttonPushed = true;
					TheShell->pop();
				}
				else if (controlID == buttonHostID)
				{
					HostDirectConnectGame();
				}
				else if (controlID == buttonJoinID)
				{
					JoinDirectConnectGame();
				}
				break;
			}

		case GEM_EDIT_DONE:
			{
				break;
			}
		default:
			return MSG_IGNORED;

	}

	return MSG_HANDLED;
}
