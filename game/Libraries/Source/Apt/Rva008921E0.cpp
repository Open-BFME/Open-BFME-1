// cl: /DNDEBUG /MD /EHs-c-
// Retail has two independent leaves: 008921E0..008921ED (14 bytes), then
// INT3 padding at EE/EF, and 008921F0..0089220C (29 bytes). Native function
// names and owner types are unproved; both exported names retain the address.
// The existing opaque global-pointer declaration is reused without accessing
// Rva008B38F0Global's layout. The second leaf borrows a char-pointer storage
// view and writes the physical four-byte field at +0x1238; it makes no claim
// about construction, ownership, lifetime, or the field's native meaning.
class Rva008B38F0Global;
extern Rva008B38F0Global *g_01337820;
extern int g_bfme1017I;
// retail 0x013377D8; defining spelling (BfmePicker1284.cpp), declared
// incomplete here because only the pointer value is used.
struct BfmePickWorld1284;
extern BfmePickWorld1284 *g_bfmeHolderBU;
void __cdecl Rva008921E0(Rva008B38F0Global *value)
{
    if (value) g_01337820 = value;
}
void __cdecl Rva008921F0()
{
    if (!g_bfme1017I && g_bfmeHolderBU)
        *(unsigned int *)(reinterpret_cast<char *>(g_bfmeHolderBU) + 0x1238) = 0;
}
