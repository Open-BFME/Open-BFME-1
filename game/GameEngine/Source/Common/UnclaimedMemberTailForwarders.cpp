// Fourteen unclaimed 8- and 9-byte forwarders that set up `this` for an
// already-matched member and tail-jump into it:
//
//     mov ecx,[ecx+<disp>] / jmp <member>    (call through a pointer member)
//     add ecx,<disp>       / jmp <member>    (call on an embedded member)
//     mov ecx,[esp+4]      / jmp <member>    (cdecl: call on the argument)
//
// Each sat alone in a .text gap no ledger row covered: 16-byte-aligned start
// after an int3 pad run, the jmp followed by int3 padding or the next matched
// row, and no call, ILT stub, table slot, code immediate, pin or dir32 name at
// the address.  The jump targets are read off the retail bytes and every one is
// a matched row; its class is declared here under the ledger's name (each is
// declared in its own source, not in a header) so the jump resolves with no
// new pin.  Only the target's mangled name is asserted, not its layout.
//
// IDENTITY IS NOT RECOVERED for the forwarders.  Every name is derived from an
// address.

class Rva007EAD30Owner { public: void send(); };
class Rva007EADC0Owner { public: void send(); };
class ShroudManagerImpl { public: void reset(); };
class Rva009A2960 { public: void markState3(); };
class Gen009F1510 { public: void handle(); };
class Rva008811C0DwordField { public: int get() const; };
struct Rva00809500Entry;
class Rva00803620Sink { public: void rva0080AA80( Rva00809500Entry *entry ); };
class Rva00809BF0Owner { public: void notify( Rva00809500Entry *entry ); };
class Gen_007e86c0 { public: void m(); };
class Rva00826840Owner { public: void resetTables(); };
class Gen_0094BFB0 { public: void bfmeForward(); };
class Rva00851340 { public: void invoke(); };
class BfmeThingCFB { public: void bfmeGoCFB(); };

// mov ecx,[ecx+<disp>] / jmp
class Rva007EAD90Forward { public: void forward(); char m_lead[ 4 ]; Rva007EAD30Owner *m_target; };
void Rva007EAD90Forward::forward() { m_target->send(); }

class Rva007EAE20Forward { public: void forward(); char m_lead[ 4 ]; Rva007EADC0Owner *m_target; };
void Rva007EAE20Forward::forward() { m_target->send(); }

class Rva008F7340Forward { public: void forward(); char m_lead[ 0xC ]; ShroudManagerImpl *m_target; };
void Rva008F7340Forward::forward() { m_target->reset(); }

class Rva009A2580Forward { public: void forward(); char m_lead[ 0xC ]; Rva009A2960 *m_target; };
void Rva009A2580Forward::forward() { m_target->markState3(); }

class Rva009EBA00Forward { public: void forward(); char m_lead[ 8 ]; Gen009F1510 *m_target; };
void Rva009EBA00Forward::forward() { m_target->handle(); }

class Rva00880E40Forward { public: int forward() const; char m_lead[ 0xC ]; Rva008811C0DwordField *m_target; };
int Rva00880E40Forward::forward() const { return m_target->get(); }

class Rva00803710Forward { public: void forward( Rva00809500Entry *entry ); char m_lead[ 0x18 ]; Rva00803620Sink *m_target; };
void Rva00803710Forward::forward( Rva00809500Entry *entry ) { m_target->rva0080AA80( entry ); }

class Rva00803720Forward { public: void forward( Rva00809500Entry *entry ); char m_lead[ 0x18 ]; Rva00809BF0Owner *m_target; };
void Rva00803720Forward::forward( Rva00809500Entry *entry ) { m_target->notify( entry ); }

// add ecx,<disp> / jmp
class Rva008006B0Forward { public: void forward(); char m_lead[ 0x10 ]; Gen_007e86c0 m_member; };
void Rva008006B0Forward::forward() { m_member.m(); }

class Rva007F93D0Forward { public: void forward(); char m_lead[ 0x14 ]; Gen_007e86c0 m_member; };
void Rva007F93D0Forward::forward() { m_member.m(); }

// mov ecx,[esp+4] / jmp
void Rva008231B0Forward( Rva00826840Owner *target ) { target->resetTables(); }
void Rva0094C640Forward( Gen_0094BFB0 *target ) { target->bfmeForward(); }
void Rva00852290Forward( Rva00851340 *target ) { target->invoke(); }
void Rva008FF900Forward( BfmeThingCFB *target ) { target->bfmeGoCFB(); }
