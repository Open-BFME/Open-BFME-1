// Open-BFME: probe forwarder reconstructed from retail RVA 0x0082AD60.

extern "C" __declspec(dllimport) int __stdcall InterlockedExchange(
    void *object, int flag);

void Rva0082AD60Invoke(void *object, int flag)
{
    InterlockedExchange(object, flag);
}
