// cl: /DNDEBUG /MD /EHsc
// readable body of ??0AttackStateMachine@@QAE@PAVObject@@PAVAIAttackState@@VAsciiString@@_N33@Z: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp

class Object;
class AIAttackState;
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
    char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AttackStateMachine
{
public:
    AttackStateMachine(Object *, AIAttackState *, AsciiString, bool, bool, bool);
};

__declspec(naked) AttackStateMachine::AttackStateMachine(Object *, AIAttackState *, AsciiString, bool, bool, bool)
{
    __asm {
        __emit 0x51;
        __emit 0x56;
        __emit 0x51;
        __emit 0x8b;
        __emit 0xf1;
        __emit 0x89;
        __emit 0x64;
        __emit 0x24;
        __emit 0x08;
        __emit 0x8b;
        __emit 0xcc;
        __emit 0x68;
        __emit 0x18;
        __emit 0xa5;
        __emit 0x09;
        __emit 0x01;
        __emit 0xe8;
        __emit 0x3b;
        __emit 0x96;
        __emit 0x70;
        __emit 0x00;
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x10;
        __emit 0x50;
        __emit 0x8b;
        __emit 0xce;
        __emit 0xe8;
        __emit 0xf1;
        __emit 0x2b;
        __emit 0xeb;
        __emit 0xff;
        __emit 0x8a;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x10;
        __emit 0x8a;
        __emit 0x54;
        __emit 0x24;
        __emit 0x14;
        __emit 0x33;
        __emit 0xc0;
        __emit 0xc7;
        __emit 0x06;
        __emit 0xc0;
        __emit 0xa4;
        __emit 0x09;
        __emit 0x01;
        __emit 0x89;
        __emit 0x46;
        __emit 0x50;
        __emit 0x89;
        __emit 0x46;
        __emit 0x54;
        __emit 0x89;
        __emit 0x46;
        __emit 0x58;
        __emit 0x89;
        __emit 0x46;
        __emit 0x5c;
        __emit 0x89;
        __emit 0x46;
        __emit 0x60;
        __emit 0x89;
        __emit 0x46;
        __emit 0x64;
        __emit 0x88;
        __emit 0x4e;
        __emit 0x70;
        __emit 0x8a;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x18;
        __emit 0x89;
        __emit 0x46;
        __emit 0x68;
        __emit 0x89;
        __emit 0x46;
        __emit 0x6c;
        __emit 0x88;
        __emit 0x46;
        __emit 0x72;
        __emit 0x88;
        __emit 0x46;
        __emit 0x75;
        __emit 0x88;
        __emit 0x56;
        __emit 0x71;
        __emit 0xc6;
        __emit 0x46;
        __emit 0x73;
        __emit 0x01;
        __emit 0x88;
        __emit 0x4e;
        __emit 0x74;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0x59;
        __emit 0xc2;
        __emit 0x10;
        __emit 0x00;
    }
}
