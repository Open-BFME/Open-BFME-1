#pragma once

// PLAYER=0, SCRIPT=1 and AI=2 have independent BFME evidence; values 3-4 follow Zero Hour.
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
// Historical BFME declaration: e02bb973f0:game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateIdle.cpp
enum CommandSourceType
{
    CMD_FROM_PLAYER = 0,
    CMD_FROM_SCRIPT = 1,
    CMD_FROM_AI = 2,
    CMD_FROM_DOZER = 3,
    CMD_DEFAULT_SWITCH_WEAPON = 4
};
