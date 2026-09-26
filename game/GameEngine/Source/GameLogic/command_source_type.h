#pragma once

// The global command-source enum and values follow the shipped GameCommon declaration.
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
// BFME AIUpdateInterfacePrivateIdle.cpp also declares this sequence.
enum CommandSourceType
{
    CMD_FROM_PLAYER = 0,
    CMD_FROM_SCRIPT = 1,
    CMD_FROM_AI = 2,
    CMD_FROM_DOZER = 3,
    CMD_DEFAULT_SWITCH_WEAPON = 4
};
