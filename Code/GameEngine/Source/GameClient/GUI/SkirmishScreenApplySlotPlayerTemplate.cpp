// ?applySlotPlayerTemplate@BfmeAptScreenSkirmish@@QAE_NPAVGameSlot@@H@Z
// Retail 0x0057C890.  The secondary APT interface uses slot 4 for the
// player-template callback.  The body updates the slot and the local honors
// profile, then refreshes the profile display and writes the new slot list.

template <typename T> class StringBase
{
    friend class AsciiString;

private:
    StringBase( const StringBase<T> &other );
    ~StringBase();

    void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    static AsciiString TheEmptyString;

    AsciiString( const AsciiString &other )
        : StringBase<char>( other ) {}
    ~AsciiString() {}
};

class GameSlot
{
public:
    virtual void reset();

    int m_state;
    unsigned char m_accepted;
    unsigned char m_hasMap;
    unsigned char m_isMuted;
    unsigned char m_pad;
    int m_color;
    int m_startPos;
    int m_playerTemplate;
};

class PlayerTemplate
{
private:
    char m_pad[ 8 ];

public:
    AsciiString m_displayName;
};

class PlayerTemplateStore
{
public:
    const PlayerTemplate *getNthPlayerTemplate( int index ) const;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

class SkirmishBattleHonors
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual bool load();
    virtual bool write();

    void setPreferredSide( int value );
};

class Open2Pref09D050
{
public:
    void store( AsciiString value );
};

class SkirmishPreferences
{
public:
    void setSlotList();
};

class BfmeAptScreenSkirmish
{
public:
    bool applySlotPlayerTemplate( GameSlot *slot, int playerTemplate );
    void _bfme_updateProfileDisplay();

private:
    char m_pad[ 0x16c ];
    SkirmishBattleHonors m_honors;
};

// ?applySlotPlayerTemplate@BfmeAptScreenSkirmish@@QAE_NPAVGameSlot@@H@Z
bool BfmeAptScreenSkirmish::applySlotPlayerTemplate(
    GameSlot *slot, int playerTemplate )
{
    int templateIndex = playerTemplate;
    slot->m_playerTemplate = templateIndex;
    if( templateIndex <= -2 )
        slot->m_startPos = -1;

    if( slot->m_state == 5 )
    {
        if( templateIndex == -1 )
        {
            m_honors.setPreferredSide( templateIndex );
            ( (Open2Pref09D050 *)&m_honors )->store(
                AsciiString::TheEmptyString );
        }
        else if( templateIndex == -2 )
        {
            m_honors.setPreferredSide( templateIndex );
            ( (Open2Pref09D050 *)&m_honors )->store(
                AsciiString::TheEmptyString );
        }
        else
        {
            const PlayerTemplate *player =
                ThePlayerTemplateStore->getNthPlayerTemplate( templateIndex );
            if( player != 0 )
            {
                m_honors.setPreferredSide( templateIndex );
                ( (Open2Pref09D050 *)&m_honors )->store(
                    player->m_displayName );
            }
        }

        ( (BfmeAptScreenSkirmish *)( (char *)this - 0x258 ) )->_bfme_updateProfileDisplay();
    }

    ( (SkirmishPreferences *)&m_honors )->setSlotList();
    m_honors.write();
    return true;
}
