// ?slot0@Rva007F8840Owner@@UAEXI@Z
// partial score=0.82 date=2026-09-15
// cl: /O2 /GX-
// Retail 0x007F8840, 242 bytes.  This is the one-argument override in
// BfmeThingTWA's verified secondary interface at object +4.  The local owner
// view keeps that derived identity separate from the generic base interface
// body at 0x0088C500; the receiver is the secondary this-pointer.

struct Rva00804150ProtoMangleRef;

extern void Rva008054A0( Rva00804150ProtoMangleRef *ref );
extern int Rva00806040( Rva00804150ProtoMangleRef *ref,
	unsigned int *addr, int *port );
extern int Rva008060B0( Rva00804150ProtoMangleRef *ref,
	int status, int latency );

class BfmeE1036
{
public:
	void bfmeGo1036E();
};

struct Rva007E9B70Obj
{
	virtual void v0();
	virtual void v1();
};

class Gen_007e9b70
{
public:
	virtual void v0();
	virtual void v1();
	virtual unsigned int m();
};

extern Rva007E9B70Obj *Rva007E9B70Get();

typedef void ( __cdecl *Rva007F8840Callback )( void *context, void *data );

class Rva00803080
{
public:
	virtual void slot0( unsigned int opaque );
};

class Rva007F8840Owner : public Rva00803080
{
public:
	virtual void slot0( unsigned int opaque );
};

void Rva007F8840Owner::slot0( unsigned int )
{
	char *base = (char *)this;

	if( *(void **)( base + 4 ) == 0 )
		return;
	if( *(void **)( base + 0x24 ) == 0 )
		return;

	Rva008054A0( (Rva00804150ProtoMangleRef *)*(void **)( base + 4 ) );

	int outPort = 0;
	unsigned int outAddr = 0;
	int rc = Rva00806040(
		(Rva00804150ProtoMangleRef *)*(void **)( base + 4 ),
		&outAddr, &outPort );

	*(unsigned int *)( base + 0x14 ) = outAddr;
	*(int *)( base + 0x18 ) = outPort;

	switch( *(int *)( base + 8 ) )
	{
	case 3:
		( (BfmeE1036 *)( base - 4 ) )->bfmeGo1036E();
		*(int *)( base + 8 ) = 0;
		break;

	case 2:
		if( rc != 0 )
			*(int *)( base + 8 ) = 3;
		break;

	case 1:
		if( rc > 0 )
		{
			( *(Rva007F8840Callback *)( base + 0x24 ) )(
				base + 0xc, *(void **)( base + 0x28 ) );
			if( *(unsigned char *)( base + 0x20 ) == 0 )
			{
				*(int *)( base + 8 ) = 3;
				break;
			}
			{
				unsigned int now =
					( (Gen_007e9b70 *)Rva007E9B70Get() )->m();
				int latency = now - *(int *)( base + 0x1c );
				Rva008060B0(
					(Rva00804150ProtoMangleRef *)*(void **)( base + 4 ),
					0, latency );
			}
			*(int *)( base + 8 ) = 2;
			break;
		}
		else if( rc < 0 )
		{
			( *(Rva007F8840Callback *)( base + 0x24 ) )(
				base + 0xc, *(void **)( base + 0x28 ) );
			if( *(unsigned char *)( base + 0x20 ) == 0 )
			{
				*(int *)( base + 8 ) = 3;
				break;
			}
			{
				unsigned int now =
					( (Gen_007e9b70 *)Rva007E9B70Get() )->m();
				int latency = now - *(int *)( base + 0x1c );
				Rva008060B0(
					(Rva00804150ProtoMangleRef *)*(void **)( base + 4 ),
					1, latency );
			}
			*(int *)( base + 8 ) = 2;
		}
		break;

	default:
		break;
	}
}
