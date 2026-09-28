// cl: /O2 /MD
// Retail 0x0081C2E0: after four INT3 bytes; LEA EAX,[ECX+8]; RET;
// followed by twelve INT3 bytes. No semantic identity is asserted.
class Rva0081C2E0 {
public:
    void *address();
};
void *Rva0081C2E0::address() { return (char *)this + 8; }
