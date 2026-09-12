// ?personaAccept@BfmeAptScreenSkirmish@@QAEXH@Z
// lane 35 scratch, based on reverse/attempts/0x0057d600.cpp
// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc

template <typename T> class StringBase
{
    friend class UnicodeString;

private:
    StringBase() : m_data( 0 ) {}
    StringBase( const StringBase<T> &other );
    void trim();
    void set( const StringBase<T> &other );
    void releaseBuffer();

public:
    void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    static UnicodeString TheEmptyString;
    UnicodeString( const UnicodeString &other )
        : StringBase<unsigned short>( other ) {}
    __forceinline ~UnicodeString() { releaseBuffer(); }
    UnicodeString &operator=( const UnicodeString &other )
    {
        StringBase<unsigned short>::set( other );
        return *this;
    }
    void trim() { StringBase<unsigned short>::trim(); }
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

class Gen0009FBB0Owner
{
public:
    void Rva0009FBB0( UnicodeString value );
};

class SkirmishPreferencesMap
{
public:
    virtual void slot0();
    void *m_head;
};

class SkirmishPreferencesVector
{
public:
    void *m_head;
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

    SkirmishPreferencesMap m_map;
    char m_unmodelled_0c[ 4 ];
    UnicodeString m_userName;
    SkirmishPreferencesVector m_userNames;
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

    SkirmishPreferencesMap m_map;
    char m_unmodelled_0c[ 4 ];
    UnicodeString m_userName;
    int m_values[ 10 ];
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

extern "C" void _ReadWriteBarrier();
#pragma intrinsic( _ReadWriteBarrier )

class SkirmishScreenState
{
public:
    virtual void slot0();
    virtual void reset();

private:
    char m_unmodelled[ 0x130 ];
};

typedef bool (__fastcall *SkirmishPreferencesWriteCall)( SkirmishPreferences * );
typedef void (__fastcall *SkirmishScreenStateResetCall)( SkirmishScreenState * );

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
    bool m_profileOpen;
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
        if( ( (Rva0009F090WideList *)&m_preferences )->findNoCase( value ) >= 0 )
        {
            g_theWindowManager->unidentified_00015235(
                m_movie, kErrorSameName, 0, 0, 0, 0, 0, 0 );
            int previousMode = m_mode;
            m_previousMode = previousMode;
            m_mode = 4;
        }
        else
        {
            SkirmishPreferences *preferences = &m_preferences;
            ( (Gen0009FDF0Owner *)preferences )->Rva0009FDF0( value );
            ( (Gen0009FBB0Owner *)preferences )->Rva0009FBB0( value );
            preferences->write();
            m_honors.write();
            SkirmishBattleHonors honors( preferences->getUserName() );
            ( (Rva0057D0C0 *)&m_honors )->operator=(
                (const Rva0057D0C0 *)&honors );
            _bfme_refreshProfile();
            preferences->write();
            m_honors.setProfileCreatedDate();
            m_honors.write();
            g_theWindowManager->unidentified_00015235(
                m_movie, kPopUpControl, 1, kClose, 0, 0, 0, 0 );
            m_profileOpen = true;
            void **preferencesVtable = *(void ***)&m_preferences;
            ( (SkirmishPreferencesWriteCall)preferencesVtable[ 3 ] )(
                &m_preferences );
            ( (SkirmishScreenStateResetCall)( *(void ***)&m_state )[ 1 ] )(
                &m_state );
            m_mode = 5;
        }
    }
    else if( !m_preferences.unidentified_00017AF8() )
    {
        int movie = m_movie;
        g_theWindowManager->unidentified_00015235(
            movie, kPopUpControl, 1, kClose, 0, 0, 0, 0 );
        int profileMovie = m_movie;
        g_theWindowManager->unidentified_00015235(
            profileMovie, kPopUpControl, 1, kProfileAction, 0, 0, 0, 0 );
        return;
    }
    else
    {
        _bfme_refreshProfile();
        int movie = m_movie;
        g_theWindowManager->unidentified_00015235(
            movie, kPopUpControl, 1, kClose, 0, 0, 0, 0 );
        _ReadWriteBarrier();
        m_profileOpen = 1;
        m_mode = 7;
    }
}
