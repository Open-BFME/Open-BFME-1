// BFME placement-delete helpers emitted by the Dozer state memory-pool glue.
// The three class-specific functions share retail body 0x007EFFF0 (12 bytes).

extern "C" void __cdecl free(void *);

class DozerActionState
{
public:
    enum DozerActionStateMagicEnum { DOZER_ACTION_STATE_GLUE_NOT_IMPLEMENTED = 0 };
    static void operator delete(void *p, DozerActionStateMagicEnum);
};

class DozerPrimaryIdleState
{
public:
    enum DozerPrimaryIdleStateMagicEnum { DOZER_PRIMARY_IDLE_STATE_GLUE_NOT_IMPLEMENTED = 0 };
    static void operator delete(void *p, DozerPrimaryIdleStateMagicEnum);
};

class DozerPrimaryGoingHomeState
{
public:
    enum DozerPrimaryGoingHomeStateMagicEnum { DOZER_PRIMARY_GOING_HOME_STATE_GLUE_NOT_IMPLEMENTED = 0 };
    static void operator delete(void *p, DozerPrimaryGoingHomeStateMagicEnum);
};

void DozerActionState::operator delete(void *p, DozerActionStateMagicEnum)
{
    free(p);
}

void DozerPrimaryIdleState::operator delete(void *p, DozerPrimaryIdleStateMagicEnum)
{
    free(p);
}

void DozerPrimaryGoingHomeState::operator delete(void *p, DozerPrimaryGoingHomeStateMagicEnum)
{
    free(p);
}
