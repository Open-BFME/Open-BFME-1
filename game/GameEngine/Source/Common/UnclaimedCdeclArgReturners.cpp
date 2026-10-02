// Unclaimed tiny bodies with one shape:
//
//     mov eax,[esp+4] / ret
//
// A __cdecl function returns its first stack argument; the caller pops it.
//
// Every body here sat in a .text gap no ledger row covered.  Both ends are
// proven by the retail layout: the start is 16-byte aligned directly after an
// int3 pad run, and the terminal instruction is followed by int3 padding or by
// the next matched row.  Retail was linked without identical-COMDAT folding,
// so each address is its own function even where the bytes repeat.  Most are
// unreferenced (no call, ILT stub or table slot reaches them); the notes column
// of each ledger row lists the references that do exist.  Members before an
// accessed field are spelled as a lead array because only their total size is
// witnessed.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

int Rva007A62D0Pass( int value ) { return value; }
int Rva008FE9F0Pass( int value ) { return value; }
int Rva00902120Pass( int value ) { return value; }
int Rva00923CC0Pass( int value ) { return value; }
int Rva0093CA30Pass( int value ) { return value; }
int Rva0094BDE0Pass( int value ) { return value; }
int Rva0094BDF0Pass( int value ) { return value; }
int Rva009A2DD0Pass( int value ) { return value; }
int Rva009C8FB0Pass( int value ) { return value; }
int Rva009C8FC0Pass( int value ) { return value; }
int Rva009CE720Pass( int value ) { return value; }
int Rva009CE730Pass( int value ) { return value; }
int Rva009ECD10Pass( int value ) { return value; }
