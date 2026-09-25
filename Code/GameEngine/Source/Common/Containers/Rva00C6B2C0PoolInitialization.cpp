// Retail 00C6B2C0 initializes storage at VA012F1000 and registers its cleanup.
// The complete 15-byte callee0039D5B0 clears three pointers and returns ret4;
// its allocator-reference argument is unused. This is not WOLLobby's list.
struct Rva0039D5B0UnusedTag {};
struct Rva00EF1000Storage
{
    void initialize(const Rva0039D5B0UnusedTag &);
    void *word0;
    void *word4;
    void *word8;
};
extern Rva00EF1000Storage Rva00EF1000Global;
void bfmeForward_00C6FEF0();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void Rva00C6B2C0Initialize()
{
    Rva0039D5B0UnusedTag allocator;
    Rva00EF1000Global.initialize(allocator);
    atexit(bfmeForward_00C6FEF0);
}
