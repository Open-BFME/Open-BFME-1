// ?Rva00894380@@YAXXZ
// partial score=0.0 date=2026-09-22
// Partial reconstruction of retail 0x00894380. The command dispatch and
// terminal callback path still need the original exception and string shape.
typedef unsigned int Word;
struct Rva00894380Entry { Word count; Word kind; Word *items; };
extern void bfmeSetVKI(void *, const char *);
extern void bfmeInsert(void *, Word);

void Rva00894380()
{
    Word *&cursor = *reinterpret_cast<Word **>(0x013377e0);
    const Word *const bytes = *reinterpret_cast<Word **>(0x013377dc);
    Word &frame = *reinterpret_cast<Word *>(0x013377ec);
    Rva00894380Entry *const entry = *reinterpret_cast<Rva00894380Entry **>(0x013377f0);
    const Word stop = frame + 1;
    if (!bytes) return;
    while (frame != stop) {
        Word *item = entry->items;
        Word *const end = item + entry->count * 2;
        for (; item != end; item += 2)
            if (item[1] != 4 && item[1] != 2) break;
        if (item == end) {
            while (*cursor <= frame) {
                Word *next = cursor + 1;
                cursor = next;
                switch (*next & 3) {
                case 0: case 1:
                    cursor += 1;
                    bfmeInsert(reinterpret_cast<void *>(0x013377d8), *next);
                    break;
                case 2: {
                    const char *text = reinterpret_cast<const char *>(next) + 1;
                    while (*reinterpret_cast<const char *>(cursor))
                        cursor = reinterpret_cast<Word *>(reinterpret_cast<char *>(cursor) + 1);
                    bfmeSetVKI(reinterpret_cast<void *>(0x013377f0), text);
                    break;
                }
                case 3:
                    cursor = reinterpret_cast<Word *>(reinterpret_cast<char *>(next) + 1);
                    break;
                }
            }
        }
        if (reinterpret_cast<const char *>(cursor) - reinterpret_cast<const char *>(bytes)
            >= *reinterpret_cast<int *>(0x013377e4)) return;
        ++frame;
        if (!*reinterpret_cast<Word *>(0x013377dc)) return;
    }
}
