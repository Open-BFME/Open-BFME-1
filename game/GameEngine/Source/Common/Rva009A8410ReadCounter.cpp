// cl: /O2 /MD /DNDEBUG
// The CPUID/RDTSC hardware operation and register preservation require inline
// assembly with this compiler. The local, output store, frame and return are
// ordinary C++; no hand-written prologue or byte emission is used.
// Original function identity is unproven. See identity_evidence/0x009a8410.md.
void Rva009A8410(unsigned int *result)
{
    unsigned int stamp;
    __asm {
        pushad
        cpuid
        rdtsc
        mov stamp, eax
        popad
    }
    *result = stamp;
}
