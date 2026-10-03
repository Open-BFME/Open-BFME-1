// cl: /O2 /MD
// Retail VA0112B5C4 slot3; constructor 7F6D60 installs it at 7F6D68.
// Complete 4B MOV EAX,[ECX+8]; RET; followed by INT3. Ghidra agrees.
// Constructor evidence establishes this opaque owner; the method keeps its RVA.
class Rva007F6D60Child
{
public:
    unsigned int rva007F5620();
};

unsigned int Rva007F6D60Child::rva007F5620()
{
    return *reinterpret_cast<const unsigned int *>(reinterpret_cast<const char *>(this) + 8);
}
