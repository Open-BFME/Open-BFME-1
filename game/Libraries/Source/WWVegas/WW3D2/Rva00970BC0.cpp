// cl: /DNDEBUG /MD
// Native empty entries of table VA0113E730, installed by constructor
// 00970EC0 and destructor00970C40. Each complete extent is RET followed
// by fifteen INT3 bytes. Method/owner identities are deliberately opaque.
// See identity_evidence/00970bc0-00970c00-empty-slots.md.
class Rva00970BC0
{
public:
 virtual void method();
};
void Rva00970BC0::method() {}

class Rva00970C00
{
public:
 virtual void method();
};
void Rva00970C00::method() {}
