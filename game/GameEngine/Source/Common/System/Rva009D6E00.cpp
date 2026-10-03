// cl: /DNDEBUG /MD
// Table1144090 slot7 enters this RET4-only method. The ignored argument is
// an opaque stack-word view, not a claim about its original source type.
// Evidence: identity_evidence/009a16c0-009a16d0-empty-slots.md.
class Rva009D6E00
{
public:
 virtual void method(unsigned int);
};
void Rva009D6E00::method(unsigned int) {}
