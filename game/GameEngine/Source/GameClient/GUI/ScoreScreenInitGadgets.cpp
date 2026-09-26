// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc
//
// AptScoreScreen::InitGadgets callback, retail 0x00571EC0 (142 bytes).

extern "C" int __cdecl strcmp( const char *left, const char *right );

template <typename T> class StringBase
{
    friend class UnicodeString;

private:
    StringBase( const StringBase<T> &other );
    void releaseBuffer();

    void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    static UnicodeString TheEmptyString;

    UnicodeString( const UnicodeString &other )
        : StringBase<unsigned short>( other ) {}

    ~UnicodeString()
    {
        ((StringBase<unsigned short> *)this)->releaseBuffer();
    }
};

class GameWindow
{
public:
    void *winGetUserData();
    void winSetUserData( void *userData );
};

void GadgetTextEntrySetText( GameWindow *window, UnicodeString text );

class BfmeAptScreenScoreScreen
{
public:
    void _bfme_onInitGadget(
        const char *name, void *argument, GameWindow *window );

private:
    char m_unmodelled[ 0x310 ];
    GameWindow *m_persistentUnitsListBox;
    GameWindow *m_renameUnitsTextEntry;
};

// ?_bfme_onInitGadget@BfmeAptScreenScoreScreen@@QAEXPBDPAXPAVGameWindow@@@Z
void BfmeAptScreenScoreScreen::_bfme_onInitGadget(
    const char *name, void *, GameWindow *window )
{
    if( window == 0 )
        return;

    if( strcmp( name, "PersistentUnitsListBox" ) == 0 )
    {
        m_persistentUnitsListBox = window;
        unsigned char *userData = (unsigned char *)window->winGetUserData();
        userData[ 0x12 ] = 1;
        window->winSetUserData( userData );
        return;
    }

    if( strcmp( name, "RenameUnitsTextEntry" ) == 0 )
    {
        m_renameUnitsTextEntry = window;
        GadgetTextEntrySetText( window, UnicodeString::TheEmptyString );
        unsigned char *userData = (unsigned char *)window->winGetUserData();
        if( userData != 0 )
            *(unsigned short *)( userData + 0x10 ) = 20;
    }
}
