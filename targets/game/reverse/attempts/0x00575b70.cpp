// ?_bfme_populateSinglePlayer@BfmeAptScreenScoreScreen@@QAEXXZ
// partial score=0.35 date=2026-09-20
// BFME ScoreScreen single-player population candidate.
// The helper declarations follow the decoded retail calls and existing shims.
// This file is an untracked probe candidate until byte verification succeeds.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline /ICode/Libraries/Source/WWVegas/WWLib

typedef char Bool;

template <typename T> class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;

private:
    StringBase() : m_data( 0 ) {}
    StringBase( const T *text );
    StringBase( const StringBase<T> &other );
    ~StringBase();
    void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString( const char *text ) : StringBase<char>( text ) {}
    AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
    ~AsciiString() {}
    void __cdecl format( AsciiString format, ... );
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString() : StringBase<unsigned short>() {}
    UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
    UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
    ~UnicodeString() {}
    void translate( const AsciiString &text );
    void set( const UnicodeString &text );
    void set( const unsigned short *text, int length );
    void concat( const unsigned short *text, int length );
};

class GameTextInterface
{
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual UnicodeString fetch( AsciiString text, Bool *exists = 0 );
};

class WindowManager
{
public:
    void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
};

class BfmeThingBIF
{
public:
    void bfmeGoBIF( void *what, void *out );
};

class BfmeTableAI
{
public:
    AsciiString bfmeNumberedAI( int number );
};

class ScoreKeeper
{
public:
    int getTotalUnitsDestroyed();
    int getTotalBuildingsDestroyed();
    int getTimeTakenScore();
    int countMissionObjectives( int *completed );
    int calculateScore();
    int computeFirst();
    int computeSecond();
};

class CampaignManager
{
public:
    int getMissionObjectiveCount();
    Bool isMissionObjectiveEligible( int index );
    Bool isMissionObjectiveIndexed( int index );
    Bool isMissionObjectiveComplete( int index );
    AsciiString objectiveName( int index );
};

class Registry
{
public:
    void *findTemplate( AsciiString name );
};

class LivingWorldArmy
{
public:
    AsciiString getName() const;
};

class ThingTemplatePortraitShim
{
public:
    const void *getSelectedPortraitImage() const;
};

class GroupRoom
{
public:
    GroupRoom( const GroupRoom &other );
};

class RegionManager
{
public:
    void *findRegion( const AsciiString &name );
};

class BfmeAptScreenScoreScreen : public BfmeTableAI
{
public:
    void _bfme_populateSinglePlayer();
    void _bfme_setScoreRegionBonus( int *index, const AsciiString &label, int value );
    void _bfme_setTerritoryBonus( int group, int kind, int value );

private:
    char m_unmodelled[ 0x334 ];
};

struct PlayerListView
{
    char pad[ 0xc ];
    char *local;
};

struct GlobalDataView
{
    char pad1224[ 0x1224 ];
    int w1224;
    int w1228;
    int w122c;
    int w1230;
    int w1234;
    int w1238;
    int w123c;
    int w1240;
    int w1244;
    int w1248;
    int w124c;
    int w1250;
};

struct LocalListView
{
    char *begin;
    char *end;
    char *unused;
};

struct BitVectorView
{
    unsigned int *words;
    unsigned int *end;
    unsigned int bit;
};

extern WindowManager *g_theWindowManager;
extern GameTextInterface *TheGameText;
extern PlayerListView *ThePlayers;
extern GlobalDataView *TheWritableGlobalData;
extern CampaignManager *TheCampaignManager;
extern char *TheBfmeGameLogic;
extern Registry *TheRegistry;
extern BfmeThingBIF *TheManager;

#define ThePlayers (*(PlayerListView **)0x012ed748)
#define TheWritableGlobalData (*(GlobalDataView **)0x012ed5c8)
#define TheCampaignManager (*(CampaignManager **)0x012f1028)
#define TheBfmeGameLogic (*(char **)0x012f0898)
#define TheRegistry (*(Registry **)0x012ef1d8)
#define TheManager (*(BfmeThingBIF **)0x012f19e8)

extern "C" unsigned int __cdecl bfmeLenVGI( const unsigned short *text );
extern "C" void __cdecl copyBits( void *first, void *last, void *out );
extern "C" void __cdecl buildRows( void *first, void *last, int shift, void *out, void *player );
extern "C" void __cdecl sortRows( void *first, void *last, void *compare );
extern "C" void __cdecl copyRow( void *out, void *first, void *last, void *source );
extern "C" void __cdecl initLocalList( void *list );
extern "C" void __cdecl appendPortrait( void *list, void *prev, void *value, void *out, int one, int two );

