// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x008C6800 (50 bytes). The registered Apt callback returns an
// AptBoolean from either true or the Boolean predicate on the stack top.

class AptValue;
class AptBoolean { public: static AptBoolean *Create(bool); };
struct Rva008AE770Stack
{
	int m_count;
	int m_rva0133874C;
	AptValue** m_rva01338750;
};

extern Rva008AE770Stack Rva008AE770TheStack;
// The retail body at 0x008C4A30 is reached through an incremental-link thunk
// whose only proven signature is void(). The real body is __cdecl and returns
// an AptBoolean-compatible bool in AL, so call it through a reinterpreted
// function pointer rather than aliasing a second name onto one address.
void d_008c4a30();
typedef bool (__cdecl *Rva008C4A30Predicate)(AptValue *);

AptBoolean *__cdecl rva008C6800(void *, int count)
{
    if (count == 0)
        return AptBoolean::Create(true);

    Rva008AE770Stack& stk = Rva008AE770TheStack;
    AptValue** args = stk.m_rva01338750;
    AptValue *top = args[stk.m_count - 1];
    // The generated callee's void() placeholder hides its retail cdecl ABI:
    // the body reads one stack pointer and returns a Boolean in AL.
    return AptBoolean::Create(((Rva008C4A30Predicate)(void *)d_008c4a30)(top));
}
