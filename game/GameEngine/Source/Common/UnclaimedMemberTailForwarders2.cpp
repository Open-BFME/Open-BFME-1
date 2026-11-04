// An unclaimed 8-byte forwarder that sets up `this` for an already-matched
// member and tail-jumps into it:
//
//     mov ecx,[ecx+0x18] / jmp <member>    (call through a pointer member)
//
// It sat alone in a .text gap no ledger row covered: 16-byte-aligned start
// directly after the ret of the preceding matched row (so no int3 pad precedes
// it), the jmp followed by int3 padding, and no call, jmp, ILT stub, vtable
// slot or code immediate at its address.  The jump target is read off the
// retail bytes and is a matched row, 0x0080A940; its class is declared here
// under the ledger's name (it is declared in its own source, not in a header)
// so the jump resolves with no new pin.  Only the target's mangled name is
// asserted, not its layout.  The stack argument passes through untouched.
//
// IDENTITY IS NOT RECOVERED.  The name is derived from an address.

class Rva007E8810Message;
class Rva0080A940Owner { public: void initFromMessage( Rva007E8810Message *message ); };

class Rva008036F0Forward { public: void forward( Rva007E8810Message *message ); char m_lead[ 0x18 ]; Rva0080A940Owner *m_target; };
void Rva008036F0Forward::forward( Rva007E8810Message *message ) { m_target->initFromMessage( message ); }
