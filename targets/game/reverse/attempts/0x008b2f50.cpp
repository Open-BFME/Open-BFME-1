// ?Rva008B2F50@Rva008993E0Owner@@QAEPAXPAX0@Z
// partial score=0.0 date=2026-09-22
// Partial reconstruction of retail vtable slot 10 at 0x008B2F50.
// Only the first dispatch arm is represented; the remaining arms need work.
typedef unsigned int Word;
class Rva008993E0Owner {
public:
    char pad[0x20];
    void *Rva008B2F50(void *text, void *context);
};
extern "C" Word * __cdecl rva008D5DC0(const char *, unsigned short);
extern "C" void * __cdecl rva00897640(unsigned int);
extern "C" void * __cdecl rva00899FC0(void *);
void *Rva008993E0Owner::Rva008B2F50(void *text, void *context)
{
    if (!text) return 0;
    Word *source = reinterpret_cast<Word *>(context);
    Word *kind = rva008D5DC0(reinterpret_cast<const char *>(*source + 8),
                              *reinterpret_cast<unsigned short *>(*source + 2));
    if (!kind) return 0;
    if (kind[1] == 1) {
        void *&singleton = *reinterpret_cast<void **>(0x01338360);
        if (!singleton) {
            void *memory = rva00897640(0x24);
            singleton = memory ? rva00899FC0(memory) : 0;
            if (singleton) {
                Word *flags = reinterpret_cast<Word *>(singleton) + 1;
                *flags = (*flags & 0xffffc07f) | 0x40;
            }
        }
        return singleton;
    }
    return 0;
}
