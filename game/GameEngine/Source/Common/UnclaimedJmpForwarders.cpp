// Unreferenced 5-byte forwarders: each is a lone `jmp rel32` after int3
// padding, and no call, jump, ILT entry, table slot or code immediate in the
// image reaches its address (a scan of every E8/E9 target and every dword in
// the image). The forwarder keeps `this` and its stack arguments as it found
// them, so VC7.1 emits the call as a tail jmp. The jump targets are read off
// the retail bytes and every one is a matched row; each target class is
// declared here under the ledger's name (as in UnclaimedMemberTailForwarders
// .cpp), and only the target's mangled name is asserted, not its layout.
//
// IDENTITY IS NOT RECOVERED for the forwarders. Every name is derived from an
// address.

class Rva007E8810Message { public: ~Rva007E8810Message(); };
class Rva007F6BA0 { public: void clear(); };
class Rva007F6C60 { public: void clear(); };
class Rva007F78E0Block { public: void clear(); };
class Rva00801570 { public: void clear(); };
class Rva00801600 { public: void clear(); };
class Rva00802A10 { public: void clear(); };
class Q3EhMember0089C900 { public: ~Q3EhMember0089C900(); };
class BfmeStrVKK { public: void bfmeTruncVKK( unsigned int length ); };
class BfmeA1232 { public: void bfmePop1232( int count ); };
class BfmeStackBB { public: void bfmePopN( int count ); };
class BfmeRoomXM;
class BfmeElemCU;
struct Rva00892640Item;
struct Rva009B4680State;
struct BfmeCharRange;
class Gen009D7B80 { public: unsigned int bfmeBucket( const BfmeCharRange *range ) const; };

void bfmeWalkXM( BfmeRoomXM *room, int a, int b );
void bfmeResetAll();
void *Rva008939C0( BfmeElemCU *elems, int a, int b );
Rva00892640Item *Rva00893B30ResizeItems( Rva00892640Item *items, int a, int b );
int Rva00956A80Get();
int Rva009B4680Normalize( Rva009B4680State *state );

class Rva007F4DD0Forward { public: void forward(); };
void Rva007F4DD0Forward::forward() { reinterpret_cast<Rva007E8810Message *>( this )->~Rva007E8810Message(); }

class Rva00808B20Forward { public: void forward(); };
void Rva00808B20Forward::forward() { reinterpret_cast<Rva007E8810Message *>( this )->~Rva007E8810Message(); }

class Rva007F77A0Forward { public: void forward(); };
void Rva007F77A0Forward::forward() { reinterpret_cast<Rva007F6BA0 *>( this )->clear(); }

class Rva007F7800Forward { public: void forward(); };
void Rva007F7800Forward::forward() { reinterpret_cast<Rva007F6C60 *>( this )->clear(); }

class Rva007F7F40Forward { public: void forward(); };
void Rva007F7F40Forward::forward() { reinterpret_cast<Rva007F78E0Block *>( this )->clear(); }

class Rva00801B60Forward { public: void forward(); };
void Rva00801B60Forward::forward() { reinterpret_cast<Rva00801570 *>( this )->clear(); }

class Rva00801BC0Forward { public: void forward(); };
void Rva00801BC0Forward::forward() { reinterpret_cast<Rva00801600 *>( this )->clear(); }

class Rva00802C20Forward { public: void forward(); };
void Rva00802C20Forward::forward() { reinterpret_cast<Rva00802A10 *>( this )->clear(); }

class Rva0089C9C0Forward { public: void forward(); };
void Rva0089C9C0Forward::forward() { reinterpret_cast<Q3EhMember0089C900 *>( this )->~Q3EhMember0089C900(); }

class Rva008C4A20Forward { public: void forward( unsigned int length ); };
void Rva008C4A20Forward::forward( unsigned int length ) { reinterpret_cast<BfmeStrVKK *>( this )->bfmeTruncVKK( length ); }

class Rva008C5FB0Forward { public: void forward( int count ); };
void Rva008C5FB0Forward::forward( int count ) { reinterpret_cast<BfmeA1232 *>( this )->bfmePop1232( count ); }

class Rva008C5FC0Forward { public: void forward( int count ); };
void Rva008C5FC0Forward::forward( int count ) { reinterpret_cast<BfmeStackBB *>( this )->bfmePopN( count ); }

class Rva009D7DB0Forward { public: unsigned int forward( const BfmeCharRange *range ) const; };
unsigned int Rva009D7DB0Forward::forward( const BfmeCharRange *range ) const { return reinterpret_cast<const Gen009D7B80 *>( this )->bfmeBucket( range ); }

void Rva00861200Forward( BfmeRoomXM *room, int a, int b ) { bfmeWalkXM( room, a, b ); }
void Rva00891DD0Forward() { bfmeResetAll(); }
void *Rva00893CA0Forward( BfmeElemCU *elems, int a, int b ) { return Rva008939C0( elems, a, b ); }
Rva00892640Item *Rva00893CB0Forward( Rva00892640Item *items, int a, int b ) { return Rva00893B30ResizeItems( items, a, b ); }
int Rva008FD360Forward() { return Rva00956A80Get(); }
int Rva009AC580Forward( Rva009B4680State *state ) { return Rva009B4680Normalize( state ); }
