// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline

#include "StringInline.h"

// ScriptActions::executeAction reaches this body for RESUME_SUPPLY_TRUCKING.
// The player-mask loop and the fallback field at Player+0x2c match the BFME
// rewrite of the Zero Hour action.

typedef bool Bool;
typedef int Int;
typedef unsigned short PlayerMaskType;

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
    PlayerMaskType getPlayerMaskFromAsciiString(const AsciiString &name,
        Bool *found);
};

// 0x012F076C is the game's ScriptEngine *TheScriptEngine, defined once in
// ScriptEngine.cpp.  This TU sees only the player-mask entry point, so it
// keeps the local view and casts the canonical global to it.
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

static __forceinline BfmeScriptEngine_getPlayerMaskFromAsciiString *
bfmeScriptEngine(void)
{
    return (BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine;
}

class Player
{
public:
    void setUnitsShouldIdleOrResume(Bool idle);
};

class PlayerList
{
public:
    Player *getEachPlayerFromMask(PlayerMaskType &mask);
    Player *getNthPlayer(Int index);

    Int getPlayerCount() const
    {
        return m_playerCount;
    }

    unsigned char m_beforePlayerCount[0x10];
    Int m_playerCount;
};

extern PlayerList *ThePlayerList;

class ScriptActions
{
protected:
    void doResumeSupplyTruckingForIdleUnits(const AsciiString &playerName);
};

void ScriptActions::doResumeSupplyTruckingForIdleUnits(
    const AsciiString &playerName)
{
    PlayerMaskType playerMask =
        bfmeScriptEngine()->getPlayerMaskFromAsciiString(playerName, 0);
    if (!playerMask)
    {
        for (Int i = 0; i < ThePlayerList->getPlayerCount(); ++i)
        {
            Player *player = ThePlayerList->getNthPlayer(i);
            if (!*reinterpret_cast<Int *>(
                    reinterpret_cast<unsigned char *>(player) + 0x2c))
                player->setUnitsShouldIdleOrResume(false);
        }
        return;
    }

    do
    {
        Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
        if (player)
            player->setUnitsShouldIdleOrResume(false);
    } while (playerMask);
}
