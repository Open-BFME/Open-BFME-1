// Open-BFME: lock-pointer release wrapper reconstructed from retail RVA 0x009ECAC0.

extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *lock);

class Rva009ECAC0Object
{
public:
    void release(void);
};

void Rva009ECAC0Object::release(void)
{
    LeaveCriticalSection(*reinterpret_cast<void **>(this));
}
