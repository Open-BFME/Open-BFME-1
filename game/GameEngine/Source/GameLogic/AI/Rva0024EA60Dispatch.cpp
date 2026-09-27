// cl: /DNDEBUG /MD /O2 /Ob2
// Retail 0x0024EA60: ECX receiver and one pointer argument, ret 4.
// The first route forwards the receiver and argument to the byte-verified
// C++ helper at 0x0024E990; the second remains the distinct ILT 0x00041506.

class Object;
class Rva0024E990Owner
{
public:
    void rva0024e990(Object *other);
};

extern void j_00041506();

class Rva0002F8DD
{
public:
    __declspec(noinline) void forward(void *argument);
};

void Rva0002F8DD::forward(void *argument)
{
    reinterpret_cast<Rva0024E990Owner *>(this)->rva0024e990(
        reinterpret_cast<Object *>(argument));
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
