// The IAT slot is KERNEL32 InterlockedIncrement; the method name is address-derived.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *addend);

class Rva000874A0Object
{
public:
    void reset(void);
};

void Rva000874A0Object::reset(void)
{
    InterlockedIncrement(reinterpret_cast<long volatile *>(reinterpret_cast<char *>(this) + 4));
}
