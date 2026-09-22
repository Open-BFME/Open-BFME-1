// Retail 003433F0 / 727B: scoped ScriptEngine subroutine dispatch.
// The explicit scope-name, script-name and Team* arguments distinguish this
// entry from the ScriptAction* sibling at00343780. No named matched caller
// establishes the original method spelling, so the method retains its RVA.
// Native LatchRestore<Team*> saves this+1708C; LatchRestore<AsciiString>
// saves this+17088. The retail Team* latch vtable is VA010E75AC, whose slot0
// follows ILT0001976D to003377A0. Its native deleting destructor is39B exact,
// including restoring the saved pointer and conditional operator delete.
// AsciiString latch ctor/dtor and all ScriptEngine helpers were independently
// verified for the adjacent00343780 body; Team::getControllingPlayer follows
// ILT0002369B to000EC8F0 (team prototype+4 then owningPlayer+8).
// StringBase::isEmpty uses the definition in Source/string/StringBase.cpp.
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common

#include "ascii_string.h"
template<> inline bool StringBase<char>::isEmpty() const { return !m_data || m_data->length == 0; }
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

class Player;

class Team
{
public:
  Player *getControllingPlayer() const;
};

struct Rva003412E0Node;
class Rva00355950Arr;

class ScriptGroup
{
public:
  Rva003412E0Node *getScript() const { return *(Rva003412E0Node **)((const char *)this + 8); }
  bool isActive() const { return *(const unsigned char *)((const char *)this + 0x0C) != 0; }
  bool isSubroutine() const { return *(const unsigned char *)((const char *)this + 0x0D) != 0; }
};

class Script
{
public:
  bool isSubroutine() const { return *(const unsigned char *)((const char *)this + 0x17) != 0; }
};

#include "LatchRestore.h"

class ScriptEngine
{
protected:
  ScriptGroup *findGroup(AsciiString name, AsciiString *canonicalOut);
  Script *findScript(AsciiString name, AsciiString *canonicalOut);
  Rva00355950Arr *Rva0033C290(AsciiString *canonical);

public:
  void walkNamed(Rva00355950Arr *array, Rva003412E0Node *node, bool filter);
  void applyNamed(void *object, void *slot);
  void AppendDebugMessage(const AsciiString &message, bool forcePause);

protected:
  void Rva003433F0(const AsciiString &scopeName,
                   const AsciiString &scriptName,
                   Team *pThisTeam);
};

AsciiString Rva00195FC0JoinPath(const AsciiString &left, const AsciiString &right);

#define RVA003433F0_REPORT(HEADLINE) \
  do { \
    AppendDebugMessage(AsciiString(HEADLINE), false); \
    AppendDebugMessage(Rva00195FC0JoinPath(canonical, scriptName), false); \
  } while (0)

void ScriptEngine::Rva003433F0(const AsciiString &scopeName,
                               const AsciiString &scriptName,
                               Team *pThisTeam)
{
  if (scriptName.isEmpty())
    return;
  if (scriptName.compare("<none>") == 0)
    return;

  Player *savedPlayer = *(Player **)((char *)this + 0x170AC);
  Team **callingTeam = (Team **)((char *)this + 0x1708C);
  LatchRestore<Team *> callingTeamLatch(*callingTeam, pThisTeam);
  LatchRestore<AsciiString> scope(*(AsciiString *)((char *)this + 0x17088), scopeName);
  Team *activeTeam = *callingTeam;
  *(Team **)((char *)this + 0x17094) = 0;
  *(Player **)((char *)this + 0x170AC) = 0;
  if (activeTeam)
    *(Player **)((char *)this + 0x170AC) =
      activeTeam->getControllingPlayer();

  AsciiString canonical;
  ScriptGroup *group = findGroup(scriptName, &canonical);
  if (group) {
    if (group->isSubroutine()) {
      if (group->isActive()) {
        Rva00355950Arr *array = Rva0033C290(&canonical);
        if (array) {
          LatchRestore<AsciiString> restore(*(AsciiString *)((char *)this + 0x17088), canonical);
          walkNamed(array, group->getScript(), false);
        }
      }
    } else {
      RVA003433F0_REPORT("***Attempting to call script that is not a subroutine:***");
    }
  } else {
    Script *script = findScript(scriptName, &canonical);
    if (script) {
      if (script->isSubroutine()) {
        LatchRestore<AsciiString> restore(*(AsciiString *)((char *)this + 0x17088), canonical);
        applyNamed(script, (void *)&scriptName);
      } else {
        RVA003433F0_REPORT("***Attempting to call script that is not a subroutine:***");
      }
    } else {
      RVA003433F0_REPORT("***Script not defined:***");
    }
  }

  *(Player **)((char *)this + 0x170AC) = savedPlayer;
}
