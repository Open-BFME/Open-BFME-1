// cl: /O2 /MD
// Retail 0x00C6DBF0 is the namespace-scope dynamic initializer for the
// Rva008838F0Owner global at 0x0130EA10: it constructs the owner with the
// (owner, table) pair and registers the 0x00C70EB0 atexit cleanup, which
// destroys it. Defining the global here lets MSVC emit those bytes as its
// compiler-local _$E1; the ledger row names that COFF symbol via
// object-symbol=_$E1.
class Rva008838F0Owner
{
public:
    Rva008838F0Owner(void *owner, void **table);
    ~Rva008838F0Owner();
};

extern void *g_012D4D14[];

Rva008838F0Owner g_bfmeRva0130EA10Owner((void *)"heap memory", g_012D4D14);
