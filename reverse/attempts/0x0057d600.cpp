// ?personaAccept@BfmeAptScreenSkirmish@@QAEXH@Z
// partial score=0.92 date=2026-09-09
// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc

template <typename T> class StringBase
{
    friend class UnicodeString;

private:
    StringBase() : m_data( 0 ) {}
    StringBase( const StringBase<T> &other );
    void trim();
    ~StringBase();

public:
    void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    static UnicodeString TheEmptyString;
    UnicodeString &operator=( const UnicodeString &other );
    void trim();
};

class GameWindow;
UnicodeString GadgetTextEntryGetText( GameWindow *window );

class Rva0009F090WideList
{
public:
    int findNoCase( UnicodeString value );
};

class Gen0009FDF0Owner
{
public:
    void Rva0009FDF0( UnicodeString value );
};

class SkirmishPreferences
{
public:
    virtual ~SkirmishPreferences();
    virtual void slot1();
    virtual bool load();
    virtual bool write();

    bool unidentified_00017AF8();
    UnicodeString getUserName();

    char m_unmodelled[ 0x14 ];
};

class SkirmishBattleHonors
{
public:
    virtual ~SkirmishBattleHonors();
    virtual void slot1();
    virtual bool load();
    virtual bool write();

    SkirmishBattleHonors( UnicodeString userName );
    void setProfileCreatedDate();

    char m_unmodelled[ 0x38 ];
};

class Rva0057D0C0
{
public:
    Rva0057D0C0 &operator=( const Rva0057D0C0 *other );
};

class WindowManager
{
public:
    void unidentified_00015235( int movie, const char *function,
        int argumentCount, const void *argument1, const void *argument2,
        int unused1, int unused2, int unused3 );
};

extern WindowManager *g_theWindowManager;

class SkirmishScreenState
{
public:
    virtual void slot0();
    virtual void reset();

private:
    char m_unmodelled[ 0x130 ];
};

class BfmeAptScreenSkirmish
{
public:
    void personaAccept( int argument );
    void _bfme_refreshProfile();

private:
    char m_unmodelled_250[ 0x250 ];
    int m_movie;
    char m_unmodelled_254[ 8 ];
    SkirmishScreenState m_state;
    char m_unmodelled_390[ 0x1c ];
    SkirmishPreferences m_preferences;
    SkirmishBattleHonors m_honors;
    int m_mode;
    int m_previousMode;
    unsigned char m_unmodelled_408;
    unsigned char m_profileOpen;
    char m_unmodelled_40a[ 0x22 ];
    GameWindow *m_createPersonaEntry;
};

static const char *const kErrorSameName = (const char *)0x0110B35C;
static const char *const kPopUpControl = (const char *)0x0110B2DC;
static const char *const kClose = (const char *)0x0110B2EC;
static const char *const kProfileAction = (const char *)0x01107BB4;

// ?personaAccept@BfmeAptScreenSkirmish@@QAEXH@Z
void BfmeAptScreenSkirmish::personaAccept( int )
{
    if( m_mode != 2 )
        return;

    UnicodeString value = UnicodeString::TheEmptyString;
    if( m_createPersonaEntry != 0 )
        value = GadgetTextEntryGetText( m_createPersonaEntry );

    value.trim();

    if( ( (StringBase<unsigned short> *)&value )->m_data != 0 &&
        *(unsigned short *)( (char *)((StringBase<unsigned short> *)&value)->m_data + 4 ) != 0 )
    {
        SkirmishPreferences *preferences = &m_preferences;
        if( ( (Rva0009F090WideList *)preferences )->findNoCase( value ) >= 0 )
        {
            g_theWindowManager->unidentified_00015235(
                m_movie, kErrorSameName, 0, 0, 0, 0, 0, 0 );
            m_previousMode = m_mode;
            m_mode = 4;
        }
        else
        {
            ( (Gen0009FDF0Owner *)preferences )->Rva0009FDF0( value );
            preferences->write();
            m_honors.write();
            {
                SkirmishBattleHonors honors( preferences->getUserName() );
                ( (Rva0057D0C0 *)&m_honors )->operator=(
                    (const Rva0057D0C0 *)&honors );
            }
            _bfme_refreshProfile();
            preferences->write();
            m_honors.setProfileCreatedDate();
            m_honors.write();
            g_theWindowManager->unidentified_00015235(
                m_movie, kPopUpControl, 1, kClose, 0, 0, 0, 0 );
            m_preferences.write();
            m_profileOpen = 1;
            m_state.reset();
            m_mode = 5;
        }
    }
    else if( !m_preferences.unidentified_00017AF8() )
    {
        g_theWindowManager->unidentified_00015235(
            m_movie, kPopUpControl, 1, kClose, 0, 0, 0, 0 );
        g_theWindowManager->unidentified_00015235(
            m_movie, kPopUpControl, 1, kProfileAction, 0, 0, 0, 0 );
        m_profileOpen = 1;
        m_mode = 7;
    }
    else
    {
        _bfme_refreshProfile();
        g_theWindowManager->unidentified_00015235(
            m_movie, kPopUpControl, 1, kClose, 0, 0, 0, 0 );
        m_profileOpen = 1;
        m_mode = 7;
    }
}
