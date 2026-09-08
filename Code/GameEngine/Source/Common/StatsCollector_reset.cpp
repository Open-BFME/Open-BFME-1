// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Include/Precompiled

#include "PreRTS.h"

// The retail body at 0x000A2F60 resets BFME's expanded stats record after it
// writes the new file header. The file-system call, StatsCollector call chain,
// field offsets, and GameLogic frame read identify this as StatsCollector::reset.
template <typename T>
class StringBase
{
    friend class AsciiString;

public:
    StringBase() : m_data( 0 ) {}

private:
    StringBase( const StringBase<T> &other );
    StringBase( const T *text );
    void releaseBuffer();

public:
    char *m_data;
};

class AsciiString : public StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
    AsciiString( const char *text ) : StringBase<char>( text ) {}
    ~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
};

class FileSystem
{
public:
    Bool createDirectory( AsciiString directory );
};

extern FileSystem *TheFileSystem;

class GameLogic
{
public:
    UnsignedInt getFrame() const { return m_frame; }

private:
    unsigned char m_unmodelled00[ 0x3C ];
    UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class StatsCollector
{
public:
    void reset();
    void collectUnitCountStats();

private:
    void createFileName();
    void writeInitialFileInfo();
    void writeStatInfo();
    void collectScoreKeeperStats();

    AsciiString m_statsFileName;
    UnsignedInt m_moneyWithdrawn;
    UnsignedInt m_moneyDeposited;
    UnsignedInt m_buildCommands;
    UnsignedInt m_moveCommands;
    UnsignedInt m_attackCommands;
    UnsignedInt m_scrollMapCommands;
    UnsignedInt m_aiUnits;
    UnsignedInt m_playerUnits;
    UnsignedInt m_alliesKilled;
    UnsignedInt m_neutralsKilled;
    UnsignedInt m_enemiesKilled;
    UnsignedInt m_scoreKeeperMoneySpent;
    UnsignedInt m_scoreKeeperMoneyEarned;
    UnsignedInt m_scoreKeeperUnitsDestroyed;
    UnsignedInt m_scoreKeeperUnitsBuilt;
    UnsignedInt m_scoreKeeperUnitsLost;
    UnsignedInt m_scoreKeeperBuildingsDestroyed;
    UnsignedInt m_scoreKeeperBuildingsBuilt;
    UnsignedInt m_scoreKeeperBuildingsLost;
    UnsignedInt m_scrollBeginTime;
    UnsignedInt m_scrollTime;
    Bool m_isScrolling;
    Int m_timeCount;
    Int m_lastUpdate;
    Int m_startFrame;
};

static char statsDir[ 255 ] = "Stats\\";

void StatsCollector::reset()
{
    TheFileSystem->createDirectory( AsciiString( statsDir ) );
    createFileName();
    writeInitialFileInfo();
    collectUnitCountStats();
    writeStatInfo();

    m_buildCommands = 0;
    m_moveCommands = 0;
    m_attackCommands = 0;
    m_scrollMapCommands = 0;
    m_aiUnits = 0;
    m_playerUnits = 0;
    m_scrollTime = 0;
    m_moneyDeposited = 0;
    m_moneyWithdrawn = 0;
    m_scoreKeeperMoneySpent = 0;
    m_scoreKeeperMoneyEarned = 0;
    m_scoreKeeperUnitsDestroyed = 0;
    m_scoreKeeperUnitsBuilt = 0;
    m_scoreKeeperUnitsLost = 0;
    m_scoreKeeperBuildingsDestroyed = 0;
    m_scoreKeeperBuildingsBuilt = 0;
    m_scoreKeeperBuildingsLost = 0;
    m_alliesKilled = 0;
    m_neutralsKilled = 0;
    m_enemiesKilled = 0;
    collectScoreKeeperStats();
    m_lastUpdate = TheGameLogic->getFrame();
}
