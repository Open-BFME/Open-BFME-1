// cl: /DNDEBUG /MD

extern "C" __declspec(dllimport) void __cdecl free(void *);

struct Rva0086FD80Callback
{
    unsigned char pad[0x14];
    void *data;
};

void Rva0086FD80FreeCallback(Rva0086FD80Callback *callback)
{
    free(callback->data);
}
