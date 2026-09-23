// Retail 0x005A7550, 69 bytes. Equality is defined by the adjacent
// BfmeKeyOD ordering routine: neither operand may sort before the other.
// No named caller establishes the original function spelling, so the name
// retains the retail address.
struct BfmeKeyOD;
extern char bfmeTestQP(void *left, void *right);

bool Rva005A7550KeyEqual(const BfmeKeyOD *left, const BfmeKeyOD *right)
{
    int different;
    if (bfmeTestQP((void *)left, (void *)right) ||
        bfmeTestQP((void *)right, (void *)left))
        different = 1;
    else
        different = 0;

    // VC7.1 keeps the 32-bit branch value and tests its low byte here.
    return !(unsigned char)different;
}
