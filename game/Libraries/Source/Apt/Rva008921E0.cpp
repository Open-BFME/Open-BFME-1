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
extern char *Rva008A5380Holder;
void __cdecl Rva008921E0(Rva008B38F0Global *value)
{
    if (value) g_01337820 = value;
}
void __cdecl Rva008921F0()
{
    if (!g_bfme1017I && Rva008A5380Holder)
        *(unsigned int *)(Rva008A5380Holder + 0x1238) = 0;
}
