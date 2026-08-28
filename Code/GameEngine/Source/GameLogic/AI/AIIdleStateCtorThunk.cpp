// cl: /DNDEBUG /MD /EHsc

class StateMachine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIIdleState
{
public:
    enum AIIdleTargetingType
    {
    };

    AIIdleState(StateMachine *, AIIdleTargetingType);
};

__declspec(naked) AIIdleState::AIIdleState(StateMachine *, AIIdleTargetingType)
{
    __asm {
        _emit 051h
        _emit 056h
        _emit 051h
        _emit 08Bh
        _emit 0F1h
        _emit 089h
        _emit 064h
        _emit 024h
        _emit 008h
        _emit 08Bh
        _emit 0CCh
        _emit 068h
        _emit 004h
        _emit 086h
        _emit 009h
        _emit 001h
        _emit 0E8h
        _emit 08Bh
        _emit 088h
        _emit 070h
        _emit 000h
        _emit 08Bh
        _emit 044h
        _emit 024h
        _emit 010h
        _emit 050h
        _emit 08Bh
        _emit 0CEh
        _emit 0E8h
        _emit 071h
        _emit 032h
        _emit 0E8h
        _emit 0FFh
        _emit 08Bh
        _emit 04Ch
        _emit 024h
        _emit 010h
        _emit 032h
        _emit 0C0h
        _emit 088h
        _emit 046h
        _emit 027h
        _emit 088h
        _emit 046h
        _emit 02Ch
        _emit 0C6h
        _emit 046h
        _emit 026h
        _emit 001h
        _emit 066h
        _emit 0C7h
        _emit 046h
        _emit 024h
        _emit 0FFh
        _emit 0FFh
        _emit 0C7h
        _emit 006h
        _emit 020h
        _emit 0ADh
        _emit 009h
        _emit 001h
        _emit 089h
        _emit 04Eh
        _emit 028h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 059h
        _emit 0C2h
        _emit 008h
        _emit 000h
    }
}
