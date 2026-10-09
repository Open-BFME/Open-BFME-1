// cl: /DNDEBUG /MD /EHsc
// Retail 0x0039EF60, 244 bytes, ret 4: ECX holds an index-backed handle.
// Original owner is unproved; this address-derived name claims only the query.
// The pool has 0x88-byte entries, with six bit words at +0x60. The signed
// bounds test returns true for an index at or beyond the pool's end. Index -1
// interns a default temporary through ILT 0x00037FD8, then destroys it through
// 0x00043699. Constructor ILT 0x00008067 targets 0x0039DC20. Those three
// contracts and layout agree with the landed BfmeSecondPlainMemberSet.cpp.
// Keep the entry-pointer local: it preserves retail's separate additions.
struct BitWords0039EF60 {
    unsigned words[6];
};
// The temporary uses the matched ??0Gen00043699 ctor but its destructor is the
// matched ??1S4Elem0039EBE0 body; a trivial base class gives the destructor its
// own ledger identity without disturbing the constructed type's codegen.
class S4Elem0039EBE0 {
public:
    ~S4Elem0039EBE0();
};
class Gen00043699 : public S4Elem0039EBE0 {
public:
    Gen00043699();
    unsigned char prefix[0x60];
    BitWords0039EF60 bits;
    unsigned char tail[0x10];
};
struct BfmeAttributePool {
    Gen00043699 *start, *finish, *end;
};
// Rva00C6B2C0PoolInitialization.cpp owns the 12-byte pool cell at VA 012F1000.
struct Rva00EF1000Storage;
extern Rva00EF1000Storage Rva00EF1000Global;
#define TheBfmeAttributePool (reinterpret_cast<BfmeAttributePool &>(Rva00EF1000Global))
unsigned bfmeInternAttributeEntry(Gen00043699 *entry);
class AttributeBitQuery0039EF60 {
public:
    int index;
    bool test(unsigned bit);
};
bool AttributeBitQuery0039EF60::test(unsigned bit)
{
    if (index >= TheBfmeAttributePool.finish - TheBfmeAttributePool.start)
        return true;
    if (index == -1) {
        index = bfmeInternAttributeEntry(&Gen00043699());
    }
    Gen00043699 *p = TheBfmeAttributePool.start + index;
    BitWords0039EF60 bits = p->bits;
    return (bits.words[bit >> 5] & (1U << (bit & 31))) != 0;
}
