// cl: /DNDEBUG /MD /O2 /Ob2
// Retail 0x0024EA60: ECX receiver and one pointer argument, ret 4.
// The old Pathfinder name resolved both calls to unrelated routines. Keep
// the owner address-derived and preserve the two actual retail routes.
// 0x0002F8DD is the five-byte forwarding entry to generated body 0x0024E990.

extern void d_0024e990();
extern void j_00041506();

class Rva0002F8DD
{
public:
    __declspec(noinline) void forward(void *argument);
};

void Rva0002F8DD::forward(void *argument)
{
    typedef void (Rva0002F8DD::*Call)(void *);
    union { void (*raw)(); Call member; } call;
    call.raw = d_0024e990;
    (this->*call.member)(argument);
}

class Rva0024EA60
{
public:
    void dispatch(void *argument);
};

void Rva0024EA60::dispatch(void *argument)
{
    reinterpret_cast<Rva0002F8DD *>(this)->forward(argument);
    typedef void (Rva0024EA60::*Call)(void *);
    union { void (*raw)(); Call member; } call;
    call.raw = j_00041506;
    (this->*call.member)(argument);
}
