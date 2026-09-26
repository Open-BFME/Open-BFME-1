// cl: /DNDEBUG /MD

__declspec(dllimport) void __cdecl bfmeFree1035(void *);

struct Rva0086FD80Callback
{
    unsigned char pad[0x14];
    void *data;
};

void Rva0086FD80FreeCallback(Rva0086FD80Callback *callback)
{
    bfmeFree1035(callback->data);
}
