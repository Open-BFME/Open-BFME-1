// Open-BFME: lock-pointer release wrapper reconstructed from retail RVA 0x009ECAC0.

extern "C" __declspec(dllimport) void __stdcall Rva01358E74Leave(void *lock);

class Rva009ECAC0Object
{
public:
    void release(void);
};

void Rva009ECAC0Object::release(void)
{
    Rva01358E74Leave(*reinterpret_cast<void **>(this));
}