void BfmeAptScreenScoreScreen::_bfme_populateSinglePlayer()
{
    char *self = (char *)this;
    register char *player = 0;
    PlayerListView *players;
    register char *score = 0;
    register int *battle;
    int zero = 0;

    *(int *)( self + 0x25c ) = zero;
    players = ThePlayers;
    if( players != 0 )
        player = players->local;
    if( player != 0 )
        score = player + 0x348;
    if( score == 0 )
        return;

    *(int *)( self + 0x294 ) = *(int *)( score + 0x8c );
    battle = (int *)( self + 0x298 );
    *(int *)( self + 0x298 ) = TheWritableGlobalData->w1224;
    *(int *)( self + 0x2a0 ) = ((ScoreKeeper *)score)->getTotalUnitsDestroyed();
    *(int *)( self + 0x2a4 ) = TheWritableGlobalData->w1228;
    *(int *)( self + 0x2ac ) = *(int *)( score + 0x114 );
    *(int *)( self + 0x2b0 ) = TheWritableGlobalData->w122c;
    *(int *)( self + 0x2dc ) = ((ScoreKeeper *)score)->getTotalBuildingsDestroyed();
    *(int *)( self + 0x2e0 ) = TheWritableGlobalData->w1230;
    *(int *)( self + 0x2b8 ) = *(int *)( score + 0x124 );
    *(int *)( self + 0x2bc ) = TheWritableGlobalData->w1244;
    *(int *)( self + 0x2c4 ) = *(int *)( score + 4 );
    *(int *)( self + 0x2c8 ) = TheWritableGlobalData->w1240;
    *(int *)( self + 0x2d0 ) = ((ScoreKeeper *)score)->getTimeTakenScore();
    *(int *)( self + 0x2d4 ) = 1;

    *(int *)( self + 0x278 ) = 0;
    for( int i = 0; i < 7; ++i )
    {
        battle[2] = battle[0] * battle[1];
        *(int *)( self + 0x278 ) += battle[2];
        battle += 3;
    }

    CampaignManager *campaign = TheCampaignManager;
    if( campaign == 0 )
        return;

    *(int *)( self + 0x304 ) = 0;
    int objectives = campaign->getMissionObjectiveCount();
    for( int objective = 0; objective < objectives; ++objective )
    {
        if( !campaign->isMissionObjectiveEligible( objective ) )
            continue;
        if( !campaign->isMissionObjectiveIndexed( objective ) )
            continue;

        int row = *(int *)( self + 0x304 );
        *(unsigned char *)( self + 0x308 + row ) =
            campaign->isMissionObjectiveComplete( objective );

        AsciiString key;
        key.format( (AsciiString)"APT:objective%d", row + 1 );
        AsciiString label = campaign->objectiveName( objective );
        UnicodeString text = TheGameText->fetch( label );
        g_theWindowManager->bfme_setAptText( key, text );
        *(int *)( self + 0x304 ) = row + 1;
    }

    *(int *)( self + 0x27c ) =
        ((ScoreKeeper *)score)->countMissionObjectives( 0 ) *
        TheWritableGlobalData->w123c;

    if( TheBfmeGameLogic == 0 || TheRegistry == 0 )
        return;

    {
    LocalListView list = { 0, 0, 0 };
    initLocalList( &list );
    unsigned int count = (unsigned int)( list.end - list.begin ) / 4;
    unsigned int pos = 0;
    void *out = 0;
    void *outEnd = 0;
    void *last = 0;
    while( pos < count )
    {
        char *entry = ((char **)list.begin)[pos];
        if( entry != 0 )
        {
            int frame = *(int *)( entry + 0x34 ) - *(int *)( entry + 0x30 );
            int index = frame / 0x80;
            AsciiString name = ((LivingWorldArmy *)( *(char **)( entry + 0x30 ) + index ))->getName();
            void *templateObject = TheRegistry->findTemplate( name );
            if( templateObject != 0 && (*(unsigned int *)( (char *)templateObject + 0xd0 ) & 0x02000000) != 0 )
            {
                void *portrait = (void *)((ThingTemplatePortraitShim *)templateObject)->getSelectedPortraitImage();
                int selected = *(int *)( (char *)templateObject + 0x4d0 );
                unsigned char image = *(unsigned char *)( *(char **)( entry + 0x30 ) + 0x39 );
                if( last != 0 )
                {
                    *(int *)last = selected;
                    *(int *)( (char *)last + 4 ) = image;
                    *(int *)( (char *)last + 8 ) = (int)portrait;
                    last = (char *)last + 0xc;
                    outEnd = last;
                }
                else
                {
                    appendPortrait( &list, last, portrait, &out, 1, 1 );
                    last = outEnd;
                }
            }
        }
        ++pos;
    }

    if( out != 0 )
    {
        unsigned int rows = (unsigned int)(((char *)outEnd - (char *)out) / 12);
        if( rows != 0 )
        {
            sortRows( out, outEnd, this );
            buildRows( out, outEnd, (int)( rows * 2 ), &list, player );
            if( rows > 0x10 )
                copyRow( out, outEnd, &list, score );
        }
    }
    }

    BitVectorView *bits = (BitVectorView *)( self + 0x2e8 );
    BitVectorView sourceBits = { bits->words, bits->end, bits->bit };
    copyBits( &sourceBits, bits, bits );
    unsigned int upgrades = 0;
    if( bits->words != 0 )
    {
        unsigned int *word = bits->words;
        unsigned int *end = bits->end;
        while( word != end )
        {
            unsigned int value = *word++;
            for( unsigned int bit = 0; bit < 32; ++bit )
                if( ( value & ( 1U << bit ) ) != 0 )
                    ++upgrades;
        }
    }
    *(int *)( score + 0x11c ) = upgrades;

    int heroValue = TheWritableGlobalData->w1234 * (int)upgrades;
    *(int *)( self + 0x280 ) = heroValue;
    {
    UnicodeString heroText;
    heroText.translate( ((BfmeTableAI *)this)->bfmeNumberedAI( TheWritableGlobalData->w1234 ) );
    heroText.set( (const unsigned short *)L"x ", 2 );
    AsciiString heroLabel( "APT:HeroPointsIncrement" );
    g_theWindowManager->bfme_setAptText( heroLabel, heroText );
    }

    *(int *)( self + 0x2fc ) = *(int *)( score + 0x120 );
    int unitValue = TheWritableGlobalData->w1238 * *(int *)( score + 0x120 );
    *(int *)( self + 0x284 ) = unitValue;
    {
    UnicodeString unitText;
    unitText.translate( ((BfmeTableAI *)this)->bfmeNumberedAI( TheWritableGlobalData->w1238 ) );
    unitText.set( (const unsigned short *)L"x ", 2 );
    AsciiString unitLabel( "APT:UnitPointsIncrement" );
    g_theWindowManager->bfme_setAptText( unitLabel, unitText );
    }

    ((UnicodeString *)( self + 0x300 ))->set(
        *(const UnicodeString *)( player + 0x28 ) );
    *(int *)( self + 0x288 ) = 0;
    if( TheCampaignManager != 0 )
    {
        for( int region = 0; region < 4; ++region )
        {
            AsciiString army( "LW:RegionBonusArmy" );
            AsciiString legendary( "LW:RegionLegendaryBonus" );
            AsciiString resource( "LW:RegionBonusResource" );
            TheManager->bfmeGoBIF( &army, &region );
            TheManager->bfmeGoBIF( &legendary, &region );
            TheManager->bfmeGoBIF( &resource, &region );
        }
    }

    int scoreRegion = 0;
    AsciiString armyLabel( "Result/Infos/ScoreMap/Picture/Image" );
    _bfme_setScoreRegionBonus( &scoreRegion, armyLabel, *(int *)( score + 0x12c ) );
    AsciiString legendaryLabel( "SubMenus/TerritoryBonus/TerritoryMap/TerritoryMap/Picture/Image" );
    _bfme_setScoreRegionBonus( &scoreRegion, legendaryLabel, *(int *)( score + 0x134 ) );
    AsciiString resourceLabel( "APT:ScoreMapName" );
    _bfme_setScoreRegionBonus( &scoreRegion, resourceLabel, *(int *)( score + 0x130 ) );

    _bfme_setTerritoryBonus( 0, 0, *(int *)( score + 0x12c ) );
    _bfme_setTerritoryBonus( 0, 1, TheWritableGlobalData->w1248 );
    _bfme_setTerritoryBonus( 0, 2, TheWritableGlobalData->w1248 * *(int *)( score + 0x12c ) );
    _bfme_setTerritoryBonus( 1, 0, *(int *)( score + 0x134 ) );
    _bfme_setTerritoryBonus( 1, 1, TheWritableGlobalData->w1250 );
    _bfme_setTerritoryBonus( 1, 2, TheWritableGlobalData->w1250 * *(int *)( score + 0x134 ) );
    _bfme_setTerritoryBonus( 2, 0, *(int *)( score + 0x130 ) );
    _bfme_setTerritoryBonus( 2, 1, TheWritableGlobalData->w124c );
    _bfme_setTerritoryBonus( 2, 2, TheWritableGlobalData->w124c * *(int *)( score + 0x130 ) );
    *(int *)( self + 0x288 ) = ((ScoreKeeper *)score)->computeFirst();
    *(int *)( self + 0x28c ) = ((ScoreKeeper *)score)->computeSecond();
}
