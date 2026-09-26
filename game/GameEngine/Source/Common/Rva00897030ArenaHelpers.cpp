// cl: /DNDEBUG /MD /O2

extern char *g_bfmeArenaCursor;

char *Rva00897030Advance()
{
    return g_bfmeArenaCursor += 0x60;
}

char *Rva00897040Current()
{
    return g_bfmeArenaCursor;
}

class Rva008971C0Handler
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual bool dispatch();
};

bool Rva008971C0Dispatch(Rva008971C0Handler *handler)
{
    if (!handler)
        return false;
    return handler->dispatch();
}

class Rva0089C860State
{
public:
    Rva0089C860State *initialize(int value);
};

class Rva008976A0State : public Rva0089C860State
{
public:
    Rva008976A0State(int value);
};

Rva008976A0State::Rva008976A0State(int value)
{
    initialize(value);
}
