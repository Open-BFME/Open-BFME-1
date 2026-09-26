// cl: /DNDEBUG /MD /EHsc
// Retail 0x00260E80 is an anonymous one-argument member body.  No named
// caller or vtable entry identifies its owner, so this neutral owner records
// only the ABI and object layouts proven by the retail instructions.
//
// The body creates a temporary AIGroup from TheAI, adds the four-byte object
// pointers in the supplied range, applies a zero-command packet whose first
// field is object+0x38, and destroys the temporary group.  The four existing
// ILT thunk rows are called through typed member-pointer views so ECX and
// argument widths remain explicit without introducing aliases or pins.

typedef int Int;

class AIGroup
{
};

class AI
{
};

struct Rva00260E80Packet
{
	void *first;
	unsigned char flag;
	void *objectA;
	void *objectB;
};

struct Rva00260E80Input
{
	void *object;
	void **begin;
	void **end;
};

extern AI *TheAI;
extern void j_0003b570( void );
extern void j_0002b7e2( void );
extern void j_00048c43( void );
extern void j_00015f69( void );

typedef AIGroup *(AI::*Rva00260E80CreateCall)( void );
typedef void (AIGroup::*Rva00260E80AddCall)( void * );
typedef void (AIGroup::*Rva00260E80ApplyCall)(
	Rva00260E80Packet *, Int );
typedef void (AI::*Rva00260E80DestroyCall)( AIGroup * );

class Rva00260E80Owner
{
public:
	void apply( Rva00260E80Input &input );
};

void Rva00260E80Owner::apply( Rva00260E80Input &input )
{
	union
	{
		void *asVoid;
		Rva00260E80CreateCall asMember;
	} createCast;
	createCast.asVoid = (void *)j_0003b570;
	AIGroup *group = (TheAI->*createCast.asMember)();
	if ( group == 0 )
		return;

	void **current = input.begin;
	union
	{
		void *asVoid;
		Rva00260E80AddCall asMember;
	} addCast;
	addCast.asVoid = (void *)j_0002b7e2;
	while ( current != input.end )
	{
		(group->*addCast.asMember)( *current );
		++current;
	}

	Rva00260E80Packet packet;
	packet.first = (char *)input.object + 0x38;
	packet.flag = 0;
	packet.objectA = 0;
	packet.objectB = 0;
	union
	{
		void *asVoid;
		Rva00260E80ApplyCall asMember;
	} applyCast;
	applyCast.asVoid = (void *)j_00048c43;
	(group->*applyCast.asMember)( &packet, 0 );

	union
	{
		void *asVoid;
		Rva00260E80DestroyCall asMember;
	} destroyCast;
	destroyCast.asVoid = (void *)j_00015f69;
	(TheAI->*destroyCast.asMember)( group );
}
