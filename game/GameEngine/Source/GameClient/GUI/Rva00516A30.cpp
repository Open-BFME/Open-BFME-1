// cl: /O2 /Ob2 /DNDEBUG /MD
class MpGameSetup
{
public:
    void GadgetInit();
};
// Opaque ABI view. The existing MpGameSetup provider supplies the direct
// callee identity; the wrapper's original identity is not inferred from it.
class Rva00516A30
{
public:
    virtual void method();
};
void Rva00516A30::method()
{
    reinterpret_cast<MpGameSetup *>(reinterpret_cast<char *>(this) + 0x25c)->GadgetInit();
}
