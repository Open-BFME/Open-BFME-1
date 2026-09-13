// ?rva007F8840@Rva007F8840Owner@@QAEXXZ
// partial score=0.45 date=2026-09-13
// Open-BFME5: FESL/ProtoMangle bridge step, retail 0x007F8840. Drives
// Y2ProtoMangleHelpers.cpp's Rva008054A0/Rva00806040/Rva008060B0 through
// this object's ref (+4) and dispatch state (+8), using the matched
// BfmeE1036 tail object at this-4 (bfmeGo1036E) for state 3. The +0x24
// field is a plain callback function pointer, called with (this+0xc,
// this[0x28]) whenever a fresh lookup completes (rc!=0) in state 1.

struct Rva00804150ProtoMangleRef;

extern void Rva008054A0( Rva00804150ProtoMangleRef *ref );
extern int Rva00806040( Rva00804150ProtoMangleRef *ref, unsigned int *addr, int *port );
extern int Rva008060B0( Rva00804150ProtoMangleRef *ref, int status, int latency );

class BfmeE1036
{
public:
	void bfmeGo1036E();
};

struct Rva007E9B70Obj
{
	virtual void v0();
	virtual void v1();
	virtual int getBase();   // slot 2, +8
};
extern Rva007E9B70Obj *Rva007E9B70Get();

typedef void ( __cdecl *Rva007F8840Callback )( void *context, void *data );

class Rva007F8840Owner
{
public:
	void rva007F8840();
};

void Rva007F8840Owner::rva007F8840()
{
	char *base = (char *)this;

	if( *(void **)( base + 4 ) == 0 )
		return;
	if( *(void **)( base + 0x24 ) == 0 )
		return;

	Rva008054A0( (Rva00804150ProtoMangleRef *)*(void **)( base + 4 ) );

	unsigned int outAddr = 0;
	int outPort = 0;
	int rc = Rva00806040( (Rva00804150ProtoMangleRef *)*(void **)( base + 4 ), &outAddr, &outPort );

	*(volatile unsigned int *)( base + 0x14 ) = outAddr;
	*(volatile int *)( base + 0x18 ) = outPort;

	switch( *(int *)( base + 8 ) )
	{
	case 1:
		if( rc > 0 )
		{
			( *(Rva007F8840Callback *)( base + 0x24 ) )( base + 0xc, *(void **)( base + 0x28 ) );
			if( *(unsigned char *)( base + 0x20 ) == 0 )
			{
				*(int *)( base + 8 ) = 3;
				return;
			}
			{
				Rva007E9B70Obj *obj = Rva007E9B70Get();
				int latency = obj->getBase() - *(int *)( base + 0x1c );
				Rva008060B0( (Rva00804150ProtoMangleRef *)*(void **)( base + 4 ), 0, latency );
			}
			*(int *)( base + 8 ) = 2;
			return;
		}
		if( rc >= 0 )
			return;
		( *(Rva007F8840Callback *)( base + 0x24 ) )( base + 0xc, *(void **)( base + 0x28 ) );
		if( *(unsigned char *)( base + 0x20 ) == 0 )
		{
			*(int *)( base + 8 ) = 3;
			return;
		}
		{
			Rva007E9B70Obj *obj = Rva007E9B70Get();
			int latency = obj->getBase() - *(int *)( base + 0x1c );
			Rva008060B0( (Rva00804150ProtoMangleRef *)*(void **)( base + 4 ), 1, latency );
		}
		*(int *)( base + 8 ) = 2;
		return;

	case 2:
		if( rc != 0 )
			*(int *)( base + 8 ) = 3;
		return;

	case 3:
		( (BfmeE1036 *)( base - 4 ) )->bfmeGo1036E();
		*(int *)( base + 8 ) = 0;
		return;
	}
}
