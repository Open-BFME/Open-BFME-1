// cl: /O2 /GS
// The factory at 0x007F4810 stores this object at +0x244 of the FESL owner.
// Its 0x007F4440 method is the slot-zero call on the third interface at +0x0C.

class BfmeC994
{
public:
	BfmeC994( char *buffer, int size );
	void clear();

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
	primary->getService()->send( &message, (void *)0x00BF4520, primary, 10000 );
	message.clear();
}
