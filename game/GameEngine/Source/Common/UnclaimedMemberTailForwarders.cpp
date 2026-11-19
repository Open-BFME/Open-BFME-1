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
class LanTheaterEmulator { public: void notifyAddress( Rva00809500Entry *entry ); };
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

class Rva00803700Forward { public: void forward( Rva00809500Entry *entry ); char m_lead[ 0x18 ]; LanTheaterEmulator *m_target; };
void Rva00803700Forward::forward( Rva00809500Entry *entry ) { m_target->notifyAddress( entry ); }

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

// Two more embedded-member forwarders, both `add ecx,0x1C / jmp`, unreferenced
// after int3 padding.  0x009221F0 assigns a C string to a StringClass at +0x1C
// through StringClass::operator=(const char *) (0x007AF330, reached through
// its ILT stub); 0x0087EF90 destroys an AsciiString at +0x1C, whose inline
// destructor is the tail call into the matched releaseBuffer (0x00887940).
class StringClass { public: const StringClass &operator=( const char *text ); };
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }
private:
	void releaseBuffer();
	char *m_text;
};

class Rva009221F0Named { public: void setName( const char *name ); char m_lead[ 0x1C ]; StringClass m_name; };
void Rva009221F0Named::setName( const char *name ) { m_name = name; }

class Rva0087EF90Named { public: ~Rva0087EF90Named(); char m_lead[ 0x1C ]; BFMERetailAsciiString m_name; };
Rva0087EF90Named::~Rva0087EF90Named() {}

// Nine 11-byte forwarders the ledger had split into six unowned bytes and a
// gap "thunk" over the trailing jmp: each is one body, `mov ecx,[ecx+disp32]`
// (or `add ecx,disp32`) and the tail jump, between int3 pads and with no
// reference to its start.  The jmp targets are the matched rows declared
// below; the stack arguments pass through untouched.
class MeshGeometryClass
{
	friend class Rva0092C4D0Forward;
public:
	const char *Get_Name() const;
protected:
	void Generate_Culling_Tree();
};
class VertexMaterialClass;
class MeshMatDescClass
{
public:
	VertexMaterialClass *Peek_Material( int vidx, int pass ) const;
	void Set_Material( int vidx, VertexMaterialClass *vmat, int pass );
};
class BfmeTexVGS;
class BfmeMeshVGT { public: void bfmeSetVGT( BfmeTexVGS **textures, int a, int b ); };
class BfmeTexVGR;
class BfmeMeshVGR { public: void bfmeSetVGR( int index, BfmeTexVGR **textures, int a, int b ); };
class Rva00988F00Owner { public: float field2C() const; };
#include "../../Include/Common/NameKeyType.h"
class NameKeyGenerator { public: NameKeyType nameToLowercaseKey( const char *name ); };
class SegLineRendererClass { public: void Reset_Line(); };

// mov ecx,[ecx+disp32] / jmp
class Rva0092C340Forward { public: const char *forward(); char m_lead[ 0xC8 ]; MeshGeometryClass *m_target; };
const char *Rva0092C340Forward::forward() { return m_target->Get_Name(); }

class Rva0092C4D0Forward { public: void forward(); char m_lead[ 0xC8 ]; MeshGeometryClass *m_target; };
void Rva0092C4D0Forward::forward() { m_target->Generate_Culling_Tree(); }

class Rva0092CA50Forward { public: void forward( BfmeTexVGS **textures, int a, int b ); char m_lead[ 0x9C ]; BfmeMeshVGT *m_target; };
void Rva0092CA50Forward::forward( BfmeTexVGS **textures, int a, int b ) { m_target->bfmeSetVGT( textures, a, b ); }

class Rva0092F060Forward { public: VertexMaterialClass *forward( int vidx, int pass ); char m_lead[ 0x9C ]; MeshMatDescClass *m_target; };
VertexMaterialClass *Rva0092F060Forward::forward( int vidx, int pass ) { return m_target->Peek_Material( vidx, pass ); }

class Rva0094DFA0Forward { public: void forward( int vidx, VertexMaterialClass *vmat, int pass ); char m_lead[ 0x9C ]; MeshMatDescClass *m_target; };
void Rva0094DFA0Forward::forward( int vidx, VertexMaterialClass *vmat, int pass ) { m_target->Set_Material( vidx, vmat, pass ); }

class Rva0094DFB0Forward { public: void forward( int index, BfmeTexVGR **textures, int a, int b ); char m_lead[ 0x9C ]; BfmeMeshVGR *m_target; };
void Rva0094DFB0Forward::forward( int index, BfmeTexVGR **textures, int a, int b ) { m_target->bfmeSetVGR( index, textures, a, b ); }

class Rva0097E4E0Forward { public: float forward(); char m_lead[ 0x130 ]; Rva00988F00Owner *m_target; };
float Rva0097E4E0Forward::forward() { return m_target->field2C(); }

class Rva009EDE30Forward { public: NameKeyType forward( const char *name ); char m_lead[ 0x1F0 ]; NameKeyGenerator *m_target; };
NameKeyType Rva009EDE30Forward::forward( const char *name ) { return m_target->nameToLowercaseKey( name ); }

// add ecx,disp32 / jmp
class Rva0094F940Forward { public: void forward(); char m_lead[ 0xE0 ]; SegLineRendererClass m_target; };
void Rva0094F940Forward::forward() { m_target.Reset_Line(); }

// 0x0026EDA0, the same split (17 unowned bytes before a gap thunk at +0x11):
// replace the first argument by the dword at its +0x74 in place, then tail-jump
// on the embedded member at +0x204 into the matched bfmeRemoveAll (0x002E0990,
// through its ILT stub) with the second argument passed through.
class Gen_002E0990 { public: void bfmeRemoveAll( void *item, int count ); };
struct Rva0026EDA0Arg { char m_lead[ 0x74 ]; void *m_item; };
class Rva0026EDA0Forward { public: void forward( Rva0026EDA0Arg *arg, int count ); char m_lead[ 0x204 ]; Gen_002E0990 m_target; };
void Rva0026EDA0Forward::forward( Rva0026EDA0Arg *arg, int count ) { m_target.bfmeRemoveAll( arg->m_item, count ); }

// 0x000E9FD0, the same split (6 unowned bytes before a gap thunk at +6):
// `add ecx,0xC8` and a tail jump through ILT stub 0x00019BCD into the matched
// BitFlags<181>::testSetAndClear (0x000E9910) on an embedded flag set, both
// reference arguments passed through.
template <int NUMBITS> class BitFlags
{
public:
	bool testSetAndClear( const BitFlags &mustBeSet, const BitFlags &mustBeClear ) const;
private:
	unsigned m_bits[ ( NUMBITS + 31 ) / 32 ];
};
class Rva000E9FD0Forward
{
public:
	bool forward( const BitFlags< 181 > &mustBeSet, const BitFlags< 181 > &mustBeClear ) const;
	char m_lead[ 0xC8 ];
	BitFlags< 181 > m_flags;
};
bool Rva000E9FD0Forward::forward( const BitFlags< 181 > &mustBeSet, const BitFlags< 181 > &mustBeClear ) const
{
	return m_flags.testSetAndClear( mustBeSet, mustBeClear );
}
