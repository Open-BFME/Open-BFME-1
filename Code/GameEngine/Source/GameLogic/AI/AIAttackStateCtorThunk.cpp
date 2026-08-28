// cl: /DNDEBUG /MD /EHsc
// readable body of ??0AIAttackState@@QAE@PAVStateMachine@@_N11PAVAttackExitConditionsInterface@@@Z: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp

class StateMachine;
class AttackExitConditionsInterface;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIAttackState
{
public:
    AIAttackState(StateMachine*, bool, bool, bool, AttackExitConditionsInterface*);
};

__declspec(naked) AIAttackState::AIAttackState(StateMachine*, bool, bool, bool, AttackExitConditionsInterface*)
{
    __asm {
        _emit 51h
        _emit 56h
        _emit 51h
        _emit 8Bh
        _emit 0F1h
        _emit 89h
        _emit 64h
        _emit 24h
        _emit 08h
        _emit 8Bh
        _emit 0CCh
        _emit 68h
        _emit 24h
        _emit 0A1h
        _emit 09h
        _emit 01h
        _emit 0E8h
        _emit 9Bh
        _emit 0C2h
        _emit 70h
        _emit 00h
        _emit 8Bh
        _emit 44h
        _emit 24h
        _emit 10h
        _emit 50h
        _emit 8Bh
        _emit 0CEh
        _emit 0E8h
        _emit 81h
        _emit 6Ch
        _emit 0E8h
        _emit 0FFh
        _emit 8Bh
        _emit 4Ch
        _emit 24h
        _emit 1Ch
        _emit 8Ah
        _emit 54h
        _emit 24h
        _emit 10h
        _emit 0C7h
        _emit 46h
        _emit 24h
        _emit 0E0h
        _emit 76h
        _emit 09h
        _emit 01h
        _emit 33h
        _emit 0C0h
        _emit 89h
        _emit 46h
        _emit 28h
        _emit 89h
        _emit 4Eh
        _emit 2Ch
        _emit 8Ah
        _emit 4Ch
        _emit 24h
        _emit 14h
        _emit 89h
        _emit 46h
        _emit 30h
        _emit 0C7h
        _emit 06h
        _emit 0C8h
        _emit 0A0h
        _emit 09h
        _emit 01h
        _emit 0C7h
        _emit 46h
        _emit 24h
        _emit 0B0h
        _emit 0A0h
        _emit 09h
        _emit 01h
        _emit 89h
        _emit 46h
        _emit 40h
        _emit 88h
        _emit 56h
        _emit 44h
        _emit 8Ah
        _emit 54h
        _emit 24h
        _emit 18h
        _emit 89h
        _emit 46h
        _emit 48h
        _emit 88h
        _emit 46h
        _emit 4Ch
        _emit 88h
        _emit 46h
        _emit 4Dh
        _emit 88h
        _emit 4Eh
        _emit 45h
        _emit 88h
        _emit 56h
        _emit 46h
        _emit 0C7h
        _emit 46h
        _emit 50h
        _emit 03h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 89h
        _emit 46h
        _emit 34h
        _emit 89h
        _emit 46h
        _emit 38h
        _emit 89h
        _emit 46h
        _emit 3Ch
        _emit 8Bh
        _emit 0C6h
        _emit 5Eh
        _emit 59h
        _emit 0C2h
        _emit 14h
        _emit 00h
    }
}

