// The target is a conditional forwarding wrapper.  Its tail jump lands at
// the independently matched BfmeThingAMA::bfmeGoAMA entry through ILT
// 0x000043A9; the owner of this copy is not established by the evidence.

struct Rva0024B7C0Object
{
	unsigned char unused_000[0x1FC];
	void *contained_by;
};

struct BfmeStateAMA;

class BfmeThingAMA
{
public:
	void bfmeGoAMA( void *object, void *context, BfmeStateAMA *state );
};

class Rva0024B7C0Owner
{
public:
	void forwardIfUncontained( Rva0024B7C0Object *object,
		void *context, BfmeStateAMA *state );
};

void Rva0024B7C0Owner::forwardIfUncontained( Rva0024B7C0Object *object,
	void *context, BfmeStateAMA *state )
{
	if ( object->contained_by == 0 )
		reinterpret_cast<BfmeThingAMA *>( this )->bfmeGoAMA( object, context, state );
}
