// cl: /O2 /GS
// The factory at 0x007F4810 stores this object at +0x244 of the FESL owner.
// Its 0x007F4440 method is the slot-zero call on the third interface at +0x0C.

// Retail 0x007E86C0: the shared seven-byte cleanup the FESL message bodies call
// (store the base vtable 0x01129358 into *this, then ret).  It is defined under
// this name in game/gen_small/fun_005.cpp, so the post-send cleanup spells it
// through this neutral declaration rather than a member of the local view.
class Gen_007e86c0
{
public:
	void m();
};

class BfmeC994
{
public:
	BfmeC994( char *buffer, int size );

	char pad[ 0x30 ];
	char tail;
};

class Rva007EA690FieldAddress
{
public:
	char *get();
};

class Rva007EA6A0FieldAddress
{
public:
	char *get();
};

class Rva007EA660FieldAddress
{
public:
	char *get();
};

class Gen_007ea670
{
public:
	char *bfmePlatform();
};

class Energy;

class Player
{
public:
	Energy *getEnergy();
};

class Rva007EA650FieldAddress
{
public:
	char *get();
};

class Rva007EAC30Owner;
class Rva007F9B80Service;

class Rva007F4440Primary
{
public:
	virtual void v0() = 0;
	virtual Rva007F9B80Service *getService() = 0;
	virtual void v2() = 0;
	virtual void v3() = 0;
	virtual void build( BfmeC994 *, char *, char *, char *, char *, char *, char *, char * ) = 0;
};

class Rva007F4440Owner
{
public:
	virtual Rva007EAC30Owner *getOwner() = 0;
};

class Rva007F9B80Service
{
public:
	virtual void v0() = 0;
	virtual void v1() = 0;
	virtual void send( BfmeC994 *, void *, Rva007F4440Primary *, int ) = 0;
};

class Rva007F4440Runner
{
public:
	virtual void run( int, int, int );
};

extern char *g_Rva012C3A18;

// The second send() argument, the FESL message-type global at 0x00BF4520. No
// name is recorded for it yet, so the address-derived g_00BF4520 stands in;
// declaring it keeps the argument relocatable in a linked build.
extern char g_00BF4520[];

void Rva007F4440Runner::run( int mode, int, int )
{
	if( mode != 3 )
		return;
	char buffer[ 0x100 ];
	BfmeC994 message( buffer, 0x100 );
	Rva007EAC30Owner *owner = ((Rva007F4440Owner *)((char *)this - 8))->getOwner();
	char *clientType = ( (Rva007EA660FieldAddress *)owner )->get()[0] == 0
		? 0
		: ( (Rva007EA660FieldAddress *)owner )->get();
	Rva007F4440Primary *primary = (Rva007F4440Primary *)((char *)this - 12);
	primary->build( &message,
		( (Rva007EA650FieldAddress *)owner )->get(),
		( (Rva007EA690FieldAddress *)owner )->get(),
		( (Rva007EA6A0FieldAddress *)owner )->get(),
		( char * )( (Player *)owner )->getEnergy(),
		g_Rva012C3A18,
		( (Gen_007ea670 *)owner )->bfmePlatform(),
		clientType );
	primary->getService()->send( &message, (void *)g_00BF4520, primary, 10000 );
	reinterpret_cast< Gen_007e86c0 * >( &message )->m();
}
