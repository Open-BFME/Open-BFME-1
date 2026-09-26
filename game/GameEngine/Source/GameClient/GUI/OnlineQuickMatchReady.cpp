// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// OnlineQuickMatch readiness population, retail 0x005588E0 (259 bytes).

template <typename T> class StringBase
{
    friend class UnicodeString;

private:
    StringBase() : m_data( 0 ) {}
    StringBase( const StringBase<T> &other );
    ~StringBase();

    void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString() : StringBase<unsigned short>() {}
    UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
    ~UnicodeString() {}

    void format( UnicodeString format, ... );
};

class GameTextInterface
{
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0c() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void slot18() = 0;
    virtual void slot1c() = 0;
    virtual void slot20() = 0;
    virtual void slot24() = 0;
    virtual UnicodeString fetch( const char *label, bool *exists = 0 ) = 0;
};

extern GameTextInterface *TheGameText;
extern int GameSpyColor[];

class GameWindow {};

class PopulateRemoteIPComboBoxEntry : public UnicodeString
{
public:
    PopulateRemoteIPComboBoxEntry( const UnicodeString &source ) : UnicodeString( source ) {}
};

extern void GadgetComboBoxReset( GameWindow *comboBox );
extern int GadgetComboBoxAddEntryPopulateRemoteIPComboBox(
    GameWindow *comboBox, PopulateRemoteIPComboBoxEntry text, int color );
extern void GadgetComboBoxSetSelectedPos( GameWindow *comboBox, int selected, bool dontHide );

#pragma comment(linker, "/alternatename:?GadgetComboBoxReset@@YAXPAVGameWindow@@@Z=?j_00007004@@YAXXZ")
#pragma comment(linker, "/alternatename:?GadgetComboBoxAddEntryPopulateRemoteIPComboBox@@YAHPAVGameWindow@@VPopulateRemoteIPComboBoxEntry@@H@Z=?j_0002f338@@YAXXZ")
#pragma comment(linker, "/alternatename:?GadgetComboBoxSetSelectedPos@@YAXPAVGameWindow@@H_N@Z=?j_000439c3@@YAXXZ")

template <typename T> const T &max( const T &a, const T &b )
{
    if( a > b )
        return a;
    return b;
}

class QuickMatchPreferences
{
public:
    virtual ~QuickMatchPreferences();
    int getNumPlayers();

private:
    unsigned char m_unmodelled[ 0x10 ];
};

#pragma comment(linker, "/alternatename:?getNumPlayers@QuickMatchPreferences@@QAEHXZ=?j_00037169@@YAXXZ")

class BfmeAptScreenOnlineQuickMatch
{
public:
    bool rva005588E0Ready();

private:
    unsigned char m_beforePreferences[ 0x40 ];
    QuickMatchPreferences m_preferences;
    unsigned char m_betweenPreferencesAndCombo[ 0x0c ];
    GameWindow *m_remoteIPCombo;
};

bool BfmeAptScreenOnlineQuickMatch::rva005588E0Ready()
{
    if( m_remoteIPCombo == 0 )
        return false;

    int color = GameSpyColor[ 0 ];
    GadgetComboBoxReset( m_remoteIPCombo );

    UnicodeString text;
    for( int i = 1; i <= 2; ++i )
    {
        text.format( TheGameText->fetch( "GUI:PlayersVersusPlayers" ), i, i );
        GadgetComboBoxAddEntryPopulateRemoteIPComboBox( m_remoteIPCombo, text, color );
    }

    GadgetComboBoxSetSelectedPos( m_remoteIPCombo, max( 0, m_preferences.getNumPlayers() ), false );
    return true;
}
