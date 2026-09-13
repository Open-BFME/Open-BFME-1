// cl: /DNDEBUG /MD /EHsc
// readable body of ?onExit@AIAttackState@@UAEXW4StateExitType@@@Z: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// Open-BFME5: lift MASM dump to standalone C++ thunk.

enum StateExitType { EXIT_NORMAL = 0 };
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIAttackState
{
public:
	virtual void onExit(StateExitType);
};

// ?onExit@AIAttackState@@UAEXW4StateExitType@@@Z
__declspec(naked) void AIAttackState::onExit(StateExitType)
{
	__asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x1b
        __emit 0x64
        __emit 0x00
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xec
        __emit 0x08
        __emit 0x56
        __emit 0x57
        __emit 0x6a
        __emit 0x44
        __emit 0x8b
        __emit 0xf9
        __emit 0xe8
        __emit 0x0d
        __emit 0xd3
        __emit 0x6f
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x74
        __emit 0x1c
        __emit 0x51
        __emit 0x89
        __emit 0x64
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0xcc
        __emit 0x68
        __emit 0x48
        __emit 0xb3
        __emit 0x09
        __emit 0x01
        __emit 0xe8
        __emit 0x79
        __emit 0x3f
        __emit 0x70
        __emit 0x00
        __emit 0x8b
        __emit 0x47
        __emit 0x10
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xa0
        __emit 0x4c
        __emit 0xea
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x10
        __emit 0x5f
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5e
        __emit 0x83
        __emit 0xc4
        __emit 0x14
        __emit 0xc3
	}
}
