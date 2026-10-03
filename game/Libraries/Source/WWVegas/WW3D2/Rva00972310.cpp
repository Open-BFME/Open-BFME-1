// cl: /O2 /MD
// Retail VA0113E830 slot13; constructor 9723C0 installs it at 9723EA.
// Complete 6B MOV EAX,00424F58; RET; followed by INT3. Ghidra agrees.
// Constructor evidence establishes this opaque owner; the method keeps its RVA.
class Rva009723C0Proto
{
public:
    unsigned int rva00972310();
};

unsigned int Rva009723C0Proto::rva00972310()
{
    return 0x00424f58;
}
