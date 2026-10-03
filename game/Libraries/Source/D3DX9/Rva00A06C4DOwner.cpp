// cl: /O2 /MD
// Retail table VA01148F90 is installed at RVA00A1209C and00A06C59.
// Slot25 points directly to00A06DF9: XOR EAX,EAX; RET4 (five bytes).
// Ghidra memory and the baseline PE agree; the following00A06DFE is
// independently table-backed. Archive template twins leave identity opaque.
class Rva00A06C4DOwner
{
public:
    unsigned long __stdcall rva00A06DF9();
};

unsigned long __stdcall Rva00A06C4DOwner::rva00A06DF9()
{
    return 0;
}
