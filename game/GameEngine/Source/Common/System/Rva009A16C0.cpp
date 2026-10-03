// cl: /DNDEBUG /MD
// Empty BFME subsystem table slots 7 and 8. The existing subsystem header
// does not declare these methods; these are opaque ABI views, not additions
// to its layout or new source identities. The second slot ignores one stack
// word, whose original type is unknown.
// Evidence: identity_evidence/009a16c0-009a16d0-empty-slots.md.
class Rva009A16C0
{
public:
 virtual void method();
};
void Rva009A16C0::method() {}

class Rva009A16D0
{
public:
 virtual void method(unsigned int);
};
void Rva009A16D0::method(unsigned int) {}
