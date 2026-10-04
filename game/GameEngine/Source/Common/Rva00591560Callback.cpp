// cl: /O2 /Ob0

// The callback's scalar free is retail's global operator delete at 0x00881EB0
// (game/Libraries/Source/WWVegas/WWLib/mem_ops.cpp, ??3@YAXPAX@Z), the only
// definition of that address; call it under that name.
void __cdecl operator delete( void *block ) throw();

// Each method below is reached through a 5-byte ILT thunk whose only
// definition in the link is its gen-thunk body, so call each under its
// defined name and reach the real thiscall shape through the established
// pointer-to-member cast idiom (see Rva00219C70Remove.cpp).
extern void j_00046538();							// ?j_00046538@@YAXXZ, ILT 0x00046538
extern void j_00011900();							// ?j_00011900@@YAXXZ, ILT 0x00011900
extern void j_00006bfe();							// ?j_00006bfe@@YAXXZ, ILT 0x00006BFE
extern void j_00002e69();							// ?j_00002e69@@YAXXZ, ILT 0x00002E69

class Rva00591560Resource
{
public:
	void run();
	void destroy();
};

class Rva00591560Context
{
public:
	Rva00591560Resource *find();
	void clear( Rva00591560Resource *resource );
};

// Call views only: they carry the thiscall shapes of the four callees and add
// no code and no vtable to this object.
class Rva00591560CallView
{
public:
	Rva00591560Resource *find();
	void run();
	void destroy();
	void clear( Rva00591560Resource *resource );
};

typedef Rva00591560Resource *(Rva00591560CallView::*Rva00591560Find)();
typedef void (Rva00591560CallView::*Rva00591560Run)();
typedef void (Rva00591560CallView::*Rva00591560Clear)( Rva00591560Resource * );

union Rva00591560FindTarget
{
	void (*freeFunction)();
	Rva00591560Find memberFunction;
};

union Rva00591560RunTarget
{
	void (*freeFunction)();
	Rva00591560Run memberFunction;
};

union Rva00591560DestroyTarget
{
	void (*freeFunction)();
	Rva00591560Run memberFunction;
};

union Rva00591560ClearTarget
{
	void (*freeFunction)();
	Rva00591560Clear memberFunction;
};

int __cdecl rva00591560Callback( Rva00591560Context *context, int message )
{
	Rva00591560FindTarget findTarget = { &j_00046538 };
	Rva00591560RunTarget runTarget = { &j_00011900 };
	Rva00591560DestroyTarget destroyTarget = { &j_00006bfe };
	Rva00591560ClearTarget clearTarget = { &j_00002e69 };

	if( context )
	{
		switch( message )
		{
		case 0x4008:
		{
			Rva00591560Resource *resource = (reinterpret_cast<Rva00591560CallView *>(context)->*findTarget.memberFunction)();
			if( resource )
			{
				(reinterpret_cast<Rva00591560CallView *>(resource)->*runTarget.memberFunction)();
				return 1;
			}
			break;
		}

		case 2:
		{
			Rva00591560Resource *resource = (reinterpret_cast<Rva00591560CallView *>(context)->*findTarget.memberFunction)();
			if( resource )
			{
				(reinterpret_cast<Rva00591560CallView *>(resource)->*destroyTarget.memberFunction)();
				operator delete( (void *)resource );
			}
			(reinterpret_cast<Rva00591560CallView *>(context)->*clearTarget.memberFunction)( 0 );
			break;
		}

		default:
			break;
		}
	}

	return 1;
}
