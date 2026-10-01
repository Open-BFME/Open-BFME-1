// Retail RVA 0x00892000: 53B; RET at +0x34, INT3 at +0x35.
// Address-qualified free wrapper; original EA name remains unproved.
// Reuse the matched clear and arena-thunk ABIs, plus the two-word
// thiscall declaration used by matched BfmeConv1038.cpp. Callee 008BDBB0
// independently ends RET8 and consumes both argument words.
// Receiver reload after the calls and +0x122C adjustment are retail-proven.
// Globals keep their existing recorded identities. No new pins.

class BfmeThingHH
{
public:
    void bfmeClearHH();
};

class BfmeSubF1038
{
public:
    void bfmeAdd1038(int a, int b);
};

extern char *Rva008A5380Holder;
extern char *g_bfmeArenaCursor;
extern int g_bfmeB1038;
void Rva00897110ArenaReadyThunk();

void Rva00892000()
{
    if (Rva008A5380Holder == 0)
        return;

    reinterpret_cast<BfmeThingHH *>(Rva008A5380Holder)->bfmeClearHH();
    Rva00897110ArenaReadyThunk();
    reinterpret_cast<BfmeSubF1038 *>(Rva008A5380Holder + 0x122C)->bfmeAdd1038(g_bfmeB1038, 0);
    g_bfmeArenaCursor -= 0x60;
}
