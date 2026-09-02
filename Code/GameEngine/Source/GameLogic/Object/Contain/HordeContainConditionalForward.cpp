// cl: /DNDEBUG /MD

struct Rva00248B40Object
{
	unsigned char unused_000[0x1FC];
	void *contained_by;
};

struct BfmeStateAMA;

class BfmeThingAMA
{
public:
	void conditionalForward( Rva00248B40Object *object,
		void *context, BfmeStateAMA *state );
	void bfmeGoAMA( void *object, void *context, BfmeStateAMA *state );
};

void BfmeThingAMA::conditionalForward( Rva00248B40Object *object,
	void *context, BfmeStateAMA *state )
{
	if ( object->contained_by == 0 )
		bfmeGoAMA( object, context, state );
}
