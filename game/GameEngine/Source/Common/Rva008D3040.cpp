// cl: /O2 /Ob2 /DNDEBUG /MD
// Existing opaque cleanup provider; full54B thiscall body ends plain RET.
class BfmeD1046
{
public:
    void bfmeGo1046D();
};
// Address-qualified entry view: table1136E0C and constructor8BE700 prove
// the receiver and the owned member at+20, not an original method name.
class Rva008D3040
{
public:
    virtual void method();
};
void Rva008D3040::method()
{
    reinterpret_cast<BfmeD1046 *>(reinterpret_cast<char *>(this) + 0x20)->bfmeGo1046D();
}
