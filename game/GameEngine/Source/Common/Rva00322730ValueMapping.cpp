// Retail00322730: complete45-byte switch. ECX is unused; the callee
// consumes one DWORD argument and returns with ret4. The old37-byte dump
// stopped before its case-zero return at00322755. Semantic identity unknown.
int __stdcall Rva00322730MapValue(unsigned int value)
{
    switch (value) {
    case 0: return 1;
    case 1: return 2;
    case 2: return 4;
    default: return -1;
    }
}
