// Open-BFME: lock-field wrappers reconstructed from retail RVAs 0x0010B660
// and 0x0010B670.

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *lock);

class Rva0010B660Lock
{
public:
    void enter(void);
    void leave(void);

private:
    char m_pad0[0x70];
};

void Rva0010B660Lock::enter(void)
{
    EnterCriticalSection(reinterpret_cast<char *>(this) + 0x70);
}

void Rva0010B660Lock::leave(void)
{
    LeaveCriticalSection(reinterpret_cast<char *>(this) + 0x70);
}
