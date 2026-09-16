// ?query@Rva00733420Owner@@QAE_NPAX@Z
// Retail 0x00733420..0x0073348E: full 110-byte function, all RET 4 tails.
// Ghidra FUN_00b33420 independently reports this extent. The old 95-byte
// dump stopped before its true/false epilogues; the 8-byte shadow-init alias
// at 0x0073347F was its interior return-one tail, not a separate function.
// No calls or relocations. Opaque identity: lookup key at record +0x58,
// test state +0x80, flag +0xC4, type +0x40 and object +0xC8.
// Matched destructor 0x00736590 witnesses 12000 records of stride 0xE8.
struct Rva00733420Record {
    char pad0[0x40];
    int type;
    char pad44[0x14];
    void *key;
    char pad5c[0x24];
    int state;
    char pad84[0x40];
    unsigned char flag;
    char padc5[3];
    void *object;
    char padcc[0x1c];
};
struct Rva00733420Owner {
    char pad[0x1b0];
    Rva00733420Record records[12000];
    int count;
    bool query(void *key);
};
bool Rva00733420Owner::query(void *key) {
    for (int i=0; i<count; ++i)
        if (records[i].key == key)
            return records[i].state > 0 && !records[i].flag && records[i].type != -2 && !records[i].object;
    return false;
}
