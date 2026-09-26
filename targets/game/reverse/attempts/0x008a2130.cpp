// ?helper@BfmeFixup2580@@QAEXPAXPAVBfmeFixupChunk2580@@0@Z
// partial score=0.0 date=2026-09-22
// Partial reconstruction of retail 0x008A2130. The later string/fixup
// cases remain to be translated from the retail control flow.
typedef unsigned int Word;
class BfmeFixupChunk2580 { public: char pad[0x1c]; int relative; };
class BfmeFixup2580 {
public:
    char pad0[0xc]; int count; Word *objects; char pad1[0xc];
    int otherCount; Word *other; int mapCount; Word *map; int flag;
    void helper(void *base, BfmeFixupChunk2580 *chunk, void *context);
};
static void fixPointer(Word &value, Word base)
{
    if (value) value += base;
}
void BfmeFixup2580::helper(void *baseArg, BfmeFixupChunk2580 *chunk, void *context)
{
    Word base = reinterpret_cast<Word>(baseArg);
    fixPointer(reinterpret_cast<Word &>(objects), base);
    fixPointer(reinterpret_cast<Word &>(map), base);
    for (int i = 0; i < mapCount; ++i)
        fixPointer(map[i * 2], base);
    for (int i = 0; i < count; ++i) {
        fixPointer(objects[i], base);
        Word *item = reinterpret_cast<Word *>(objects[i]);
        if (!item) continue;
        item[1] = objects[0];
        switch (item[0]) {
        case 2: fixPointer(item[13], base); fixPointer(item[14], base); break;
        case 3: fixPointer(item[2], base); fixPointer(item[4], base); break;
        case 4:
            fixPointer(item[9], base);
            fixPointer(item[10], base);
            fixPointer(item[12], base);
            fixPointer(item[14], base);
            break;
        case 10: fixPointer(item[13], base); break;
        }
    }
    fixPointer(reinterpret_cast<Word &>(other), base);
    for (int i = 0; i < otherCount; ++i) {
        Word *item = other + 4 * i;
        fixPointer(item[0], base);
        fixPointer(item[1], base);
    }
    (void)chunk; (void)context;
}
