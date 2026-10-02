// Retail RVA 0x00892000: 53B; RET at +0x34, INT3 at +0x35.
// Address-qualified free wrapper; original EA name remains unproved.
// Reuse the matched clear and arena-thunk ABIs, plus the two-word
// thiscall declaration used by matched BfmeConv1038.cpp. Callee 008BDBB0
// independently ends RET8 and consumes both argument words.
// Receiver reload after the calls and +0x122C adjustment are retail-proven.
// Retail loads at +0x00 and +0x19 both read VA 0x013377D8, the
// verified g_bfmeHolderBU pointer owned by BfmePicker1284.cpp.

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

struct BfmePickWorld1284;
extern BfmePickWorld1284 *g_bfmeHolderBU;
extern char *g_bfmeArenaCursor;
extern int g_bfmeB1038;
void Rva00897110ArenaReadyThunk();

void Rva00892000()
{
    if (g_bfmeHolderBU == 0)
        return;

    reinterpret_cast<BfmeThingHH *>(g_bfmeHolderBU)->bfmeClearHH();
    Rva00897110ArenaReadyThunk();
    reinterpret_cast<BfmeSubF1038 *>(reinterpret_cast<char *>(g_bfmeHolderBU) + 0x122C)->bfmeAdd1038(g_bfmeB1038, 0);
    g_bfmeArenaCursor -= 0x60;
}
