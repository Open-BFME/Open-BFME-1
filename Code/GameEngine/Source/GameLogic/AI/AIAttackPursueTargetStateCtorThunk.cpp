// cl: /DNDEBUG /MD /EHsc

class StateMachine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIAttackPursueTargetState
{
public:
    AIAttackPursueTargetState(StateMachine*, bool, bool, bool);
};

__declspec(naked) AIAttackPursueTargetState::AIAttackPursueTargetState(StateMachine*, bool, bool, bool)
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
        _emit 20h
        _emit 0A6h
        _emit 09h
        _emit 01h
        _emit 0E8h
        _emit 0ABh
        _emit 94h
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
        _emit 61h
        _emit 2Ah
        _emit 0EBh
        _emit 0FFh
        _emit 8Ah
        _emit 4Ch
        _emit 24h
        _emit 10h
        _emit 8Ah
        _emit 54h
        _emit 24h
        _emit 14h
        _emit 33h
        _emit 0C0h
        _emit 0C7h
        _emit 06h
        _emit 0C8h
        _emit 0A5h
        _emit 09h
        _emit 01h
        _emit 89h
        _emit 46h
        _emit 50h
        _emit 89h
        _emit 46h
        _emit 54h
        _emit 89h
        _emit 46h
        _emit 58h
        _emit 89h
        _emit 46h
        _emit 5Ch
        _emit 88h
        _emit 46h
        _emit 62h
        _emit 8Ah
        _emit 44h
        _emit 24h
        _emit 18h
        _emit 88h
        _emit 46h
        _emit 64h
        _emit 88h
        _emit 4Eh
        _emit 60h
        _emit 88h
        _emit 56h
        _emit 61h
        _emit 0C6h
        _emit 46h
        _emit 63h
        _emit 01h
        _emit 8Bh
        _emit 0C6h
        _emit 5Eh
        _emit 59h
        _emit 0C2h
        _emit 10h
        _emit 00h
    }
}

