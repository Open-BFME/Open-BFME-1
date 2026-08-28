// readable body of ?findControlBarOverride@GameLogic@@QBE_NABVAsciiString@@HAAPBVCommandButton@@@Z: Code/GameEngine/Source/GameLogic/System/GameLogic.cpp
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
    bool findControlBarOverride(const AsciiString &, int, const CommandButton *&) const;
};

class GameLogicFindControlBarOverrideShim
{
public:
    bool find(const AsciiString &name, int slot, const CommandButton *&out) const;
};

bool GameLogic::findControlBarOverride(const AsciiString &name, int slot, const CommandButton *&out) const
{
    return ((const GameLogicFindControlBarOverrideShim *)this)->find(name, slot, out);
}
