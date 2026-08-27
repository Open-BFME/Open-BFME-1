// Open-BFME: vtable-pointer release wrapper reconstructed from retail RVA 0x00933880.

extern "C" __declspec(dllimport) void __cdecl free(void *block);

class Rva00933880Object
{
public:
    void release(void);
};

void Rva00933880Object::release(void)
{
    free(*reinterpret_cast<void **>(this));
}
