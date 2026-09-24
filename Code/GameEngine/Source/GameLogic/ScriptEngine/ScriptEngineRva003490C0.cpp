// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common
// Retail 0x003490C0, 160 bytes. The method spelling is not established;
// matched ScriptEngine siblings prove the scope latch and field offsets.

#include "ascii_string.h"
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
#include "LatchRestore.h"

class Player;
class ScriptAction;

class Team
{
public:
    Player *getControllingPlayer() const;
};

class ScriptEngine
{
protected:
    void executeActions(ScriptAction *head);
public:
    void Rva003490C0(const AsciiString &scopeName,
                     ScriptAction *action, Team *team);
};

void ScriptEngine::Rva003490C0(const AsciiString &scopeName,
                               ScriptAction *action, Team *team)
{
    Team *savedTeam = *(Team **)((char *)this + 0x1708C);
    Player *savedPlayer = *(Player **)((char *)this + 0x170AC);
    LatchRestore<AsciiString> scope(
        *(AsciiString *)((char *)this + 0x17088), scopeName);

    *(Team **)((char *)this + 0x1708C) = team;
    *(Player **)((char *)this + 0x170AC) = 0;
    if (team)
        *(Player **)((char *)this + 0x170AC) = team->getControllingPlayer();

    executeActions(action);

    *(Team **)((char *)this + 0x1708C) = savedTeam;
    *(Player **)((char *)this + 0x170AC) = savedPlayer;
}
